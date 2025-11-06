#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // Tamanho da fila de peças futuras
#define MAX_PILHA 3  // Tamanho da pilha de reserva

// Struct que representa uma peça
typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Struct que representa a fila circular
typedef struct {
    Peca pecas[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Struct que representa a pilha linear
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

// Função que gera uma peça automaticamente
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Inicializa a fila com peças automáticas
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
    for (int i = 0; i < MAX_FILA; i++) {
        fila->tras = (fila->tras + 1) % MAX_FILA;
        fila->pecas[fila->tras] = gerarPeca(i);
        fila->tamanho++;
    }
}

// Inicializa a pilha vazia
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

// Exibe o estado atual da fila
void exibirFila(Fila *fila) {
    printf("\nFila de peças:\n");
    if (fila->tamanho == 0) {
        printf("Fila vazia!\n");
        return;
    }

    int i = fila->frente;
    for (int count = 0; count < fila->tamanho; count++) {
        printf("[ %c | %d ] ", fila->pecas[i].tipo, fila->pecas[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}

// Exibe o estado atual da pilha
void exibirPilha(Pilha *pilha) {
    printf("Pilha de reserva (Topo -> Base):\n");
    if (pilha->topo == -1) {
        printf("Pilha vazia!\n");
        return;
    }
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[ %c | %d ] ", pilha->pecas[i].tipo, pilha->pecas[i].id);
    }
    printf("\n");
}

// Remove a peça da frente da fila (dequeue)
Peca jogarPeca(Fila *fila) {
    Peca removida = {'-', -1};
    if (fila->tamanho == 0) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return removida;
    }
    removida = fila->pecas[fila->frente];
    printf("Peca [ %c | %d ] jogada!\n", removida.tipo, removida.id);
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->tamanho--;
    return removida;
}

// Insere uma nova peça no final da fila (enqueue)
void inserirPecaFila(Fila *fila, int id) {
    if (fila->tamanho == MAX_FILA) {
        printf("Fila cheia! Não é possivel inserir nova peça.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % MAX_FILA;
    fila->pecas[fila->tras] = gerarPeca(id);
    fila->tamanho++;
    printf("Nova peca [ %c | %d ] inserida na fila!\n", fila->pecas[fila->tras].tipo, fila->pecas[fila->tras].id);
}

// Adiciona uma peça ao topo da pilha (push)
void reservarPeca(Pilha *pilha, Peca p) {
    if (pilha->topo == MAX_PILHA - 1) {
        printf("Pilha cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    pilha->topo++;
    pilha->pecas[pilha->topo] = p;
    printf("Peca [ %c | %d ] reservada!\n", p.tipo, p.id);
}

// Remove a peça do topo da pilha (pop)
void usarPecaReservada(Pilha *pilha) {
    if (pilha->topo == -1) {
        printf("Pilha vazia! Nenhuma peca reservada para usar.\n");
        return;
    }
    Peca p = pilha->pecas[pilha->topo];
    printf("Peca reservada [ %c | %d ] usada!\n", p.tipo, p.id);
    pilha->topo--;
}

int main() {
    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    int idProximaPeca = MAX_FILA;
    int opcao;

    // Inicializacao das estruturas
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        printf("\n==============================\n");
        printf("      ESTADO ATUAL DO JOGO\n");
        printf("==============================\n");
        exibirFila(&fila);
        exibirPilha(&pilha);
        printf("==============================\n");

        // Menu de ações
        printf("Opcoes:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca removida = jogarPeca(&fila);
                if (removida.id != -1) {
                    inserirPecaFila(&fila, idProximaPeca++);
                }
                break;
            }
            case 2: {
                Peca p = jogarPeca(&fila);
                if (p.id != -1) {
                    reservarPeca(&pilha, p);
                    inserirPecaFila(&fila, idProximaPeca++);
                }
                break;
            }
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}