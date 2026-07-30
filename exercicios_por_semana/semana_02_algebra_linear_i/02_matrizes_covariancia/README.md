# Matriz de covariancia e risco de portfolio

Objetivo final: calcular a volatilidade diaria e anualizada de um portfolio usando retornos diarios de ativos, matriz de covariancia e pesos.

## Qual tipo de problema matriz de covariancia resolve

Em quant, a matriz de covariancia resolve o problema de medir risco conjunto entre ativos. Ela mostra nao apenas quanto cada ativo varia sozinho, mas tambem se os ativos tendem a subir juntos, cair juntos ou se compensar.

Exemplo pratico: se dois ativos caem juntos em dias ruins, eles aumentam o risco do portfolio. Se um ativo tende a subir quando outro cai, ele pode ajudar na diversificacao. Por isso, a matriz de covariancia e uma das bases para medir risco de portfolio, montar alocacoes e entender concentracao de risco.

## glossario

- `returns`: matriz de retornos diarios; linhas sao dias, colunas sao ativos.
- `weights`: vetor de pesos do portfolio; cada peso representa a fracao alocada em um ativo.
- `mean`: retorno medio diario de um ativo.
- `centered`: matriz de retornos centralizados; cada retorno menos a media do ativo.
- `Xc`: nome curto para a matriz centralizada.
- `Xc'`: transposta da matriz centralizada.
- `covariance`: matriz que mede como os ativos se movem juntos.
- `C`: nome curto da matriz de covariancia.
- `Cw`: vetor intermediario que aplica os pesos na matriz de covariancia.
- `portfolio_variance`: variancia diaria do portfolio.
- `daily_vol`: volatilidade diaria do portfolio.
- `annual_vol`: volatilidade anualizada do portfolio.

## dados de partida

```text
returns = [
    [ 0.010,  0.004, -0.002],
    [ 0.006,  0.002,  0.001],
    [-0.012, -0.006,  0.003],
    [ 0.015,  0.008, -0.004],
    [-0.004, -0.001,  0.002],
    [ 0.009,  0.005, -0.001],
]

weights = [0.50, 0.30, 0.20]
periods_per_year = 252
```

Cada numero em `returns` e um retorno diario em decimal:

```text
0.010  = +1.0%
-0.012 = -1.2%
```

A matriz `returns` tem formato:

```text
6 dias x 3 ativos
```

## dados de resultado

```text
means = [0.004000, 0.002000, -0.000167]

centered = [
    [ 0.006000,  0.002000, -0.001833],
    [ 0.002000,  0.000000,  0.001167],
    [-0.016000, -0.008000,  0.003167],
    [ 0.011000,  0.006000, -0.003833],
    [-0.008000, -0.003000,  0.002167],
    [ 0.005000,  0.003000, -0.000833],
]

covariance = [
    [ 0.000101,  0.000049, -0.000025],
    [ 0.000049,  0.000024, -0.000012],
    [-0.000025, -0.000012,  0.000007],
]

Cw = [0.000060, 0.000029, -0.000015]

portfolio_variance = 0.000036
daily_vol = 0.006008
annual_vol = 0.095367
```

Interpretacao esperada:

```text
O portfolio tem volatilidade diaria aproximada de 0.60% e volatilidade anualizada aproximada de 9.54%.
Os ativos 0 e 1 aumentam risco conjunto porque tem covariancia positiva.
O ativo 2 ajuda na diversificacao porque tem covariancia negativa com os ativos 0 e 1.
```

## tipagem das funcoes py e c++

Python:

```python
def column_means(matrix: list[list[float]]) -> list[float]: ...
def center_matrix(matrix: list[list[float]], means: list[float]) -> list[list[float]]: ...
def transpose(matrix: list[list[float]]) -> list[list[float]]: ...
def matrix_shape(matrix: list[list[float]]) -> tuple[int, int]: ...
def validate_rectangular(matrix: list[list[float]]) -> None: ...
def validate_matmul_dimensions(a: list[list[float]], b: list[list[float]]) -> None: ...
def matmul(a: list[list[float]], b: list[list[float]]) -> list[list[float]]: ...
def matvec(matrix: list[list[float]], vector: list[float]) -> list[float]: ...
def covariance_matrix(centered: list[list[float]]) -> list[list[float]]: ...
def dot(u: list[float], v: list[float]) -> float: ...
```

C++:

```cpp
std::vector<double> column_means(const std::vector<std::vector<double>>& matrix);
std::vector<std::vector<double>> center_matrix(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& means
);
std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& matrix);
std::pair<std::size_t, std::size_t> matrix_shape(const std::vector<std::vector<double>>& matrix);
void validate_rectangular(const std::vector<std::vector<double>>& matrix);
void validate_matmul_dimensions(
    const std::vector<std::vector<double>>& a,
    const std::vector<std::vector<double>>& b
);
std::vector<std::vector<double>> matmul(
    const std::vector<std::vector<double>>& a,
    const std::vector<std::vector<double>>& b
);
std::vector<double> matvec(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& vector
);
std::vector<std::vector<double>> covariance_matrix(const std::vector<std::vector<double>>& centered);
double dot(const std::vector<double>& u, const std::vector<double>& v);
void print_vector(const std::string& name, const std::vector<double>& values);
void print_matrix(const std::string& name, const std::vector<std::vector<double>>& matrix);
```

Regra importante:

```text
Nao crie `quadratic_form(weights, cw)` se ela apenas chamar `dot(weights, cw)`.
Nao crie `daily_volatility(portfolio_variance)` se ela apenas chamar `sqrt(portfolio_variance)`.
Nao crie `annualized_volatility(daily_vol, periods_per_year)` se ela apenas chamar `daily_vol * sqrt(periods_per_year)`.
Nao crie aliases como `Vector`, `Matrix` ou `Shape` se eles apenas renomeiam `std::vector` ou `std::pair`.
Nesse exercicio, depois de calcular `Cw`, use diretamente:

portfolio_variance = dot(weights, cw)
daily_vol = sqrt(portfolio_variance)
annual_vol = daily_vol * sqrt(periods_per_year)
```

## Referencias + termos para pesquisar

Termos:

- matriz de covariancia risco de portfolio
- covariancia amostral
- variancia de portfolio
- forma quadratica w transposto C w
- volatilidade anualizada
- diversificacao de portfolio
- covariance matrix portfolio risk
- sample covariance
- portfolio variance
- quadratic form
- annualized volatility
- diversification covariance
- linear algebra matrix multiplication

Referencias:

- [MIT OpenCourseWare 18.065 - Matrix Methods in Data Analysis, Signal Processing, and Machine Learning](https://ocw.mit.edu/courses/18-065-matrix-methods-in-data-analysis-signal-processing-and-machine-learning-spring-2018/)
- [Stanford CS229 - Linear Algebra Review and Reference](https://cs229.stanford.edu/section-spring2019/cs229-linalg.pdf)
- [NumPy `cov`](https://numpy.org/doc/2.1/reference/generated/numpy.cov.html)
- [NumPy `matmul`](https://numpy.org/devdocs/reference/generated/numpy.matmul.html)
- [NumPy `dot`](https://numpy.org/doc/stable/reference/generated/numpy.dot.html)
- [cppreference `std::vector`](https://en.cppreference.com/w/cpp/container/vector)

## Como rodar

Execucao normal:

```powershell
python .\python\main.py
g++ -std=c++23 -O2 -Wall -Wextra .\cpp\main.cpp -o .\cpp\main.exe
.\cpp\main.exe
```

Testes:

```powershell
python -m unittest discover -s .\python\tests
g++ -std=c++23 -O2 -Wall -Wextra .\cpp\tests.cpp -o .\cpp\tests.exe
.\cpp\tests.exe
```

Arquivos de teste prontos:

```text
python/tests/test_main.py
cpp/tests.cpp
```

Os testes devem chamar as funcoes diretamente e validar pelo menos:

- resultado esperado para os dados de partida;
- `dot` multiplicando posicao com posicao;
- `dot(u, v) == dot(v, u)`;
- `dot(a * u, v) == a * dot(u, v)`;
- `transpose(transpose(A)) == A`;
- `matvec(I, v) == v`;
- matriz de covariancia simetrica;
- variancia de portfolio calculada por `dot(weights, Cw)`;
- volatilidade diaria e anualizada pela raiz quadrada correta.

Animacoes e voz:

```powershell
python -m pip install manim edge-tts mutagen
powershell -ExecutionPolicy Bypass -File .\animations\generate_voice.ps1
python -m manim -qm --media_dir .\animations\media .\animations\scenes.py FullExerciseScene
```

O script de voz deve tentar primeiro `edge-tts` com a voz neural gratuita `pt-BR-FranciscaNeural`.
Se `edge-tts` falhar ou a maquina estiver offline, use fallback local com SAPI do Windows.

Video final:

```text
animations/media/videos/scenes/720p30/FullExerciseScene.mp4
```

O `FullExerciseScene` deve mostrar:

- dados de partida;
- formula matematica de cada step;
- funcao do codigo relacionada;
- transformacao visual dos valores;
- resultado de cada step;
- interpretacao quant do resultado;
- narracao sincronizada com o que aparece na tela.

## **Como saber se voce entendeu**

1. Por que precisamos centralizar os retornos antes da covariancia?
2. O que significa covariancia positiva entre dois ativos?
3. O que significa covariancia negativa entre dois ativos?
4. Por que a matriz de covariancia e simetrica?
5. Por que `Cw` vem antes de calcular a variancia final?
6. Por que `portfolio_variance = dot(weights, Cw)` vira um numero unico?
7. Por que tiramos raiz quadrada da variancia para chegar na volatilidade?
8. Por que anualizamos volatilidade usando `sqrt(252)`?
9. Qual ativo ajuda mais na diversificacao neste exemplo?

### step 1

A media de retorno de cada ativo serve para descobrir o retorno medio diario de cada coluna antes de medir desvios e risco.

Matematica em alto nivel:

```text
mean[j] = soma dos retornos do ativo j / quantidade de dias
```

#### step 1.1

A funcao deve percorrer cada coluna da matriz `returns`, somar os valores e dividir por `n`.

```text
mean[j] =
    (
        returns[0][j]
      + returns[1][j]
      + returns[2][j]
      + returns[3][j]
      + returns[4][j]
      + returns[5][j]
    )
    / 6
```

Funcao relacionada:

```text
column_means(returns)
```

Resultado esperado:

```text
means = [0.004000, 0.002000, -0.000167]
```

### step 2

A matriz centralizada mostra quanto cada retorno ficou acima ou abaixo da media do proprio ativo.

Matematica em alto nivel:

```text
retorno centralizado = retorno do dia - media do ativo
```

#### step 2.1

A funcao deve criar uma nova matriz com a mesma dimensao de `returns`, sem reutilizar linhas compartilhadas.

```text
centered[i][j] = returns[i][j] - means[j]
```

Exemplo:

```text
centered[0][0] = 0.010 - 0.004
centered[0][0] = 0.006
```

Funcao relacionada:

```text
center_matrix(returns, means)
```

### step 3

A transposta `Xc'` troca dias por ativos para permitir a multiplicacao `Xc' Xc`.

Matematica em alto nivel:

```text
Xc  tem formato 6 x 3
Xc' tem formato 3 x 6
```

#### step 3.1

A funcao deve colocar o valor que estava em `matrix[i][j]` na posicao `transposed[j][i]`.

```text
transposed[j][i] = matrix[i][j]
```

Funcao relacionada:

```text
transpose(centered)
```

### step 4

A matriz de covariancia resume como os ativos se movem juntos e prepara o calculo do risco do portfolio.

Matematica em alto nivel:

```text
C = Xc' Xc / (n - 1)
```

#### step 4.1

Este substep calcula `M`, o produto matricial entre a transposta centralizada e a matriz centralizada.

```text
M = Xc' * Xc
```

Formula matematica:

```text
M[a][b] =
    soma centered_t[a][k] * centered[k][b]
    para k indo de 0 ate 5
```

Dimensoes:

```text
centered_t tem formato 3 x 6
centered   tem formato 6 x 3
M          tem formato 3 x 3

k percorre a dimensao compartilhada:

centered_t colunas = 6
centered   linhas  = 6

Entao k representa o indice do dia usado na soma.
```

Formula aberta para uma celula:

```text
M[a][b] =
    centered_t[a][0] * centered[0][b]
  + centered_t[a][1] * centered[1][b]
  + centered_t[a][2] * centered[2][b]
  + centered_t[a][3] * centered[3][b]
  + centered_t[a][4] * centered[4][b]
  + centered_t[a][5] * centered[5][b]
```

Cuidado comum:

```text
No terceiro loop de `matmul`, k nao deve ir ate a.size().

a.size()       = quantidade de linhas de a
a[0].size()    = quantidade de colunas de a
b.size()       = quantidade de linhas de b

Como a[0].size() precisa ser igual a b.size(), use:

for k in range(a[0].size())
```

Neste exercicio:

```text
a = centered_t -> 3 x 6
b = centered   -> 6 x 3

a.size()    = 3
a[0].size() = 6
b.size()    = 6

Se k for ate a.size(), a conta soma so 3 dias.
Se k for ate a[0].size(), a conta soma os 6 dias corretos.
```

Relacao no codigo:

```text
centered_t = transpose(centered)
M = matmul(centered_t, centered)

for i in range(a.size()):
    for j in range(b[0].size()):
        for k in range(a[0].size()):
            result[i][j] += a[i][k] * b[k][j]
```

Dentro de `covariance_matrix(centered)`, a mesma conta pode aparecer diretamente assim:

```text
M = matmul(transpose(centered), centered)
```

#### step 4.2

Este substep calcula cada celula da matriz de covariancia amostral dividindo o produto `M` por `n - 1`.

```text
covariance[a][b] = M[a][b] / (n - 1)
```

No exercicio:

```text
n = 6
n - 1 = 5
```

Relacao no codigo:

```text
covariance_matrix(centered)
```

Dentro de `covariance_matrix`, a conta precisa ser equivalente a:

```text
M = matmul(transpose(centered), centered)
covariance[a][b] = M[a][b] / (len(centered) - 1)
```

Resultado esperado:

```text
covariance = [
    [ 0.000101,  0.000049, -0.000025],
    [ 0.000049,  0.000024, -0.000012],
    [-0.000025, -0.000012,  0.000007],
]
```

### step 5

O vetor `Cw` aplica os pesos do portfolio na matriz de covariancia antes da variancia final.

Matematica em alto nivel:

```text
Cw = C * w
```

#### step 5.1

A funcao deve multiplicar cada linha da matriz de covariancia pelo vetor de pesos.

```text
cw[i] = C[i][0] * w[0] + C[i][1] * w[1] + C[i][2] * w[2]
```

Funcao relacionada:

```text
matvec(covariance, weights)
```

Resultado esperado:

```text
Cw = [0.000060, 0.000029, -0.000015]
```

Interpretacao:

```text
Cw[0] positivo: ativo 0 aumenta risco conjunto.
Cw[1] positivo: ativo 1 aumenta risco conjunto.
Cw[2] negativo: ativo 2 ajuda a compensar risco conjunto.
```

### step 6

A variancia diaria do portfolio transforma `Cw` em um unico numero de risco usando novamente os pesos.

Matematica em alto nivel:

```text
portfolio_variance = w' C w
portfolio_variance = w' (Cw)
portfolio_variance = dot(weights, Cw)
```

#### step 6.1

A funcao `dot` deve multiplicar os vetores posicao com posicao, nao todos contra todos.

```text
portfolio_variance =
    weights[0] * cw[0]
  + weights[1] * cw[1]
  + weights[2] * cw[2]
```

Funcao relacionada:

```text
dot(weights, cw)
```

Resultado esperado:

```text
portfolio_variance = 0.000036
```

### step 7

A volatilidade diaria transforma variancia em uma medida de risco na mesma escala dos retornos diarios.

Matematica em alto nivel:

```text
daily_vol = sqrt(portfolio_variance)
```

#### step 7.1

A funcao deve tirar a raiz quadrada da variancia diaria.

```text
daily_vol = sqrt(0.000036090667)
daily_vol = 0.006008
```

Trecho relacionado no codigo:

```text
daily_vol = sqrt(portfolio_variance)
```

### step 8

A volatilidade anualizada coloca o risco diario em escala anual, assumindo 252 pregoes por ano.

Matematica em alto nivel:

```text
annual_vol = daily_vol * sqrt(periods_per_year)
```

#### step 8.1

A funcao deve multiplicar a volatilidade diaria por `sqrt(252)`.

```text
annual_vol = 0.006007550804 * sqrt(252)
annual_vol = 0.095367
```

Trecho relacionado no codigo:

```text
annual_vol = daily_vol * sqrt(periods_per_year)
```

### step 9

A conclusao transforma os numeros calculados em leitura de risco e diversificacao.

Matematica em alto nivel:

```text
C[0][1] > 0  -> ativos 0 e 1 aumentam risco conjunto
C[0][2] < 0  -> ativo 2 compensa parte do risco do ativo 0
C[1][2] < 0  -> ativo 2 compensa parte do risco do ativo 1
annual_vol   -> risco anualizado do portfolio
```

#### step 9.1

O trecho final deve usar `covariance`, `cw`, `portfolio_variance`, `daily_vol` e `annual_vol` para escrever uma conclusao curta.

Texto esperado:

```text
O portfolio tem volatilidade diaria aproximada de 0.60% e volatilidade anualizada aproximada de 9.54%.
Os ativos 0 e 1 aumentam risco conjunto por terem covariancia positiva.
O ativo 2 ajuda na diversificacao porque tem covariancia negativa com os ativos 0 e 1.
```

Trecho relacionado:

```text
run_exercise()
```
