# cppModule09

# EX02

## Algoritmo de Ordenação Merge-Insert (Ford–Johnson)

O **Merge-Insert**, também conhecido como **algoritmo de Ford–Johnson**, é um algoritmo de ordenação por comparação
famoso por usar **um número mínimo de comparações no pior caso**.

Ele é mais teórico do que prático, mas é muito importante para entender **limites inferiores de ordenação**.

---

## Características principais

- Baseado em **comparações**
- Usa a estratégia **dividir, ordenar parcialmente e inserir**
- Minimiza o número de comparações
- Complexidade:
  - Tempo: `O(n log n)`
  - Comparações: próximo do mínimo teórico
- Pouco usado em produção devido à **complexidade de implementação**

---

## Ideia geral do algoritmo

O algoritmo funciona em **cinco etapas principais**:

1. Agrupar os elementos em pares
2. Ordenar cada par internamente
3. Ordenar os maiores elementos dos pares
4. Inserir os menores elementos um a um
5. Usar uma ordem especial de inserção para reduzir comparações

---

## Passo a passo detalhado

### 1️ Formar pares

Dado um vetor de entrada:

```text
[8, 3, 5, 2, 9, 1, 4]
```

Agrupamos em pares consecutivos:

```text
(8, 3), (5, 2), (9, 1)
```

Se houver um elemento sobrando, ele é guardado para o final:

```text
Sobra: 4
```

### 2 Ordenar cada par

Dentro de cada par, colocamos o menor primeiro:

```text
(3, 8), (2, 5), (1, 9)
```

### 3️ Separar maiores e menores

Criamos duas listas:

- Maiores (segundos elementos dos pares)
- Menores (primeiros elementos dos pares)

```text
Maiores:  [8, 5, 9]
Menores:  [3, 2, 1]
```

### 4️ Ordenar os maiores (recursivamente)

Ordenamos apenas a lista dos maiores:

```text
Maiores ordenados: [5, 8, 9]
```

### 5️ Inserir os menores (merge-insert)

Agora inserimos os menores um a um na lista dos maiores,
usando busca binária para reduzir comparações.

A ordem de inserção não é sequencial — ela segue a
sequência de Jacobsthal, que minimiza comparações.

Exemplo simplificado:

```text
Inserir 1 → [1, 5, 8, 9]
Inserir 2 → [1, 2, 5, 8, 9]
Inserir 3 → [1, 2, 3, 5, 8, 9]
```

### 6️ Inserir elemento sobrando (se existir)

Caso exista um elemento sem par, ele é inserido por busca binária:

```text
Inserir 4 → [1, 2, 3, 4, 5, 8, 9]
```

### Por que esse algoritmo é especial?

Ele usa menos comparações que Merge Sort
Chega muito perto do limite inferior teórico:

```text
⌈log₂(n!)⌉ comparações
```

É referência em teoria da computação
Serve como base para estudos sobre otimização de comparações

### Desvantagens

```text
Implementação complexa
Difícil de entender e depurar
Pouco usado em aplicações reais
Overhead maior que algoritmos clássicos
```

### Conclusão

```text
O algoritmo Ford–Johnson não é feito para ser o mais rápido na prática,
mas sim para mostrar que é possível ordenar com menos comparações.

Ele é um excelente exemplo de como estratégia e matemática
podem superar abordagens tradicionais.
```
