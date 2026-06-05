#include <stdio.h>
#include <stdlib.h>

/* ==========================================================================
 * BLCO 1: IMPRESSÃO DO SUBSET
 * Objetivo: Exibir os elementos formatados exatamente como a 42 exige.
 * ========================================================================== */
void print_subset(int *subset, int size) {
    // Se o subset for vazio (ex: target 0), apenas pula a linha e encerra
    if (size == 0) {
        printf("\n");
        return;
    }
    
    // Loop para imprimir cada número do subconjunto atual
    for (int i = 0; i < size; i++) {
        // Regra de formatação: Se for o último elemento (i == size - 1), 
        // não coloca espaço depois dele (""). Caso contrário, coloca (" ").
        printf("%d%s", subset[i], (i == size - 1) ? "" : " ");
    }
    printf("\n"); // Quebra de linha obrigatória após listar o subset
}

/* ==========================================================================
 * BLOCO 2: O CORAÇÃO DO ALGORITMO (BACKTRACKING)
 * Objetivo: Tomar uma decisão binária (sim/não) para cada número do conjunto.
 * ========================================================================== */

/*
int *set, int set_size -> Mesa de trabalho, o array com os numeros que o usuario digitou

int index -> o ponteiro que aponta para o numero da mesa que estamos olhando

int *subset, int subset_size -> Nossa sacola, e quantos elementos colocamos nela até agora

int current_sum -> Nossa folha de papel com a soma acumulada dos numeros que colocamso na sacola

int target -> Alvo que temos que encontrar
*/

void backtrack(int *set, int set_size, int index, int *subset, int subset_size, int current_sum, int target) {
    
    // CASO BASE: Se o índice alcançou o tamanho do conjunto, processamos todos os números
    if (index == set_size) {
        // Checagem de sucesso: Se a soma acumulada atingiu o objetivo, imprime o caminho feito
        if (current_sum == target) {
            print_subset(subset, subset_size);
        }
        return; // Retorna para a chamada anterior (faz o "backtrack")
    }

    // DECISÃO 1: NÃO incluir o número atual (set[index]) no subconjunto
    // Apenas avançamos o 'index' para o próximo elemento. O resto continua igual.
    backtrack(set, set_size, index + 1, subset, subset_size, current_sum, target);

    // DECISÃO 2: SIM, incluir o número atual (set[index]) no subconjunto
    // 1º: Colocamos o número na posição livre atual do nosso subconjunto
    subset[subset_size] = set[index];
    
    // 2º: Chamamos a recursão avançando o 'index', aumentando o tamanho do subset ocupado (+1)
    //     e somando o valor do número atual à nossa 'current_sum'.
    backtrack(set, set_size, index + 1, subset, subset_size + 1, current_sum + set[index], target);
    
    // Nota de estudo: Não precisamos "limpar" o array subset na volta, porque 
    // a Decision 2 das próximas execuções vai simplesmente sobrescrever o valor.
}

/* ==========================================================================
 * BLOCO 3: BUROCRACIA E TRATAMENTO DE INPUT (MAIN)
 * Objetivo: Validar os argumentos do terminal e preparar a memória.
 * ========================================================================== */
int main(int argc, char **argv) {
    
    // 1. Validação de segurança: Se o programa rodar sem argumentos (ex: só ./powerset)
    if (argc < 2) {
        return 1; // ExamShell exige código de erro (1) aqui
    }

    // 2. Regra específica da 42: Se o Target (argv[1]) for exatamente "0"
    // O subset vazio sempre soma 0. Imprime nova linha e finaliza com sucesso (0).
    if (argv[1][0] == '0' && argv[1][1] == '\0') {
        printf("\n");
        return 0;
    }

    // 3. Mapeamento de dados da linha de comando
    int target = atoi(argv[1]);   // O primeiro argumento após o programa é o Target
    int set_size = argc - 2;      // Total de argumentos menos o programa e o target

    // 4. Validação do conjunto: Se passaram o target mas nenhum número (ex: ./powerset 5)
    if (set_size <= 0) {
        return 1; // Falha
    }

    // 5. Alocação Dinâmica para os arrays ('set' original e o 'subset' auxiliar)
    int *set = malloc(sizeof(int) * set_size);
    int *subset = malloc(sizeof(int) * set_size);
    
    // Proteção de memória do malloc
    if (!set || !subset) {
        free(set);
        free(subset);
        return 1;
    }

    // 6. Conversão de Strings para Inteiros
    // Preenchemos nosso array 'set'. Os números começam a partir do argv[2].
    for (int i = 0; i < set_size; i++) {
        set[i] = atoi(argv[i + 2]);
    }

    // 7. O Chute Inicial
    // Iniciamos no índice 0, com tamanho de subset 0 e soma acumulada 0.
    backtrack(set, set_size, 0, subset, 0, 0, target);

    // 8. Limpeza de Memória Obrigatória
    free(set);
    free(subset);
    return 0;
}