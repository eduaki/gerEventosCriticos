#include <stdio.h>
#include "arvore.c"
#include "menu.h"

int main()
{
  int op = -1;

  do
  {
    printf("================================\n");
    printf("     Gerenciador de eventos     \n");
    printf("================================\n");
    printf("|1 - Registrar evento           |\n");
    printf("|2 - Visualizar todos eventos   |\n");
    printf("|3 - Resolver evento            |\n");
    printf("|4 - Busca avancada             |\n");
    printf("|5 - Apagar evento              |\n");
    printf("|6 - Edita severidade do evento |\n");
    printf("|7 - Metricas da arvore         |\n");
    printf("|0 - Sair                       |\n");
    printf("================================\n");
    printf("> ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
      menu_novoEvento();
      break;
    case 2:
    {
      printf("===============================\n");
      printf("      Eventos registrados      \n");
      printf("===============================\n");
      if (arvore == NULL)
        printf("Nenhum evento registrado...\n");
      else
        printTree(arvore);
      printf("\n");
    }
    break;
    case 3:
    {
      int idEvento = 0;
      printf("===============================\n");
      printf("        Resolver evento        \n");
      printf("===============================\n");
      printf("Id do evento > ");
      scanf("%d", &idEvento);
      Event *evento = resolverEvento(arvore, idEvento);

      printf("===============================\n");
      printf("        Evento resolvido       \n");
      printf("===============================\n");
      printf("Tipo: %s\n", tipoEventoStr(evento->tipo));
      printf("Severidade: %d\n", evento->sev_nivel);
      printf("Status: [%s]\n", statusStr(evento->status));
      printf("data-hora: %s-%s\n", evento->timestamp.date, evento->timestamp.time);

      break;
    }
    case 4:
      menu_buscaAvancada();
      break;
    case 5:
    {
      int idEvento = -1;
      printf("===============================\n");
      printf("        Apagar um evento       \n");
      printf("===============================\n");
      printf("Id evento > ");
      scanf("%d", &idEvento);
      Node *node = buscaEvento(idEvento, arvore);
      Event *evento = node->evento;
      remover(arvore, evento);
      Node *nodeVerif = buscaEvento(idEvento, arvore);
      if (nodeVerif == NULL)
        printf("\nO evento (%d) foi deletado com sucesso!\n", idEvento);
      else
        printf("\nO evento precisa ser resolvido para ser apagado!\n");
    }
    break;
    case 6:
    {
      int idEvento = -1;
      int novaSeveridade = -1;
      printf("===============================\n");
      printf("  Mudar severidade do evento   \n");
      printf("===============================\n");
      printf("Id do evento > ");
      scanf("%d", &idEvento);
      Event *evento = buscaEvento(idEvento, arvore)->evento;
      printf("Nivel atual de severidade: %d\n", evento->sev_nivel);
      printf("Novo nivel de severidade > ");
      scanf("%d", &novaSeveridade);

      evento = mudaSeveridade(idEvento, arvore, novaSeveridade);

      printf("===============================\n");
      printf("         Evento editado        \n");
      printf("===============================\n");
      printf("Tipo: %s\n", tipoEventoStr(evento->tipo));
      printf("Severidade: %d\n", evento->sev_nivel);
      printf("Status: [%s]\n", statusStr(evento->status));
      printf("data-hora: %s-%s\n", evento->timestamp.date, evento->timestamp.time);
      break;
    }
    case 7:
      menu_metricasArvore();
      break;
    case 0:
      printf("Encerrando...\n");
      break;
    default:
      printf("Opcao invalida!\n\n");
      break;
    }
  } while (op != 0);

  return 0;
}
