#include <stdio.h>
#include "sStack.h"
#include "dStack.h"

int main (int argc, char *argv[]) {
    FILE *a;
    FILE *b;
    char m;                                             // variável para verificar o primeiro caractere;
    int n;                                              // variável para verificar os demais caracteres;
    a = fopen (argv[1], "r");
    b = fopen (argv[2], "w");                           // abre os arquivos
    if (a == NULL) {
        printf ("Erro!!\n");
    } else if (b == NULL) {
        printf ("Erro!!\n");
    } else {
        fscanf(a, "%c", &m);                            //verifica o primeiro caractere
        if (m == 'd') {
            printf("Pilha Dinâmica\n");
            dStack d;
            dItem x;
            dInit(&d);
            for (int i = 0; !feof (a); i++) {
                fscanf(a, "%i", &n);                    //verifica os demais caracteres
                x.key = n;
                dPush(x, &d);                           //insere os elementos na pilha
            }
            dPrint (&d);                                // apenas para verificar se todos os valores estão inseridos como deveriam
            for (int i = dSize (&d); i > 0; i--) {      // verifica e atualiza o valor do topo da pilha
                int k = 0;                              // variável que indicará o tamanho do array, reseta para 0 toda vez que percorrer o "for"
                int bin[k];                             // array para armazenar os números binários
                n = d.topo->item.key;                   // variável a ser convertida para binário
                while (n >= 0) {                        // código da conversão
                    if (n < 2) {
                        k++;                            // valor de k é incrementado em cada loop para que não tenha um array maior que o necessário
                        bin[k - 1] = n % 2;
                        n = 0;
                        n--;
                    } else if (n % 2 == 0) {
                        k++;
                        bin[k - 1] = n % 2;
                        n = n / 2;
                    } else {
                        k++;
                        bin[k - 1] = n % 2;
                        n = (n - 1) / 2;
                    }
                }
                for (int j = (k - 1); j >= 0; j--) {    // imprime a conversão no arquivo
                    fprintf (b, "%i", bin[j]);
                }
                fputs ("\n", b);                        // quebra de linha
                dPop (&d, &x);                          // desempilha o elemento convertido
            }
            dPrint (&d);                                // apenas para verificar se todos os valores foram removidos como deveriam
        }
        if (m == 'e') {
            printf("Pilha Estática\n");
            sStack s;
            sItem y;
            sInit(&s);
            for (int i = 0; !feof (a); ++i) {
                fscanf(a, "%i", &n);                    // verifica os demais caracteres
                y.key = n;
                sPush(y, &s);                           // insere os elementos na pilha
            }
            sPrint (&s);                                // apenas para verificar se todos os valores estão inseridos como deveriam
            for (int i = s.top; i > 0; i--) {           // verifica e atualiza o valor do topo da pilha
                int k = 0;                              // variável que indicará o tamanho do array, reseta para 0 toda vez que percorrer o "for"
                int bin[k];                             // array para armazenar os números binários
                n = s.array[i - 1].key;                 // variável a ser convertida para binário
                while (n >= 0) {                        // código da conversão
                    if (n < 2) {
                        k++;                            // valor de k é incrementado em cada loop para que não tenha um array maior que o necessário
                        bin[k - 1] = n % 2;
                        n = 0;
                        n--;
                    } else if (n % 2 == 0) {
                        k++;
                        bin[k - 1] = n % 2;
                        n = n / 2;
                    } else {
                        k++;
                        bin[k - 1] = n % 2;
                        n = (n - 1) / 2;
                    }
                }
                for (int j = (k - 1); j >= 0; j--) {    // imprime a conversão no arquivo
                    fprintf (b, "%i", bin[j]);
                }
                fputs ("\n", b);                        // quebra de linha
                sPop (&s, &y);                          // desempilha o elemento convertido
            }
            sPrint (&s);                                // apenas para verificar se todos os valores foram removidos como deveriam
        }
    }
    fclose (a);
    fclose (b);                                         // fecha os arquivos
    return 0;
}