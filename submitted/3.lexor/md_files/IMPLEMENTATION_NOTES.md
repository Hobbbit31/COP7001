# Implementation Notes (Person B)

This project keeps parsing and evaluation separate. The parser builds a clean AST, and a
second pass walks the AST to perform semantic checks and constant-only evaluation. This
keeps Bison actions simple and makes it easy to extend later.

## What we changed
- Added an evaluation pass (`src/eval.c`, `src/eval.h`) that interprets the AST.
- Connected evaluation to the driver in `src/main.c`.
- Implemented a small symbol table with scope chaining (`src/symtab.c`, `src/symtab.h`).
- Kept AST creation and freeing in `src/ast.c` and `src/ast.h`.

## AST design
- Each AST node includes a `line` number for error reporting.
- Statement lists are stored as a simple linked list (`ASTNodeList`).
- Expressions are modeled as unary and binary operator nodes, plus literals and identifiers.
- A constant-folding pass simplifies literal-only expressions for cleaner output.

## Symbol table + scope rules
- Each block (`{ ... }`) creates a new scope.
- Variables are stored in the nearest scope and can shadow outer scopes.
- Redeclaration in the same scope is rejected.

## Semantic checks
- Use-before-declaration is reported with line numbers.
- Assignment to undeclared variables is rejected.
- Division by zero is detected.

## Evaluation rules
- Integers only; comparisons return 0/1.
- Only fully constant expressions are evaluated and assigned.
- If a condition is not constant, the branch/loop body is skipped.
- The evaluator still checks identifiers for declaration errors.
- A variable summary is printed after evaluation.
- The evaluator keeps running to report multiple errors in a single pass.

## How to run
- Build: `make`
- Run: `./parser path/to/file`
- Exit status: 0 on success, 1 on parse or semantic error.
- AST-only mode: `./parser --no-eval path/to/file`

## Short summary for TA
The parser builds an AST from the input program. A second pass walks the AST to perform
semantic checks and constant-only evaluation (scope handling, use-before-declare,
invalid assignments, and division by zero). Each block introduces a new scope, and
errors are reported with line numbers for clarity.
