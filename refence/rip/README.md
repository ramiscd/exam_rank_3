# 📖 README: Remove Invalid Parentheses (RIP)

## 🎯 1. O Que o Exercício Faz?

O objetivo deste algoritmo é pegar uma string de parênteses que está desbalanceada (ou seja, com parênteses sobrando ou faltando pares) e encontrar **todas as combinações válidas possíveis** removendo o **menor número possível** de parênteses.

**Exemplo:**

* **Entrada:** `())(`
* **Problema:** O segundo `)` não tem par, e o último `(` nunca fecha. Total a remover = 2.
* **Saída esperada:** `()` (removendo o `)` extra e o `(` extra).

---

## 🧠 2. A Lógica em Alto Nível (A "Sacada")

Em vez de tentar remover parênteses aleatoriamente e ver se dá certo, o código segue um plano cirúrgico em duas fases principais:

1. **A Fase Matemática (Na `main`):** Antes de tentar qualquer coisa, o código faz uma varredura na string para descobrir **exatamente** quantos parênteses estão sobrando. Isso é brilhante porque nos dá um "alvo". Se sabemos que só precisamos remover 1 parêntese, não vamos perder tempo testando caminhos que removem 2, 3 ou 0.
2. **A Fase de Busca (Backtracking):** Sabendo nosso alvo (ex: remover 1), o algoritmo caminha pela string. Para cada parêntese que encontra, ele abre dois universos paralelos (ramos): num universo, ele apaga o parêntese; no outro, ele o mantém. Ele faz isso até o final da string. Se ao final ele removeu exatamente o alvo e a string ficou balanceada, ele imprime o resultado.

---

## 🔄 3. O Fluxo de Dados e Variáveis

### Variáveis Globais de Estado (Por Função)

| Função | Variável | Descrição Didática |
| --- | --- | --- |
| `esta_valido` | `balanco` | Funciona como uma balança de pratos. `(` coloca peso, `)` tira peso. Se a balança ficar negativa, afundou (inválido). No fim, tem que estar em `0`. |
| `main` | `abre` | Conta quantos `(` estão abertos e aguardando um parceiro. |
| `main` | `fecha` | Conta os `)` "órfãos", ou seja, aqueles que apareceram sem nenhum `(` anterior para fazer par. |
| `main` | `total_remover` | O número mágico! É a soma de `abre + fecha`. Define a cota exata de remoções permitidas. |
| `resolver` | `indice` | O "dedo" que aponta para qual letra da string estamos olhando agora. |
| `resolver` | `removidos` | O contador de quantas remoções já fizemos no caminho atual. |
| `resolver` | `alvo_remocoes` | A cota máxima que não pode ser ultrapassada (passada da `main`). |

---

## 🔍 4. Dissecando as Funções

### A. `str_len` e `esta_valido` (Os Ajudantes)

* **`str_len`:** Apenas mede a string para a função `write` saber quantos bytes imprimir.
* **`esta_valido`:** É o "juiz". Ele ignora espaços (que representam parênteses deletados) e varre a string somando e subtraindo.
* *Regra de ouro:* Um `)` **nunca** pode aparecer se o saldo for zero. Se isso ocorrer, `balanco` fica negativo e a função aborta retornando `0` (Falso).



### B. `main` (O Estrategista)

A grande sacada matemática está no `for`:

```c
if (str[i] == '(') abre++;
else if (str[i] == ')') {
    if (abre > 0) abre--; // Casou! Cancela um 'abre'
    else fecha++;         // Viúvo! Não tinha '(' para ele. Sobrou.
}

```

Isso garante que só vamos acionar o processo pesado (backtracking) sabendo o limite exato.

### C. `resolver` (O Trabalhador Braçal - Backtracking)

Esta é a joia da coroa. Vamos dividi-la em 4 blocos de lógica:

1. **A Poda (Otimização extrema):** `if (removidos > alvo_remocoes) return;`
Se a cota era remover 1, e já removemos 2, aborta imediatamente. Não gaste processamento.
2. **A Condição de Parada (Fim da Linha):** `if (s[indice] == '\0')`
Chegamos ao final da palavra. É hora de checar: Conseguimos remover o número exato pedido? A palavra ficou válida? Se sim para ambos, imprime. Retorna para fechar esse ramo da árvore.
3. **A Bifurcação (O "E Se?"):**
Aqui é onde a mágica acontece para cada parêntese:
* **Opção 1 (Apagar):** Trocamos a letra por `' '`. Chamamos a função de novo, avançando o `indice` e somando `1` nos `removidos`.
* **O Resgate (Backtracking puro):** Depois que a Opção 1 termina de explorar todas as suas possibilidades futuras, *precisamos desfazer a alteração* (`s[indice] = original`). Se não fizermos isso, a string original ficará destruída para as próximas tentativas.


4. **Opção 2 (Manter):**
Com o caractere restaurado, chamamos a função novamente, avançando o `indice`, mas **sem** aumentar os `removidos`.

---

## 🌳 5. Visualização do Backtracking

Para entender como as bifurcações funcionam, imagine o teste de mesa para a string curta `"())"`.

* A `main` descobre que há um `)` sobrando. **`total_remover = 1`**.
* Começamos no `indice = 0`.

Veja a árvore de decisões que a recursão cria:

```text
                            INÍCIO: "())"
                            Indice: 0, Removidos: 0, Alvo: 1
                                  |
                   Indice 0 é '('. Duas escolhas:
                                  |
              /----------------------------------------\
    ESCOLHA 1: REMOVE                          ESCOLHA 2: MANTÉM
    String: " ))"  <-- VOCÊ ESTAVA CERTO       String: "())"
    Rem: 1, Ind: 1                             Rem: 0, Ind: 1
          |                                          |
    Indice 1 é ')'.                            Indice 1 é ')'.
    /-------------\                            /-------------\
REMOVE          MANTÉM                     REMOVE          MANTÉM
"  )"           " ))"                      "( )"           "())"
Rem: 2 (PODA)   Rem: 1, Ind: 2             Rem: 1, Ind: 2  Rem: 0, Ind: 2
(Passou alvo)         |                          |               |
                Indice 2 é ')'.            Indice 2 é ')'. Indice 2 é ')'.
                /-----------\              /-----------\   /-----------\
            REMOVE         MANTÉM      REMOVE       MANTÉM REMOVE       MANTÉM
            "   "          " ))"       "(  )"       "( )"  "() "        "())"
            Rem: 2 (PODA)  FIM         Rem: 2(PODA) FIM    FIM          FIM
                           Inválido                 VÁLIDO VÁLIDO       Inválido
                                                    Imprime Imprime
```

**Por que imprime duas vezes?**
Porque no primeiro ramo válido ele deletou o primeiro `)`, gerando `" ()"`. No segundo ramo válido ele manteve o primeiro `)` mas deletou o segundo `)`, gerando `"( )"`. Visualmente parecem iguais, mas estruturalmente o código os tratou como elementos diferentes.
