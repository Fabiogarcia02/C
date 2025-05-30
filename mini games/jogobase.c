#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    srand(time(NULL));
    int numero, opcao, pontos = 100;

    printf("Escolha o nivel de dificuldade:\n");
    printf("1 - Facil\n");
    printf("2 - Medio\n");
    printf("3 - Dificil\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    int numeroaleatorio, tentativas;

    if (opcao == 1) {
        numeroaleatorio = rand() % 11;
        tentativas = 5;
        printf("Nivel facil: O numero secreto esta entre 0 e 10.\n");
        printf("Voce tem 100 pontos\n");
    }
    else if (opcao == 2) {
        numeroaleatorio = rand() % 101;
        tentativas = 8;
        printf("Nivel medio: O numero secreto esta entre 0 e 100.\n");
        printf("Voce tem 100 pontos.\n");
    }
    else if (opcao == 3) {
        numeroaleatorio = rand() % 1001;
        tentativas = 10;
        printf("Nivel dificil: O numero secreto esta entre 0 e 1000.\n");
        printf("Voce tem 100 pontos\n");
    }
    else {
        printf("Opcao invalida.\n");
        return 1;
    }

    for (int i = 1; i <= tentativas; i++) {
        printf("Tentativa %d: ", i);
        scanf("%d", &numero);

        if (numero > numeroaleatorio) {
            pontos -= 10;
            printf("O numero secreto eh menor.\n");
        }
        else if (numero < numeroaleatorio) {
            pontos -= 10;
            printf("O numero secreto eh maior.\n");
        }
        else {
            printf("Parabens, acertou!\n");
            printf("Voce tem: %d pontos\n", pontos);
            break;
        }


        if (pontos <= 0) {
            printf("Voce ficou sem pontos. Fim de jogo!\n");
            break;
        }
    }

    if (numero != numeroaleatorio) {
        printf("Voce nao acertou. O numero aleatorio era: %d\n", numeroaleatorio);
        printf("Voce tem: %d pontos\n", pontos);
    }

    return 0;
}

