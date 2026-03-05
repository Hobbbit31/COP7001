# A/B Contract

This file defines the frozen interface between the lexer (Person A) and parser/AST (Person B).

## Tokens (from src/parser.y)

Keywords:
- VAR
- IF
- ELSE
- WHILE

Literals:
- INTEGER (carries int value in yylval.ival)
- IDENTIFIER (carries char* in yylval.sval; must be strdup'd)

Operators (multi-char tokens):
- EQ for "=="
- NEQ for "!="
- LE for "<="
- GE for ">="

Single-character tokens are returned as their literal char:
- '=' '+' '-' '*' '/' '<' '>' '(' ')' '{' '}' ';'

## YYSTYPE

Bison union (from src/parser.y):
- int ival
- char *sval
- ASTNode *node
- ASTNodeList *list

Lexer only uses:
- yylval.ival for INTEGER
- yylval.sval for IDENTIFIER

## Line Numbers

Lexer must maintain yylineno (use `%option yylineno`).
Parser uses yylineno in yyerror and for AST node line fields.

## Stability

If any token name or YYSTYPE changes, Person A must update lexer accordingly.
