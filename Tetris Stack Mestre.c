#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Struct que representa uma peça
typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;    // Identificador unico
} Peca;

// Struct da fila circular
typedef struct {
    Peca pecas[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Struct da pilha linear
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

// Função que gera uma peça aleatória
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Inicializa a fila
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

// Inicializa a pilha
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

// Exibe a fila
void exibirFila(Fila *fila) {
    printf("\nFila de pecas:\n");
    int i = fila->frente;
    for (int count = 0; count < fila->tamanho; count++) {
        printf("[ %c | %d ] ", fila->pecas[i].tipo, fila->pecas[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}

// Exibe a pilha
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

// Remove peça da frente da fila (dequeue)
Peca jogarPeca(Fila *fila) {
    Peca removida = {'-', -1};
    if (fila->tamanho == 0) return removida;
    removida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->tamanho--;
    return removida;
}

// Adiciona peça no final da fila (enqueue)
void inserirPecaFila(Fila *fila, Peca p) {
    if (fila->tamanho == MAX_FILA) return;
    fila->tras = (fila->tras + 1) % MAX_FILA;
    fila->pecas[fila->tras] = p;
    fila->tamanho++;
}

// Push na pilha
void pushPilha(Pilha *pilha, Peca p) {
    if (pilha->topo == MAX_PILHA - 1) return;
    pilha->topo++;
    pilha->pecas[pilha->topo] = p;
}

// Pop da pilha
Peca popPilha(Pilha *pilha) {
    Peca removida = {'-', -1};
    if (pilha->topo == -1) return removida;
    removida = pilha->pecas[pilha->topo];
    pilha->topo--;
    return removida;
}

// Troca simples: frente da fila com topo da pilha
void trocarFrenteTopo(Fila *fila, Pilha *pilha) {
    if (fila->tamanho == 0 || pilha->topo == -1) {
        printf("Nao ha pecas suficientes para troca.\n");
        return;
    }
    Peca temp = fila->pecas[fila->frente];
    fila->pecas[fila->frente] = pilha->pecas[pilha->topo];
    pilha->pecas[pilha->topo] = temp;
    printf("Troca simples realizada entre frente da fila e topo da pilha.\n");
}

// Troca múltipla: 3 primeiros da fila com 3 da pilha
void trocarTres(Fila *fila, Pilha *pilha) {
    if (fila->tamanho < 3 || pilha->topo < 2) {
        printf("Nao ha pecas suficientes para troca tripla.\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int indexFila = (fila->frente + i) % MAX_FILA;
        Peca temp = fila->pecas[indexFila];
        fila->pecas[indexFila] = pilha->pecas[pilha->topo - i];
        pilha->pecas[pilha->topo - i] = temp;  // Corrigido
    }
    printf("Troca tripla realizada entre 3 primeiros da fila e 3 da pilha.\n");
}

int main() {
    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    int idProximaPeca = MAX_FILA;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        printf("\n==============================\n");
        printf("      ESTADO ATUAL DO JOGO\n");
        printf("==============================\n");
        exibirFila(&fila);
        exibirPilha(&pilha);
        printf("==============================\n");

        printf("Opcoes:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Peca p = jogarPeca(&fila);
                if (p.id != -1) {
                    printf("Peca [ %c | %d ] jogada!\n", p.tipo, p.id);
                    inserirPecaFila(&fila, gerarPeca(idProximaPeca++));
                }
                break;
            }
            case 2: {
                Peca p = jogarPeca(&fila);
                if (p.id != -1) {
                    pushPilha(&pilha, p);
                    printf("Peca [ %c | %d ] enviada para pilha!\n", p.tipo, p.id);
                    inserirPecaFila(&fila, gerarPeca(idProximaPeca++));
                }
                break;
            }
            case 3: {
                Peca p = popPilha(&pilha);
                if (p.id != -1) {
                    printf("Peca [ %c | %d ] usada da pilha!\n", p.tipo, p.id);
                }
                break;
            }
            case 4:
                trocarFrenteTopo(&fila, &pilha);
                break;
            case 5:
                trocarTres(&fila, &pilha);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
