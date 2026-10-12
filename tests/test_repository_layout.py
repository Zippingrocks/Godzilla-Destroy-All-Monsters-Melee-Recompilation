import hashlib
import json
import re
import subprocess
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class RepositoryLayoutTests(unittest.TestCase):
    def test_required_project_documents_exist(self):
        required = [
            ".github/ISSUE_TEMPLATE/accessibility_report.yml",
            ".github/ISSUE_TEMPLATE/bug_report.yml",
            ".github/ISSUE_TEMPLATE/config.yml",
            ".github/ISSUE_TEMPLATE/feature_request.yml",
            ".github/pull_request_template.md",
            "ACCESSIBILITY.md",
            "AGENTS.md",
            "CODE_OF_CONDUCT.md",
            "CONTRIBUTING.md",
            "README.md",
            "SECURITY.md",
            "docs/architecture.md",
            "docs/build-and-run.md",
            "docs/images/godzilla-damm-xbox-cover.png",
            "docs/parity-workflow.md",
            "docs/repository-layout.md",
            "docs/roadmap.md",
            "docs/runtime-assets.md",
            "docs/status.md",
            "fixtures/retail-xbox-us.json",
        ]
        for relative in required:
            self.assertTrue((ROOT / relative).is_file(), relative)

    def test_fixture_pins_supported_executable(self):
        fixture = json.loads(
            (ROOT / "fixtures/retail-xbox-us.json").read_text(encoding="utf-8")
        )
        digest = fixture["source_files"]["default.xbe"]["sha256"]
        self.assertEqual(fixture["title_id"], "0x49470039")
        self.assertEqual(len(digest), hashlib.sha256().digest_size * 2)
        self.assertRegex(digest, r"^[0-9a-f]{64}$")

    def test_no_retail_or_runtime_artifacts_are_tracked(self):
        tracked = subprocess.run(
            ["git", "-c", f"safe.directory={ROOT.as_posix()}", "ls-files", "-z"],
            cwd=ROOT,
            check=True,
            capture_output=True,
        ).stdout.decode("utf-8").split("\0")
        forbidden_suffixes = {
            ".bmp", ".dmp", ".exe", ".iso", ".log", ".png", ".sav",
            ".xbe", ".xiso", ".xmv",
        }
        allowed_artwork = {"docs/images/godzilla-damm-xbox-cover.png"}
        for relative in filter(None, tracked):
            if relative.replace("\\", "/") in allowed_artwork:
                continue
            self.assertNotIn(Path(relative).suffix.lower(), forbidden_suffixes, relative)

    def test_local_markdown_links_resolve(self):
        link_pattern = re.compile(r"\[[^]]+\]\((?!https?://|#)([^)#]+)(?:#[^)]+)?\)")
        documents = [
            ROOT / "README.md",
            ROOT / "ACCESSIBILITY.md",
            ROOT / "CODE_OF_CONDUCT.md",
            ROOT / "CONTRIBUTING.md",
            ROOT / "SECURITY.md",
            *sorted((ROOT / "docs").glob("*.md")),
        ]
        for document in documents:
            text = document.read_text(encoding="utf-8")
            for target in link_pattern.findall(text):
                resolved = (document.parent / target).resolve()
                self.assertTrue(resolved.exists(), f"{document}: {target}")


if __name__ == "__main__":
    unittest.main()
