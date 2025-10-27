#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h> // Para DBL_MAX

// Definicao de PI, caso nao esteja definida no math.h (alguns compiladores C99)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- Constantes e Struct (Requisito: Pelo menos uma struct) ---
#define MAX_HISTORICO 10
#define MAX_N 3        // Para matrizes 3x3
#define MAX_ESTATISTICA 10 // Limite para arrays estatísticos

typedef struct {
    char tipo[20];
    double a, b;
    double resultado;
    int id;
} Operacao;

// --- Variaveis Globais (Gerenciamento de Estado e Historico) ---
Operacao historico[MAX_HISTORICO]; // Requisito: Array de struct para histórico
int contador_historico = 0;
int id_operacao_global = 1;

// --- Prototipos de Funcoes (Separacao Logica) ---

// Funcoes de Calculo (20+ funcoes)
long long c_fatorial(int n);
double c_exp_euler(double x);
double c_graus_para_radianos(double graus);
double c_max_array(const double array[], int tamanho);
double c_min_array(const double array[], int tamanho); // Funcao adicional
double c_calcula_mdc(int a, int b);
int c_divisao(double a, double b, double *resultado); 
int c_raiz_quadrada(double radicando, double *resultado);
int c_raiz_n(double radicando, double n, double *resultado);
int c_log_natural(double x, double *resultado);
int c_log_base_n(double x, double base, double *resultado);
double c_seno_graus(double angulo);
double c_cosseno_graus(double angulo);
double c_tangente_graus(double angulo);
void c_calcular_estatisticas(const double array[], int tamanho, double *media, double *mediana, double *desvio);
int c_soma_matrizes(int tamanho, const double A[MAX_N][MAX_N], const double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]);
int c_multiplica_matrizes(int tamanho, const double A[MAX_N][MAX_N], const double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]);
// Funcoes de calculo simples inline/prototipadas
double c_soma(double a, double b);
double c_subtracao(double a, double b);
double c_multiplicacao(double a, double b);
double c_potencia(double base, double expoente);
double c_celsius_para_fahrenheit(double celsius); // 20a funcao
double c_fahrenheit_para_celsius(double fahrenheit); // 21a funcao

// Funcoes de I/O e Historico
void ioc_limpar_tela();
void ioc_adicionar_historico(const char *tipo, double a, double b, double resultado);
void ioc_listar_historico();
int ioc_validar_entrada_int(const char *prompt);
double ioc_validar_entrada_double(const char *prompt);
void ioc_ordenar_array(double array[], int tamanho);
void ioc_pegar_dados_matriz(int tamanho, double M[MAX_N][MAX_N]);
void ioc_exibir_matriz(int tamanho, const double M[MAX_N][MAX_N]);
void menu_secundario(int grupo);
void ioc_salvar_historico_csv();
void ioc_carregar_historico_csv();


//================================================================
//                 IMPLEMENTACOES DAS FUNCOES
//================================================================

// --- Funções Simples (Implementação Inline ou Simples) ---
double c_soma(double a, double b) { return a + b; }
double c_subtracao(double a, double b) { return a - b; }
double c_multiplicacao(double a, double b) { return a * b; }
double c_potencia(double base, double expoente) { return pow(base, expoente); }
double c_exp_euler(double x) { return exp(x); }
double c_graus_para_radianos(double graus) { return graus * (M_PI / 180.0); }
double c_celsius_para_fahrenheit(double celsius) { return celsius * 9.0 / 5.0 + 32.0; }
double c_fahrenheit_para_celsius(double fahrenheit) { return (fahrenheit - 32.0) * 5.0 / 9.0; }

// --- Funções de Cálculo com Tratamento de Erro/Limite ---

int c_divisao(double a, double b, double *resultado) {
    if (b == 0.0) return 0; // Erro: divisão por zero
    *resultado = a / b;
    return 1;
}

long long c_fatorial(int n) {
    if (n < 0) return -1; // Erro: negativo
    if (n > 20) return -2; // Erro: limite para 'long long'
    
    long long res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

int c_raiz_quadrada(double radicando, double *resultado) {
    if (radicando < 0) return 0;
    *resultado = sqrt(radicando);
    return 1;
}

int c_raiz_n(double radicando, double n, double *resultado) {
    if (fabs(n) < 1e-9) return 0; // Raiz 0
    if (radicando < 0 && (int)n % 2 == 0) return 0; // Raiz par de negativo
    
    *resultado = pow(radicando, 1.0 / n);
    return 1;
}

int c_log_natural(double x, double *resultado) {
    if (x <= 0) return 0; // Erro: log(x <= 0)
    *resultado = log(x);
    return 1;
}

int c_log_base_n(double x, double base, double *resultado) {
    if (x <= 0 || base <= 0 || base == 1) return 0;
    *resultado = log(x) / log(base);
    return 1;
}

double c_seno_graus(double angulo) {
    return sin(c_graus_para_radianos(angulo));
}

double c_cosseno_graus(double angulo) {
    return cos(c_graus_para_radianos(angulo));
}

double c_tangente_graus(double angulo) {
    double radianos = c_graus_para_radianos(angulo);
    double cos_val = cos(radianos);
    
    if (fabs(cos_val) < 1e-9) return DBL_MAX; // Indefinido (erro)
    return tan(radianos);
}

// --- Estatística e Outros ---

double c_calcula_mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

double c_max_array(const double array[], int tamanho) {
    if (tamanho <= 0) return NAN;
    double max = array[0];
    for(int i = 1; i < tamanho; i++) {
        if(array[i] > max) max = array[i];
    }
    return max;
}

double c_min_array(const double array[], int tamanho) {
    if (tamanho <= 0) return NAN;
    double min = array[0];
    for(int i = 1; i < tamanho; i++) {
        if(array[i] < min) min = array[i];
    }
    return min;
}

void c_calcular_estatisticas(const double array[], int tamanho, double *media, double *mediana, double *desvio) {
    if (tamanho <= 0) { *media = *mediana = *desvio = 0.0; return; }

    double soma_val = 0.0;
    for (int i = 0; i < tamanho; i++) soma_val += array[i];
    *media = soma_val / tamanho;
    
    // Mediana: array deve estar ORDENADO
    if (tamanho % 2 != 0) {
        *mediana = array[tamanho / 2];
    } else {
        *mediana = (array[tamanho / 2 - 1] + array[tamanho / 2]) / 2.0;
    }

    // Desvio-Padrão
    double soma_desvio_quadrado = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma_desvio_quadrado += pow(array[i] - *media, 2);
    }
    *desvio = sqrt(soma_desvio_quadrado / tamanho);
}

// --- Matrizes (Requisito: Uso de Arrays) ---

int c_soma_matrizes(int tamanho, const double A[MAX_N][MAX_N], const double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]) {
    if (tamanho < 2 || tamanho > MAX_N) return 0; 
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return 1;
}

int c_multiplica_matrizes(int tamanho, const double A[MAX_N][MAX_N], const double B[MAX_N][MAX_N], double C[MAX_N][MAX_N]) {
    if (tamanho < 2 || tamanho > MAX_N) return 0;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < tamanho; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return 1;
}

//================================================================
//                 IMPLEMENTACOES DAS FUNCOES I/O E HISTORICO
//================================================================

void ioc_limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Funcao de comparacao para qsort (necessaria para Mediana)
int comparar_doubles_qsort(const void *a, const void *b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void ioc_ordenar_array(double array[], int tamanho) {
    qsort(array, tamanho, sizeof(double), comparar_doubles_qsort);
}

// Requisito: Validação de entradas
int ioc_validar_entrada_int(const char *prompt) {
    int valor;
    int resultado_scanf;
    do {
        printf("%s", prompt);
        resultado_scanf = scanf("%d", &valor);
        if (resultado_scanf == 0) {
            printf("[ERRO] Entrada invalida. Digite um inteiro.\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            return valor;
        }
    } while (1);
}

double ioc_validar_entrada_double(const char *prompt) {
    double valor;
    int resultado_scanf;
    do {
        printf("%s", prompt);
        resultado_scanf = scanf("%lf", &valor);
        if (resultado_scanf == 0) {
            printf("[ERRO] Entrada invalida. Digite um numero real.\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            return valor;
        }
    } while (1);
}

// Requisito: Histórico de operações
void ioc_adicionar_historico(const char *tipo, double a, double b, double resultado) {
    int indice = contador_historico % MAX_HISTORICO;
    
    strncpy(historico[indice].tipo, tipo, 19);
    historico[indice].tipo[19] = '\0';
    historico[indice].a = a;
    historico[indice].b = b;
    historico[indice].resultado = resultado;
    historico[indice].id = id_operacao_global++;

    if (contador_historico < MAX_HISTORICO) {
        contador_historico++;
    }
}

void ioc_listar_historico() {
    ioc_limpar_tela();
    printf("=======================================\n");
    printf("         HISTORICO DE OPERACOES        \n");
    printf("=======================================\n");
    
    if (contador_historico == 0) {
        printf("Nenhuma operacao registrada ainda.\n");
    } else {
        int limite = (contador_historico < MAX_HISTORICO) ? contador_historico : MAX_HISTORICO;
        int inicio = (contador_historico < MAX_HISTORICO) ? 0 : contador_historico % MAX_HISTORICO;
        
        for (int i = 0; i < limite; i++) {
            int indice = (inicio + i) % MAX_HISTORICO;
            printf("ID %d | %-12s (A:%.2f | B:%.2f) = %.4f\n", 
                   historico[indice].id, historico[indice].tipo, 
                   historico[indice].a, historico[indice].b, historico[indice].resultado);
        }
    }
    printf("---------------------------------------\n");
    printf("Pressione ENTER para voltar ao menu...");
    getchar();
}

// Funcoes de persistencia (esqueleto)
void ioc_salvar_historico_csv() {
    printf("[AVISO] Funcao de salvar historico nao implementada nesta versao.\n");
}
void ioc_carregar_historico_csv() {
    printf("[AVISO] Funcao de carregar historico nao implementada nesta versao.\n");
}

// I/O Matrizes
void ioc_pegar_dados_matriz(int tamanho, double M[MAX_N][MAX_N]) {
    printf("Digite os elementos da matriz %dx%d:\n", tamanho, tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            char prompt[50];
            sprintf(prompt, "Elemento [%d][%d]: ", i + 1, j + 1);
            M[i][j] = ioc_validar_entrada_double(prompt);
        }
    }
}

void ioc_exibir_matriz(int tamanho, const double M[MAX_N][MAX_N]) {
    printf("\n[Resultado da Matriz %dx%d]\n", tamanho, tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("|");
        for (int j = 0; j < tamanho; j++) {
            printf(" %8.2f ", M[i][j]);
        }
        printf("|\n");
    }
}

// Menu Secundário (Lógica central)
void menu_secundario(int grupo) {
    double a, b, resultado;
    int sucesso;
    int sub_escolha;

    while (1) {
        ioc_limpar_tela();
        printf("=======================================\n");
        printf("        GRUPO DE OPERACOES %d          \n", grupo);
        printf("=======================================\n");

        if (grupo == 1) { // BASICAS
            printf(" 1. Soma       2. Subtracao\n 3. Multiplicacao 4. Divisao\n 0. Voltar\n");
            sub_escolha = ioc_validar_entrada_int("Escolha: ");
            if (sub_escolha == 0) return;

            if (sub_escolha == 4) {
                a = ioc_validar_entrada_double("Dividendo (a): ");
                b = ioc_validar_entrada_double("Divisor (b): ");
                sucesso = c_divisao(a, b, &resultado);
                if (sucesso) printf("Resultado: %.2f / %.2f = %.4f\n", a, b, resultado);
                else printf("[ERRO] Divisao por zero nao permitida.\n");
                ioc_adicionar_historico("Divisao", a, b, sucesso ? resultado : NAN);
            } else if (sub_escolha >= 1 && sub_escolha <= 3) {
                a = ioc_validar_entrada_double("Primeiro numero (a): ");
                b = ioc_validar_entrada_double("Segundo numero (b): ");
                if (sub_escolha == 1) { resultado = c_soma(a, b); ioc_adicionar_historico("Soma", a, b, resultado); }
                else if (sub_escolha == 2) { resultado = c_subtracao(a, b); ioc_adicionar_historico("Subtracao", a, b, resultado); }
                else if (sub_escolha == 3) { resultado = c_multiplicacao(a, b); ioc_adicionar_historico("Multiplicacao", a, b, resultado); }
                printf("Resultado: %.4f\n", resultado);
            } else { printf("[ERRO] Opcao invalida.\n"); }
        }
        else if (grupo == 2) { // POTENCIAS/RAIZES
            printf(" 1. Potencia (x^y)   2. Raiz Quadrada\n 3. Raiz N       4. e^x\n 0. Voltar\n");
            sub_escolha = ioc_validar_entrada_int("Escolha: ");
            if (sub_escolha == 0) return;

            if (sub_escolha == 1) { // Potencia
                a = ioc_validar_entrada_double("Base (x): ");
                b = ioc_validar_entrada_double("Expoente (y): ");
                resultado = c_potencia(a, b);
                printf("Resultado: %.2f ^ %.2f = %.4f\n", a, b, resultado);
                ioc_adicionar_historico("Potencia", a, b, resultado);
            } else if (sub_escolha == 2) { // Raiz Quadrada
                a = ioc_validar_entrada_double("Radicando: ");
                sucesso = c_raiz_quadrada(a, &resultado);
                if (sucesso) printf("Resultado: sqrt(%.2f) = %.4f\n", a, resultado);
                else printf("[ERRO] Raiz quadrada de numero negativo nao permitida.\n");
                ioc_adicionar_historico("Raiz Quad", a, 0.0, sucesso ? resultado : NAN);
            } else if (sub_escolha == 3) { // Raiz N
                a = ioc_validar_entrada_double("Radicando: ");
                b = ioc_validar_entrada_double("Indice da Raiz (N): ");
                sucesso = c_raiz_n(a, b, &resultado);
                if (sucesso) printf("Resultado: Raiz %.0f de %.2f = %.4f\n", b, a, resultado);
                else printf("[ERRO] Raiz invalida (Ex: indice par de negativo, ou indice 0).\n");
                ioc_adicionar_historico("Raiz N", a, b, sucesso ? resultado : NAN);
            } else if (sub_escolha == 4) { // e^x
                a = ioc_validar_entrada_double("Expoente (x): ");
                resultado = c_exp_euler(a);
                printf("Resultado: e^%.2f = %.4f\n", a, resultado);
                ioc_adicionar_historico("Exp Euler", a, 0.0, resultado);
            } else { printf("[ERRO] Opcao invalida.\n"); }
        }
        else if (grupo == 3) { // LOGS/FATORIAL
            printf(" 1. Fatorial (!)   2. Log Natural\n 3. Log Base N 4. Max/Min\n 0. Voltar\n");
            sub_escolha = ioc_validar_entrada_int("Escolha: ");
            if (sub_escolha == 0) return;

            if (sub_escolha == 1) { // Fatorial
                int n = ioc_validar_entrada_int("Numero inteiro (max 20): ");
                long long res_fatorial = c_fatorial(n);
                if (res_fatorial == -1) printf("[ERRO] Fatorial nao definido para negativos.\n");
                else if (res_fatorial == -2) printf("[ERRO] Limite (%d!) excedido para long long.\n", n);
                else { printf("Resultado: %d! = %lld\n", n, res_fatorial); }
                ioc_adicionar_historico("Fatorial", (double)n, 0.0, (double)res_fatorial);
            } else if (sub_escolha == 2) { // Log Natural
                a = ioc_validar_entrada_double("Valor (x > 0): ");
                sucesso = c_log_natural(a, &resultado);
                if (sucesso) printf("Resultado: ln(%.2f) = %.4f\n", a, resultado);
                else printf("[ERRO] Logaritmo nao definido para x <= 0.\n");
                ioc_adicionar_historico("Log Nat", a, 0.0, sucesso ? resultado : NAN);
            } else if (sub_escolha == 3) { // Log Base N
                a = ioc_validar_entrada_double("Valor (x > 0): ");
                b = ioc_validar_entrada_double("Base (base > 0 e base != 1): ");
                sucesso = c_log_base_n(a, b, &resultado);
                if (sucesso) printf("Resultado: log_%.2f(%.2f) = %.4f\n", b, a, resultado);
                else printf("[ERRO] Condicoes do logaritmo (x>0, base>0, base!=1) nao atendidas.\n");
                ioc_adicionar_historico("Log N", a, b, sucesso ? resultado : NAN);
            } else { printf("[ERRO] Opcao invalida.\n"); }
        }
        else if (grupo == 4) { // TRIG/CONV
            printf(" 1. Seno (graus)       2. Cosseno (graus)\n 3. Tangente (graus) 4. Celsius para Fahrenheit\n 5. Fahrenheit para Celsius\n 0. Voltar\n");
            sub_escolha = ioc_validar_entrada_int("Escolha: ");
            if (sub_escolha == 0) return;

            if (sub_escolha >= 1 && sub_escolha <= 3) { // Trigonometria
                a = ioc_validar_entrada_double("Angulo em graus: ");
                if (sub_escolha == 1) { resultado = c_seno_graus(a); printf("Resultado: Sen(%.2f) = %.4f\n", a, resultado); ioc_adicionar_historico("Seno", a, 0.0, resultado); }
                else if (sub_escolha == 2) { resultado = c_cosseno_graus(a); printf("Resultado: Cos(%.2f) = %.4f\n", a, resultado); ioc_adicionar_historico("Cosseno", a, 0.0, resultado); }
                else if (sub_escolha == 3) { 
                    resultado = c_tangente_graus(a); 
                    if (resultado == DBL_MAX) printf("[ERRO] Tangente indefinida (90/270 graus).\n");
                    else printf("Resultado: Tan(%.2f) = %.4f\n", a, resultado); 
                    ioc_adicionar_historico("Tangente", a, 0.0, resultado);
                }
            } else if (sub_escolha == 4) { // C p/ F
                a = ioc_validar_entrada_double("Temperatura em Celsius: ");
                resultado = c_celsius_para_fahrenheit(a);
                printf("Resultado: %.2f C = %.2f F\n", a, resultado);
                ioc_adicionar_historico("C->F", a, 0.0, resultado);
            } else if (sub_escolha == 5) { // F p/ C
                a = ioc_validar_entrada_double("Temperatura em Fahrenheit: ");
                resultado = c_fahrenheit_para_celsius(a);
                printf("Resultado: %.2f F = %.2f C\n", a, resultado);
                ioc_adicionar_historico("F->C", a, 0.0, resultado);
            } else { printf("[ERRO] Opcao invalida.\n"); }
        }
        else if (grupo == 5) { // MATRIZES
            double A[MAX_N][MAX_N], B[MAX_N][MAX_N], C[MAX_N][MAX_N];
            int tamanho_matriz;
            printf(" 1. Soma Matrizes  2. Multiplicacao Matrizes\n 0. Voltar\n");
            sub_escolha = ioc_validar_entrada_int("Escolha: ");
            if (sub_escolha == 0) return;
            
            tamanho_matriz = ioc_validar_entrada_int("Tamanho da matriz (2 ou 3): ");
            if (tamanho_matriz != 2 && tamanho_matriz != 3) { printf("[ERRO] Tamanho invalido. Digite 2 ou 3.\n"); break; }
            ioc_pegar_dados_matriz(tamanho_matriz, A);
            ioc_pegar_dados_matriz(tamanho_matriz, B);

            if (sub_escolha == 1) { // Soma
                sucesso = c_soma_matrizes(tamanho_matriz, A, B, C);
                if (sucesso) { ioc_exibir_matriz(tamanho_matriz, C); ioc_adicionar_historico("Soma Matriz", (double)tamanho_matriz, (double)tamanho_matriz, C[0][0]); }
                else printf("[ERRO] Erro na soma de matrizes.\n");
            } else if (sub_escolha == 2) { // Multiplicação
                sucesso = c_multiplica_matrizes(tamanho_matriz, A, B, C);
                if (sucesso) { ioc_exibir_matriz(tamanho_matriz, C); ioc_adicionar_historico("Mult Matriz", (double)tamanho_matriz, (double)tamanho_matriz, C[0][0]); }
                else printf("[ERRO] Erro na multiplicacao de matrizes.\n");
            } else { printf("[ERRO] Opcao invalida.\n"); }
        }
        else if (grupo == 6) { // ESTATISTICA
            printf(" 1. Estatistica (Media/Mediana/Desvio)\n 2. Maximo/Minimo (Array)\n 3. MDC\n 0. Voltar\n");
            sub_escolha = ioc_validar_entrada_int("Escolha: ");
            if (sub_escolha == 0) return;

            if (sub_escolha == 1) { // Média/Mediana/Desvio
                int n_elementos = ioc_validar_entrada_int("Quantos elementos? (Max 10): ");
                if (n_elementos <= 0 || n_elementos > MAX_ESTATISTICA) { printf("[ERRO] Quantidade invalida.\n"); break; }
                double dados[MAX_ESTATISTICA];
                for (int i = 0; i < n_elementos; i++) { char prompt[50]; sprintf(prompt, "Elemento #%d: ", i + 1); dados[i] = ioc_validar_entrada_double(prompt); }
                double dados_ordenados[MAX_ESTATISTICA];
                memcpy(dados_ordenados, dados, n_elementos * sizeof(double));
                ioc_ordenar_array(dados_ordenados, n_elementos);
                double media, mediana, desvio;
                c_calcular_estatisticas(dados_ordenados, n_elementos, &media, &mediana, &desvio);
                printf("\nResultados: Media: %.4f | Mediana: %.4f | Desvio-P: %.4f\n", media, mediana, desvio);
                ioc_adicionar_historico("Estatistica", media, mediana, desvio);
            } else if (sub_escolha == 2) { // Max/Min
                int n_elementos = ioc_validar_entrada_int("Quantos elementos? (Max 10): ");
                if (n_elementos <= 0 || n_elementos > MAX_ESTATISTICA) { printf("[ERRO] Quantidade invalida.\n"); break; }
                double dados[MAX_ESTATISTICA];
                for (int i = 0; i < n_elementos; i++) { char prompt[50]; sprintf(prompt, "Elemento #%d: ", i + 1); dados[i] = ioc_validar_entrada_double(prompt); }
                double max = c_max_array(dados, n_elementos);
                double min = c_min_array(dados, n_elementos);
                printf("\nResultados: Maximo: %.4f | Minimo: %.4f\n", max, min);
                ioc_adicionar_historico("Max/Min", max, min, max);
            } else if (sub_escolha == 3) { // MDC
                int a_int = ioc_validar_entrada_int("Primeiro inteiro (a): ");
                int b_int = ioc_validar_entrada_int("Segundo inteiro (b): ");
                resultado = c_calcula_mdc(a_int, b_int);
                printf("Resultado: MDC(%d, %d) = %.0f\n", a_int, b_int, resultado);
                ioc_adicionar_historico("MDC", (double)a_int, (double)b_int, resultado);
            } else { printf("[ERRO] Opcao invalida.\n"); }
        }

        printf("\nPressione ENTER para continuar...");
        getchar();
    }
}

// --- Funcao Principal ---

int main() {
    int escolha;
    int executando = 1;

    while (executando) {
        ioc_limpar_tela();
        printf("===================================================\n");
        printf("         CALCULADORA MODULAR C (20+ FUNCOES)       \n");
        printf("===================================================\n");
        printf(" [1] BASICAS: Soma, Subtracao, Multiplicacao, Divisao\n");
        printf(" [2] POTENCIAS/RAIZES: Potencia, Raiz Quadrada, Raiz N, e^x\n");
        printf(" [3] LOGS/FATORIAL: Fatorial, Log Natural, Log Base N, Max/Min\n");
        printf(" [4] TRIG/CONV: Seno, Cosseno, Tangente (Graus), C<->F\n");
        printf(" [5] MATRIZES: Soma e Multiplicacao (2x2 ou 3x3)\n");
        printf(" [6] ESTATISTICA: Media, Mediana, Desvio Padrao, MDC\n");
        printf("---------------------------------------------------\n");
        printf(" [7] HISTORICO: Ver, Salvar, Carregar\n");
        printf(" [0] SAIR\n");
        printf("===================================================\n");
        
        escolha = ioc_validar_entrada_int("Escolha o grupo de operacoes: ");

        if (escolha >= 1 && escolha <= 6) {
            menu_secundario(escolha);
        } else if (escolha == 7) {
            printf(" 1. Listar Historico\n 2. Salvar (CSV)\n 3. Carregar (CSV)\n 0. Voltar\n");
            int sub_escolha = ioc_validar_entrada_int("Escolha: ");
            if (sub_escolha == 1) ioc_listar_historico();
            else if (sub_escolha == 2) ioc_salvar_historico_csv();
            else if (sub_escolha == 3) ioc_carregar_historico_csv();
            else if (sub_escolha != 0) printf("[ERRO] Opcao invalida.\n");
        } else if (escolha == 0) {
            printf("\nSaindo da calculadora. Ate mais!\n");
            executando = 0;
        } else {
            printf("\n[ERRO] Opcao invalida. Tente novamente.\n");
            printf("Pressione ENTER para continuar...");
            getchar();
        }
    }

    return 0;
}