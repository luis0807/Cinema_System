#ifndef CINEMA_H
#define CINEMA_H

typedef struct
{
    char nome[100];
    char dataLancamento[11];
} Filme;

typedef struct
{
    int linha;
    int coluna;
    int ocupado;
} Assento;

typedef struct
{
    int numeroBilhete;
    char nomeCliente[100];
    char nomeFilme[100];
    int linha;
    int coluna;
    int meiaEntrada;
} Bilhete;

#endif