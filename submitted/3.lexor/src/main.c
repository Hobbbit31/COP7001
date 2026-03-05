#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "eval.h"
#include "symtab.h"

extern int yyparse(void);
extern FILE *yyin;
extern ASTNode *root;

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s [--no-eval|--ast-only] [file]\n", prog);
}

int main(int argc, char **argv) {
    /* Optional flags + file argument; default is stdin. */
    int do_eval = 1;
    const char *filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--no-eval") == 0 || strcmp(argv[i], "--ast-only") == 0) {
            do_eval = 0;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (!filename) {
            filename = argv[i];
        } else {
            print_usage(argv[0]);
            return 1;
        }
    }

    if (filename) {
        yyin = fopen(filename, "r");
        if (!yyin) {
            perror("fopen");
            return 1;
        }
    }

    /* Parse first, then print the AST, then optionally evaluate. */
    int rc = yyparse();
    int eval_rc = 0;
    SymTab *globals = NULL;

    if (rc == 0 && root) {
        /* Fold constant-only expressions so equivalent literals print the same. */
       
        

        if (do_eval) {
            eval_rc = eval_program(root, &globals);
            ast_fold_constants(root);
        }
        ast_pretty_print(root);
        if (do_eval) {
            if (eval_rc == 0) {
                symtab_dump(globals);
            }
        }
    }

    ast_free(root);

    if (filename && yyin) {
        fclose(yyin);
    }

    while (globals) {
        globals = symtab_pop(globals);
    }

    int success = (rc == 0 && (!do_eval || eval_rc == 0));
    if (success) {
        printf("OK\n");
    }

    return success ? 0 : 1;

}
