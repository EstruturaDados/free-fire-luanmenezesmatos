#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct Item: representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct No: representa um nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor mochila: armazena até 10 itens
#define MAX_ITENS 10
Item mochila[MAX_ITENS];
int numItens = 0;

// Lista encadeada
No* inicio = NULL;

// Contadores de comparações
int comparacoesSequencialVetor = 0;
int comparacoesBinariaVetor = 0;
int comparacoesSequencialLista = 0;

// Função para limpar a tela (simulada)
void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("===== MOCHILA FREE FIRE =====\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("0. Sair\n");
    printf("=============================\n");
    printf("Escolha uma opção: ");
}

// Funções para vetor (lista sequencial)
void inserirItemVetor() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    Item novo;
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo do item (arma, munição, cura, etc): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[numItens++] = novo;
    printf("Item adicionado com sucesso!\n");
}

void removerItemVetor() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < numItens; i++) {
        comparacoesSequencialVetor++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        for (int j = encontrado; j < numItens - 1; j++) {
            mochila[j] = mochila[j + 1];
        }
        numItens--;
        printf("Item removido com sucesso!\n");
    } else {
        printf("Item não encontrado!\n");
    }
}

void listarItensVetor() {
    printf("Itens na mochila (vetor):\n");
    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-30s %-20s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    if (numItens == 0) {
        printf("Nenhum item cadastrado.\n");
    }
}

void buscarSequencialVetor() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    comparacoesSequencialVetor = 0;
    for (int i = 0; i < numItens; i++) {
        comparacoesSequencialVetor++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        printf("Item encontrado:\n");
        printf("Nome: %s\n", mochila[encontrado].nome);
        printf("Tipo: %s\n", mochila[encontrado].tipo);
        printf("Quantidade: %d\n", mochila[encontrado].quantidade);
    } else {
        printf("Item não encontrado!\n");
    }
    printf("Comparações realizadas (sequencial vetor): %d\n", comparacoesSequencialVetor);
}

// Ordenação por nome (Bubble Sort)
void ordenarVetor() {
    int trocou;
    for (int i = 0; i < numItens - 1; i++) {
        trocou = 0;
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
    printf("Itens ordenados por nome!\n");
}

// Busca binária por nome (após ordenação)
void buscarBinariaVetor() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item a buscar (binária): ");
    scanf(" %[^\n]", nomeBusca);

    int inicioIdx = 0, fimIdx = numItens - 1, meio, encontrado = -1;
    comparacoesBinariaVetor = 0;
    while (inicioIdx <= fimIdx) {
        meio = (inicioIdx + fimIdx) / 2;
        comparacoesBinariaVetor++;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);
        if (cmp == 0) {
            encontrado = meio;
            break;
        } else if (cmp < 0) {
            inicioIdx = meio + 1;
        } else {
            fimIdx = meio - 1;
        }
    }
    if (encontrado != -1) {
        printf("Item encontrado:\n");
        printf("Nome: %s\n", mochila[encontrado].nome);
        printf("Tipo: %s\n", mochila[encontrado].tipo);
        printf("Quantidade: %d\n", mochila[encontrado].quantidade);
    } else {
        printf("Item não encontrado!\n");
    }
    printf("Comparações realizadas (binária vetor): %d\n", comparacoesBinariaVetor);
}

// Funções para lista encadeada
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de memória!\n");
        return;
    }
    printf("Nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo do item (arma, munição, cura, etc): ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicio;
    inicio = novo;
    printf("Item adicionado na lista!\n");
}

void removerItemLista() {
    if (!inicio) {
        printf("Lista vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    No *atual = inicio, *anterior = NULL;
    comparacoesSequencialLista = 0;
    while (atual) {
        comparacoesSequencialLista++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                inicio = atual->proximo;
            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado na lista!\n");
    printf("Comparações realizadas (sequencial lista): %d\n", comparacoesSequencialLista);
}

void listarItensLista() {
    printf("Itens na mochila (lista encadeada):\n");
    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("-------------------------------------------------------------\n");
    No* atual = inicio;
    int vazio = 1;
    while (atual) {
        printf("%-30s %-20s %-10d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        vazio = 0;
    }
    if (vazio) printf("Nenhum item cadastrado.\n");
}

void buscarSequencialLista() {
    if (!inicio) {
        printf("Lista vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    No* atual = inicio;
    comparacoesSequencialLista = 0;
    while (atual) {
        comparacoesSequencialLista++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("Item encontrado na lista:\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Comparações realizadas (sequencial lista): %d\n", comparacoesSequencialLista);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado na lista!\n");
    printf("Comparações realizadas (sequencial lista): %d\n", comparacoesSequencialLista);
}

// Menu principal para escolha de estrutura
void menuEstrutura() {
    int estrutura, opcao;
    do {
        limparTela();
        printf("Escolha a estrutura de dados:\n");
        printf("1. Vetor (lista sequencial)\n");
        printf("2. Lista encadeada\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &estrutura);
        limparTela();
        if (estrutura == 1) {
            do {
                printf("===== MOCHILA (VETOR) =====\n");
                printf("1. Adicionar um item\n");
                printf("2. Remover um item\n");
                printf("3. Listar todos os itens\n");
                printf("4. Buscar item por nome (sequencial)\n");
                printf("5. Ordenar itens por nome\n");
                printf("6. Buscar item por nome (binária)\n");
                printf("0. Voltar\n");
                printf("===========================\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                limparTela();
                switch (opcao) {
                    case 1: inserirItemVetor(); listarItensVetor(); break;
                    case 2: removerItemVetor(); listarItensVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: ordenarVetor(); listarItensVetor(); break;
                    case 6: buscarBinariaVetor(); break;
                    case 0: break;
                    default: printf("Opção inválida!\n");
                }
                if (opcao != 0) {
                    printf("\nPressione ENTER para continuar...");
                    getchar(); getchar();
                }
            } while (opcao != 0);
        } else if (estrutura == 2) {
            do {
                printf("===== MOCHILA (LISTA ENCADEADA) =====\n");
                printf("1. Adicionar um item\n");
                printf("2. Remover um item\n");
                printf("3. Listar todos os itens\n");
                printf("4. Buscar item por nome (sequencial)\n");
                printf("0. Voltar\n");
                printf("=====================================\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                limparTela();
                switch (opcao) {
                    case 1: inserirItemLista(); listarItensLista(); break;
                    case 2: removerItemLista(); listarItensLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                    case 0: break;
                    default: printf("Opção inválida!\n");
                }
                if (opcao != 0) {
                    printf("\nPressione ENTER para continuar...");
                    getchar(); getchar();
                }
            } while (opcao != 0);
        } else if (estrutura == 0) {
            printf("Saindo do sistema. Boa sorte na ilha!\n");
        } else {
            printf("Opção inválida!\n");
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar();
        }
    } while (estrutura != 0);
}

int main() {
    menuEstrutura();
    return 0;
}

// ...existing code...
