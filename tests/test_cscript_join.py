import importlib.util
import sys
import types
from pathlib import Path

# Load the script module as part of a pseudo package so relative imports work
SCRIPT_PATH = (
    Path(__file__).resolve().parents[1]
    / "qa"
    / "rpc-tests"
    / "test_framework"
    / "script.py"
)

# Expose a minimal "test_framework" package so relative imports succeed
pkg = types.ModuleType("test_framework")
pkg.__path__ = [str(SCRIPT_PATH.parent)]
sys.modules["test_framework"] = pkg
spec = importlib.util.spec_from_file_location("test_framework.script", SCRIPT_PATH)
script = importlib.util.module_from_spec(spec)
spec.loader.exec_module(script)
CScript = script.CScript


def test_cscript_join_returns_cscript():
    delim = CScript([b" "])
    parts = [CScript([b"a"]), CScript([b"b"]), CScript([b"c"])]
    result = delim.join(parts)
    assert isinstance(result, CScript)

    coerced = [CScript._CScript__coerce_instance(p) for p in parts]
    expected_bytes = bytes(delim).join(coerced)
    assert result == CScript(expected_bytes)


