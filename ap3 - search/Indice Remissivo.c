#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  int chave;
} FilaItens;

typedef struct NodeFila *PonteiroFila;

typedef struct NodeFila{
  FilaItens item;
  PonteiroFila proximo;
} NodeFila;

typedef struct {
  PonteiroFila inicio;
  PonteiroFila fim;
  int tamanho;
} Fila;

void IniciaFila (Fila *fila) {
  fila->inicio = fila->fim = NULL;
  fila->tamanho = 0;
}//função IniciaFila

int TamanhoFila (Fila *fila) {
  return fila->tamanho;
}//função TamanhoFila

bool VerificaFilaVazia (Fila *fila) {
  return TamanhoFila (fila) == 0;
}//função VerificaFilaVazia

void Enfileira (FilaItens item, Fila *fila) {
  PonteiroFila aux;
  aux = (PonteiroFila) malloc (sizeof (PonteiroFila));
  aux->item = item;
  aux->proximo = NULL;
  if (VerificaFilaVazia (fila) == true) {
    fila->inicio = fila->fim = aux;
    fila->tamanho ++;
  }else {
    fila->fim->proximo = aux;
    fila->fim = aux;
    fila->tamanho ++;
  }//else
}//função Enfileira

void Desenfileira (Fila *fila) {
  PonteiroFila aux;
  aux = fila->inicio;
  if (TamanhoFila (fila) == 1) {
    fila->inicio = fila->fim = NULL;
    fila->tamanho--;
  }else {
    fila->inicio = fila->inicio->proximo;
    fila->tamanho--;
  }//else
  free (aux);
}//função Desenfileira

void ImprimirFila (FILE *arq, Fila *fila) {
  PonteiroFila aux;
  if (VerificaFilaVazia (fila) == true){
    printf ("A fila não contem itens");
  }else {
    for (aux = fila->inicio; aux != NULL; aux = aux->proximo) {
      fprintf(arq, ",%i", aux->item.chave);
    }//for
  }//else
}//função ImprimirFila

FilaItens TopoFila (Fila *fila) {
  FilaItens item;
  item = fila->inicio->item;
  return item;
}//função TopoFila

FilaItens FimFila (Fila *fila) {
  FilaItens item;
  item = fila->fim->item;
  return item;
}//função FimFila


typedef struct {
  Fila fila;
  FilaItens filaitens;
  int ordem_inserida;
  char *nome_do_no;
} ItemArvore;

typedef struct NoArvore *PonteiroArvore;

typedef struct NoArvore {
  ItemArvore item;
  PonteiroArvore direito;
  PonteiroArvore esquerdo;
} Arvore;

void IniciaArvore (PonteiroArvore *arvore) {
  (*arvore) = NULL;
}//função IniciaArvore

bool VerificaArvoreVazia (PonteiroArvore *arvore) {
  return ((*arvore) == NULL);
}//função VerificaArvoreVazia

int ProfundidadeArvore (PonteiroArvore *arvore) {
  if ((*arvore) == NULL)
    return 0;
  else {
    int ProfundidadeEsquerdo = ProfundidadeArvore (&(*arvore)->esquerdo);
    int ProfundidadeDireito = ProfundidadeArvore (&(*arvore)->direito);
    if (ProfundidadeEsquerdo > ProfundidadeDireito){
      return ProfundidadeEsquerdo + 1;
    }else{
      return ProfundidadeDireito + 1;
    }//else
  }//else
}//função ProfundidadeArvore

int TamanhoArvore (PonteiroArvore *arvore) {
  if ((*arvore) == NULL){
    return 0;
  }else{
    return (TamanhoArvore (&(*arvore)->esquerdo) + 1 + TamanhoArvore (&(*arvore)->direito));
  }//else
}//função TamanhoArvore

bool InsereArvore (PonteiroArvore *arvore, ItemArvore item) {
  if (VerificaArvoreVazia (&(*arvore)) == true) {
    (*arvore) = (Arvore*) malloc (sizeof (Arvore));
    (*arvore)->direito = (*arvore)->esquerdo = NULL;
    (*arvore)->item = item;
    return true;
  }else if (strcmp ((*arvore)->item.nome_do_no, item.nome_do_no) == 0){
    return false;
  }else if (strcmp ((*arvore)->item.nome_do_no, item.nome_do_no) > 0){
    return (InsereArvore (&(*arvore)->esquerdo, item));
  }else if (strcmp ((*arvore)->item.nome_do_no, item.nome_do_no) < 0){
    return (InsereArvore (&(*arvore)->direito, item));
  }else{
    return false;
  }//else
}//função InsereArvore

void ProcuraOrdemInserida (PonteiroArvore *arvore, int chave, PonteiroArvore *ret) {
  if ((*arvore) == NULL) {
    return;
  }//if
  if ((*arvore)->item.ordem_inserida == chave){
    (*ret) = (*arvore);
  }//if
  ProcuraOrdemInserida (&(*arvore)->esquerdo, chave, &(*ret));
  ProcuraOrdemInserida (&(*arvore)->direito, chave, &(*ret));
}//função ProcuraOrdemInserida

void EmOrdem (PonteiroArvore *arvore) {
  if ((*arvore) == NULL) {
    return;
  }//if
  EmOrdem (&(*arvore)->esquerdo);
  printf ("%s: %i ", (*arvore)->item.nome_do_no, (*arvore)->item.ordem_inserida);
  EmOrdem (&(*arvore)->direito);
}//função EmOrdem

bool ProcuraArvore (PonteiroArvore *arvore, char *chave, ItemArvore *ret) {
  if ((*arvore) == NULL){
    return false;
  }//if
  if (strcmp ((*arvore)->item.nome_do_no, chave) == 0) {
    *ret = (*arvore)->item;
    return true;
  }//if
  if (strcmp ((*arvore)->item.nome_do_no, chave) < 0){
    return ProcuraArvore (&(*arvore)->esquerdo, chave, ret);
  }else{
    return ProcuraArvore (&(*arvore)->direito, chave, ret);
  }//else
}//função ProcuraArvore

PonteiroArvore PegaItemMinimo (PonteiroArvore *arvore) {
  PonteiroArvore aux;
  if ((*arvore)->esquerdo == NULL) {
    aux = (*arvore);
    (*arvore) = (*arvore)->direito;
    return aux;
  }else{
    return PegaItemMinimo (&(*arvore)->esquerdo);
  }//else
}//função PegaItemMinimo

PonteiroArvore PegaItemMaximo (PonteiroArvore *arvore) {
  PonteiroArvore aux;
  if ((*arvore)->direito == NULL) {
      aux = (*arvore);
      (*arvore) = (*arvore)->esquerdo;
      return aux;
  }else{
    return PegaItemMaximo (&(*arvore)->direito);
  }//else
}//função PegaItemMaximo

bool RemoveArvore (PonteiroArvore *arvore, char *chave) {
  if ((*arvore) == NULL){
    return false;
  }else if (strcmp ((*arvore)->item.nome_do_no, chave) == 0) {
    PonteiroArvore aux;
    aux = (*arvore);
    if (((*arvore)->esquerdo == NULL) && ((*arvore)->direito == NULL)){
      (*arvore) = NULL;
    }else if ((*arvore)->esquerdo == NULL){
      (*arvore) = (*arvore)->direito;
    }else if ((*arvore)->direito == NULL){
      (*arvore) = (*arvore)->esquerdo;
    }else{
      aux = PegaItemMinimo(&(*arvore)->direito);
      (*arvore)->item = aux->item;
    }//else
    free (aux);
    return true;
  }else if (strcmp ((*arvore)->item.nome_do_no, chave) < 0){
    return RemoveArvore(&(*arvore)->esquerdo, chave);
  }else{
    return RemoveArvore(&(*arvore)->direito, chave);
  }//else
}//função RemoveArvore

char *ArvoreMaximo (PonteiroArvore *arvore) {
  if ((*arvore)->direito == NULL){
    return (*arvore)->item.nome_do_no;
  }else{
    return ArvoreMaximo (&(*arvore)->direito);
  }//else
}//função ArvoreMaximo

char *ArvoreMinimo (PonteiroArvore *arvore) {
  if ((*arvore)->esquerdo == NULL){
    return (*arvore)->item.nome_do_no;
  }else{
    return ArvoreMinimo (&(*arvore)->esquerdo);
  }//else
}//função ArvoreMinimo

void DestroiArvore (PonteiroArvore *arvore) {
  if ((*arvore) == NULL) {
    return;
  }//if
  DestroiArvore (&(*arvore)->esquerdo);
  DestroiArvore (&(*arvore)->direito);
  RemoveArvore(&(*arvore), (*arvore)->item.nome_do_no);
}//função DestroiArvore

bool verifica_delimitador (char c) {
  if ((c == ' ') || (c == ',') || (c == '.') || (c == ';') || (c == ':') || (c == '/') || (c == '\n') || (c == '\0') ||
      (c == '\t') || (c == '?') || (c == '!') || (c == '[') || (c == ']') || (c == '{') || (c == '}') ||
      (c == '(') || (c == ')') || (c == '-') || (c == '_') || (c == '+') || (c == '=') || (c == '@') ||
      (c == '#') || (c == '$') || (c == '%') || (c == '&') || (c == '*') || (c == '~') || (c == '"') ||
      (c == '\'') || (c == '<') || (c == '>')){
    return true;
  }else{
    return false;
  }//else
}//função verifica_delimitador

int main(int argc, char *argv[]) {
  FILE *entrada;
  FILE *saida;
  entrada = fopen (argv[1], "r");
  saida = fopen (argv[2], "w");
  if (entrada == NULL){
    perror ("Erro ao abrir arquivo de entrada !!\n");
  }else if(saida == NULL){
    perror ("Erro ao abrir arquivo de saida !!\n");
  }else {
    char linha1[10001], linha2[1001], *token, temporario[10001];
    int pagina = 0;

    PonteiroArvore ret;
    PonteiroArvore arvore;
    ItemArvore item;
    IniciaArvore (&arvore);
    item.ordem_inserida = 0;

    fgets (linha1, sizeof(linha1), entrada);
    linha1[strcspn (linha1, ">")] = '\0';

    for (int i = 0; i < strlen(linha1); i ++){
      linha1[i] = tolower (linha1[i]);
    }//for
    token = strtok (linha1, ":");

    while (token != NULL) {
      token = strtok (NULL, ",");
      if (token != NULL) {
        item.ordem_inserida ++;
        item.nome_do_no = token;
        IniciaFila (&item.fila);
        InsereArvore (&arvore, item);
      }//if
    }//while

    while (!feof (entrada)) {
      fgets (linha2, sizeof (linha2), entrada);
      for (int i = 0; i < strlen (linha2); i++){
        linha2[i] = tolower (linha2[i]);
      }//for
      if ((linha2[0] == '<') && (linha2[1] == 'p') && (linha2[2] == 'a') && (linha2[3] == 'g') && (linha2[4] == 'e')
          && (linha2[5] == ':')) {
        pagina ++;
      }else {
        for (int i = 0; i < strlen (linha2); i++) {
          if (verifica_delimitador (linha2[i]) == false){
            strncat (temporario, &linha2[i], 1);
          }else{
            for (int j = 1; j < TamanhoArvore (&arvore) + 1; j++) {
              ProcuraOrdemInserida (&arvore, j, &ret);
              if (strcmp (temporario, ret->item.nome_do_no) == 0){
                if (VerificaFilaVazia (&ret->item.fila) == true) {
                  ret->item.filaitens.chave = pagina;
                  Enfileira(ret->item.filaitens, &ret->item.fila);
                }else if (ret->item.fila.fim->item.chave != pagina) {
                  ret->item.filaitens.chave = pagina;
                  Enfileira(ret->item.filaitens, &ret->item.fila);
                }//else if
              }//if
            }//for
          strcpy (temporario, "");
          }//else
        }//for
      }//else
    }//while

    for (int i = 0; i < TamanhoArvore(&arvore) ; i++) {
      ProcuraOrdemInserida(&arvore, i, &ret);
      fprintf (saida ,"%s", ret->item.nome_do_no);
      ImprimirFila(saida, &ret->item.fila);
      fprintf (saida, "\n");
    }//for
    DestroiArvore (&arvore);
  }//else

  fclose (entrada);
  fclose (saida);
  return 0;
}//função main
