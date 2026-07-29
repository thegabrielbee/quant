# Matrizes - Matriz de covariancia e risco de portfolio

Semana 2: Algebra linear I.

Este exercicio e o primeiro contato com matrizes em risco quantitativo. No exercicio 1 voce comparou uma estrategia com o mercado usando vetores. Aqui voce passa para varios ativos ao mesmo tempo e usa uma matriz para medir como eles se movem juntos.

## Pergunta do exercicio

Voce tem 3 ativos e um portfolio com pesos fixos. Qual e o risco diario e anualizado desse portfolio?

Para responder, voce vai construir a matriz de covariancia dos retornos e calcular:

```text
portfolio_variance = w' C w
```

Onde:

- `w` e o vetor de pesos do portfolio;
- `C` e a matriz de covariancia dos ativos;
- `w' C w` e a variancia do portfolio.

## Traducao para linguagem quant

- `returns`: matriz de retornos. Cada linha e um dia; cada coluna e um ativo.
- `weights`: vetor de pesos do portfolio. Exemplo: `0.50` significa 50% do capital.
- `media por coluna`: retorno medio de cada ativo.
- `matriz centralizada`: retornos depois de subtrair a media de cada ativo.
- `covariancia`: mede se dois ativos tendem a subir/descer juntos.
- `variancia`: covariancia de um ativo com ele mesmo; fica na diagonal da matriz.
- `matriz de covariancia`: tabela onde cada celula mostra a covariancia entre dois ativos.
- `w' C w`: forma quadratica que transforma covariancia dos ativos em risco do portfolio.
- `volatilidade`: raiz quadrada da variancia.
- `volatilidade anualizada`: volatilidade diaria multiplicada por `sqrt(252)`.

Por que isso importa? Em quant, risco nao e apenas "quanto cada ativo mexe sozinho". O risco tambem depende de como os ativos mexem juntos. Dois ativos volateis podem reduzir risco se um tende a compensar o outro.

## Dados de partida

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

- `0.010` significa `+1.0%`;
- `-0.012` significa `-1.2%`.

A matriz tem formato `6x3`:

```text
6 dias x 3 ativos
```

## Objetivo final

Calcular:

1. media de retorno de cada ativo;
2. matriz de retornos centralizados;
3. matriz transposta `Xc'`;
4. matriz de covariancia amostral `C = Xc' Xc / (n - 1)`;
5. vetor intermediario `Cw`;
6. variancia diaria do portfolio `w' C w`;
7. volatilidade diaria do portfolio;
8. volatilidade anualizada do portfolio;
9. conclusao curta sobre diversificacao.

## Formulas por exercicio

### 1. Media de retorno de cada ativo

A media de retorno de cada ativo serve para descobrir o comportamento medio de cada coluna antes de medir os desvios e o risco.

Formula completa do step 1, do inicio ao resultado:

```text
Entrada deste step:

returns = matriz de retornos diarios

Saida deste step:

means = vetor com a media diaria de cada ativo
```

Passo 1: identifique `n`.

```text
returns tem formato 6 x 3

6 linhas = 6 dias
3 colunas = 3 ativos

n = 6
```

Passo 2: escreva a conta principal.

```text
mean[j] = soma da coluna j / n
```

Passo 3: escreva a formula aberta.

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

Passo 4: substitua os valores deste exercicio.

```text
mean[0] =
    (0.010 + 0.006 + (-0.012) + 0.015 + (-0.004) + 0.009) / 6
mean[0] = 0.024 / 6
mean[0] = 0.004000

mean[1] =
    (0.004 + 0.002 + (-0.006) + 0.008 + (-0.001) + 0.005) / 6
mean[1] = 0.012 / 6
mean[1] = 0.002000

mean[2] =
    ((-0.002) + 0.001 + 0.003 + (-0.004) + 0.002 + (-0.001)) / 6
mean[2] = -0.001 / 6
mean[2] = -0.000166667
```

Resultado do step 1:

```text
means = [0.004000, 0.002000, -0.000167]
```

Esse resultado sai da funcao `column_means`, recebendo `returns`.

#### 1.1 Ligacao com codigo

A funcao `column_means` deve percorrer cada coluna de `returns`, somar os valores daquela coluna e dividir por `n`.

Formula matematica:

```text
mean[j] = (returns[0][j] + returns[1][j] + ... + returns[n - 1][j]) / n
```

Funcao no codigo:

```text
column_means(returns)
```

### 2. Matriz de retornos centralizados

A matriz de retornos centralizados serve para transformar retornos brutos em desvios em torno da media de cada ativo.

Formula completa do step 2, do inicio ao resultado:

```text
Entrada deste step:

returns = matriz de retornos diarios
means   = medias calculadas no step 1

Saida deste step:

centered = matriz de retornos centralizados
```

Passo 1: escreva a conta principal.

```text
centered[i][j] = returns[i][j] - means[j]
```

Passo 2: entenda os indices.

```text
i = indice do dia
j = indice do ativo

means[j] usa a media do mesmo ativo j.
```

Passo 3: calcule um exemplo de celula.

```text
returns[0][0] = 0.010
mean[0] = 0.004

centered[0][0] = 0.010 - 0.004
centered[0][0] = 0.006
```

Passo 4: aplique a mesma conta em todas as celulas.

```text
centered = [
    [ 0.006000,  0.002000, -0.001833],
    [ 0.002000,  0.000000,  0.001167],
    [-0.016000, -0.008000,  0.003167],
    [ 0.011000,  0.006000, -0.003833],
    [-0.008000, -0.003000,  0.002167],
    [ 0.005000,  0.003000, -0.000833],
]
```

Resultado do step 2:

```text
centered tem formato 6 x 3
```

Esse resultado sai da funcao `center_matrix`, recebendo `returns` e `means`.

#### 2.1 Ligacao com codigo

A funcao `center_matrix` deve percorrer cada celula da matriz original e subtrair a media da coluna correspondente.

Formula matematica:

```text
centered[i][j] = returns[i][j] - means[j]
```

Funcao no codigo:

```text
center_matrix(returns, means)
```

### 3. Matriz transposta `Xc'`

A matriz transposta `Xc'` serve para trocar dias por ativos e permitir a multiplicacao `Xc' Xc` usada na covariancia.

Formula completa do step 3, do inicio ao resultado:

```text
Entrada deste step:

centered = matriz centralizada calculada no step 2

Saida deste step:

transposed = matriz transposta Xc'
```

Passo 1: confira as dimensoes.

```text
centered tem formato 6 x 3

6 linhas = 6 dias
3 colunas = 3 ativos
```

Passo 2: troque linhas por colunas.

```text
transposed tem formato 3 x 6

3 linhas = 3 ativos
6 colunas = 6 dias
```

Passo 3: escreva a regra de troca.

```text
transposed[j][i] = centered[i][j]
```

Passo 4: aplique a regra aos dados deste exercicio.

```text
transposed = [
    [ 0.006000,  0.002000, -0.016000,  0.011000, -0.008000,  0.005000],
    [ 0.002000,  0.000000, -0.008000,  0.006000, -0.003000,  0.003000],
    [-0.001833,  0.001167,  0.003167, -0.003833,  0.002167, -0.000833],
]
```

Resultado do step 3:

```text
Xc' tem formato 3 x 6
```

Esse resultado sai da funcao `transpose`, recebendo `centered`.

#### 3.1 Ligacao com codigo

A funcao `transpose` deve colocar o valor que estava na linha `i` e coluna `j` na linha `j` e coluna `i`.

Formula matematica:

```text
transposed[j][i] = centered[i][j]
```

Funcao no codigo:

```text
transpose(centered)
```

### 4. Matriz de covariancia amostral

A matriz de covariancia `C` serve para resumir, em uma tabela ativo contra ativo, como os retornos centralizados se movem juntos e como isso vira risco do portfolio.

Formula completa do step 4, do inicio ao resultado:

```text
Entrada deste step:

centered = matriz centralizada calculada no step 2
Xc'      = transposta calculada no step 3

Saida deste step:

C = matriz de covariancia amostral
```

Passo 1: escreva a conta principal.

```text
C = Xc' Xc / (n - 1)
```

Passo 2: confira as dimensoes.

```text
Xc' tem formato 3 x 6
Xc  tem formato 6 x 3

entao:

Xc' Xc tem formato 3 x 3
C tambem tem formato 3 x 3
```

Passo 3: lembre de onde vem `n`.

```text
centered tem 6 linhas
cada linha e um dia

n = 6
n - 1 = 5
```

Passo 4: escreva a formula de uma celula.

```text
C[a][b] =
    (
        centered[0][a] * centered[0][b]
      + centered[1][a] * centered[1][b]
      + centered[2][a] * centered[2][b]
      + centered[3][a] * centered[3][b]
      + centered[4][a] * centered[4][b]
      + centered[5][a] * centered[5][b]
    )
    / 5
```

Passo 5: resultado deste exercicio.

```text
C = [
    [ 0.000101,  0.000049, -0.000025],
    [ 0.000049,  0.000024, -0.000012],
    [-0.000025, -0.000012,  0.000007],
]
```

Esse resultado sai da funcao `covariance_matrix`, recebendo `centered`.

#### 4.1 O que essa matriz guarda

A matriz de covariancia e uma tabela ativo contra ativo.

Como temos 3 ativos, a matriz C tem formato 3 x 3.

Cada celula `C[a][b]` compara dois ativos:

```text
        ativo 0    ativo 1    ativo 2
ativo 0  C[0][0]   C[0][1]   C[0][2]
ativo 1  C[1][0]   C[1][1]   C[1][2]
ativo 2  C[2][0]   C[2][1]   C[2][2]
```

A leitura e:

```text
C[a][b] = covariancia entre o ativo a e o ativo b
```

Na diagonal, o ativo e comparado com ele mesmo:

```text
C[0][0] = variancia do ativo 0
C[1][1] = variancia do ativo 1
C[2][2] = variancia do ativo 2
```

Fora da diagonal, dois ativos diferentes sao comparados:

```text
C[0][1] = covariancia entre ativo 0 e ativo 1
C[0][2] = covariancia entre ativo 0 e ativo 2
C[1][2] = covariancia entre ativo 1 e ativo 2
```

#### 4.2 O que a covariancia mede

A covariancia mede se dois ativos costumam desviar da propria media
na mesma direcao ou em direcoes opostas.

Aqui nao usamos o retorno bruto direto. Usamos o retorno centralizado:

```text
centered[i][a] = retorno do ativo a no dia i menos a media do ativo a
centered[i][b] = retorno do ativo b no dia i menos a media do ativo b
```

Para calcular uma celula `C[a][b]`, voce compara os dois ativos dia por dia:

```text
se os dois desvios forem positivos, o produto fica positivo
se os dois desvios forem negativos, o produto tambem fica positivo
se um desvio for positivo e o outro negativo, o produto fica negativo
```

Interpretacao financeira:

```text
covariancia positiva:
os ativos tendem a surpreender na mesma direcao.
Quando um fica acima da propria media, o outro tambem tende a ficar.
Quando um fica abaixo da propria media, o outro tambem tende a ficar.

leitura de risco:
isso aumenta o risco conjunto, porque perdas podem acontecer ao mesmo tempo.
Em portfolio, covariancia positiva reduz o beneficio de diversificacao.

covariancia negativa:
os ativos tendem a surpreender em direcoes opostas.
Quando um fica acima da propria media, o outro tende a ficar abaixo.

leitura de risco:
isso pode reduzir o risco do portfolio, porque um ativo pode compensar o outro.
Em portfolio, covariancia negativa ajuda na diversificacao.

covariancia perto de zero:
os desvios dos dois ativos nao mostram uma relacao linear clara.
Um ativo ficar acima ou abaixo da media nao diz muito sobre o outro.

leitura de risco:
o efeito de um ativo sobre o risco do outro e fraco.
Pode haver diversificacao, mas nao uma protecao tao direta quanto na covariancia negativa.
```

#### 4.3 Formula de uma celula

A formula de uma celula calcula a covariancia entre dois ativos especificos, comparando os desvios dos dois ativos em todos os dias observados.

```text
C[a][b] =
    (
        centered[0][a] * centered[0][b]
      + centered[1][a] * centered[1][b]
      + centered[2][a] * centered[2][b]
      + ...
      + centered[n - 1][a] * centered[n - 1][b]
    )
    / (n - 1)
```

Onde:

```text
i = indice do dia
a = indice do primeiro ativo
b = indice do segundo ativo
n = quantidade de dias observados
```

Passo a passo para calcular `C[a][b]` na mao:

```text
1. escolha dois ativos: a e b
2. pegue os retornos centralizados desses dois ativos
3. em cada dia, multiplique o desvio do ativo a pelo desvio do ativo b
4. some todos esses produtos
5. divida por n - 1
```

#### 4.4 De onde vem `n`

`n` vem da quantidade de linhas da matriz de retornos.

Cada linha e um dia observado.

No nosso exercicio:

```text
returns  tem formato 6 x 3
centered tem formato 6 x 3

6 linhas = 6 dias

n = 6
n - 1 = 5
```

Dividimos por `n - 1` porque estamos calculando covariancia amostral.

#### 4.5 Exemplo manual: `C[0][1]`

Aqui vamos calcular a covariancia entre o ativo 0 e o ativo 1.

Os desvios centralizados desses dois ativos sao:

```text
ativo 0: [ 0.006,  0.002, -0.016,  0.011, -0.008,  0.005]
ativo 1: [ 0.002,  0.000, -0.008,  0.006, -0.003,  0.003]
```

Agora multiplique dia por dia:

```text
dia 0:  0.006 *  0.002 = 0.000012
dia 1:  0.002 *  0.000 = 0.000000
dia 2: -0.016 * -0.008 = 0.000128
dia 3:  0.011 *  0.006 = 0.000066
dia 4: -0.008 * -0.003 = 0.000024
dia 5:  0.005 *  0.003 = 0.000015
```

Some:

```text
0.000012
+ 0.000000
+ 0.000128
+ 0.000066
+ 0.000024
+ 0.000015
= 0.000245
```

Agora divida por `n - 1`.

Como `n = 6`, entao `n - 1 = 5`:

```text
C[0][1] = 0.000245 / 5
C[0][1] = 0.000049
```

#### 4.6 Formula matricial

A formula matricial calcula todas as covariancias de uma vez usando a transposta `Xc'` e a matriz centralizada `Xc`.

```text
C = Xc' Xc / (n - 1)
```

Essa formula faz a mesma conta da secao anterior, mas para todos os pares de ativos de uma vez.

Primeiro calcule:

```text
M = Xc' Xc
```

`M` ainda nao e a matriz de covariancia final. `M` guarda as somas antes da divisao por `n - 1`.

Depois:

```text
C = M / (n - 1)
```

Essa divisao significa dividir cada celula de `M` pelo mesmo numero:

```text
C[0][0] = M[0][0] / 5
C[0][1] = M[0][1] / 5
C[0][2] = M[0][2] / 5

C[1][0] = M[1][0] / 5
C[1][1] = M[1][1] / 5
C[1][2] = M[1][2] / 5

C[2][0] = M[2][0] / 5
C[2][1] = M[2][1] / 5
C[2][2] = M[2][2] / 5
```

#### 4.7 Por que `Xc' Xc` monta a matriz inteira

Essa multiplicacao monta a matriz inteira porque cada linha de `Xc'` representa um ativo e cada coluna de `Xc` tambem representa um ativo.

```text
Xc  tem formato 6 x 3
Xc' tem formato 3 x 6
```

Logo:

```text
Xc' * Xc tem formato 3 x 3
```

Isso acontece porque:

```text
(3 x 6) * (6 x 3) = 3 x 3
```

A dimensao `6` e o numero de dias. Ela e usada no meio da multiplicacao.

A dimensao final `3 x 3` aparece porque temos 3 ativos contra 3 ativos.

Para uma celula de `M = Xc' Xc`:

```text
M[a][b] =
    Xc'[a][0] * Xc[0][b]
  + Xc'[a][1] * Xc[1][b]
  + Xc'[a][2] * Xc[2][b]
  + ...
  + Xc'[a][5] * Xc[5][b]
```

Como `Xc'[a][i]` e o mesmo valor de `Xc[i][a]`, isso vira:

```text
M[a][b] =
    Xc[0][a] * Xc[0][b]
  + Xc[1][a] * Xc[1][b]
  + Xc[2][a] * Xc[2][b]
  + ...
  + Xc[5][a] * Xc[5][b]
```

Ou seja: `Xc' Xc` calcula automaticamente as somas dos produtos dos desvios para todos os pares de ativos.

Depois `covariance_matrix(centered)` divide cada celula por `n - 1`.

### 5. Vetor intermediario `Cw`

O vetor `Cw` serve para aplicar os pesos do portfolio na matriz de covariancia, deixando pronto o calculo da variancia diaria `w' C w`.

Formula completa do step 5, do inicio ao resultado:

```text
Entrada deste step:

C = matriz de covariancia calculada no step 4
w = vetor de pesos do portfolio

Saida deste step:

Cw = vetor intermediario usado no step 6
```

Passo 1: escreva a conta principal.

```text
Cw = C * w
```

Passo 2: confira as dimensoes.

```text
C tem formato 3 x 3
w tem formato 3 x 1

entao:

Cw tem formato 3 x 1
```

Passo 3: escreva a formula aberta.

```text
cw[0] = C[0][0] * w[0] + C[0][1] * w[1] + C[0][2] * w[2]
cw[1] = C[1][0] * w[0] + C[1][1] * w[1] + C[1][2] * w[2]
cw[2] = C[2][0] * w[0] + C[2][1] * w[1] + C[2][2] * w[2]
```

Passo 4: substitua os valores deste exercicio.

```text
C = [
    [ 0.000101200000,  0.000049000000, -0.000024600000],
    [ 0.000049000000,  0.000024400000, -0.000012200000],
    [-0.000024600000, -0.000012200000,  0.000006966667],
]

w = [0.50, 0.30, 0.20]
```

Passo 5: calcule linha por linha.

```text
cw[0] =
    0.000101200000 * 0.50
  + 0.000049000000 * 0.30
  + (-0.000024600000) * 0.20

cw[0] = 0.000050600000 + 0.000014700000 - 0.000004920000
cw[0] = 0.000060380000

cw[1] =
    0.000049000000 * 0.50
  + 0.000024400000 * 0.30
  + (-0.000012200000) * 0.20

cw[1] = 0.000024500000 + 0.000007320000 - 0.000002440000
cw[1] = 0.000029380000

cw[2] =
    (-0.000024600000) * 0.50
  + (-0.000012200000) * 0.30
  + 0.000006966667 * 0.20

cw[2] = -0.000012300000 - 0.000003660000 + 0.000001393333
cw[2] = -0.000014566667
```

Resultado do step 5:

```text
Cw = [0.000060380000, 0.000029380000, -0.000014566667]

com 6 casas decimais:

Cw = [0.000060, 0.000029, -0.000015]
```

Esse resultado sai da funcao `matvec`, recebendo `covariance` e `weights`.

#### 5.1 O que este passo transforma

Este passo transforma uma matriz de risco entre ativos em um vetor de risco ajustado pelos pesos do portfolio.

A matriz `C` guarda a covariancia entre todos os pares de ativos:

```text
C = matriz 3 x 3
```

O vetor `w` guarda quanto do portfolio esta em cada ativo:

```text
w = [0.50, 0.30, 0.20]
```

Formula matematica:

```text
Cw = C * w
```

Ligacao com codigo:

```text
matvec(covariance, weights)
```

#### 5.2 Formula de cada posicao de `Cw`

Cada posicao `cw[i]` calcula como o ativo `i` se relaciona com o risco do portfolio ponderado pelos pesos.

Formula matematica:

```text
cw[i] = C[i][0] * w[0] + C[i][1] * w[1] + C[i][2] * w[2]
```

Como temos 3 ativos, a formula aberta fica:

```text
cw[0] = C[0][0] * w[0] + C[0][1] * w[1] + C[0][2] * w[2]
cw[1] = C[1][0] * w[0] + C[1][1] * w[1] + C[1][2] * w[2]
cw[2] = C[2][0] * w[0] + C[2][1] * w[1] + C[2][2] * w[2]
```

Ligacao com codigo:

```text
matvec(covariance, weights)
```

Esse exemplo sai da funcao `matvec`, recebendo `covariance` e `weights`.

#### 5.3 Como `Cw` entra na variancia final

`Cw` ainda nao e o risco final do portfolio; ele e o meio do caminho para calcular `w' C w`.

Formula matematica:

```text
portfolio_variance = w' C w
portfolio_variance = w' (Cw)
portfolio_variance = dot(w, Cw)
```

Separando em dois passos:

```text
1. Cw = C * w
2. w' Cw = dot(w, Cw)
```

Ligacao com codigo:

```text
cw = matvec(covariance, weights)
portfolio_variance = dot(weights, cw)
```

#### 5.4 Interpretacao de risco

Cada valor `cw[i]` mostra a contribuicao do ativo `i` depois de considerar como ele se mistura com os pesos dos outros ativos.

Valor matematico analisado:

```text
cw[i]
```

Ligacao com codigo:

```text
cw = matvec(covariance, weights)
cw[i]
```

Leitura pratica:

```text
se Cw[i] for alto e positivo:
o ativo i esta aumentando o risco conjunto do portfolio

se Cw[i] for negativo:
o ativo i esta ajudando a compensar o risco dos outros ativos

se Cw[i] for perto de zero:
o ativo i tem pouca relacao linear com o risco combinado do portfolio
```

### 6. Variancia diaria do portfolio

A variancia diaria do portfolio serve para transformar todos os riscos e covariancias dos ativos em um unico numero de risco diario.

Formula completa do step 6, do inicio ao resultado:

```text
Entrada deste step:

w  = vetor de pesos do portfolio
Cw = vetor intermediario calculado no step 5

Saida deste step:

portfolio_variance = variancia diaria do portfolio
```

Passo 1: escreva a conta principal.

```text
portfolio_variance = w' C w
```

Passo 2: use o resultado do step 5 para simplificar.

```text
Cw = C * w

entao:

portfolio_variance = w' (Cw)
portfolio_variance = dot(w, Cw)
```

Neste step, a funcao nao precisa receber `C` de novo.

`C` ja foi usado no step 5 para calcular `Cw`.

Passo 3: escreva a formula aberta.

```text
portfolio_variance =
    w[0] * cw[0]
  + w[1] * cw[1]
  + w[2] * cw[2]
```

Passo 4: substitua os valores deste exercicio.

```text
w = [0.50, 0.30, 0.20]
Cw = [0.000060380000, 0.000029380000, -0.000014566667]

portfolio_variance =
    0.50 * 0.000060380000
  + 0.30 * 0.000029380000
  + 0.20 * (-0.000014566667)
```

Passo 5: calcule termo por termo.

```text
portfolio_variance =
    0.000030190000
  + 0.000008814000
  - 0.000002913333

portfolio_variance = 0.000036090667
```

Resultado do step 6:

```text
portfolio_variance = 0.000036
```

Esse resultado sai da funcao `quadratic_form`, recebendo `weights` e `cw`.

#### 6.1 Ligacao com codigo

A funcao `quadratic_form` deve receber `Cw` ja calculado e fazer somente o produto interno entre `weights` e `Cw`.

Formula matematica:

```text
portfolio_variance = dot(weights, cw)
```

Funcao no codigo:

```text
quadratic_form(weights, cw)
```

#### 6.2 Interpretacao de risco

Este numero ainda esta em unidade de variancia, entao ele nao e tao intuitivo quanto volatilidade.

Valor matematico analisado:

```text
portfolio_variance = 0.000036090667
```

Ligacao com codigo:

```text
portfolio_variance = quadratic_form(weights, cw)
```

### 7. Volatilidade diaria do portfolio

A volatilidade diaria serve para transformar a variancia diaria em uma medida de risco na mesma unidade dos retornos diarios.

Formula completa do step 7, do inicio ao resultado:

```text
Entrada deste step:

portfolio_variance = variancia diaria calculada no step 6

Saida deste step:

daily_vol = volatilidade diaria do portfolio
```

Passo 1: escreva a conta principal.

```text
daily_vol = sqrt(portfolio_variance)
```

Passo 2: substitua o valor deste exercicio.

```text
daily_vol = sqrt(0.000036090667)
daily_vol = 0.006007550804
```

Resultado do step 7:

```text
daily_vol = 0.006008
daily_vol aproximadamente 0.6008% ao dia
```

Esse resultado sai da funcao `daily_volatility`, recebendo `portfolio_variance`.

#### 7.1 Ligacao com codigo

A funcao `daily_volatility` deve tirar a raiz quadrada da variancia diaria.

Formula matematica:

```text
daily_vol = sqrt(portfolio_variance)
```

Funcao no codigo:

```text
daily_volatility(portfolio_variance)
```

### 8. Volatilidade anualizada do portfolio

A volatilidade anualizada serve para colocar o risco diario em uma escala anual, assumindo 252 pregoes por ano.

Formula completa do step 8, do inicio ao resultado:

```text
Entrada deste step:

daily_vol = volatilidade diaria calculada no step 7
periods_per_year = quantidade de pregoes por ano

Saida deste step:

annual_vol = volatilidade anualizada do portfolio
```

Passo 1: escreva a conta principal.

```text
annual_vol = daily_vol * sqrt(periods_per_year)
```

Passo 2: substitua os valores deste exercicio.

```text
daily_vol = 0.006007550804
periods_per_year = 252

annual_vol = 0.006007550804 * sqrt(252)
```

Passo 3: calcule.

```text
sqrt(252) = 15.874507866

annual_vol = 0.006007550804 * 15.874507866
annual_vol = 0.095366912501
```

Resultado do step 8:

```text
annual_vol = 0.095367
annual_vol aproximadamente 9.5367% ao ano
```

Esse resultado sai da funcao `annualized_volatility`, recebendo `daily_vol` e `periods_per_year`.

#### 8.1 Ligacao com codigo

A funcao `annualized_volatility` deve multiplicar a volatilidade diaria por `sqrt(periods_per_year)`.

Formula matematica:

```text
annual_vol = daily_vol * sqrt(periods_per_year)
```

Funcao no codigo:

```text
annualized_volatility(daily_vol, periods_per_year)
```

### 9. Conclusao sobre diversificacao

A conclusao sobre diversificacao serve para transformar os numeros calculados em uma leitura curta sobre risco conjunto do portfolio.

Formula completa do step 9, do inicio ao resultado:

```text
Entrada deste step:

C = matriz de covariancia calculada no step 4
Cw = vetor intermediario calculado no step 5
portfolio_variance = variancia calculada no step 6
daily_vol = volatilidade diaria calculada no step 7
annual_vol = volatilidade anualizada calculada no step 8

Saida deste step:

conclusion = nota curta sobre diversificacao e risco
```

Passo 1: leia as covariancias fora da diagonal.

```text
C[0][1] =  0.000049 -> ativos 0 e 1 aumentam risco conjunto
C[0][2] = -0.000025 -> ativo 2 tende a compensar ativo 0
C[1][2] = -0.000012 -> ativo 2 tende a compensar ativo 1
```

Passo 2: leia o vetor `Cw`.

```text
Cw = [0.000060, 0.000029, -0.000015]

Cw[0] positivo -> ativo 0 aumenta o risco combinado
Cw[1] positivo -> ativo 1 aumenta o risco combinado
Cw[2] negativo -> ativo 2 ajuda a compensar o risco combinado
```

Passo 3: leia o risco final.

```text
portfolio_variance = 0.000036
daily_vol = 0.006008
annual_vol = 0.095367
```

Passo 4: escreva a conclusao.

```text
O portfolio tem volatilidade diaria aproximada de 0.60% e volatilidade anualizada aproximada de 9.54%.
Os ativos 0 e 1 aumentam risco conjunto por terem covariancia positiva.
O ativo 2 ajuda na diversificacao porque tem covariancia negativa com os ativos 0 e 1.
```

Esse resultado sai do trecho final de `run_exercise`, depois que `covariance_matrix`, `matvec`, `quadratic_form` e `annualized_volatility` ja foram chamados.

#### 9.1 Ligacao com codigo

O trecho final de `run_exercise` deve imprimir os resultados e uma conclusao curta usando os sinais da matriz de covariancia e o risco final calculado.

Valores usados:

```text
covariance
cw
portfolio_variance
daily_vol
annual_vol
```

Funcao/trecho no codigo:

```text
run_exercise()
```

## Resultado de referencia

Use estes valores para conferir sua implementacao:

```text
means = [0.004000, 0.002000, -0.000167]

centered primeira linha = [0.006000, 0.002000, -0.001833]

covariance = [
    [ 0.000101,  0.000049, -0.000025],
    [ 0.000049,  0.000024, -0.000012],
    [-0.000025, -0.000012,  0.000007],
]

Cw = [0.000060, 0.000029, -0.000015]

portfolio_variance = 0.000036
daily_vol          = 0.006008
annual_vol         = 0.095367
```

Interpretacao esperada: os ativos 0 e 1 tem covariancia positiva; eles tendem a andar juntos. O ativo 2 tem covariancia negativa com os dois primeiros, entao ajuda na diversificacao. Mesmo assim, o portfolio ainda tem risco porque os pesos em ativos 0 e 1 sao grandes.

## O que implementar em Python

Comece sem `numpy`. A proposta e entender as contas de matriz.

Funcoes sugeridas:

```python
def column_means(matrix: list[list[float]]) -> list[float]:
    ...

def center_matrix(matrix: list[list[float]], means: list[float]) -> list[list[float]]:
    ...

def transpose(matrix: list[list[float]]) -> list[list[float]]:
    ...

def matrix_shape(matrix: list[list[float]]) -> tuple[int, int]:
    ...

def validate_rectangular(matrix: list[list[float]]) -> None:
    ...

def validate_matmul_dimensions(a: list[list[float]], b: list[list[float]]) -> None:
    ...

def matmul(a: list[list[float]], b: list[list[float]]) -> list[list[float]]:
    ...

def matvec(matrix: list[list[float]], vector: list[float]) -> list[float]:
    ...

def covariance_matrix(centered: list[list[float]]) -> list[list[float]]:
    ...

def dot(u: list[float], v: list[float]) -> float:
    ...

def quadratic_form(weights: list[float], cw: list[float]) -> float:
    ...

def daily_volatility(portfolio_variance: float) -> float:
    ...

def annualized_volatility(daily_vol: float, periods_per_year: int) -> float:
    ...
```

No `run_exercise()`:

1. calcule `means`;
2. calcule `centered`;
3. calcule `covariance`;
4. calcule `cw = matvec(covariance, weights)`;
5. calcule `portfolio_variance = quadratic_form(weights, cw)`;
6. calcule `daily_vol`;
7. calcule `annual_vol`;
8. imprima tudo com 6 casas decimais;
9. escreva uma conclusao curta.

## O que implementar em C++

Use `std::vector<double>` e `std::vector<std::vector<double>>`.

Voce vai precisar de:

```cpp
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
```

Funcoes sugeridas, somente declaracoes:

```cpp
using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;
using Shape = std::pair<std::size_t, std::size_t>;

Vector column_means(const Matrix& matrix);
Matrix center_matrix(const Matrix& matrix, const Vector& means);
Matrix transpose(const Matrix& matrix);
Shape matrix_shape(const Matrix& matrix);
void validate_rectangular(const Matrix& matrix);
void validate_matmul_dimensions(const Matrix& a, const Matrix& b);
Matrix matmul(const Matrix& a, const Matrix& b);
Vector matvec(const Matrix& matrix, const Vector& vector);
Matrix covariance_matrix(const Matrix& centered);
double dot(const Vector& u, const Vector& v);
double quadratic_form(const Vector& weights, const Vector& cw);
double daily_volatility(double portfolio_variance);
double annualized_volatility(double daily_vol, int periods_per_year);
void print_vector(const std::string& name, const Vector& values);
void print_matrix(const std::string& name, const Matrix& matrix);
```

No `run_exercise()`:

1. crie `returns`, `weights` e `periods_per_year`;
2. chame as funcoes na mesma ordem das formulas;
3. imprima os blocos 1 a 9;
4. mantenha `std::fixed << std::setprecision(6)`.

## Como saber se voce entendeu

1. Por que a matriz precisa ser centralizada antes da covariancia?
2. O que significa uma covariancia positiva entre dois ativos?
3. O que significa uma covariancia negativa?
4. Por que `w' C w` vira um numero unico?
5. Por que tiramos raiz quadrada da variancia para chegar na volatilidade?
6. Por que multiplicamos a volatilidade diaria por `sqrt(252)`?

## Termos para pesquisar

Portugues:

- matriz de covariancia;
- covariancia amostral;
- variancia de portfolio;
- forma quadratica w transposto C w;
- volatilidade anualizada;
- diversificacao de portfolio.

Ingles:

- covariance matrix;
- sample covariance;
- portfolio variance;
- quadratic form portfolio risk;
- annualized volatility;
- diversification covariance.

## Referencias

Para algebra linear e matrizes:

- [MIT OpenCourseWare 18.065 - Matrix Methods in Data Analysis, Signal Processing, and Machine Learning](https://ocw.mit.edu/courses/18-065-matrix-methods-in-data-analysis-signal-processing-and-machine-learning-spring-2018/)
- [Stanford CS229 - Linear Algebra Review and Reference](https://cs229.stanford.edu/section-spring2019/cs229-linalg.pdf)

Para conferir conceitos e ferramentas depois de implementar manualmente:

- [NumPy `cov`](https://numpy.org/doc/2.1/reference/generated/numpy.cov.html)
- [NumPy `matmul`](https://numpy.org/devdocs/reference/generated/numpy.matmul.html)
- [NumPy `dot`](https://numpy.org/doc/stable/reference/generated/numpy.dot.html)
- [cppreference `std::vector`](https://en.cppreference.com/w/cpp/container/vector)

## Como rodar

```powershell
python .\python\main.py
g++ -std=c++23 -O2 -Wall -Wextra .\cpp\main.cpp -o .\cpp\main.exe
.\cpp\main.exe
```

## Entregavel

Preencha `notes.md` respondendo:

```text
Por que covariancias fora da diagonal importam para diversificacao?
Use a matriz de covariancia e o valor de annual_vol para justificar.
```
