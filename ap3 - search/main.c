#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool verifica_delimitador (char c) {
    if ((c == ' ') || (c == ',') || (c == '.') || (c == ';') || (c == ':') || (c == '/') || (c == '\n') || (c == '\0') ||
            (c == '\t') || (c == '?') || (c == '!') || (c == '[') || (c == ']') || (c == '{') || (c == '}') ||
            (c == '(') || (c == ')') || (c == '-') || (c == '_') || (c == '+') || (c == '=') || (c == '@') ||
            (c == '#') || (c == '$') || (c == '%') || (c == '&') || (c == '*') || (c == '~') || (c == '"') ||
            (c == '\'') || (c == '<') || (c == '>')) return true;
    else return false;
}

int main(int argc, char *argv[]) {
    FILE *a;
    FILE *b;
    a = fopen (argv[1], "r");
    b = fopen (argv[2], "w");
    if ((a == NULL) || (b == NULL))
        printf ("Erro!!\n");
    else {
        char linha1[10001], linha2[1001], *token, tmp[10001];
        int pag = 0;

        TreePointer ret;
        TreePointer t;
        TreeItem x;
        init_tree (&t);
        x.insert_order = 0;

        fgets (linha1, sizeof(linha1), a);
        linha1[strcspn (linha1, ">")] = '\0';
        for (int i = 0; i < strlen (linha1); i ++)
            linha1[i] = tolower (linha1[i]);
        token = strtok (linha1, ":");
        while (token != NULL) {
            token = strtok (NULL, ",");
            if (token != NULL) {
                x.insert_order ++;
                x.node_name = token;
                init_queue (&x.queue);
                insert_tree (&t, x);
            }
        }
        while (!feof (a)) {
            fgets (linha2, sizeof (linha2), a);
            for (int i = 0; i < strlen (linha2); i ++)
                linha2[i] = tolower (linha2[i]);
            if ((linha2[0] == '<') && (linha2[1] == 'p') && (linha2[2] == 'a') && (linha2[3] == 'g') && (linha2[4] == 'e')
                && (linha2[5] == ':')) {
                pag ++;
            }
            else {
                for (int i = 0; i < strlen (linha2); i ++) {
                    if (verifica_delimitador (linha2[i]) == false)
                        strncat (tmp, &linha2[i], 1);
                    else {
                        for (int j = 1; j < tree_size (&t) + 1; j ++) {
                            search_insert_order (&t, j, &ret);
                            if (strcmp (tmp, ret->x.node_name) == 0){
                                if (check_empty_queue (&ret->x.queue) == true) {
                                    ret->x.queueitem.key = pag;
                                    enqueue(ret->x.queueitem, &ret->x.queue);
                                }
                                else if (ret->x.queue.end->x.key != pag) {
                                    ret->x.queueitem.key = pag;
                                    enqueue(ret->x.queueitem, &ret->x.queue);
                                }
                            }
                        }
                        strcpy (tmp, "");
                    }
                }
            }
        }
        for (int i = 1; i < tree_size (&t) + 1; i ++) {
            search_insert_order(&t, i, &ret);
            fprintf (b ,"%s", ret->x.node_name);
            print_queue (b, &ret->x.queue);
            fprintf (b, "\n");
        }
        destroy_tree (&t);
    }
    fclose (a);
    fclose (b);
    return 0;
}