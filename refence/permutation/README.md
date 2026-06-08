# 📖 Guia Definitivo: Permutações com Backtracking e Array de Estado

Este documento destrincha o algoritmo de permutações exigido na prova da 42, utilizando a abordagem de **Backtracking com Array de Estado**. Esta é a solução mais segura, limpa e menos propensa a erros de índice (*Segfault*).

## 1. Entendendo o Problema

**O Objetivo:** Dada uma string (ex: `"abc"`), imprimir todas as suas combinações possíveis.
**A Regra de Ouro:** As combinações **devem** ser impressas em rigorosa ordem alfabética.
**A Matemática:** O número de combinações de uma string de tamanho $n$ (sem letras repetidas) é dado pelo seu fatorial ($n!$).

* `"ab"` -> $2! = 2 \times 1 = 2$ combinações (`ab`, `ba`).
* `"abc"` -> $3! = 3 \times 2 \times 1 = 6$ combinações.

## 2. A Analogia do Tabuleiro de Scrabble

Para entender como o código funciona, esqueça a programação por um minuto.
Imagine que você tem **3 peças de madeira** (A, B, C) e um **tabuleiro com 3 espaços vazios** `[ ] [ ] [ ]`. Você precisa formar todas as palavras possíveis, em ordem alfabética.

1. **Ordem Inicial:** Você sempre olha as peças da esquerda para a direita na mesa. Logo, você primeiro garante que elas estão ordenadas: `A, B, C`.
2. **Escolha:** Você pega a primeira peça disponível (A) e coloca no primeiro espaço: `[A] [ ] [ ]`.
3. **Mergulho:** Agora você foca no próximo espaço. As peças na mesa são B e C. Você pega a primeira disponível (B): `[A] [B] [ ]`.
4. **Fundo do Poço:** Sobrou a C. `[A] [B] [C]`. O tabuleiro está cheio! Você anota a palavra e **desfaz o último passo**.
5. **Backtrack (O Retorno):** Você tira o C. Tenta colocar outra no lugar, mas não há mais opções. Você tira o B. A mesa agora tem B e C. Você tenta a próxima disponível (C): `[A] [C] [ ]`. E coloca o B no final: `[A] [C] [B]`.

O seu programa fará exatamente isso: ele preenche um "tabuleiro" (`res`), usando um "bloco de notas" (`used`) para lembrar quais peças já foram usadas.

## 3. O Fluxo de Dados na Memória (Diagrama)

Aqui está o que acontece com as variáveis quando tentamos permutar `"abc"`:

* `str`: `"abc"` (Nossas peças na mesa, intocáveis)
* `res`: `[ ][ ][ ]` (Nosso tabuleiro)
* `used`: `[0][0][0]` (0 = livre, 1 = no tabuleiro)

### Passo a Passo da Execução (Árvore de Decisões)

```text
NÍVEL 0 (Preenchendo res[0])
├─ Tenta 'a' (used[0] = livre)
│  ├─ Marca used[0]=1 ─> res = "a_ _"
│  │
│  NÍVEL 1 (Preenchendo res[1])
│  ├─ Tenta 'a' (PULA, used[0] é 1)
│  ├─ Tenta 'b' (used[1] = livre)
│  │  ├─ Marca used[1]=1 ─> res = "ab_"
│  │  │
│  │  NÍVEL 2 (Preenchendo res[2])
│  │  ├─ Tenta 'a' (PULA)
│  │  ├─ Tenta 'b' (PULA)
│  │  ├─ Tenta 'c' (used[2] = livre)
│  │  │  ├─ Marca used[2]=1 ─> res = "abc"
│  │  │  │  IMPRIME "abc"
│  │  │  └─ Desmarca used[2]=0 (Backtrack)
│  │  │
│  │  └─ Desmarca used[1]=0 (Backtrack) ─> res volta a ser "a_ _"
│  │
│  └─ Tenta 'c' (used[2] = livre)
│     ├─ Marca used[2]=1 ─> res = "ac_"
│     └─ ... e a lógica se repete para gerar "acb"

```

---

## 4. Dissecando o Código (Linha a Linha)

### 4.1. A Estrutura de Ordenação

Não podemos confiar que o usuário passará a string ordenada. Antes de permutar, precisamos de um *Selection Sort* simples para garantir que nossa base inicie correta.

```c
void    sort_str(char *str, int len)
{
    int     i = 0;
    int     j;
    char    tmp;

    while (i < len - 1)
    {
        j = i + 1; // j sempre compara com o próximo elemento
        while (j < len)
        {
            if (str[i] > str[j]) // Se a letra da esquerda for "maior" (ex: z > a)
            {
                // Troca básica (Swap)
                tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

```

### 4.2. O Coração do Algoritmo: A Função `solve`

Esta é a função recursiva. Entenda os parâmetros:

* `char *str`: As letras originais ordenadas.
* `char *res`: A nova string que estamos construindo.
* `int *used`: O array de zeros e uns indicando quem está em uso.
* `int pos`: Qual índice de `res` estamos tentando preencher agora.
* `int len`: O tamanho total da palavra.

```c
void    solve(char *str, char *res, int *used, int pos, int len)
{
    int i;

    // CONDIÇÃO DE PARADA (BASE CASE)
    // Se a posição atual for igual ao tamanho da string, enchemos o tabuleiro!
    if (pos == len)
    {
        write(1, res, len); // Imprime a palavra montada
        write(1, "\n", 1);  // Quebra a linha
        return ;            // Fim desta linha temporal, retorna para o passo anterior
    }
    
    i = 0;
    // Tenta encaixar cada uma das letras originais na posição 'pos'
    while (i < len)
    {
        // Só usamos a letra se ela estiver livre (used == 0)
        if (used[i] == 0)
        {
            // 1. AÇÃO (Take)
            used[i] = 1;           // Anota: "Peguei a letra 'i'"
            res[pos] = str[i];     // Coloca a letra no tabuleiro

            // 2. RECURSÃO (Explore)
            // Congela tudo e chama a função para preencher a PRÓXIMA casa (pos + 1)
            solve(str, res, used, pos + 1, len);

            // 3. BACKTRACK (Undo)
            // A recursão acima terminou. A palavra foi impressa. 
            // Precisamos devolver a letra para a mesa para tentar as próximas.
            used[i] = 0;           // Anota: "Letra 'i' está livre de novo"
        }
        i++;
    }
}

```

> **Ponto Didático Importante:** Veja que nós **não apagamos** `res[pos]`. Não precisamos. O `used[i] = 0` é suficiente, pois na próxima iteração do loop, quando escolhermos outra letra livre, ela simplesmente vai sobrescrever o que estava em `res[pos]`.

### 4.3. A Preparação: Função `main`

A `main` cuida dos preparativos: conferir os argumentos, descobrir o tamanho, ordenar e criar os espaços de memória.

```c
int main(int argc, char **argv)
{
    char    res[255];   // Define um limite seguro para palavras grandes
    int     used[255];  // Mesmo tamanho para mapear o uso
    int     len;
    int     i;

    // Tratamento de erro (o seu ajuste vital)
    if (argc != 2)
        return (1);
        
    // ft_strlen embutido
    len = 0;
    while (argv[1][len])
        len++;
        
    // Garante que "cba" vire "abc" antes da mágica começar
    sort_str(argv[1], len);
    
    // Zera explicitamente o array de 'used' para evitar lixo de memória
    i = 0;
    while (i < len)
    {
        used[i] = 0;
        i++;
    }
    
    // O gatilho: inicia na posição 0 do tabuleiro
    solve(argv[1], res, used, 0, len);
    
    return (0);
}

```

---

## 5. Resumo Tático (O que lembrar na hora do exame)

Quando você abrir o terminal branco da prova, siga este checklist mental:

1. **A infraestrutura:** Comece escrevendo a `main`. Trate o erro (`argc != 2`), conte o `len`, declare um `char res[255]` e um `int used[255]`. Zere o array `used` com um `while`.
2. **A ordem:** Crie o `sort_str`. É um loop duplo de `while` com um `if (str[i] > str[j])` dentro. Troca simples com variável auxiliar `tmp`.
3. **A recursão em 3 atos:** Na função `solve`, lembre do padrão sagrado do Backtracking dentro do bloco `if (used[i] == 0)`:
* **Marca:** `used[i] = 1; res[pos] = str[i];`
* **Mergulha:** `solve(..., pos + 1, ...);`
* **Desmarca:** `used[i] = 0;`