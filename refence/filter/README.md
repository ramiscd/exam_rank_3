# 42 `filter` — guia de estudo

Este documento é um compilado da conversa sobre o exercício `filter` da 42. A ideia é servir como revisão rápida, referência de implementação e apoio para entender o fluxo completo do programa.

## Objetivo do exercício

O programa recebe exatamente um argumento e lê tudo da `stdin`. Depois imprime o conteúdo lido em `stdout`, substituindo toda ocorrência do padrão informado por `*` repetido no mesmo tamanho do padrão.

Exemplo:

```bash
./filter abc
```

Entrada:

```txt
xxabcyy
```

Saída:

```txt
xx***yy
```

## Ideia principal

O exercício tem duas partes:

1. Ler todo o conteúdo da `stdin` e guardar em memória.
2. Percorrer esse conteúdo procurando o padrão e escrevendo a saída.

A abordagem mais simples para a prova é:

```txt
stdin inteira
  ↓
buffer dinâmico
  ↓
procura do padrão
  ↓
saída final
```

## Conceitos importantes

### `tmp` buffer

`tmp` é um buffer temporário usado em cada chamada de `read()`.

Ele recebe apenas o bloco atual lido do `stdin`.

Exemplo:

* primeira leitura: `abc`
* segunda leitura: `def`

O conteúdo do `tmp` é sobrescrito a cada iteração.

### `buffer` acumulado

`buffer` é o texto final guardado na heap.

Ele cresce dinamicamente com `realloc()` para guardar todo o conteúdo lido até o momento.

### `bytes`

Quantidade de bytes retornada por cada `read()`.

### `len`

Tamanho atual do conteúdo acumulado em `buffer`.

### `cur`

Cursor de leitura usado na função de substituição.

Ele indica a posição atual na varredura do texto.

### `match`

Ponteiro para a posição onde o padrão foi encontrado.

### `pattern`

String recebida como argumento que será procurada no texto.

---

## Fluxo mental da solução

### 1. Validar argumentos

O programa deve receber exatamente um argumento, e esse argumento não pode estar vazio.

### 2. Ler toda a entrada

O programa lê a `stdin` em blocos, acumula tudo em um buffer dinâmico e garante `\0` no final.

### 3. Procurar e substituir

O programa percorre o buffer final da esquerda para a direita.

Sempre que encontra o padrão:

* escreve o texto antes do match
* escreve `*` repetido no tamanho do padrão
* pula o padrão encontrado
* continua a busca

No final, escreve o restante do texto.

---

## Leitura da stdin

### O que acontece

A função `read_all_stdin()` faz o seguinte:

```txt
buffer = vazio
len = 0

enquanto read ainda retornar dados:
    lê um pedaço para tmp
    aumenta o buffer com realloc
    copia tmp para o final de buffer
    atualiza len
    coloca '\0'

retorna buffer completo
```

### Linha importante

```c
while ((bytes = read(0, tmp, BUF_SIZE)) > 0)
```

Significa:

* tenta ler do `stdin`
* guarda a quantidade lida em `bytes`
* continua enquanto houver dados

### Crescimento do buffer

```c
char *new_buf = realloc(buffer, len + bytes + 1);
```

Aqui o buffer final cresce para caber:

* o conteúdo antigo
* os novos bytes
* o `\0` final

### Cópia para o final

```c
memmove(buffer + len, tmp, bytes);
```

Copia o conteúdo recém-lido para o final do buffer acumulado.

### Finalização da string

```c
buffer[len] = '\0';
```

Garante que o conteúdo acumulado vire uma string C válida.

---

## Substituição do padrão

### O que acontece

A função `replace_pattern()` faz o seguinte:

```txt
cur = buffer

while encontrar pattern em cur:
    escrever antes do match
    escrever "***"
    pular pattern
    atualizar cur

escrever resto final
```

### Busca do padrão

```c
while ((match = memmem(cur, strlen(cur), pattern, len)))
```

* procura `pattern` dentro do texto a partir de `cur`
* se encontrar, retorna o endereço do match
* se não encontrar, retorna `NULL`

### Escrever antes do match

```c
write(1, cur, match - cur);
```

Escreve tudo que existe entre o cursor atual e o início da ocorrência encontrada.

### Escrever a substituição

A substituição deve ser `*` repetido no tamanho do padrão.

Uma função auxiliar como `write_stars()` facilita isso.

### Avançar o cursor

```c
cur = match + len;
```

O cursor pula exatamente o tamanho do padrão encontrado e continua a busca depois dele.

### Escrever o resto final

Quando não existe mais match:

```c
write(1, cur, strlen(cur));
```

Escreve o restante do texto até o final.

---

## Funções principais

### `validate_args`

```txt
verifica se o programa foi chamado com exatamente um argumento válido
```

Resumo mental:

```txt
se a chamada estiver errada, retorna erro
```

### `read_all_stdin`

```txt
lê todo o stdin em blocos e acumula tudo em um buffer dinâmico
```

Resumo mental:

```txt
transforma stream em string completa
```

### `write_stars`

```txt
imprime uma quantidade de '*' igual ao tamanho do padrão
```

Resumo mental:

```txt
gera a substituição
```

### `replace_pattern`

```txt
varre o texto procurando o padrão e escreve a saída já substituída
```

Resumo mental:

```txt
cur = buffer
while encontrar pattern em cur:
    escrever antes do match
    escrever "***"
    pular pattern
    atualizar cur
escrever resto final
```

---

## Código com significado das variáveis

```c
char *read_all_stdin(void)
{
	char tmp[BUF_SIZE];     // buffer temporário: recebe cada bloco lido pelo read()
	char *buffer = NULL;    // buffer final: acumula todo o conteúdo do stdin
	int bytes;              // quantidade de bytes lidos em cada iteração
	int len = 0;            // tamanho atual do buffer acumulado
```

```c
void replace_pattern(char *buffer, char *pattern)
{
	char *cur;              // cursor atual dentro do texto
	char *match;            // posição onde o pattern foi encontrado
	int len;                // tamanho do pattern
```

---

## Resumo das linhas mais importantes

```txt
while ((bytes = read(0, tmp, BUF_SIZE)) > 0)
```

```txt
enquanto o read conseguir ler bytes da stdin, guarda a quantidade lida e processa esse bloco
```

```txt
char *new_buf = realloc(buffer, len + bytes + 1);
```

```txt
realoca o buffer final para caber o conteúdo antigo mais os novos bytes lidos
```

```txt
memmove(buffer + len, tmp, bytes);
```

```txt
copia o bloco temporário para o final do buffer acumulado
```

```txt
while ((match = memmem(cur, strlen(cur), pattern, len)))
```

```txt
enquanto existir uma ocorrência do padrão a partir do cursor atual, continua buscando matches
```

```txt
write(1, cur, match - cur);
```

```txt
escreve no stdout tudo que existe entre o cursor atual e o início do match
```

---

## Exemplo mental completo

Entrada:

```txt
xxabcyy
```

Pattern:

```txt
abc
```

Fluxo:

```txt
cur = xxabcyy

acha abc
escreve xx
escreve ***
cur = yy

não encontra mais match
escreve yy
```

Resultado:

```txt
xx***yy
```

---

## GDB

### Rodar com arquivo de entrada

Criar arquivo:

```bash
printf "abcdef" > input.txt
```

Executar no GDB:

```gdb
b read_all_stdin
r < input.txt
```

### Imprimir conteúdo do buffer

```gdb
p buffer
x/s buffer
x/20cb tmp
```

### O que observar

* `tmp` muda a cada `read()`
* `buffer` cresce com `realloc()`
* `len` aumenta
* `cur` anda na substituição
* `match` aponta para a ocorrência encontrada

---

## Erros comuns

### 1. Esquecer de atualizar o retorno do `realloc`

```c
buffer = new_buf;
```

Isso é obrigatório porque o endereço pode mudar.

### 2. Esquecer o `\0`

Sem o terminador, a string C fica inválida.

### 3. Tentar imprimir `"***"` com o tamanho do pattern

Se o pattern tiver mais de 3 caracteres, isso vira erro.

A forma correta é imprimir `*` repetido no tamanho do pattern.

### 4. Não avançar o cursor corretamente

Se não fizer:

```c
cur = match + len;
```

o loop pode entrar em erro ou repetir match.

### 5. Ignorar o retorno de validação dos argumentos

O `main` deve parar se a validação falhar.

---

## Estrutura mental final para decorar

```txt
validar argumentos
    ↓
lê stdin inteira em buffer dinâmico
    ↓
cur = buffer
    ↓
enquanto encontrar pattern em cur:
    escrever antes do match
    escrever substituição
    avançar cur
    ↓
escrever resto final
```

---

## Frase-resumo

```txt
O programa lê todo o input para memória, depois percorre o texto da esquerda para a direita, substituindo cada ocorrência do padrão por asteriscos e imprimindo o resultado final.
```
