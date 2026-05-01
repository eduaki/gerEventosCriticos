#include <stdio.h>
#include <string.h>
#include "utils.h"

// arvore usada em todo o programa
Node *arvore = NULL;

void menu_novoEvento()
{
  int conterId = 1;
  int tipo_opt = 0;
  int sev_nivel = 0;
  int regiao_opt = 0;
  char data[11];
  char hora[9];

  tEvento tipoEvento;
  Regiao regiao;
  Status status = ATIVO;
  int regiao_valida = 0;

  printf("===============================\n");
  printf("     Adicionar novo evento     \n");
  printf("===============================\n");

  printf("Tipo evento:\n");
  printf("\t1- Acidente de transito\n");
  printf("\t2- Falhas em semaforo\n");
  printf("\t3- Interrupcoes de energia\n");
  printf("\t4- Alagamento\n");
  printf("\t5- Incendio\n");
  printf("opcao: ");
  scanf("%d", &tipo_opt);

  switch (tipo_opt)
  {
  case 1:
    tipoEvento = ACIDENTES_TRANSITO;
    break;
  case 2:
    tipoEvento = FALHAS_SEMAFOROS;
    break;
  case 3:
    tipoEvento = INTERRUPCOES_ENERGIA;
    break;
  case 4:
    tipoEvento = ALAGAMENTOS;
    break;
  case 5:
    tipoEvento = INCENDIOS;
    break;
  default:
    printf("Digite uma opcao correta!\n");
    return;
  }

  printf("\nNivel de severidade (1-5): ");
  scanf("%d", &sev_nivel);

  if (sev_nivel < 1 || sev_nivel > 5)
  {
    printf("Severidade invalida!\n");
    return;
  }
  do
  {
    regiao_valida = 0;
    printf("\nRegiao:\n");
    printf("\t1- Norte\n");
    printf("\t2- Sul\n");
    printf("\t3- Sudeste\n");
    printf("\t4- Nordeste\n");
    printf("opcao: ");
    scanf("%d", &regiao_opt);

    switch (regiao_opt)
    {
    case 1:
      regiao = NORTE;
      regiao_valida = 1;
      break;
    case 2:
      regiao = SUL;
      regiao_valida = 1;
      break;
    case 3:
      regiao = SUDESTE;
      regiao_valida = 1;
      break;
    case 4:
      regiao = NORDESTE;
      regiao_valida = 1;
      break;
    default:
      printf("Regiao invalida!\n");
    }
  } while (!regiao_valida);

  printf("\nData (dd/mm/yyyy): ");
  scanf("%10s", data);

  printf("Hora (hh:mm:ss): ");
  scanf("%8s", hora);

  Event *novoEvento = (Event *)malloc(sizeof(Event));

  novoEvento->id = conterId++ + sev_nivel + tipo_opt;
  novoEvento->tipo = tipoEvento;
  novoEvento->sev_nivel = sev_nivel;
  novoEvento->reg = regiao;
  novoEvento->status = status;
  strcpy(novoEvento->timestamp.date, data);
  strcpy(novoEvento->timestamp.time, hora);

  arvore = inserirNo(arvore, novoEvento);

  printf("\nEvento registrado com id: %d\n", novoEvento->id);
}

void menu_buscaAvancada()
{
  int opt = -1;

  do
  {
    printf("================================\n");
    printf("     Gerenciador de eventos     \n");
    printf("================================\n");
    printf("|1 - Intervalo Severidade       |\n");
    printf("|2 - Eventos por regiao         |\n");
    printf("|3 - intervalo de id            |\n");
    printf("|0 - voltar ao menu principal   |\n");
    printf("================================\n");
    printf("| > ");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
    {
      int menorSev = 0, maiorSev = 0;
      printf("Selecione o intervalo da severidade:\n");
      printf("\tMenor severidade > ");
      scanf("%d", &menorSev);
      printf("\tMaior severidade > ");
      scanf("%d", &maiorSev);

      printf("\n===============================\n");
      printf("      Eventos encontrados:     \n");
      printf("===============================\n");
      buscaIntervaloSeveridade(arvore, menorSev, maiorSev);
      printf("\n");
      break;
    }
    case 2:
    {
      int regiao_opt = 0;
      Regiao regiao;
      printf("Selecione a região:\n");
      printf("\t1- Norte\n");
      printf("\t2- Sul\n");
      printf("\t3- Sudeste\n");
      printf("\t4- Nordeste\n");
      printf("opcao: ");
      scanf("%d", &regiao_opt);

      switch (regiao_opt)
      {
      case 1:
        regiao = NORTE;
        break;
      case 2:
        regiao = SUL;
        break;
      case 3:
        regiao = SUDESTE;
        break;
      case 4:
        regiao = NORDESTE;
        break;
      default:
        printf("Região invalida!\n");
        break;
      }

      printf("\n===============================\n");
      printf("      Eventos encontrados:      \n");
      printf("================================\n");
      buscaEventosPorRegiao(arvore, regiao);
      printf("\n");
      break;
    }
    case 3:
    {
      int menorId = 0, maiorId = 0;
      printf("Selecione o intervalo dos Ids:\n");
      printf("\tMenor Id > ");
      scanf("%d", &menorId);
      printf("\tMaior Id > ");
      scanf("%d", &maiorId);

      printf("\n===============================\n");
      printf("      Eventos encontrados:     \n");
      printf("===============================\n");
      buscaIntervaloId(arvore, menorId, maiorId);
      printf("\n");
      break;
    }
    case 0:
      printf("Voltando...");
      break;
    default:
      printf("Opcao invalida!");
      break;
    }

  } while (opt != 0);
}

void menu_metricasArvore()
{
  int opt = -1;

  do
  {
    printf("================================\n");
    printf("      Metricas da Arvore        \n");
    printf("================================\n");
    printf("|1 - Altura total               |\n");
    printf("|2 - Numero total de nos        |\n");
    printf("|3 - Numero de eventos ativos   |\n");
    printf("|4 - Fator balanceamento medio  |\n");
    printf("|5 - Ver todas as metricas      |\n");
    printf("|0 - voltar ao menu principal   |\n");
    printf("================================\n");
    printf("| > ");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
    {
      printf("\n===============================\n");
      printf("         Altura da Arvore       \n");
      printf("===============================\n");
      printf("Altura: %d\n\n", alturaArvore(arvore));
      break;
    }
    case 2:
    {
      printf("\n===============================\n");
      printf("      Numero Total de Nos       \n");
      printf("===============================\n");
      printf("Total de nos: %d\n\n", contarNos(arvore));
      break;
    }
    case 3:
    {
      printf("\n===============================\n");
      printf("    Numero de Eventos Ativos    \n");
      printf("===============================\n");
      printf("Eventos ativos: %d\n\n", contarEventosAtivos(arvore));
      break;
    }
    case 4:
    {
      printf("\n===============================\n");
      printf("   Fator Balanceamento Medio    \n");
      printf("===============================\n");
      printf("Fator medio: %.2f\n\n", fatorBalanceamentoMedio(arvore));
      break;
    }
    case 5:
    {
      printf("\n===============================\n");
      printf("        Todas as Metricas       \n");
      printf("===============================\n");
      printf("Altura da arvore: %d\n", alturaArvore(arvore));
      printf("Total de nos: %d\n", contarNos(arvore));
      printf("Eventos ativos: %d\n", contarEventosAtivos(arvore));
      printf("Fator balanceamento medio: %.2f\n", fatorBalanceamentoMedio(arvore));
      printf("Total de rotacoes realizadas: %d\n\n", totalRotacoes);
      break;
    }
    case 0:
      printf("Voltando...\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }

  } while (opt != 0);
}