#ifndef ARVORE_C
#define ARVORE_C

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int totalRotacoes = 0;

typedef struct Timestamp
{
  char date[11]; /// dd/mm/yyyy
  char time[9];  /// hh:mm:ss
} Timestamp;

typedef struct Event
{
  int id, sev_nivel;
  tEvento tipo;
  Regiao reg;
  Status status;
  Timestamp timestamp;
} Event;

typedef struct Node
{
  Event *evento;
  int altura;
  struct Node *esq, *dir;
} Node;

// calcula altura do no
int alturaNo(Node *no)
{
  if (no == NULL)
    return -1;
  return no->altura;
}

// cria um novo no
Node *criaNo(Event *valor)
{
  Node *novo = (Node *)malloc(sizeof(Node));
  novo->altura = 0;
  novo->dir = NULL;
  novo->esq = NULL;
  novo->evento = valor;

  return novo;
}

// calcula fator de balanceamento
int fatorBalanceamento(Node *no)
{
  if (no == NULL)
    return 0;
  return alturaNo(no->esq) - alturaNo(no->dir);
}

// faz a soma do fator de balanceamento para o calculo da media
double somarFatoresBalanceamento(Node *raiz, int *count)
{
  if (raiz == NULL)
    return 0.0;

  double soma = fatorBalanceamento(raiz);
  *count += 1;

  soma += somarFatoresBalanceamento(raiz->esq, count);
  soma += somarFatoresBalanceamento(raiz->dir, count);

  return soma;
}

// calcula a media do fator de balanceamento
double fatorBalanceamentoMedio(Node *raiz)
{
  if (raiz == NULL)
    return 0.0;

  int count = 0;
  double soma = somarFatoresBalanceamento(raiz, &count);

  if (count == 0)
    return 0.0;

  return soma / count;
}

// conta a quantidade de nos da arvore
int contarNos(Node *raiz)
{
  if (raiz == NULL)
    return 0;
  return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

// conta a quantidade de eventos com o status ATIVO
int contarEventosAtivos(Node *raiz)
{
  if (raiz == NULL)
    return 0;
  int count = (raiz->evento->status == ATIVO) ? 1 : 0;
  return count + contarEventosAtivos(raiz->esq) + contarEventosAtivos(raiz->dir);
}

// verifica qual o filho com menor valor na arvore
Node *menorValor(Node *no)
{
  Node *atual = no;
  while (atual->esq != NULL)
    atual = atual->esq;
  return atual;
}

// rotacao simples a esquerda
Node *rotacaoEsq(Node *raiz)
{
  Node *no = raiz->dir;
  raiz->dir = no->esq;
  no->esq = raiz;
  raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
  no->altura = maior(alturaNo(no->esq), alturaNo(no->dir)) + 1;
  totalRotacoes++;
  return no;
}

// rotacao simples a direita
Node *rotacaoDir(Node *raiz)
{
  Node *no = raiz->esq;
  raiz->esq = no->dir;
  no->dir = raiz;
  raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
  no->altura = maior(alturaNo(no->esq), alturaNo(no->dir)) + 1;
  totalRotacoes++;
  return no;
}

// rotacao dupla a esquerda
Node *rotacaoDEsq(Node *raiz)
{
  raiz->esq = rotacaoEsq(raiz->esq);
  return rotacaoDir(raiz);
}

// rotacao dupla a direita
Node *rotacaoDDir(Node *raiz)
{
  raiz->dir = rotacaoDir(raiz->dir);
  return rotacaoEsq(raiz);
}

// insere um novo no a arvore
Node *inserirNo(Node *raiz, Event *evento)
{
  if (raiz == NULL)
    return criaNo(evento);

  if (evento->id < raiz->evento->id)
    raiz->esq = inserirNo(raiz->esq, evento);
  else if (evento->id > raiz->evento->id)
    raiz->dir = inserirNo(raiz->dir, evento);
  else
    return raiz;

  raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir) + 1);

  int fb = fatorBalanceamento(raiz);

  if (fb > 1 && evento->id < raiz->esq->evento->id)
    return rotacaoDir(raiz);
  if (fb < -1 && evento->id > raiz->dir->evento->id)
    return rotacaoEsq(raiz);
  if (fb > 1 && evento->id > raiz->esq->evento->id)
    return rotacaoDDir(raiz);
  if (fb < -1 && evento->id < raiz->dir->evento->id)
    return rotacaoDEsq(raiz);

  return raiz;
}

// remove um no da arvore
Node *remover(Node *raiz, Event *evento)
{

  if (raiz == NULL)
    return raiz;

  if (evento->id < raiz->evento->id)
    raiz->esq = remover(raiz->esq, evento);
  else if (evento->id > raiz->evento->id)
    raiz->dir = remover(raiz->dir, evento);
  else
  {
    // apenas nos com status RESOLVIDO podem ser apagados
    if (raiz->evento->status != RESOLVIDO)
      return raiz;

    if (raiz->esq == NULL || raiz->dir == NULL)
    {
      Node *temp = raiz->esq ? raiz->esq : raiz->dir;

      if (temp == NULL)
      {
        temp = raiz;
        raiz = NULL;
      }
      else
        *raiz = *temp;

      free(temp);
    }
    else
    {
      Node *temp = menorValor(raiz->dir);
      raiz->evento = temp->evento;
      raiz->dir = remover(raiz->dir, temp->evento);
    }
  }

  if (raiz == NULL)
    return raiz;

  raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir) + 1);

  int fb = fatorBalanceamento(raiz);

  if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
    rotacaoDir(raiz);
  if (fb > 1 && fatorBalanceamento(raiz->esq) < 0)
    rotacaoDDir(raiz);
  if (fb < -1 && fatorBalanceamento(raiz->esq) <= 0)
    rotacaoEsq(raiz);
  if (fb < -1 && fatorBalanceamento(raiz->esq) > 0)
    rotacaoDEsq(raiz);

  return raiz;
}

// realiza a busca de um no atravez do id do evento
Node *buscaEvento(int id, Node *raiz)
{
  if (raiz == NULL)
    return NULL;

  if (id < raiz->evento->id)
    return buscaEvento(id, raiz->esq);
  else if (id > raiz->evento->id)
    return buscaEvento(id, raiz->dir);
  else
    return raiz;
}

// define o status de um evento como RESOLVIDO
Event *resolverEvento(Node *raiz, int id)
{
  Event *evento = buscaEvento(id, raiz)->evento;
  evento->status = RESOLVIDO;
  return evento;
}

// edita o nivel de severidade do evento
Event *mudaSeveridade(int id, Node *raiz, int nova_sev)
{
  Event *evento = buscaEvento(id, raiz)->evento;
  evento->sev_nivel = nova_sev;
  return evento;
}

// exibe o conteudo da arvore usando o metodo in-order
void printTree(Node *raiz)
{
  if (raiz != NULL)
  {
    printTree(raiz->esq);
    printf("%d - (%d) %s [%s]\n", raiz->evento->id, raiz->evento->sev_nivel, tipoEventoStr(raiz->evento->tipo), statusStr(raiz->evento->status));
    printTree(raiz->dir);
  }
}

// exibe os nos pelo intervalo da severidade
void buscaIntervaloSeveridade(Node *raiz, int menorSev, int maiorSev)
{
  if (raiz == NULL)
    return;

  buscaIntervaloSeveridade(raiz->esq, menorSev, maiorSev);

  if (raiz->evento->sev_nivel >= menorSev && raiz->evento->sev_nivel <= maiorSev)
  {
    printf("%d - (%d) %s [%s]\n",
           raiz->evento->id,
           raiz->evento->sev_nivel,
           tipoEventoStr(raiz->evento->tipo),
           statusStr(raiz->evento->status));
  }

  buscaIntervaloSeveridade(raiz->dir, menorSev, maiorSev);
}

// exibe os nos pelo intervalo do id
void buscaIntervaloId(Node *raiz, int menorId, int maiorId)
{
  if (raiz == NULL)
    return;

  buscaIntervaloId(raiz->esq, menorId, maiorId);

  if (raiz->evento->id >= menorId && raiz->evento->id <= maiorId)
  {
    printf("%d - (%d) %s [%s]\n",
           raiz->evento->id,
           raiz->evento->sev_nivel,
           tipoEventoStr(raiz->evento->tipo),
           statusStr(raiz->evento->status));
  }

  buscaIntervaloId(raiz->dir, menorId, maiorId);
}

// exibe os eventos por regiao do acontecido
void buscaEventosPorRegiao(Node *raiz, Regiao regiao)
{
  if (raiz == NULL)
    return;

  buscaEventosPorRegiao(raiz->esq, regiao);

  if (raiz->evento->reg == regiao)
  {
    printf("%d - (%d) %s [%s]\n",
           raiz->evento->id,
           raiz->evento->sev_nivel,
           tipoEventoStr(raiz->evento->tipo),
           statusStr(raiz->evento->status));
  }

  buscaEventosPorRegiao(raiz->dir, regiao);
}

#endif