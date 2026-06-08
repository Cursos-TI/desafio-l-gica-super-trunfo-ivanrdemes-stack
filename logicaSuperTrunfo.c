#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura da carta
struct Carta {
    char estado[50];
    char codigo[10];
    char nome_cidade[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
};

// Função para calcular atributos derivados
void calcular_atributos(struct Carta *c) {
    c->densidade_populacional = (float)c->populacao / c->area;
    c->pib_per_capita = c->pib / (float)c->populacao;
}

// Exibir carta completa
void exibir_carta(struct Carta c) {
    printf("\n========================================\n");
    printf("Carta: %s (%s)\n", c.nome_cidade, c.codigo);
    printf("Estado: %s\n", c.estado);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidade_populacional);
    printf("PIB per capita: %.2f\n", c.pib_per_capita);
    printf("========================================\n");
}

// Menu de atributos
void mostrar_menu() {
    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Populacional (menor vence)\n");
    printf("6 - PIB per capita\n");
    printf("Opção: ");
}

// Função para comparar cartas
int comparar_cartas(struct Carta c1, struct Carta c2, int atributo) {
    switch (atributo) {
        case 1: // População
            if (c1.populacao > c2.populacao) return 1;
            if (c2.populacao > c1.populacao) return 2;
            return 0;

        case 2: // Área
            if (c1.area > c2.area) return 1;
            if (c2.area > c1.area) return 2;
            return 0;

        case 3: // PIB
            if (c1.pib > c2.pib) return 1;
            if (c2.pib > c1.pib) return 2;
            return 0;

        case 4: // Pontos turísticos
            if (c1.pontos_turisticos > c2.pontos_turisticos) return 1;
            if (c2.pontos_turisticos > c1.pontos_turisticos) return 2;
            return 0;

        case 5: // Densidade populacional (menor vence)
            if (c1.densidade_populacional < c2.densidade_populacional) return 1;
            if (c2.densidade_populacional < c1.densidade_populacional) return 2;
            return 0;

        case 6: // PIB per capita
            if (c1.pib_per_capita > c2.pib_per_capita) return 1;
            if (c2.pib_per_capita > c1.pib_per_capita) return 2;
            return 0;

        default:
            return -1;
    }
}

// Exibir valor do atributo escolhido
void exibir_atributo_escolhido(struct Carta c, int atributo) {
    switch (atributo) {
        case 1:
            printf("%s: %d\n", c.nome_cidade, c.populacao);
            break;
        case 2:
            printf("%s: %.2f km²\n", c.nome_cidade, c.area);
            break;
        case 3:
            printf("%s: %.2f\n", c.nome_cidade, c.pib);
            break;
        case 4:
            printf("%s: %d\n", c.nome_cidade, c.pontos_turisticos);
            break;
        case 5:
            printf("%s: %.2f hab/km²\n", c.nome_cidade, c.densidade_populacional);
            break;
        case 6:
            printf("%s: %.2f\n", c.nome_cidade, c.pib_per_capita);
            break;
    }
}

// Nome do atributo
void nome_atributo(int atributo) {
    switch (atributo) {
        case 1: printf("População"); break;
        case 2: printf("Área"); break;
        case 3: printf("PIB"); break;
        case 4: printf("Pontos Turísticos"); break;
        case 5: printf("Densidade Populacional"); break;
        case 6: printf("PIB per capita"); break;
        default: printf("Atributo inválido");
    }
}

// Limpar buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand(time(NULL));

    // Cadastro das cartas
    struct Carta cartas[] = {
        {"São Paulo", "SP01", "São Paulo", 12300000, 1521.11, 699280000.0, 50, 0, 0},
        {"Rio de Janeiro", "RJ01", "Rio de Janeiro", 6000000, 1200.25, 350000000.0, 45, 0, 0},
        {"Minas Gerais", "MG01", "Belo Horizonte", 2530000, 331.40, 105829000.0, 30, 0, 0},
        {"Bahia", "BA01", "Salvador", 2418000, 693.80, 63200000.0, 40, 0, 0},
        {"Paraná", "PR01", "Curitiba", 1964000, 434.90, 98500000.0, 28, 0, 0},
        {"Ceará", "CE01", "Fortaleza", 2428000, 312.35, 73600000.0, 35, 0, 0},
        {"Pernambuco", "PE01", "Recife", 1489000, 218.84, 54000000.0, 33, 0, 0},
        {"Amazonas", "AM01", "Manaus", 2256000, 11401.10, 103281000.0, 25, 0, 0}
    };

    int total_cartas = sizeof(cartas) / sizeof(cartas[0]);

    // Calcular atributos derivados
    for (int i = 0; i < total_cartas; i++) {
        calcular_atributos(&cartas[i]);
    }

    int placar_jogador = 0;
    int placar_computador = 0;
    int empates = 0;
    char jogar_novamente = 's';

    printf("========================================\n");
    printf("      SUPER TRUNFO - CIDADES DO BRASIL\n");
    printf("========================================\n");

    while (jogar_novamente == 's' || jogar_novamente == 'S') {
        int i = rand() % total_cartas;
        int j;

        do {
            j = rand() % total_cartas;
        } while (j == i);

        struct Carta jogador = cartas[i];
        struct Carta computador = cartas[j];

        printf("\nSua carta foi sorteada!\n");
        exibir_carta(jogador);

        int atributo;
        do {
            mostrar_menu();
            if (scanf("%d", &atributo) != 1) {
                printf("Entrada inválida! Digite um número de 1 a 6.\n");
                limpar_buffer();
                atributo = 0;
                continue;
            }

            if (atributo < 1 || atributo > 6) {
                printf("Opção inválida! Escolha entre 1 e 6.\n");
            }
        } while (atributo < 1 || atributo > 6);

        printf("\n----------------------------------------\n");
        printf("Atributo escolhido: ");
        nome_atributo(atributo);
        printf("\n----------------------------------------\n");

        printf("\nSua carta:\n");
        exibir_atributo_escolhido(jogador, atributo);

        printf("Carta do computador:\n");
        exibir_atributo_escolhido(computador, atributo);

        int resultado = comparar_cartas(jogador, computador, atributo);

        printf("\nResultado da rodada:\n");
        if (resultado == 1) {
            printf("Você venceu! Sua carta (%s) ganhou da carta (%s).\n",
                   jogador.nome_cidade, computador.nome_cidade);
            placar_jogador++;
        } else if (resultado == 2) {
            printf("Computador venceu! A carta (%s) ganhou da sua carta (%s).\n",
                   computador.nome_cidade, jogador.nome_cidade);
            placar_computador++;
        } else {
            printf("Empate entre %s e %s!\n", jogador.nome_cidade, computador.nome_cidade);
            empates++;
        }

        printf("\nPlacar atual:\n");
        printf("Você: %d\n", placar_jogador);
        printf("Computador: %d\n", placar_computador);
        printf("Empates: %d\n", empates);

        printf("\nDeseja jogar novamente? (s/n): ");
        limpar_buffer();
        scanf("%c", &jogar_novamente);
    }

    printf("\n========================================\n");
    printf("             FIM DE JOGO\n");
    printf("========================================\n");
    printf("Placar final:\n");
    printf("Você: %d\n", placar_jogador);
    printf("Computador: %d\n", placar_computador);
    printf("Empates: %d\n", empates);

    if (placar_jogador > placar_computador) {
        printf("\nParabéns! Você foi o grande campeão!\n");
    } else if (placar_computador > placar_jogador) {
        printf("\nO computador venceu desta vez!\n");
    } else {
        printf("\nO jogo terminou empatado!\n");
    }

    return 0;
}