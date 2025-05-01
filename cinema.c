#include "cinema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINHAS 5
#define COLUNAS 5
#define MAX_BILHETES 100
#define MAX_FILMES 5

// Funções auxiliares

Assento sala[LINHAS][COLUNAS];
Bilhete bilhetes[MAX_BILHETES];
int totalBilhetes = 0;
int numeroBilheteAtual = 1000;

void inicializarSala()
{
    int i, j;
    for (i = 0; i < LINHAS; i++)
        for (j = 0; j < COLUNAS; j++)
        {
            sala[i][j].linha = i;
            sala[i][j].coluna = j;
            sala[i][j].ocupado = 0;
        }
}

void mostrarSala()
{
    int i, j;
    printf("   ");
    for (j = 0; j < COLUNAS; j++)
        printf(" %d ", j + 1);
    printf("\n");
    for (i = 0; i < LINHAS; i++)
    {
        printf(" %c ", 'A' + i);
        for (j = 0; j < COLUNAS; j++)
        {
            if (sala[i][j].ocupado == 0)
            {
                printf(" D ");
            }
            else
            {
                printf(" X ");
            }
        }
        printf("\n");
    }
}

Filme filmes[MAX_FILMES] = {
    {"Senhor dos Anais", "15/03/2023"},
    {"Homem Aranha", "25/12/2022"},
    {"Matrix", "10/01/2021"},
    {"Avatar", "20/04/2023"},
    {"Prenda-me se for Capaz", "05/07/2014"}};

    
void listarFilmes()
{
    int i;
    printf("Filmes disponiveis:\n");
    for (i = 0; i < MAX_FILMES; i++)
    {
        printf("%d - %s (%s)\n", i + 1, filmes[i].nome, filmes[i].dataLancamento);
    }
}

Bilhete reservarBilhete()
{
    Bilhete b;

    listarFilmes();

    int escolha;
    printf("Escolha o filme (1-%d): ", MAX_FILMES);
    scanf("%d", &escolha);
    getchar();
    strcpy(b.nomeFilme, filmes[escolha - 1].nome);
    if (escolha > MAX_FILMES)
    {
        printf("Filme Inexistente");
        abort();
    }

    mostrarSala();

    char linhaChar;
    int coluna;
    printf("Informe a linha (A-E): ");
    scanf(" %c", &linhaChar);
    printf("Informe a coluna (1-%d): ", COLUNAS);
    scanf("%d", &coluna);

    int linha = linhaChar - 'A';
    coluna--;

    if (sala[linha][coluna].ocupado)
    {
        printf("Assento ja ocupado!\n");
        b.numeroBilhete = -1;
        return b;
    }

    sala[linha][coluna].ocupado = 1;
    b.linha = linha;
    b.coluna = coluna;
    b.numeroBilhete = numeroBilheteAtual++;

    printf("Nome do cliente: ");
    getchar();
    fgets(b.nomeCliente, 100, stdin);
    b.nomeCliente[strcspn(b.nomeCliente, "\n")] = 0;

    printf("Tipo de ingresso (0 = Inteira, 1 = Meia): ");
    scanf("%d", &b.meiaEntrada);

    bilhetes[totalBilhetes++] = b;

    printf("Bilhete reservado com sucesso! Numero: %d\n", b.numeroBilhete);
    return b;
}

void imprimirBilhete(Bilhete b)
{
    printf("------ BILHETE ------\n");
    printf("Filme: %s\n", b.nomeFilme);
    printf("Cliente: %s\n", b.nomeCliente);
    printf("Assento: %c%d\n", 'A' + b.linha, b.coluna + 1);
    printf("Tipo: %s\n", b.meiaEntrada ? "Meia-entrada" : "Inteira");
    printf("Numero: %d\n", b.numeroBilhete);
    printf("---------------------\n");
}

int buscaBilhete(int numero)
{
    int i;
    for (i = 0; i < totalBilhetes; i++)
    {
        if (bilhetes[i].numeroBilhete == numero)
            return i;
    }
    return -1;
}

void relatorio()
{
    printf("\n--- Relatorio de Bilhetes ---\n");
    int i;
    for (i = 0; i < totalBilhetes; i++)
    {
        imprimirBilhete(bilhetes[i]);
    }
}

// Menu principal
void menu()
{
    int opcao;
    do
    {
        printf("\n--- Sistema de Bilheteria ---\n");
        printf("1. Reservar Lugar\n");
        printf("2. Imprimir Bilhete\n");
        printf("3. Relatorio de Bilhetes\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            reservarBilhete();
            break;
        case 2:
        {
            int numero;
            printf("Informe o numero do bilhete: ");
            scanf("%d", &numero);
            int i = buscaBilhete(numero);
            if (i != -1)
                imprimirBilhete(bilhetes[i]);
            else
                printf("Bilhete nao encontrado!\n");
            break;
        }
        case 3:
            relatorio();
            break;
        case 4:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 4);
}
