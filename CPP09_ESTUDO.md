# CPP09 (STL) — Guia de estudo para defesa

Este documento resume **o que cada exercício pede**, **como o seu código resolve**, quais são os **pontos críticos** (parsing, erros, containers) e quais perguntas normalmente aparecem na **avaliação por pares**.

> Subject: `pt_br.subject_cpp9.pdf` (versão 3.0).  
> Exercícios: `ex00` (BitcoinExchange), `ex01` (RPN), `ex02` (PmergeMe).

---

## Regras do módulo (o que o avaliador costuma checar)

- **C++98**, compilação com `-Wall -Wextra -Werror` (o Makefile deve aceitar `-std=c++98`).
- **Sem bibliotecas externas** e sem funções proibidas (o subject do CPP09 não proíbe nada extra, mas continuam valendo as regras gerais do Common Core).
- **Sem `using namespace ...` e sem `friend`**, a menos que o enunciado permita (aqui não permite).
- **Cada exercício deve usar STL** e **não pode reusar o mesmo container** nos exercícios seguintes:
  - `ex00`: usar pelo menos um container (ex.: `std::map`).
  - `ex01`: usar um container diferente do `ex00` (ex.: `std::stack`).
  - `ex02`: usar **dois containers diferentes** (ex.: `std::vector` e `std::deque`).

---

## ex00 — `btc` (Bitcoin Exchange)

### O que o enunciado pede

- Ler um **DB CSV** (fornecido no subject) com a taxa do bitcoin ao longo do tempo.
- Receber **um arquivo** como argumento (ex.: `input.txt`).
- Cada linha do input: **`date | value`**.
- `date` válida: **`YYYY-MM-DD`**.
- `value` válido: **float ou int**, **positivo**, **entre 0 e 1000**.
- Se a data **não existe** no DB: usar a **data mais próxima inferior** (lower/equal).
- Em caso de erro, imprimir mensagens “apropriadas” (o próprio subject dá exemplos).

### Como o seu código está estruturado

- **Classe**: `BitcoinExchange`
- **Container usado**: `std::map<std::string, double>` para guardar `date -> rate`.
  - `std::map` é ideal porque mantém as chaves ordenadas e permite busca por “data mais próxima inferior” com `lower_bound`.

### Lógica principal (passo a passo)

1. No construtor (`BitcoinExchange::BitcoinExchange()`), o programa tenta abrir o DB (`data.csv`).
2. Carrega o CSV para o `std::map`.
3. Em `validInputFile(...)`:
   - valida header `date | value`
   - para cada linha:
     - valida o formato estrito `YYYY-MM-DD | value`
     - valida se o valor é número e se está em `[0, 1000]`
     - valida data (mês/dia/leap year e mínimo 2009-01-02)
     - calcula e imprime: `date => value = value * rate`
4. `findDateAndCalculate(date, value)`:
   - usa `btcData.lower_bound(date)`
   - se existe exatamente a data, usa ela
   - se não existe, usa a data **imediatamente anterior** (decrementando o iterator)

### Pontos “de defesa” (perguntas clássicas)

- **Por que `std::map`?**
  - Porque as chaves ficam ordenadas por data (string `YYYY-MM-DD` ordena corretamente lexicograficamente) e `lower_bound` encontra o primeiro elemento `>= date`.
- **Como garantir “data inferior” e não superior?**
  - `lower_bound` retorna `>= date`; se não for exatamente igual, eu faço `--it` para pegar o elemento anterior (inferior).
- **E se a data for antes da primeira data do DB?**
  - Considero “bad input” (o subject do dataset começa em 2009-01-02).

### Mensagens de erro (alinhadas ao subject)

- Sem argumento: `Error: could not open file.`
- Valor negativo: `Error: not a positive number.`
- Valor > 1000: `Error: too large a number.`
- Linha mal formatada/data inválida: `Error: bad input => <linha>`

### Como executar (exemplos)

```bash
./btc input.txt
```

---

## ex01 — `RPN` (Reverse Polish Notation)

### O que o enunciado pede

- Receber **uma expressão RPN** como único argumento.
- Números passados como argumentos são **sempre < 10** (ou seja, dígitos simples).
- Tokens válidos: **`+ - * /`**.
- Em erro: imprimir **`Error` no stderr**.
- Não precisa lidar com parênteses nem números decimais.

### Container usado

- `std::stack<double> numbers`
  - Stack é a estrutura natural para RPN: números entram (push), operadores consomem os 2 do topo (pop/pop) e empilham o resultado (push).

### Algoritmo

1. Parsear a string usando `std::stringstream` (separa por espaços).
2. Cada token deve ter tamanho 1:
   - se for dígito: `push(valor)`
   - se for operador:
     - precisa ter pelo menos 2 operandos na stack
     - `b = pop`, `a = pop`, `push(a op b)`
     - divisão por zero -> `Error`
3. No final, a stack deve ter **exatamente 1** elemento: imprimir esse valor.

### Por que exigir tokens separados por espaços?

O subject mostra exemplos no formato `"8 9 * 9 - ..."` e assume dígitos simples. Se você aceitasse `"12"` como dois números (`1` e `2`), isso vira um parsing ambíguo e foge do formato esperado.

### Como executar

```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

Saída esperada (exemplo do subject): `42`

---

## ex02 — `PmergeMe` (Ford–Johnson / Merge-Insert Sort)

### O que o enunciado pede

- Receber uma sequência de **inteiros positivos** como argumentos.
- Ordenar usando **merge-insert sort (Ford–Johnson)**.
- Usar **dois containers diferentes** e medir o tempo para cada um.
- Output:
  - `Before: <sequência>`
  - `After: <sequência ordenada>`
  - tempo para `std::vector`
  - tempo para `std::deque`
- Em erro: imprimir **`Error` no stderr**.
- Lidar com **pelo menos 3000 inteiros**.

### Containers usados

- `std::vector<int>` e `std::deque<int>`

### Ideia do Ford–Johnson (explicação para defesa)

O Ford–Johnson reduz comparações ao:

1. **Formar pares** `(a, b)` e ordenar dentro do par: `(min, max)`.
2. **Ordenar os pares pelo `max`** (isso cria uma cadeia principal já “quase ordenada”).
3. Montar a **main chain** com os `max` em ordem.
4. Inserir os `min` restantes usando **inserção binária**, mas numa **ordem específica (Jacobsthal)** que minimiza comparações.
5. Se houver um elemento “sobrando” (quantidade ímpar), inserir o **straggler** no final com `lower_bound`.

### Como o seu código faz isso (visão prática)

- O `main.cpp`:
  - valida que cada argumento é só dígitos, converte e exige `n > 0`
  - imprime `Before`
  - mede o tempo para ordenar `vector` e `deque`
  - imprime `After` e os tempos

- O `PmergeMe`:
  - `runVector(vec)`: ordena usando o Ford–Johnson e grava no próprio `vec`
  - `runDeque(deq)`: ordena o `deque`

> Observação importante para defesa: o subject diz que é “fortemente aconselhável” implementar para cada container (evitar uma função genérica). O seu código executa ordenação para ambos; porém, **o `deque` é convertido para uma estrutura sequencial durante o processamento e depois reatribuído**. Se o avaliador for muito rígido, ele pode pedir para você justificar/ajustar isso.

### Complexidade (argumento rápido)

- A ordenação de pares + inserções binárias tende a \(O(n \log n)\) para busca, mas a implementação prática pode ter custos extras de movimentação/inserção.
- Para 3000 elementos, o objetivo é ser claramente “rápido o suficiente” e mostrar diferença de containers no tempo.

### Como executar

```bash
./PmergeMe 3 5 9 7 4
```

Saída no formato do subject:

- `Before: 3 5 9 7 4`
- `After: 3 4 5 7 9`
- tempos para `vector` e `deque`

---

## Checklist de defesa (o que treinar para explicar)

- **Por que cada container foi escolhido** (map/stack/vector/deque).
- **Como você valida entrada**:
  - `btc`: header + parsing + faixa de valor + data
  - `RPN`: tokens separados por espaços, dígitos simples e operadores
  - `PmergeMe`: apenas inteiros positivos e overflow
- **Como você encontra “data inferior” no map** (`lower_bound` e decremento).
- **Por que RPN precisa de stack** e qual é o estado válido no fim (1 elemento).
- **Explicação do Ford–Johnson**: pares, main chain, inserções, Jacobsthal, straggler.

---

## Notas rápidas sobre seu workspace

- O arquivo `pt_br.subject_cpp9.pdf` está na raiz do projeto.
- O DB `data.csv` **não está presente** no workspace no momento; o `btc` tenta abrir `data.csv` (ou `srcs/data.csv`) e, se não encontrar, retorna `Error: could not open file.`.

