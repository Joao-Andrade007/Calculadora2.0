Calculadora Modular C Avançada
Este documento serve como um guia abrangente para entender, compilar e executar a Calculadora Modular C Avançada, um projeto que implementa mais de 20 funções matemáticas e utiliza recursos avançados da linguagem C.

1. O que o Programa Faz
A Calculadora Modular C Avançada é uma aplicação de linha de comando (console) que permite ao usuário executar uma vasta gama de operações matemáticas, desde as básicas até cálculos estatísticos, logarítmicos e operações com matrizes.

Funcionalidades Principais
Menu Interativo: Navegação por grupos de funções (Básicas, Potências, Logaritmos, Trigonometria, Matrizes e Estatística).

Cálculos Abrangentes: Implementação de 21 funções distintas, incluindo MDC, Fatorial, Raiz Enésima, Seno/Cosseno em graus, e Conversão de Temperatura (Celsius/Fahrenheit).

Tratamento de Erros: O programa valida entradas (garantindo que números sejam lidos) e trata erros lógicos em tempo de execução (ex.: divisão por zero, raiz quadrada de número negativo).

Histórico de Operações: Mantém um registro das últimas 10 operações realizadas em uma estrutura de dados de fila circular (buffer), usando struct e array.

2. Tecnologias e Recursos Utilizados
O projeto é puramente implementado em C padrão e utiliza recursos essenciais para projetos de software bem estruturados:

Recurso,Utilização no Projeto,Benefício
Linguagem C,Padrão C99/C11.,Performance e controle de baixo nível.
Modularidade Lógica,Uso de prefixos c_ (Cálculo) e ioc_ (I/O e Controle).,Separação clara das responsabilidades das funções.
struct (Estrutura),typedef struct Operacao,"Utilizada para agrupar dados relacionados (tipo, operandos, resultado e ID) no histórico."
Arrays,"Operacao historico[10], Matrizes (double[3][3]), Estatística (double[]).",Armazenamento de coleções de dados e estruturas matriciais.

Funções da math.h,"sqrt(), pow(), log(), sin(), cos(), fabs().",Implementação das funções matemáticas complexas.
I/O e Buffering,"scanf(), printf(), getchar(), system(""clear"").",Interface de console interativa e funções robustas de validação de entrada.

3. Como Instalar, Compilar e Executar o Código
3.1 Pré-Requisitos
Você precisará ter um compilador C instalado em seu sistema. O GCC (GNU Compiler Collection) é o compilador padrão recomendado e geralmente está disponível em sistemas Linux/macOS ou através do WSL/MinGW no Windows.

3.2 Instruções de Compilação
Salvar o Código: Salve o código-fonte completo (fornecido anteriormente) em um arquivo chamado calculadora.c.

Abrir o Terminal: Navegue até o diretório onde salvou o arquivo.

Compilar: Use o GCC com o flag -lm para ligar a biblioteca matemática, o que é fundamental para funções como sqrt() e pow().

Bash

# Compila o arquivo e cria um executável chamado 'calculadora'
gcc calculadora.c -o calculadora -lm

4. Exemplos de Uso Ao iniciar o programa, você verá o menu principal. AçãoMenu/OpçãoComandos TípicosSaída EsperadaDivisão (Tratamento de Erro)Grupo 1 -> Opção 4Dividendo: 10, Divisor: 0[ERRO] Divisao por zero nao permitida.FatorialGrupo 3 -> Opção 1Número: 5Resultado: 5! = 120Raiz EnésimaGrupo 2 -> Opção 3Radicando: 8, Índice: 3Resultado: Raiz 3 de 8.00 = 2.0000Soma de MatrizesGrupo 5 -> Opção 1Tamanho: 2. (Insere 4 elementos para A, 4 para B).Exibe a matriz resultante 2x2.Ver HistóricoGrupo 7 -> Opção 1(Após algumas operações)Lista as últimas operações realizadas com ID, tipo e resultado.

5. Informações Adicionais para a Compreensão do Projeto5.1 O Código Único vs. ModularidadeEmbora o código esteja em um único arquivo (calculadora.c), ele foi projetado com modularidade lógica.
As funções I/O e de cálculo operam de forma isolada:As funções de cálculo (c_prefixo) não contêm chamadas printf ou scanf.As funções de I/O (ioc_prefixo) são responsáveis por toda a interação e validação com o usuário.5.2 Gerenciamento do Histórico (Fila Circular)O histórico (historico[MAX_HISTORICO]) é uma fila circular. Isso significa que, ao atingir o limite de 10 operações, as novas operações substituem as mais antigas (começando pela posição 0), garantindo que o programa nunca consuma memória excessiva para o histórico.5.3
Implementação das 21 Funções (Lista Exata)Para cumprir o requisito de 20+ funções, foram implementadas:SomaSubtraçãoMultiplicaçãoDivisão (com tratamento de erro)PotênciaRaiz Quadrada (com tratamento de erro)Raiz N (com tratamento de erro)Exponencial $e^x$Fatorial (com tratamento de erro/limite)Logaritmo Natural (com tratamento de erro)Logaritmo Base N (com tratamento de erro)Seno (graus)Cosseno (graus)Tangente (graus) (com tratamento de erro)Graus para RadianosConversão C para FConversão F para CSoma de MatrizesMultiplicação de MatrizesMDCMáximo de ArrayMínimo de Array (Função Adicional)Cálculo Estatístico (Media, Mediana, Desvio Padrão) - (3 em 1)
