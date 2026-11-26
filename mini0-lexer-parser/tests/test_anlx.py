"""Tests of anLx.py: the lexer on its own, golden runs of the whole script on
valid and invalid programs, and the parser limits documented in the README
(as strict xfails, so they turn into failures the day they are fixed)."""
import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
import anLx  # noqa: E402

GOLDEN = ROOT / "tests" / "golden"


def tags(source):
    return [tag for _, tag in anLx.lex(source, anLx.token_exprs)]


def parse(source, capsys):
    anLx.syn(anLx.lex(source, anLx.token_exprs))
    return capsys.readouterr().out


def run(path):
    return subprocess.run([sys.executable, str(ROOT / "anLx.py"), str(path)],
                          capture_output=True, text=True, check=True)


# --- lexer -----------------------------------------------------------------

def test_lexes_a_declaration():
    assert anLx.lex("x : int\n", anLx.token_exprs) == [
        ("x", "IDENTIFIER"), (":", "DOSPUNTOS"), ("int", "DATATYPE"),
        ("\n", "ENDLINE"), ("", "ENDFILE")]


def test_operators_and_literals():
    assert tags("a <= 10 + 'c' >= \"hi\" != b") == [
        "IDENTIFIER", "LESS_THAN", "INT", "PLUS", "CHAR", "GREATHER_THAN",
        "STRING", "NOT_EQUAL", "IDENTIFIER", "ENDFILE"]


def test_comments_and_blank_runs_are_skipped():
    assert tags("// line comment\nx /* block\ncomment */ : int\n\n\n") == [
        "IDENTIFIER", "DOSPUNTOS", "DATATYPE", "ENDLINE", "ENDFILE"]


def test_illegal_character_is_reported_and_skipped(capsys):
    assert tags("x @ y") == ["IDENTIFIER", "IDENTIFIER", "ENDFILE"]
    assert "[ERROR] Illegal character: @" in capsys.readouterr().err


# --- parser ----------------------------------------------------------------

@pytest.mark.parametrize("source", [
    "x : int\n",
    "x : int\ny : bool\n",
    "v : [] [] char\n",
    "fun f() : int\nend\n",
    "x : int\nfun f(a : int) : bool\nr : int\nend\n",
])
def test_accepts(source, capsys):
    assert "Analisis sintactico correcto" in parse(source, capsys)


@pytest.mark.parametrize("source, bad_token", [
    ("x int\n", ("int", "DATATYPE")),
    ("x : int\nfun f() int\nend\n", ("int", "DATATYPE")),
    ("x : \nint\n", ("\n", "ENDLINE")),
])
def test_rejects_and_names_the_token(source, bad_token, capsys):
    out = parse(source, capsys)
    assert "ERROR" in out and "Analisis sintactico correcto" not in out
    assert str(bad_token) in out


# --- golden runs -------------------------------------------------------------

@pytest.mark.parametrize("program", sorted(GOLDEN.glob("*.txt")), ids=lambda p: p.stem)
def test_golden(program):
    expected = program.with_suffix(".out").read_text()
    assert run(program).stdout == expected


def test_examples_match_the_readme():
    assert "Analisis sintactico correcto" in run(ROOT / "examples" / "valid.txt").stdout
    assert "('int', 'DATATYPE')" in run(ROOT / "examples" / "error.txt").stdout.split("ERROR")[1]


# --- documented limits --------------------------------------------------------

LIMIT = pytest.mark.xfail(strict=True, reason="documented parser limit (README)")


@LIMIT
def test_limit_function_with_two_parameters(capsys):
    assert "correcto" in parse("fun f(a : int, b : int) : int\nend\n", capsys)


@LIMIT
def test_limit_function_body_with_statements(capsys):
    assert "correcto" in parse((ROOT / "examples" / "function.txt").read_text(), capsys)


@LIMIT
def test_limit_identifier_starting_with_a_keyword():
    assert tags("doble : int\n")[0] == "IDENTIFIER"


@LIMIT
def test_limit_blank_line_after_a_block_comment(capsys):
    assert "correcto" in parse("x : int\n/* c */\ny : int\n", capsys)


@LIMIT
def test_limit_inequality_operator():
    # '<' is tried before '<>', so the INEQUAL token is never produced
    assert tags("a <> b")[1] == "INEQUAL"
