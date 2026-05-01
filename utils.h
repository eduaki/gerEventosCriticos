#ifndef UTILS_H
#define UTILS_H

typedef enum tEvento
{
  ACIDENTES_TRANSITO,
  FALHAS_SEMAFOROS,
  INTERRUPCOES_ENERGIA,
  ALAGAMENTOS,
  INCENDIOS,
} tEvento;

typedef enum Status
{
  ATIVO,
  RESOLVIDO
} Status;

typedef enum Regiao
{
  NORTE,
  SUL,
  SUDESTE,
  NORDESTE
} Regiao;

int maior(int a, int b)
{
  return (a > b) ? a : b;
}

char *tipoEventoStr(tEvento tipo)
{
  switch (tipo)
  {
  case ACIDENTES_TRANSITO:
    return "Acidente de Transito";
  case FALHAS_SEMAFOROS:
    return "Falhas em Semaforo";
  case INTERRUPCOES_ENERGIA:
    return "Interrupcoes de Energia";
  case ALAGAMENTOS:
    return "Alagamento";
  case INCENDIOS:
    return "Incendio";
  default:
    return "Desconhecido";
  }
}

char *statusStr(Status status)
{
  switch (status)
  {
  case ATIVO:
    return "ATIVO";
  case RESOLVIDO:
    return "RESOLVIDO";
  default:
    return "Desconhecido";
  }
}

char *regiaoStr(Regiao regiao)
{
  switch (regiao)
  {
  case NORTE:
    return "Norte";
  case SUL:
    return "Sul";
  case NORDESTE:
    return "Nordeste";
  case SUDESTE:
    return "Sudeste";
  default:
    return "desconhecido";
  }
}

#endif