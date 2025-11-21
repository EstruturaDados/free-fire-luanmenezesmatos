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

// Vetor mochila: armazena até 10 itens
#define MAX_ITENS 10
Item mochila[MAX_ITENS];
int numItens = 0;

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

// Função para inserir um item na mochila
void inserirItem() {
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

// Função para remover um item pelo nome
void removerItem() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < numItens; i++) {
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

// Função para listar todos os itens da mochila
void listarItens() {
    printf("Itens na mochila:\n");
    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-30s %-20s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    if (numItens == 0) {
        printf("Nenhum item cadastrado.\n");
    }
}

// Função para buscar um item pelo nome (busca sequencial)
void buscarItem() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < numItens; i++) {
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
}

int main() {
    int opcao;
    do {
        limparTela();
        exibirMenu();
        scanf("%d", &opcao);
        limparTela();
        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema. Boa sorte na ilha!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // consome o ENTER do scanf
            getchar(); // espera novo ENTER
        }
    } while (opcao != 0);
    return 0;
}

// ...comentários e funções avançadas omitidos...
