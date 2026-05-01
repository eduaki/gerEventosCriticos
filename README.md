# Gerenciador de Eventos - Árvore AVL

Um sistema de gerenciamento de eventos de cidades usando uma Árvore AVL (árvore binária de busca auto-balanceada).

## Como Rodar

### Compilar

```bash
gcc main.c -o gerenciador
```

### Executar

```bash
./gerenciador
```

## Estrutura dos Arquivos

### `main.c`

Arquivo principal que contém a função `main()` e gerencia o menu principal do programa.

- Carrega os menus disponíveis
- Controla o fluxo de execução

### `arvore.c`

Implementação da Árvore AVL com todas as operações:

- **Estruturas**: `Timestamp`, `Event`, `Node`
- **Inserção**: `inserirNo()` - adiciona eventos mantendo balanceamento
- **Remoção**: `remover()` - remove apenas eventos RESOLVIDO
- **Busca**: `buscaEvento()` - procura evento por ID
- **Rotações**: Auto-balanceamento da árvore

### `menu.h`

Contém todos os menus e funções de busca:

- `menu_novoEvento()` - adicionar novo evento
- `menu_buscaAvancada()` - buscar por severidade, região ou ID
- `menu_metricasArvore()` - visualizar métricas da árvore
- Funções auxiliares de busca

### `utils.h`

Definições de tipos e funções utilitárias:

- **Enums**: `tEvento`, `Status`, `Regiao`
- **Funções**: `maior()`, `tipoEventoStr()`, `statusStr()`, `regiaoStr()`

## Funcionalidades Principais

✅ Adicionar novo evento  
✅ Listar todos os eventos  
✅ Resolver evento (marcar como resolvido)  
✅ Remover eventos resolvidos  
✅ Busca por intervalo de severidade  
✅ Busca por região  
✅ Busca por intervalo de ID  
✅ Visualizar métricas da árvore (altura, total de nós, eventos ativos, etc.)

## Requisitos

- GCC ou compilador C compatível
- Linux/Windows/Mac com suporte a C
