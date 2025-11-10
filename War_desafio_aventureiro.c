#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


// ----------- FUNÇÃO DE ATAQUE -----------
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s tirou: %d\n", atacante->nome, dadoA);
    printf("O defensor %s tirou: %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;

        if (defensor->tropas <= 0) {
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            printf("Territorio conquistado! Agora pertence ao exercito %s.\n",
                   defensor->cor);
        }
    } else {
        printf("ATAQUE FALHOU! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}


// ----------- PROGRAMA PRINCIPAL -----------
int main() {

    srand(time(NULL));

    
    // Cadastro de territorios

    Territorio territorios[5];

    for(int i = 0; i < 5; i++) {
        printf("\n===== Cadastro do Territorio %d =====\n", i + 1);

        printf("Nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);

        printf("Cor do exercito: ");
        scanf(" %9[^\n]", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibe os cadastrados

    printf("\n\n===== Territorios Cadastrados =====\n");
    for(int i = 0; i < 5; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
                i + 1,
                territorios[i].nome,
                territorios[i].cor,
                territorios[i].tropas);
    }

    
    // ATAQUE (NOVO MÓDULO)
    
    // alocação dinâmica usando malloc
    Territorio *mapa = malloc(5 * sizeof(Territorio));

    // copia os dados existentes para área dinâmica
    for(int i = 0; i < 5; i++) {
        mapa[i] = territorios[i];
    }

    int atacante, defensor;

    while (1) {

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a 5, 0 para sair): ");
        scanf("%d", &atacante);

        if (atacante == 0)
            break;

        printf("Escolha o territorio defensor (1 a 5): ");
        scanf("%d", &defensor);

        atacante--;  
        defensor--;

        if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
            printf("\nNao pode atacar um territorio da mesma cor.\n");
        } else {
            atacar(&mapa[atacante], &mapa[defensor]);
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); getchar();
    }

    free(mapa);
    return 0;
}
