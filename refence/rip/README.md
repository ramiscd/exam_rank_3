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

---

O segredo para entender esse bloco de código é mudar o nome das variáveis na sua mente:

abre = Abertos Esperando Par

fecha = Fechados Órfãos (que fecharam sem ninguém ter aberto antes)

A Analogia do Salão de Dança 🕺💃
Imagine que os parênteses são pessoas entrando num salão de dança, uma por uma.

Cada ( é uma pessoa que entra e fica esperando alguém para fazer par (abre++).

Cada ) é uma pessoa procurando um par.

Quando um ) entra no salão, ele olha em volta:

Tem alguém esperando? (if (abre > 0)): Ótimo! Eles dão as mãos e vão dançar. A pessoa que estava esperando sai da fila (abre--). Eles estão resolvidos e não precisamos removê-los!

O salão está vazio? (else): Que pena. Esse ) entrou sem ter ninguém para ele. Ele é um órfão excedente que terá que ir embora. Anotamos ele na nossa lista de rejeitados (fecha++).

No fim da festa, quem sobrou?

As pessoas que ficaram esperando para sempre (abre).

As pessoas que entraram sem ter ninguém lá (fecha).
A soma dos dois é exatamente quem precisamos expulsar da festa (total_remover).

---
Essa é a função do "Juiz". A beleza dela está justamente na simplicidade: ela resolve um problema clássico de programação usando apenas um único número inteiro (balanco).

Para garantir que você nunca mais esqueça como ela funciona, vamos usar a Analogia do Elevador 🏢.

A Analogia do Elevador
Imagine que a variável balanco é o andar onde um elevador está. O elevador começa a trabalhar sempre no andar térreo (andar 0).

Cada vez que ele lê um (, é um comando para Subir 1 andar (balanco++).

Cada vez que ele lê um ), é um comando para Descer 1 andar (balanco--).

Para que o trajeto do elevador seja considerado Válido, ele precisa obedecer a duas regras de segurança rigorosas:

A Regra do Subsolo (if balanco < 0): O prédio não tem subsolo! Se em qualquer momento o elevador tentar descer abaixo do andar 0 (ficar negativo), ele bate no chão e quebra. Retorna 0 (Falso/Inválido) na hora.

A Regra do Expediente (return balanco == 0): No fim da palavra (fim do dia), o elevador tem que estar estacionado de volta no andar térreo (0). Se ele terminar o dia parado no andar 2 (ou seja, sobraram ( abertos), o trajeto é inválido.

Dissecando o Código Linha por Linha

```c
int esta_valido(char *s) {
    int balanco = 0;                 // O elevador começa no Térreo (0).
    
    for (int i = 0; s[i]; i++) {     // Caminha por cada letra da string
        
        if (s[i] == '(') balanco++;  // Subir!
        
        if (s[i] == ')') balanco--;  // Descer!
        
        if (balanco < 0) return 0;   // Bateu no subsolo? Quebrou! (Falso)
    }
    
    return (balanco == 0);           // Terminou no Térreo? (Retorna 1 se sim, 0 se não)
}
```

💡 O Segredo Escondido: O que acontece com os espaços?
No seu algoritmo de backtracking, você substitui os parênteses que quer remover por espaços em branco ' '.
Como essa função lida com o espaço? Ela simplesmente o ignora! O for passa pelo espaço, olha o primeiro if (não é (), olha o segundo if (não é )), não faz nada com o balanco, e vai para a próxima letra. É exatamente isso que queremos: que os espaços não interfiram na validação.

---

Chegamos ao "chefão" do seu código! Essa é a parte que mais assusta, porque a recursão com backtracking não segue uma linha reta; ela vai e volta no tempo.

Para visualizar essa função na sua cabeça durante a prova, não pense nela como um código sendo lido de cima para baixo. Pense nela como **O Explorador de Multiversos** 🌌.

Você tem apenas **uma única fita de fita cassete** (a sua string na memória do computador). Para explorar diferentes futuros sem destruir a fita, o explorador precisa gravar uma mudança, ver o que acontece no futuro e, quando voltar, **desfazer a mudança** para testar outra realidade.

Aqui está a anatomia detalhada desse explorador, dividida em 4 blocos visuais:

---

### 1. O Freio de Emergência (A Poda)

```c
if (removidos > alvo_remocoes) return;

```

A primeira coisa que o explorador faz ao entrar numa nova realidade é checar a mochila. "Já removi mais parênteses do que a cota que a `main` me deu?". Se a resposta for sim, esse universo está condenado. Ele dá um `return` imediato (aborta a missão) para não perder tempo processando algo inútil.

### 2. A Linha de Chegada

```c
if (s[indice] == '\0') {
    if (removidos == alvo_remocoes && esta_valido(s)) {
        write(1, s, str_len(s));
        write(1, "\n", 1);
    }
    return;
}

```

Se o índice bateu no `\0`, a palavra acabou. É hora de cobrar a conta:

* Removemos exatamente a quantidade pedida? (`removidos == alvo_remocoes`)
* O que sobrou faz sentido matemático? (`esta_valido(s)`)

Se as duas coisas forem verdade, **BINGO!** Ele imprime a string no estado atual dela e dá `return` para voltar no tempo e procurar outras soluções.

### 3. A Máquina do Tempo (O Backtracking Puro)

```c
if (s[indice] == '(' || s[indice] == ')') {
    char original = s[indice];    // PASSO A: Salva a letra original na manga
    
    s[indice] = ' ';              // PASSO B: Apaga a letra (Cria o Universo 1)
    resolver(s, indice + 1, removidos + 1, alvo_remocoes); // PASSO C: Viaja pro futuro
    
    s[indice] = original;         // PASSO D: DE VOLTA PRO PASSADO! Restaura a letra.
}

```

Aqui está o coração do algoritmo. Vamos olhar bem de perto:

* **Passo A:** O explorador guarda a letra atual (ex: `(`) no bolso (`char original`).
* **Passo B:** Ele coloca um espaço vazio no lugar. Ele literalmente modifica a string oficial.
* **Passo C:** Ele entra no portal! Chama a função `resolver` de novo, avançando o índice e dizendo "Ei, acabei de remover mais um". O programa vai rodar todas as possibilidades desse futuro até esgotá-las.
* **Passo D (O segredo do Backtracking):** Quando o programa finalmente sai do Passo C, significa que ele explorou tudo o que dava com aquele parêntese apagado. Agora ele precisa testar a Opção 2 (manter o parêntese). Mas a string está com um espaço vazio! É por isso que ele **restaura** o `original` no lugar. Sem o Passo D, a sua string seria destruída logo na primeira tentativa.

### 4. O Universo Paralelo (A Escolha de Manter)

```c
resolver(s, indice + 1, removidos, alvo_remocoes);

```

Esse código fica solto no final. Perceba que ele ocorre **depois** que o caractere foi restaurado.
Ele diz: *"Beleza, já vi o que acontece se eu apagar essa letra. Agora, vamos ver o que acontece no futuro se eu simplesmente pular ela e deixar ela quietinha aí."* Ele avança o índice, mas **não** aumenta os `removidos`.

---

## 👁️ Visualizando a Memória C no Microscópio

Vamos pegar uma string minúscula: `)(` com `alvo = 2`.
Acompanhe como a variável `s` (a string física na memória) muda em tempo real:

| Passo | Ação do Algoritmo | Estado Real de `s` na Memória | Índice | Removidos |
| --- | --- | --- | --- | --- |
| **Início** | Começamos na primeira letra. | `)(` | `0` | `0` |
| **Opção 1** | Apaga a primeira letra (`s[0] = ' '`). Viaja. | ` (` | `1` | `1` |
| **Opção 1** | Chega na segunda letra. Apaga ela (`s[1] = ' '`). Viaja. | `  ` | `2` | `2` |
| **Chegada** | Bateu no `\0`. Alvo é 2. É válido? SIM! Imprime. | `  ` | `2` | `2` |
| **Volta** | Volta para desfazer a Opção 1 da segunda letra. | ` (` | `1` | `1` |
| **Opção 2** | Mantém a segunda letra intacta. Viaja. | ` (` | `2` | `1` |
| **Chegada** | Bateu no `\0`. Alvo era 2, mas só removeu 1. Inválido. | ` (` | `2` | `1` |
| **Volta** | Volta TUDO lá pro começo para desfazer a primeira letra! | `)(` | `0` | `0` |
| **Opção 2** | Mantém a primeira letra intacta. Viaja. | `)(` | `1` | `0` |

Consegue perceber como o `s[indice] = original` faz a string "respirar", se expandindo em espaços vazios e voltando a ser a palavra original repetidas vezes?
