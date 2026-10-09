"""Compare same-stage reference and recomp frames without hiding differences.

Exact mode is the parity gate.  Optional integer alignment is diagnostic only
and is deliberately reported separately; it can never make exactPixels true.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import math
from pathlib import Path

from PIL import Image, ImageChops, ImageStat


def load(path: Path) -> Image.Image:
    with Image.open(path) as image:
        return image.convert("RGB")


def overlap(left: Image.Image, right: Image.Image, dx: int, dy: int):
    width, height = left.size
    lx0, lx1 = max(0, dx), min(width, width + dx)
    ly0, ly1 = max(0, dy), min(height, height + dy)
    rx0, rx1 = max(0, -dx), min(width, width - dx)
    ry0, ry1 = max(0, -dy), min(height, height - dy)
    return left.crop((lx0, ly0, lx1, ly1)), right.crop((rx0, ry0, rx1, ry1))


def metrics(reference: Image.Image, candidate: Image.Image) -> tuple[dict, Image.Image]:
    difference = ImageChops.difference(reference, candidate)
    histogram = difference.histogram()
    channel_pixels = reference.width * reference.height * 3
    absolute_sum = sum((index % 256) * count for index, count in enumerate(histogram))
    square_sum = sum((index % 256) ** 2 * count for index, count in enumerate(histogram))
    mse = square_sum / channel_pixels
    pixels = difference.get_flattened_data() if hasattr(difference, "get_flattened_data") else difference.getdata()
    changed = sum(1 for pixel in pixels if pixel != (0, 0, 0))
    extrema = difference.getextrema()
    return {
        "differentPixels": changed,
        "totalPixels": reference.width * reference.height,
        "differentPercent": changed * 100.0 / (reference.width * reference.height),
        "meanAbsoluteChannelError": absolute_sum / channel_pixels,
        "rootMeanSquareChannelError": math.sqrt(mse),
        "peakSignalToNoiseDb": None if mse == 0.0 else float(20.0 * math.log10(255.0 / math.sqrt(mse))),
        "maxChannelError": max(high for _low, high in extrema),
    }, difference


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("reference", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--diff", type=Path)
    parser.add_argument("--overlay", type=Path)
    parser.add_argument("--alignment-radius", type=int, default=0)
    args = parser.parse_args()
    for output in (args.out, args.diff, args.overlay):
        if output and output.exists():
            raise FileExistsError(f"refusing to overwrite {output}")

    reference, candidate = load(args.reference), load(args.candidate)
    result = {
        "schema": 1,
        "reference": str(args.reference.resolve()),
        "candidate": str(args.candidate.resolve()),
        "referenceSize": list(reference.size),
        "candidateSize": list(candidate.size),
        "sameDimensions": reference.size == candidate.size,
        "referenceRgbSha256": hashlib.sha256(reference.tobytes()).hexdigest(),
        "candidateRgbSha256": hashlib.sha256(candidate.tobytes()).hexdigest(),
        "exactPixels": False,
        "timingVerified": False,
        "captureStageVerified": False,
        "note": "Exact pixels require synchronized game state, frame identity, and equivalent capture stages; this file alone proves none of those.",
    }
    difference = overlay = None
    if reference.size == candidate.size:
        exact_metrics, difference = metrics(reference, candidate)
        result.update(exact_metrics)
        result["exactPixels"] = result["differentPixels"] == 0
        overlay = Image.blend(reference, candidate, 0.5)
        if args.alignment_radius:
            best = None
            for dy in range(-args.alignment_radius, args.alignment_radius + 1):
                for dx in range(-args.alignment_radius, args.alignment_radius + 1):
                    left, right = overlap(reference, candidate, dx, dy)
                    score = sum(ImageStat.Stat(ImageChops.difference(left, right)).mean) / 3.0
                    candidate_key = (score, -(left.width * left.height), abs(dx) + abs(dy), abs(dy), abs(dx))
                    if best is None or candidate_key < best[0]:
                        best = (candidate_key, score, dx, dy, left.width, left.height)
            result["diagnosticIntegerAlignment"] = {
                "meanAbsoluteChannelError": best[1], "dx": best[2], "dy": best[3],
                "overlapWidth": best[4], "overlapHeight": best[5],
                "parityGate": False,
            }

    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    if args.diff and difference is not None:
        difference.save(args.diff)
    if args.overlay and overlay is not None:
        overlay.save(args.overlay)
    print(json.dumps(result))
    return 0 if result["exactPixels"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
