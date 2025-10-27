#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// --- Requisito: Struct Operacao para o Histórico ---
#define MAX_HISTORICO 10
#define MAX_N 3 // Para as matrizes 3x3

typedef struct {
    char tipo[20];
    double a, b;
    double resultado;
    int id;
} Operacao;

// --- Protótipos das Funções de Cálculo (calculos.c) ---

// Básicas
double soma(double a, double b);
double subtracao(double a, double b);
double multiplicacao(double a, double b);
// Retorna 1 se sucesso, 0 se divisão por zero (Requisito: Verificação de erros)
int divisao(double a, double b, double *resultado); 

// Adicionais (Pelo menos 8)
double potencia(double base, double expoente);
int raiz_quadrada(double radicando, double *resultado); // Checa radicando negativo
long long fatorial(int n);                             // Retorna long long para valores maiores
double logaritmo_base_10(double x);
double seno_radianos(double angulo);
double calcula_mdc(int a, int b);
double calcula_mmc(int a, int b);
double calcular_media(const double array[], int tamanho);
double calcular_mediana(double array[], int tamanho);

// Matrizes
// Matrizes são passadas como ponteiros para o primeiro elemento, 'tamanho' é 2 ou 3
int soma_matrizes(int tamanho, const double A[MAX_N][MAX_N], const double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]);
int multiplica_matrizes(int tamanho, const double A[MAX_N][MAX_N], const double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]);


// --- Protótipos das Funções de Histórico e I/O (main.c/historico.c) ---

void adicionar_historico(Operacao historico[], int *contador, int *id_global, 
                         const char *tipo, double a, double b, double resultado);
void listar_historico(const Operacao historico[], int contador);

// Persistência
void salvar_historico_csv(const Operacao historico[], int contador, const char *nome_arquivo);
int carregar_historico_csv(Operacao historico[], int *contador, int *id_global, const char *nome_arquivo);

// I/O e Utilidades
void limpar_tela();
void exibir_menu();
int validar_entrada_int(const char *prompt);
double validar_entrada_double(const char *prompt);
void pegar_dados_matriz(int tamanho, double M[MAX_N][MAX_N]);
void exibir_matriz(int tamanho, const double M[MAX_N][MAX_N]);
void ordenar_array(double array[], int tamanho);

#endif // CALCULADORA_H