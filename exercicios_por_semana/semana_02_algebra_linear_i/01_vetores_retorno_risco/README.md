# Vetores - Retorno, risco e similaridade como operacoes vetoriais

Semana 2: Algebra linear I.

Este exercicio e o primeiro bloco de algebra linear aplicada a quant. A ideia nao e decorar formula: e aprender a olhar uma serie de retornos como um vetor e usar operacoes vetoriais para responder uma pergunta de mercado.

## Pergunta do exercicio

Voce tem uma estrategia e um benchmark de mercado. A estrategia ganhou dinheiro porque ela tem algo proprio, ou porque ela esta praticamente andando junto com o mercado?

Para responder, vamos decompor o vetor de retornos da estrategia em duas partes:

1. a parte explicada pelo mercado;
2. a parte residual, que nao foi explicada pelo mercado.

Se a parte explicada pelo mercado for quase tudo, a estrategia provavelmente tem muito beta e pouco alpha. Se o residual for grande e consistente, pode existir algo proprio para investigar.

## Traducao para linguagem quant

Imagine que cada lista de retornos diarios e uma seta em um espaco com 8 dimensoes, uma dimensao por dia.

- `strategy`: vetor de retornos da sua estrategia.
- `market`: vetor de retornos do mercado/benchmark.
- `risk_free_daily`: retorno diario livre de risco, usado para transformar retorno bruto em excesso de retorno.
- `excess return`: retorno acima da taxa livre de risco.
- `dot product`: mede quanto dois vetores andam juntos.
- `norma L2`: mede o tamanho de um vetor.
- `cosine similarity`: mede se dois vetores apontam para a mesma direcao.
- `projecao`: pega a parte da estrategia que esta alinhada com o mercado.
- `beta`: escala da exposicao ao mercado.
- `residual`: o que sobra depois de remover a parte explicada pelo mercado.

Neste exercicio, o mercado e tratado como um unico fator de risco. Isso e uma versao mini do raciocinio usado em CAPM, fator de mercado e modelos fatoriais.

## Dados de partida

```text
strategy = [0.012, -0.004, 0.006, 0.010, -0.008, 0.003, 0.007, -0.002]
market   = [0.010, -0.006, 0.004, 0.011, -0.010, 0.002, 0.006, -0.003]
risk_free_daily = 0.0002
```

Cada numero e um retorno diario em forma decimal.

Exemplos:

- `0.012` significa `+1.2%`.
- `-0.004` significa `-0.4%`.
- `0.0002` significa `+0.02%` ao dia.

## Objetivo final

Calcular:

1. retorno medio da estrategia;
2. retorno medio do mercado;
3. vetor de excesso de retorno da estrategia;
4. vetor de excesso de retorno do mercado;
5. beta da estrategia em relacao ao mercado;
6. cosine similarity entre estrategia e mercado;
7. vetor projetado, isto e, a parte da estrategia explicada pelo mercado;
8. vetor residual, isto e, a parte nao explicada pelo mercado;
9. norma do residual;
10. uma conclusao curta: parece alpha proprio ou exposicao ao mercado?

## Formulas por exercicio

Esta secao segue a mesma ordem do `Objetivo final`. Faca uma parte por vez.

### 1. Retorno medio da estrategia

Funcao no codigo:

```text
mean(strategy)
```

Formula:

```text
mean_strategy = (strategy[0] + strategy[1] + ... + strategy[n-1]) / n
```

Com os dados deste exercicio:

```text
n = 8
mean_strategy = soma(strategy) / 8
```

Esse exemplo sai da funcao `mean`, recebendo `strategy` como entrada.

Interpretacao: mostra quanto a estrategia rendeu, em media, por dia no periodo observado.

### 2. Retorno medio do mercado

Funcao no codigo:

```text
mean(market)
```

Formula:

```text
mean_market = (market[0] + market[1] + ... + market[n-1]) / n
```

Com os dados deste exercicio:

```text
n = 8
mean_market = soma(market) / 8
```

Esse exemplo sai da funcao `mean`, recebendo `market` como entrada.

Interpretacao: mostra quanto o benchmark de mercado rendeu, em media, por dia.

### 3. Excesso de retorno da estrategia

Funcao no codigo:

```text
subtract_scalar(strategy, risk_free_daily)
```

Formula para cada dia `i`:

```text
strategy_excess[i] = strategy[i] - risk_free_daily
```

Exemplo usando o primeiro dia:

```text
strategy[0] = 0.012
risk_free_daily = 0.0002
strategy_excess[0] = 0.012 - 0.0002 = 0.0118
```

Esse exemplo sai da funcao `subtract_scalar`, recebendo `strategy` e `risk_free_daily`.

Interpretacao: mede quanto a estrategia rendeu acima do retorno livre de risco.

### 4. Excesso de retorno do mercado

Funcao no codigo:

```text
subtract_scalar(market, risk_free_daily)
```

Formula para cada dia `i`:

```text
market_excess[i] = market[i] - risk_free_daily
```

Exemplo usando o primeiro dia:

```text
market[0] = 0.010
risk_free_daily = 0.0002
market_excess[0] = 0.010 - 0.0002 = 0.0098
```

Esse exemplo sai da funcao `subtract_scalar`, recebendo `market` e `risk_free_daily`.

Interpretacao: mede quanto o mercado rendeu acima do retorno livre de risco.

### 5. Beta da estrategia em relacao ao mercado

Funcao no codigo:

```text
projection_beta(strategy_excess, market_excess)
```

Aqui aparece a ideia de **projecao**.

Voce quer aproximar o vetor da estrategia usando apenas o vetor do mercado:

```text
strategy_excess ~= beta * market_excess
```

Ou seja, voce pergunta:

```text
qual numero beta faz beta * market_excess chegar mais perto de strategy_excess?
```

Antes do beta, voce precisa do produto interno:

```text
dot(u, v) = u[0]*v[0] + u[1]*v[1] + ... + u[n-1]*v[n-1]
```

Funcao auxiliar usada dentro de `projection_beta`:

```text
dot(u, v)
```

Formula do beta, tambem chamado aqui de **coeficiente da projecao**:

```text
beta = dot(strategy_excess, market_excess) / dot(market_excess, market_excess)
```

Por que essa divisao?

```text
dot(strategy_excess, market_excess)
```

mede quanto a estrategia anda junto com o mercado.

```text
dot(market_excess, market_excess)
```

mede o tamanho do mercado contra ele mesmo, isto e, o tamanho ao quadrado do vetor de mercado.

Entao:

```text
beta = alinhamento com o mercado / tamanho do mercado ao quadrado
```

Esse exemplo sai da funcao `projection_beta`, que internamente usa `dot` duas vezes.

Interpretacao: `beta` mede a escala da exposicao da estrategia ao mercado.

Leitura rapida:

- `beta = 1.0`: estrategia anda aproximadamente como o mercado;
- `beta = 0.5`: estrategia tem metade da exposicao ao mercado;
- `beta = 1.5`: estrategia amplifica movimentos do mercado;
- `beta < 0`: estrategia tende a andar contra o mercado.

Visualmente:

```text
strategy_excess
      |
      |\
      | \
      |  \ residual
      |   \
      |____\
       beta * market_excess
             mercado
```

O `beta` sozinho nao e o vetor projetado. Ele e apenas o multiplicador. A projecao vetorial completa aparece no passo 7.

### 6. Cosine similarity entre estrategia e mercado

Funcao no codigo:

```text
cosine_similarity(strategy_excess, market_excess)
```

Antes da similaridade, voce precisa da norma L2:

```text
norm(u) = sqrt(dot(u, u))
```

Funcao auxiliar usada dentro de `cosine_similarity`:

```text
norm_l2(u)
```

Formula:

```text
cosine_similarity = dot(strategy_excess, market_excess) / (norm(strategy_excess) * norm(market_excess))
```

Esse exemplo sai da funcao `cosine_similarity`, que internamente usa `dot` e `norm_l2`.

Interpretacao:

- perto de `1`: estrategia e mercado andam quase na mesma direcao;
- perto de `0`: estrategia e mercado quase nao tem alinhamento direcional;
- perto de `-1`: estrategia e mercado andam em direcoes opostas.

### 7. Vetor projetado: parte explicada pelo mercado

Funcao no codigo:

```text
scale_vector(beta, market_excess)
```

Agora voce transforma o beta em um vetor.

No passo 5 voce calculou:

```text
beta = 0.971204 aproximadamente
```

Esse numero diz:

```text
a estrategia tem aproximadamente 97.12% da escala do mercado
```

Formula para cada dia `i`:

```text
explained[i] = beta * market_excess[i]
```

Esse vetor `explained` e a **projecao de strategy_excess na direcao de market_excess**.

Em algebra linear, a projecao de um vetor `y` sobre um vetor `x` e:

```text
proj_x(y) = (dot(y, x) / dot(x, x)) * x
```

Neste exercicio:

```text
y = strategy_excess
x = market_excess
beta = dot(y, x) / dot(x, x)
explained = beta * market_excess
```

Entao:

```text
explained = proj_market_excess(strategy_excess)
```

Interpretacao: essa e a parte da estrategia que pode ser explicada apenas pela exposicao ao mercado.

Exemplo usando o primeiro dia:

```text
beta = 0.971204
market_excess[0] = 0.0098

explained[0] = beta * market_excess[0]
explained[0] = 0.971204 * 0.0098
explained[0] ~= 0.009518
```

Esse exemplo sai da funcao `scale_vector`, recebendo `beta` e `market_excess`.

Isso quer dizer:

```text
no primeiro dia, dos 0.0118 de excesso de retorno da estrategia,
aproximadamente 0.009518 vieram da exposicao ao mercado
```

Exemplo intuitivo:

```text
se beta = 1.0, a parte explicada e praticamente o proprio market_excess
se beta = 0.5, a parte explicada e metade do market_excess
```

### 8. Vetor residual: parte nao explicada pelo mercado

Funcao no codigo:

```text
subtract_vectors(strategy_excess, explained)
```

Formula para cada dia `i`:

```text
residual[i] = strategy_excess[i] - explained[i]
```

Esse exemplo sai da funcao `subtract_vectors`, recebendo `strategy_excess` e `explained`.

Interpretacao: e o pedaco que sobrou depois de retirar a exposicao ao mercado. Esse residual e o candidato inicial a "alpha proprio", mas ainda precisa ser testado com muito mais dados.

### 9. Norma do residual

Funcao no codigo:

```text
norm_l2(residual)
```

Formula:

```text
norm_residual = sqrt(dot(residual, residual))
```

Esse exemplo sai da funcao `norm_l2`, recebendo `residual`.

Interpretacao: mede o tamanho total da parte da estrategia que nao foi explicada pelo mercado.

Comparacao util:

```text
norm_explained = sqrt(dot(explained, explained))
norm_residual  = sqrt(dot(residual, residual))
```

No codigo, essa comparacao usa:

```text
norm_l2(explained)
norm_l2(residual)
```

Se `norm_residual` for muito menor que `norm_explained`, a estrategia parece mais exposicao ao mercado do que alpha proprio.

### 10. Conclusao: alpha proprio ou exposicao ao mercado?

Funcao/trecho no codigo:

```text
run_exercise()
```

Use tres numeros:

```text
beta
cosine_similarity
norm_residual
```

Regra de leitura para este exercicio:

```text
beta perto de 1
+ cosine_similarity perto de 1
+ norm_residual pequeno em relacao a norm_explained
= estrategia muito parecida com o mercado
```

Conclusao esperada aqui: a estrategia parece ter forte exposicao ao mercado. Pode ate existir residual, mas neste exemplo ele e pequeno perto da parte explicada.

Esse exemplo sai do trecho final de `run_exercise`, depois que as funcoes `projection_beta`, `cosine_similarity` e `norm_l2` ja foram chamadas.

## O que implementar em Python

Comece sem `numpy`. A proposta e entender as contas.

Crie estas funcoes em `python/main.py`:

```python
def mean(values: list[float]) -> float:
    ...

def subtract_scalar(values: list[float], scalar: float) -> list[float]:
    ...

def dot(u: list[float], v: list[float]) -> float:
    ...

def norm_l2(u: list[float]) -> float:
    ...

def cosine_similarity(u: list[float], v: list[float]) -> float:
    ...

def projection_beta(strategy_excess: list[float], market_excess: list[float]) -> float:
    ...

def scale_vector(beta: float, v: list[float]) -> list[float]:
    ...

def subtract_vectors(u: list[float], v: list[float]) -> list[float]:
    ...
```

Depois, no `main()`:

1. defina os dados hardcoded;
2. calcule os excess returns;
3. calcule `beta`;
4. calcule `explained`;
5. calcule `residual`;
6. imprima os resultados com 6 casas decimais;
7. escreva uma conclusao curta no terminal.

## O que implementar em C++

Use `std::vector<double>` e funcoes pequenas.

Voce vai precisar de:

```cpp
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
```

Funcoes sugeridas:

```cpp
double mean(const std::vector<double>& values);
std::vector<double> subtract_scalar(const std::vector<double>& values, double scalar);
double dot(const std::vector<double>& u, const std::vector<double>& v);
double norm_l2(const std::vector<double>& u);
double cosine_similarity(const std::vector<double>& u, const std::vector<double>& v);
double projection_beta(const std::vector<double>& strategy_excess, const std::vector<double>& market_excess);
std::vector<double> scale_vector(double beta, const std::vector<double>& v);
std::vector<double> subtract_vectors(const std::vector<double>& u, const std::vector<double>& v);
```

No `main()`:

1. crie `strategy`, `market` e `risk_free_daily`;
2. calcule os excess returns;
3. calcule `beta`, `cosine_similarity`, `explained` e `residual`;
4. imprima beta, similaridade, norma do residual e os vetores;
5. use `std::fixed << std::setprecision(6)` para saida legivel.

## Resultado de referencia

Use estes valores para checar se sua implementacao esta no caminho:

```text
mean_strategy          = 0.003000
mean_market            = 0.001750
dot_excess             = 0.000405
norm_strategy_excess   = 0.020316
norm_market_excess     = 0.020414
cosine_similarity      = 0.975899
beta                   = 0.971204
norm_explained         = 0.019826
norm_residual          = 0.004433
```

Interpretacao esperada: a estrategia esta muito alinhada ao mercado, porque a similaridade de cosseno ficou perto de `1`. O beta ficou perto de `1`, entao boa parte do comportamento parece exposicao ao mercado. Ainda existe residual, mas ele e bem menor que a parte explicada.

## Como saber se voce entendeu

Voce entendeu este exercicio se conseguir responder sem olhar:

1. O que significa transformar retorno bruto em excesso de retorno?
2. Por que `dot(strategy, market)` mede alinhamento?
3. O que a norma L2 esta medindo nesse contexto?
4. Por que o beta usa `dot(strategy, market) / dot(market, market)`?
5. O que significa residual pequeno?
6. Por que uma estrategia pode parecer boa, mas ser basicamente exposicao ao mercado?

## Termos para pesquisar

Pesquise em portugues:

- produto interno algebra linear
- norma euclidiana vetor
- projecao de vetor em outro vetor
- similaridade de cosseno
- beta de mercado CAPM
- excesso de retorno taxa livre de risco
- risco sistematico e risco idiossincratico
- decomposicao de retorno em beta e alpha

Pesquise em ingles:

- dot product linear algebra
- vector norm L2 norm
- vector projection formula
- cosine similarity
- market beta CAPM
- excess return risk free rate
- systematic risk idiosyncratic risk
- single factor model finance
- residual return alpha beta decomposition

## Referencias

Para aprender o conceito matematico:

- [MIT OpenCourseWare 18.06SC - Projection Matrices and Least Squares](https://ocw.mit.edu/courses/18-06sc-linear-algebra-fall-2011/pages/least-squares-determinants-and-eigenvalues/projection-matrices-and-least-squares/)
- [MIT OpenCourseWare 18.065 - Matrix Methods in Data Analysis, Signal Processing, and Machine Learning](https://ocw.mit.edu/courses/18-065-matrix-methods-in-data-analysis-signal-processing-and-machine-learning-spring-2018/)
- [Stanford CS229 - Linear Algebra Review and Reference](https://cs229.stanford.edu/section/cs229-linalg.pdf)

Para entender a parte financeira:

- [OpenStax Principles of Finance - CAPM](https://openstax.org/books/principles-finance/pages/15-3-the-capital-asset-pricing-model-capm)
- [CFA Institute - Portfolio Risk and Return, Part I](https://www.cfainstitute.org/insights/professional-learning/refresher-readings/2026/portfolio-risk-return-part-1)

Para consultar ferramentas de codigo:

- [Python `math` module](https://docs.python.org/3/library/math.html)
- [NumPy `dot`](https://numpy.org/doc/stable/reference/generated/numpy.dot.html), para conferir depois que fizer manualmente
- [NumPy `linalg.norm`](https://numpy.org/doc/stable/reference/generated/numpy.linalg.norm.html), para conferir depois que fizer manualmente
- [cppreference `std::vector`](https://en.cppreference.com/w/cpp/container/vector)
- [cppreference `std::sqrt`](https://en.cppreference.com/w/cpp/numeric/math/sqrt)

## Como rodar

```powershell
python .\python\main.py
g++ -std=c++20 -O2 -Wall -Wextra .\cpp\main.cpp -o .\cpp\main.exe
.\cpp\main.exe
```

## Entregavel

Preencha `notes.md` respondendo:

```text
A estrategia parece alpha proprio ou apenas exposicao ao mercado?
Use beta, cosine similarity e norm_residual para justificar.
```
