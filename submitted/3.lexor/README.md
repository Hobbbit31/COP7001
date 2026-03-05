# parser_with_flex_and_bison

Small scripting language implemented with Flex and Bison, backed by an AST and a
simple evaluator with semantic checks.

## Language Summary
- Statements: `var` declarations, assignments, `if/else`, `while`, and blocks.
- Expressions: integer literals, identifiers, unary `+/-`, binary `+ - * /`,
  comparisons `< > <= >= == !=`.
- Variables must be declared with `var` before use.

Example program:
```text
var x = 3;
var y = 10;
while (x < y) {
    if (x == 5)
        y = y - 1;
    else
        x = x + 1;
}
```

## Grammar Notes
- Precedence: unary > `* /` > `+ -` > comparisons > equality.
- `if/else` binds `else` to the nearest unmatched `if`.
- AST output performs constant folding on pure literal expressions.

## Semantics and Scope
- Each block (`{ ... }`) creates a new scope.
- Redeclaration in the same scope is rejected.
- Inner scopes may shadow outer variables.
- Comparisons evaluate to `0` (false) or `1` (true).
- Division by zero is reported as a semantic error.
- Only fully constant expressions are evaluated; expressions that depend on identifiers
  are checked for declaration but not computed.

## Error Handling
- Lexer reports unexpected characters with line numbers.
- Parser reports syntax errors with line numbers.
- Evaluator reports semantic errors (e.g., use-before-declare) with line numbers.
- Program exits non-zero on parse or semantic errors.
- On success, the evaluator prints a variable summary after the AST.

## Directory Structure
- `src/lexer.l` (Flex rules)
- `src/parser.y` (Bison grammar + AST construction)
- `src/ast.c` / `src/ast.h` (AST nodes and helpers)
- `src/symtab.c` / `src/symtab.h` (scoped symbol table)
- `src/eval.c` / `src/eval.h` (AST evaluation + semantic checks)
- `src/main.c` (driver)
- `tests/valid`, `tests/invalid` (sample tests)
- `md_files/CONTRACT.md` (lexer/parser token contract)
- `md_files/IMPLEMENTATION_NOTES.md` (TA-ready summary)
- `md_files/RUN.md` (quick run guide)

## Build
Requirements: `flex`, `bison`, `make`, and a C compiler.

```bash
make
```

```bash
make clean
```

## Run
```bash
./parser path/to/file
```

```bash
./parser
# then type your program and press Ctrl+D (Linux/macOS) or Ctrl+Z+Enter (Windows)
```

Skip evaluation (AST only):
```bash
./parser --no-eval path/to/file
```

Output on success:
- AST pretty-print (always)
- Variable summary (constants only; unknowns are marked) when evaluation is enabled
- `OK`

## Run Tests
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

## Assumptions and Deviations
- Grammar follows the sample handout structure with standard operator precedence.
- Block scoping is used (not global-only).
- Only integer type is supported.

## Optional Extensions
- Script file input is supported via `./parser file`.
- Parser error recovery and functions are not implemented.
- AST pretty-printing is not implemented.

## Submission Notes
- Do not include generated artifacts (`build/`, `parser`, `lex.yy.c`, `parser.tab.c`, `.o`).
- Archive should follow the lab naming convention.

## Notes
- Token contract between lexer and parser is summarized in `CONTRACT.md`.
- Implementation details and a TA-ready summary are in `IMPLEMENTATION_NOTES.md`.
