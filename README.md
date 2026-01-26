# cppModule09

## EX02

# Algoritmo de Ordenação Merge-Insert (Ford–Johnson)

O **Merge-Insert**, também conhecido como **algoritmo de Ford–Johnson**, é um algoritmo de ordenação por comparação
famoso por usar **um número mínimo de comparações no pior caso**.

Ele é mais teórico do que prático, mas é muito importante para entender **limites inferiores de ordenação**.

---

## 📌 Características principais

- Baseado em **comparações**
- Usa a estratégia **dividir, ordenar parcialmente e inserir**
- Minimiza o número de comparações
- Complexidade:
  - Tempo: `O(n log n)`
  - Comparações: próximo do mínimo teórico
- Pouco usado em produção devido à **complexidade de implementação**

---

## 🧠 Ideia geral do algoritmo

O algoritmo funciona em **cinco etapas principais**:

1. Agrupar os elementos em pares
2. Ordenar cada par internamente
3. Ordenar os maiores elementos dos pares
4. Inserir os menores elementos um a um
5. Usar uma ordem especial de inserção para reduzir comparações

---

## 🪜 Passo a passo detalhado

### 1️⃣ Formar pares

Dado um vetor de entrada:

```text
[8, 3, 5, 2, 9, 1, 4]
```
