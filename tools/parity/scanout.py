"""Decode a caller-verified linear 640x480 X8R8G8B8 Xemu RAM scanout."""
import argparse
import json
from pathlib import Path

from PIL import Image


parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("stem", type=Path)
parser.add_argument("--pitch", type=int, default=2560)
parser.add_argument("--ram-guest-base", type=lambda value: int(value, 0), default=0,
                    help="guest physical address represented by byte zero of the RAM capture")
args = parser.parse_args()
metadata = json.loads(Path(str(args.stem) + ".checkpoint.json").read_text(encoding="utf-8-sig"))
ram = Path(str(args.stem) + ".ram.bin").read_bytes()
start = (metadata["pcrtcStart"] & 0x03FFFFFF) - args.ram_guest_base
if args.pitch < 640 * 4 or start + args.pitch * 480 > len(ram):
    raise ValueError("requested scanout exceeds RAM or has an invalid pitch")
rows = [ram[start + y * args.pitch:start + y * args.pitch + 640 * 4] for y in range(480)]
image = Image.frombytes("RGBX", (640, 480), b"".join(rows), "raw", "BGRX").convert("RGB")
output = Path(str(args.stem) + ".png")
if output.exists():
    raise FileExistsError(output)
image.save(output)
print(json.dumps({"output": str(output), "pcrtcStart": start, "pitch": args.pitch,
                  "imageStage": metadata["imageStage"], "layoutAssumed": "linear-X8R8G8B8"}))
