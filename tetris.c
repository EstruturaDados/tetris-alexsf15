#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5

// ======== STRUCT DE PEÇA ========
typedef struct {
    int id;
    char nome[10]; // Ex: "I", "O", "T", "L"
} Peca;

// ======== STRUCT DE FILA CIRCULAR ========
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;
    int tras;
    int tamanho;
} FilaCircular;

// ======== FUNÇÕES DE GERAÇÃO ========
Peca gerarPeca() {
    Peca nova;
    const char tipos[4][10] = {"I", "O", "T", "L"};
    nova.id = rand() % 1000; // ID aleatório
    strcpy(nova.nome, tipos[rand() % 4]);
    return nova;
}

// ======== OPERAÇÕES DA FILA CIRCULAR ========
void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;

    // Preenche a fila com 5 peças iniciais
    for (int i = 0; i < TAM_FILA; i++) {
        fila->pecas[i] = gerarPeca();
        fila->tras = (fila->tras + 1) % TAM_FILA;
        fila->tamanho++;
    }
}

int filaVazia(FilaCircular *fila) {
    return fila->tamanho == 0;
}

int filaCheia(FilaCircular *fila) {
    return fila->tamanho == TAM_FILA;
}

void enfileirar(FilaCircular *fila, Peca p) {
    if (filaCheia(fila)) {
        printf("⚠️  A fila está cheia! Não é possível adicionar mais peças.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % TAM_FILA;
    fila->pecas[fila->tras] = p;
    fila->tamanho++;
}

Peca desenfileirar(FilaCircular *fila) {
    Peca pecaVazia = {0, " "};
    if (filaVazia(fila)) {
        printf("⚠️  A fila está vazia!\n");
        return pecaVazia;
    }
    Peca removida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_FILA;
    fila->tamanho--;
    return removida;
}

// ======== EXIBIÇÃO ========
void exibirFila(FilaCircular *fila) {
    printf("\n📦 Estado atual da Fila de Peças (%d/%d):\n", fila->tamanho, TAM_FILA);
    printf("----------------------------------\n");

    int index = fila->frente;
    for (int i = 0; i < fila->tamanho; i++) {
        printf("[%d] Peça ID: %d | Tipo: %s\n", i + 1, fila->pecas[index].id, fila->pecas[index].nome);
        index = (index + 1) % TAM_FILA;
    }

    if (fila->tamanho == 0)
        printf("(Fila vazia)\n");

    printf("----------------------------------\n");
}

// ======== MENU ========
void menu() {
    printf("\n===== 🎮 TETRIS STACK - Nível Novato =====\n");
    printf("1 - Jogar (remover peça da frente)\n");
    printf("2 - Inserir nova peça\n");
    printf("3 - Visualizar fila\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

// ======== FUNÇÃO PRINCIPAL ========
int main() {
    srand(time(NULL));
    FilaCircular fila;
    inicializarFila(&fila);

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // consome o \n

        switch (opcao) {
            case 1: {
                Peca jogada = desenfileirar(&fila);
                if (strcmp(jogada.nome, " ") != 0) {
                    printf("\n🎮 Peça jogada: ID=%d | Tipo=%s\n", jogada.id, jogada.nome);
                    // Após jogar, gerar e adicionar nova peça automaticamente
                    Peca nova = gerarPeca();
                    enfileirar(&fila, nova);
                    printf("🆕 Nova peça gerada e adicionada à fila!\n");
                }
                break;
            }

            case 2: {
                if (filaCheia(&fila)) {
                    printf("⚠️  A fila está cheia! Jogue uma peça antes.\n");
                } else {
                    Peca nova = gerarPeca();
                    enfileirar(&fila, nova);
                    printf("✅ Nova peça inserida: ID=%d | Tipo=%s\n", nova.id, nova.nome);
                }
                break;
            }

            case 3:
                exibirFila(&fila);
                break;

            case 0:
                printf("\n👋 Saindo do jogo... Até a próxima!\n");
                break;

            default:
                printf("❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
