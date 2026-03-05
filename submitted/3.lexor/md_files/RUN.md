# How to Run

This project builds a `parser` binary that reads from a file or stdin.

## Prerequisites
- `flex`
- `bison`
- `make`
- A C compiler (`cc`, `gcc`, or `clang`)

## Build
```bash
make
```

## Run with a file
```bash
./parser tests/valid/01_var_decl.txt
```

## Run without evaluation (AST only)
```bash
./parser --no-eval tests/valid/01_var_decl.txt
```

## Run with stdin
```bash
./parser
# then type your program and press Ctrl+D (Linux/macOS) or Ctrl+Z+Enter (Windows)
```

## Clean build artifacts
```bash
make clean
```

## Quick test sweep
```bash
# valid programs should exit with code 0
for f in tests/valid/*.txt; do
  ./parser "$f" || echo "FAILED: $f"
done

# invalid programs should exit with non-zero
for f in tests/invalid/*.txt; do
  ./parser "$f" && echo "UNEXPECTED PASS: $f"
done
```

## Notes
- Syntax errors and semantic errors print line numbers.
- If you see lexer errors on Windows files, make sure they use Unix line endings or that `\r` is treated as whitespace in the lexer.
