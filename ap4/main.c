#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "avl.h"

int main (int argc, char *argv[]) {
    avl_ptr t;
    avl_Item x;
    init_avl (&t);
    FILE *entrada = fopen (argv[1], "r");
    FILE *saida = fopen (argv[2], "w");
    if (entrada == NULL || saida == NULL)
        printf ("\nErro ao abrir um dos arquivos!!\n");
    else {
        char linha[101], *token, *tmp = NULL;
        fgets(linha, sizeof(linha), entrada);
        linha[strcspn (linha, "\n")] = '\0';
        token = strtok (linha, ",");
        x.key = strtol (token, &tmp, 10);
        avl_insert (&t, x);

        while (token != NULL) {
            token = strtok (NULL, ",");
            if (token != NULL) {
                x.key = strtol (token, &tmp, 10);
                avl_insert (&t, x);
            }
        }
        fprintf (saida, "[*]antes\n");
        level_print (&t, saida);

        fgets(linha, sizeof(linha), entrada);
        linha[strcspn (linha, "\n")] = '\0';
        token = strtok (linha, ",");
        x.key = strtol (token, &tmp, 10);
        avl_remove (&t, x.key);

        while (token != NULL) {
            token = strtok (NULL, ",");
            if (token != NULL) {
                x.key = strtol (token, &tmp, 10);
                avl_remove (&t, x.key);
            }
        }
        fprintf (saida, "\n[*]depois\n");
        level_print (&t, saida);

        avl_destroy (&t);
    }
    fclose (entrada);
    fclose (saida);
    return 0;
}