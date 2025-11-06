#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // Tamanho fixo da fila

// Struct que representa uma peca
typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;    // Identificador unico
} Peca;

// Struct que representa a fila circular
typedef struct {
    Peca pecas[MAX];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Funcao que gera uma peca automaticamente
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4]; // Tipo aleatorio
    p.id = id;                  // ID unico
    return p;
}

// Inicializa a fila com pecas automaticas
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
    for (int i = 0; i < MAX; i++) {
        fila->tras = (fila->tras + 1) % MAX;
        fila->pecas[fila->tras] = gerarPeca(i);
        fila->tamanho++;
    }
}

// Exibe a fila atual no terminal
void exibirFila(Fila *fila) {
    printf("\n============================\n");
    printf("       FILA DE PECAS\n");
    printf("============================\n");

    if(fila->tamanho == 0) {
        printf("Fila vazia!\n");
        return;
    }

    int i = fila->frente;
    for (int count = 0; count < fila->tamanho; count++) {
        printf("[ %c | %d ] ", fila->pecas[i].tipo, fila->pecas[i].id);
        i = (i + 1) % MAX;
    }
    printf("\n============================\n");
}

// Remove a peca da frente (dequeue)
void jogarPeca(Fila *fila) {
    if (fila->tamanho == 0) {
        printf("Fila vazia! Nenhuma peca para jogar.\n");
        return;
    }
    printf("Peca [ %c | %d ] jogada!\n", fila->pecas[fila->frente].tipo, fila->pecas[fila->frente].id);
    fila->frente = (fila->frente + 1) % MAX;
    fila->tamanho--;
}

// Insere uma nova peca no final (enqueue)
void inserirPeca(Fila *fila, int id) {
    if (fila->tamanho == MAX) {
        printf("Fila cheia! Nao e possivel inserir nova peca.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % MAX;
    fila->pecas[fila->tras] = gerarPeca(id);
    fila->tamanho++;
    printf("Nova peca [ %c | %d ] inserida!\n", fila->pecas[fila->tras].tipo, fila->pecas[fila->tras].id);
}

int main() {
    srand(time(NULL)); // Inicializa aleatoriedade
    Fila fila;
    int idProximaPeca = MAX; // ID da proxima peca gerada
    int opcao;

    // Inicializa a fila com 5 pecas
    inicializarFila(&fila);

    do {
        exibirFila(&fila);

        // Menu de opcoes
        printf("Opcoes:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, idProximaPeca++);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}