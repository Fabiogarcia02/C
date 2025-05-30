#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define TAM_CATEGORIA 30

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct produto {
    char nome[TAM_NOME];
    int codigo;
    float preco;
    int qntd;
    char categoria[TAM_CATEGORIA];
} produto;

void limparBuffer() {
    while (getchar() != '\n');
}

void exibirProduto(produto p) {
    printf("📦 Nome: %s\n", p.nome);
    printf("🔢 Código: %d\n", p.codigo);
    printf("💰 Preço: R$ %.2f\n", p.preco);
    printf("📦 Quantidade: %d\n", p.qntd);
    printf("🏷️ Categoria: %s\n", p.categoria);
}

void escolherCategoria(char *destino) {
    int opc;
    printf("Escolha a categoria:\n");
    printf("1 - Alimento 🍎\n");
    printf("2 - Limpeza 🧼\n");
    printf("3 - Eletrônico 💻\n");
    printf("4 - Outro 📁\n");
    printf("Digite o número da categoria: ");
    while (scanf("%d", &opc) != 1 || opc < 1 || opc > 4) {
        printf("❌ Opção inválida. Digite novamente: ");
        limparBuffer();
    }
    limparBuffer();

    switch (opc) {
        case 1: strcpy(destino, "Alimento"); break;
        case 2: strcpy(destino, "Limpeza"); break;
        case 3: strcpy(destino, "Eletrônico"); break;
        case 4: strcpy(destino, "Outro"); break;
    }
}

void listarPorCategoria(produto *produtos, int total) {
    char busca[TAM_CATEGORIA];
    printf("\n🔍 Digite a categoria para listar: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    int encontrados = 0;
    printf("\n📋 Produtos na categoria \"%s\":\n", busca);
    for (int i = 0; i < total; i++) {
        if (strcasecmp(produtos[i].categoria, busca) == 0) {
            printf("\n🔹 Produto %d:\n", i + 1);
            exibirProduto(produtos[i]);
            encontrados++;
        }
    }

    if (!encontrados) {
        printf("❌ Nenhum produto encontrado na categoria \"%s\".\n", busca);
    }
}

int main() {
    produto *produtos = NULL;
    int capacidade = 5;
    int total = 0;
    int opcao;

    produtos = (produto *)malloc(capacidade * sizeof(produto));
    if (!produtos) {
        printf("❌ Erro ao alocar memória.\n");
        return 1;
    }

    do {
        printf("\n🌟 Menu de Opções:\n");
        printf("1 - Adicionar produto ➕\n");
        printf("2 - Listar todos os produtos 📃\n");
        printf("3 - Mostrar produto com maior quantidade 📈\n");
        printf("4 - Buscar produto por código 🔍\n");
        printf("5 - Listar produtos por categoria 🗂️\n");
        printf("0 - Sair ❌\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        system(CLEAR);

        switch (opcao) {
            case 1:
                if (total == capacidade) {
                    capacidade *= 2;
                    produtos = (produto *)realloc(produtos, capacidade * sizeof(produto));
                    if (!produtos) {
                        printf("❌ Erro ao realocar memória.\n");
                        return 1;
                    }
                }

                printf("📝 Cadastro de Produto:\n");

                printf("Digite o nome: ");
                fgets(produtos[total].nome, TAM_NOME, stdin);
                produtos[total].nome[strcspn(produtos[total].nome, "\n")] = '\0';

                printf("Digite o preço (R$): ");
                while (scanf("%f", &produtos[total].preco) != 1 || produtos[total].preco < 0) {
                    printf("❌ Preço inválido! Digite novamente: ");
                    limparBuffer();
                }

                printf("Digite a quantidade: ");
                while (scanf("%d", &produtos[total].qntd) != 1 || produtos[total].qntd < 0) {
                    printf("❌ Quantidade inválida! Digite novamente: ");
                    limparBuffer();
                }

                printf("Digite o código: ");
                while (scanf("%d", &produtos[total].codigo) != 1 || produtos[total].codigo < 0) {
                    printf("❌ Código inválido! Digite novamente: ");
                    limparBuffer();
                }
                limparBuffer();

                escolherCategoria(produtos[total].categoria);

                printf("✅ Produto cadastrado com sucesso!\n");
                total++;
                break;

            case 2:
                printf("📋 Lista de todos os produtos:\n");
                for (int i = 0; i < total; i++) {
                    printf("\n🔹 Produto %d:\n", i + 1);
                    exibirProduto(produtos[i]);
                }
                if (total == 0) printf("⚠️ Nenhum produto cadastrado.\n");
                break;

            case 3: {
                if (total == 0) {
                    printf("⚠️ Nenhum produto para avaliar.\n");
                    break;
                }
                int maior = 0;
                for (int i = 1; i < total; i++) {
                    if (produtos[i].qntd > produtos[maior].qntd)
                        maior = i;
                }
                printf("🏆 Produto com maior quantidade:\n");
                exibirProduto(produtos[maior]);
                break;
            }

            case 4: {
                if (total == 0) {
                    printf("⚠️ Nenhum produto cadastrado.\n");
                    break;
                }
                int codigo;
                printf("Digite o código a buscar: ");
                scanf("%d", &codigo);
                limparBuffer();

                int achou = 0;
                for (int i = 0; i < total; i++) {
                    if (produtos[i].codigo == codigo) {
                        printf("🔍 Produto encontrado:\n");
                        exibirProduto(produtos[i]);
                        achou = 1;
                        break;
                    }
                }
                if (!achou) {
                    printf("❌ Produto com código %d não encontrado.\n", codigo);
                }
                break;
            }

            case 5:
                listarPorCategoria(produtos, total);
                break;

            case 0:
                printf("👋 Saindo... Obrigado por usar nosso sistema!\n");
                break;

            default:
                printf("❌ Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    free(produtos);
    return 0;
}
