# Metodologia para criar exercicios de estudo

Use esta metodologia sempre que um item do roadmap estiver abstrato demais. O objetivo e transformar um topico como "vetores", "PCA", "SVD", "risco" ou "backtesting" em um exercicio que alguem consiga estudar mesmo sem saber por onde comecar.

## Principio

Um bom exercicio precisa responder tres perguntas antes de pedir codigo:

1. Por que isso importa?
2. O que exatamente eu vou construir?
3. Como eu sei que fiz certo?

Se o README nao responder essas tres perguntas, o exercicio ainda esta generico demais.

## Regra da primeira frase

Regra curta de revisao:

```text
A PORRA DA PRIMEIRA FRASE TEM QUE SER O INFERNO DA EXPLICACAO.
```

Na pratica: depois de qualquer titulo ou subtitulo que introduza um conceito, formula, processo ou passo intermediario, a primeira frase precisa explicar para que aquilo serve no exercicio.

A primeira frase deve responder:

```text
Por que estou calculando isso?
O que esse passo entrega para o resultado final?
Como isso se conecta com o problema pratico?
```

Nao comece um topico assim:

```markdown
### 5. Vetor intermediario `Cw`

Funcao no codigo:
```

Comece assim:

```markdown
### 5. Vetor intermediario `Cw`

O vetor `Cw` serve para aplicar os pesos do portfolio na matriz de covariancia e preparar o calculo final da variancia `w' C w`.
```

Teste de qualidade: se a primeira frase nao explica o objetivo do passo, reescreva antes de adicionar formula ou codigo.

## Estrutura obrigatoria de cada topico

Cada topico do README deve seguir esta ordem:

```text
titulo do topico
explicacao com contexto pratico
formula completa do step principal, passo a passo

subtopico
explicacao com contexto pratico
formulas matematicas
ligacao com codigo
```

Na pratica:

~~~~markdown
### 5. Vetor intermediario `Cw`

O vetor `Cw` serve para aplicar os pesos do portfolio na matriz de covariancia e preparar o calculo final da variancia `w' C w`.

Formula completa do step 5, do inicio ao resultado:

```text
Entrada:
C = matriz de covariancia
w = vetor de pesos

Conta principal:
Cw = C * w

Formula aberta:
cw[0] = C[0][0] * w[0] + C[0][1] * w[1] + C[0][2] * w[2]
cw[1] = C[1][0] * w[0] + C[1][1] * w[1] + C[1][2] * w[2]
cw[2] = C[2][0] * w[0] + C[2][1] * w[1] + C[2][2] * w[2]

Resultado:
Cw = [valor_0, valor_1, valor_2]
```

#### 5.1 Formula do `Cw`

Esta formula calcula, para cada ativo, como ele se relaciona com o risco combinado do portfolio ponderado pelos pesos.

Formula matematica:

```text
cw[i] = C[i][0] * w[0] + C[i][1] * w[1] + C[i][2] * w[2]
```

Funcao no codigo:

```text
matvec(covariance, weights)
```
~~~~

Regras:

- o topico principal nunca deve comecar por formula, funcao ou codigo;
- o topico principal precisa explicar o papel pratico daquele bloco no exercicio;
- o topico principal precisa mostrar a formula completa do step, passo a passo, antes de quebrar em subtopicos;
- cada subtopico tambem precisa abrir com contexto pratico;
- depois do contexto entram formulas matematicas;
- depois da formula vem a ligacao com o codigo;
- codigo em README deve ser assinatura, chamada ou pseudocodigo curto; nao entregue implementacao pronta quando o objetivo for treino.

A formula completa do step principal deve mostrar, quando aplicavel:

- entradas usadas naquele step;
- saida produzida naquele step;
- conta principal;
- dimensoes, se tiver vetor ou matriz;
- formula aberta;
- substituicao numerica;
- resultado final daquele step;
- qual funcao do codigo produz esse resultado.

## Regras para criar funcoes

Crie funcoes para representar operacoes com responsabilidade propria, nao para embrulhar uma unica funcao simples sem adicionar nada.

Regra principal:

```text
Nao crie funcao redundante quando ela for apenas um wrapper de outra funcao simples e nao composta.
```

Regra obrigatoria de revisao no codigo:

```text
Se uma funcao do codigo existir apenas para chamar outra funcao simples, essa funcao nao deve existir.
```

Isso vale para:

- starter em Python;
- starter em C++;
- solucao de referencia;
- exemplos dentro do README;
- qualquer codigo gerado junto com o exercicio.

Quando encontrar esse caso, remova a funcao wrapper e use a chamada direta no fluxo principal.

Um wrapper e redundante quando:

- so chama uma funcao simples ja existente;
- nao valida entrada;
- nao combina multiplas operacoes;
- nao melhora a clareza do fluxo principal;
- nao representa uma formula composta que precisa ser treinada separadamente.

Exemplo ruim:

```python
def quadratic_form(weights: list[float], cw: list[float]) -> float:
    return dot(weights, cw)
```

Nesse caso, se o step ja calculou `cw`, a chamada direta e mais clara:

```python
portfolio_variance = dot(weights, cw)
```

Exemplo aceitavel:

```python
def quadratic_form(weights: list[float], covariance: list[list[float]]) -> float:
    cw = matvec(covariance, weights)
    return dot(weights, cw)
```

Aqui a funcao nao e apenas um wrapper simples, porque ela compoe duas operacoes:

```text
1. Cw = C * w
2. w' Cw = dot(w, Cw)
```

Regra de decisao:

```text
Se a funcao apenas renomeia uma chamada simples, nao crie a funcao.
Se a funcao combina passos, valida dados ou representa uma unidade conceitual importante, ela pode existir.
```

## Regras obrigatorias de testes

Todo exercicio com codigo precisa vir com testes para validar as funcoes implementadas.

Os testes nao podem validar apenas o dataset principal do README. Eles precisam validar tambem o funcionamento matematico das funcoes.

Regra principal:

```text
Teste dado de referencia e teste propriedades matematicas.
```

O conjunto minimo de testes deve cobrir:

- resultado esperado para os dados de partida do README;
- pelo menos um caso pequeno calculavel de cabeca;
- propriedades matematicas da funcao;
- caso de borda simples, quando fizer sentido;
- consistencia entre operacoes relacionadas.

Exemplos de propriedades matematicas:

- `dot(u, v) == dot(v, u)`;
- `dot(a * u, v) == a * dot(u, v)`;
- `matvec(I, v) == v`;
- `transpose(transpose(A)) == A`;
- matriz de covariancia deve ser simetrica;
- variancia de portfolio nao deve ser negativa quando a matriz de covariancia for valida;
- volatilidade deve ser `sqrt(variancia)`;
- anualizacao deve multiplicar por `sqrt(periods_per_year)`.

Evite testes fracos como:

```text
rode o exemplo principal e compare so o print final.
```

Prefira testes que chamam as funcoes diretamente:

```text
test_dot_commutativity
test_dot_linearity
test_transpose_twice_returns_original
test_covariance_matrix_is_symmetric
test_portfolio_variance_matches_manual_calculation
```

Os testes devem existir para Python e C++ quando o exercicio tiver as duas linguagens.

Padrao recomendado:

```text
python/tests/test_main.py
cpp/tests.cpp
```

Se o exercicio for muito pequeno, os testes de C++ podem ficar em `cpp/main_test.cpp`, mas ainda precisam ser separados do fluxo principal de execucao.

## Estrutura recomendada do README

Use esta ordem como padrao unico para novos READMEs de exercicio.

Nao misture este formato com templates antigos.

### 1. Titulo do que o MD ira fazer

```text
# [Titulo do que o md ira fazer]
```

Logo abaixo do titulo, escreva o objetivo final em uma frase direta:

```text
Objetivo final: [o que deve ser calculado, produzido ou concluido].
```

### 2. Qual tipo de problema o objetivo resolve

Use o formato:

```text
## Qual tipo de problema [objetivo] resolve
```

Explique o problema real que aquele exercicio resolve em quant.

Inclua uma exemplificacao basica dentro do texto, nao separada demais da explicacao.

### 3. Glossario

Use:

```text
## glossario
```

Cada termo precisa ter uma explicacao curta e pratica.

### 4. Dados de partida

Use:

```text
## dados de partida
```

Forneca dados pequenos, fechados e hardcoded.

### 5. Dados de resultado

Use:

```text
## dados de resultado
```

Mostre os valores finais esperados para conferir a implementacao.

### 6. Tipagem das funcoes py e c++

Use:

```text
## tipagem das funcoes py e c++
```

Liste somente assinaturas/tipagens, sem entregar implementacao pronta.

### 7. Referencias + termos para pesquisar

Use:

```text
## Referencias + termos para pesquisar
```

Inclua termos em portugues e ingles, junto com referencias confiaveis.

### 8. Como rodar

Use:

```text
## Como rodar
```

Inclua comandos concretos para rodar Python, C++ e os testes das duas linguagens.

Os comandos de teste sao obrigatorios. O README precisa deixar claro como validar:

- execucao normal do exercicio;
- testes das funcoes Python;
- testes das funcoes C++;
- quais propriedades matematicas os testes cobrem.

### 9. Como saber se voce entendeu

Use exatamente:

```text
## **Como saber se voce entendeu**
```

Inclua perguntas conceituais curtas.

### 10. Steps

Depois das secoes principais, crie os steps do exercicio.

Cada step principal deve seguir:

```text
### step 1
descricao enxuta do topico
matematica em alto nivel do topico

#### step 1.1
matematica em alto nivel do topico + relacao com o codigo
```

Regra:

- o step principal explica o que o passo faz;
- o step principal mostra a matematica em alto nivel;
- os substeps conectam a matematica com as funcoes que devem ser implementadas;
- os nomes das funcoes precisam aparecer nos substeps, nao escondidos no final.

### Regras gerais dos dados

- use vetores/matrizes pequenas;
- deixe os dados hardcoded no README;
- explique a unidade dos numeros;
- inclua pelo menos um caso que tenha interpretacao clara.

### Regras gerais das formulas

Cada formula ou bloco matematico deve ter:

- nome;
- para que serve aquele passo no calculo final;
- funcao correspondente no codigo;
- expressao;
- interpretacao;
- cuidado comum.

Antes de mostrar a formula, explique em uma ou duas frases o papel daquele calculo. A pessoa precisa entender por que esta fazendo aquele passo antes de implementar.

Regra importante: a relacao entre explicacao e codigo precisa ser direta. Se o texto mostra um exemplo numerico, diga de qual funcao aquele exemplo saiu.

### Regras gerais das referencias

Use referencias confiaveis e diretamente relacionadas ao exercicio.

Prioridade:

1. documentacao oficial;
2. cursos abertos de universidades;
3. livros ou notas academicas;
4. artigos tecnicos reconhecidos.

Evite jogar links genericos demais. A referencia precisa ajudar naquele exercicio.

## Checklist de qualidade

Antes de considerar o exercicio pronto, confira:

- existe contexto suficiente para alguem iniciante;
- existe uma pergunta concreta;
- os dados de partida estao no README;
- as formulas foram explicadas;
- cada topico segue a ordem: titulo, explicacao com contexto pratico, subtopicos, formulas e ligacao com codigo;
- cada step principal mostra a formula completa passo a passo, incluindo entrada, saida, substituicao numerica e resultado;
- cada topico de formula/processo explica para que aquele passo serve antes de entrar na conta;
- cada formula/exemplo aponta para a funcao correspondente no codigo;
- os passos de Python e C++ tem funcoes especificas;
- as funcoes sugeridas nao sao wrappers redundantes de chamadas simples ja existentes;
- nenhuma funcao do codigo existe apenas para chamar outra funcao simples;
- os starters mostram assinaturas/declaracoes de funcoes, mas nao entregam a implementacao;
- existem testes para Python quando houver codigo Python;
- existem testes para C++ quando houver codigo C++;
- os testes chamam funcoes diretamente, nao apenas comparam o print final;
- os testes cobrem propriedades matematicas, nao apenas os dados de input do README;
- existem resultados de referencia;
- existem perguntas para testar entendimento;
- existem termos de busca em PT e EN;
- existem referencias uteis;
- o entregavel final esta claro.

## Anti-padroes

Evite frases como:

- "implemente algo sobre o tema";
- "gere ou carregue um dataset";
- "valide com alguns cenarios";
- "faca uma analise";
- "construa um script exploratorio".
- entregar o corpo da funcao no starter quando o objetivo e treinar implementacao.
- explicar uma formula sem dizer qual funcao do codigo implementa aquela formula.
- comecar um topico direto pela formula sem explicar para que aquele passo serve no calculo final.
- criar funcao que apenas chama outra funcao simples, sem validacao, composicao ou ganho real de clareza.
- manter no codigo uma funcao wrapper que so repassa para outra funcao simples.
- entregar codigo sem testes.
- testar apenas o exemplo principal do README sem validar propriedades matematicas das funcoes.

Troque por instrucoes fechadas:

- quais dados usar;
- quais funcoes criar;
- quais metricas calcular;
- quais valores esperar;
- qual conclusao escrever.

## Exemplo unico de referencia

Este e o unico exemplo-base para novos READMEs de exercicio. Use esta ordem, estes nomes de secoes e este nivel de detalhe como referencia.

~~~~markdown
# Matriz de covariancia e risco de portfolio

Objetivo final: calcular a volatilidade diaria e anualizada de um portfolio usando retornos de ativos, matriz de covariancia e pesos.

## Qual tipo de problema matriz de covariancia resolve

Em quant, a matriz de covariancia resolve o problema de medir risco conjunto entre ativos. Ela nao olha apenas se cada ativo e volatil sozinho; ela mede tambem se os ativos tendem a cair juntos, subir juntos ou se compensar.

Exemplo pratico: se dois ativos caem juntos em dias ruins, eles aumentam o risco do portfolio. Se um ativo tende a subir quando outro cai, ele pode ajudar na diversificacao.

## glossario

- `returns`: matriz de retornos diarios; linhas sao dias, colunas sao ativos.
- `weights`: pesos do portfolio.
- `centered`: retornos depois de subtrair a media de cada ativo.
- `covariance`: matriz que mede como os ativos se movem juntos.
- `Cw`: vetor intermediario que aplica os pesos na matriz de covariancia.
- `portfolio_variance`: variancia diaria do portfolio.
- `daily_vol`: volatilidade diaria.
- `annual_vol`: volatilidade anualizada.

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

## dados de resultado

```text
means = [0.004000, 0.002000, -0.000167]
Cw = [0.000060, 0.000029, -0.000015]
portfolio_variance = 0.000036
daily_vol = 0.006008
annual_vol = 0.095367
```

## tipagem das funcoes py e c++

Python:

```python
def column_means(matrix: list[list[float]]) -> list[float]: ...
def center_matrix(matrix: list[list[float]], means: list[float]) -> list[list[float]]: ...
def transpose(matrix: list[list[float]]) -> list[list[float]]: ...
def matmul(a: list[list[float]], b: list[list[float]]) -> list[list[float]]: ...
def matvec(matrix: list[list[float]], vector: list[float]) -> list[float]: ...
def dot(u: list[float], v: list[float]) -> float: ...
```

C++:

```cpp
using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

Vector column_means(const Matrix& matrix);
Matrix center_matrix(const Matrix& matrix, const Vector& means);
Matrix transpose(const Matrix& matrix);
Matrix matmul(const Matrix& a, const Matrix& b);
Vector matvec(const Matrix& matrix, const Vector& vector);
double dot(const Vector& u, const Vector& v);
```

## Referencias + termos para pesquisar

Termos:

- matriz de covariancia risco de portfolio
- covariancia amostral
- variancia de portfolio
- covariance matrix portfolio risk
- sample covariance
- portfolio variance
- quadratic form
- linear algebra matrix multiplication

Referencias:

- MIT 18.065 Matrix Methods in Data Analysis, Signal Processing, and Machine Learning
- Stanford CS229 Linear Algebra Review
- Bodie, Kane & Marcus - Investments

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

Os testes devem chamar as funcoes diretamente e validar pelo menos:

- resultado esperado para os dados de partida;
- `dot` multiplicando posicao com posicao;
- `dot(u, v) == dot(v, u)`;
- `transpose(transpose(A)) == A`;
- matriz de covariancia simetrica;
- variancia de portfolio calculada manualmente;
- volatilidade diaria e anualizada pela raiz quadrada correta.

## **Como saber se voce entendeu**

1. Por que precisamos centralizar os retornos antes da covariancia?
2. O que significa covariancia positiva?
3. Por que `Cw` vem antes de calcular a variancia final?
4. Por que anualizamos volatilidade usando `sqrt(252)`?

### step 1

A media de retorno de cada ativo serve para descobrir o retorno medio diario de cada coluna antes de medir desvios e risco.

Matematica em alto nivel:

```text
media do ativo = soma dos retornos daquele ativo / quantidade de dias
```

#### step 1.1

A funcao deve percorrer cada coluna da matriz `returns`, somar os valores e dividir por `n`.

```text
mean[j] = soma returns[i][j] para todos os dias i / n
```

Funcao relacionada:

```text
column_means(returns)
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

Funcao relacionada:

```text
center_matrix(returns, means)
```

### step 3

A matriz de covariancia resume como os ativos se movem juntos e prepara o calculo do risco do portfolio.

Matematica em alto nivel:

```text
C = Xc' Xc / (n - 1)
```

#### step 3.1

A funcao deve transpor a matriz centralizada para permitir a multiplicacao `Xc' Xc`.

```text
Xc' tem formato ativos x dias
Xc  tem formato dias x ativos
```

Funcao relacionada:

```text
transpose(centered)
```

#### step 3.2

A funcao deve multiplicar a matriz transposta pela matriz centralizada e dividir cada celula por `n - 1`.

```text
covariance[a][b] = soma centered[i][a] * centered[i][b] para todos os dias i / (n - 1)
```

Funcoes relacionadas:

```text
matmul(transpose(centered), centered)
covariance_matrix(centered)
```

### step 4

O vetor `Cw` aplica os pesos do portfolio na matriz de covariancia antes da variancia final.

Matematica em alto nivel:

```text
Cw = C * w
```

#### step 4.1

A funcao deve multiplicar cada linha da matriz de covariancia pelo vetor de pesos.

```text
cw[i] = covariance[i][0] * weights[0] + covariance[i][1] * weights[1] + covariance[i][2] * weights[2]
```

Funcao relacionada:

```text
matvec(covariance, weights)
```

### step 5

A variancia diaria do portfolio transforma `Cw` em um unico numero de risco usando novamente os pesos.

Matematica em alto nivel:

```text
portfolio_variance = w' C w
portfolio_variance = dot(weights, Cw)
```

#### step 5.1

A funcao deve multiplicar os vetores posicao com posicao, nao todos contra todos.

```text
portfolio_variance = weights[0] * cw[0] + weights[1] * cw[1] + weights[2] * cw[2]
```

Funcao relacionada:

```text
dot(weights, cw)
```

### step 6

A volatilidade transforma variancia em uma medida de risco na mesma escala dos retornos.

Matematica em alto nivel:

```text
daily_vol = sqrt(portfolio_variance)
annual_vol = daily_vol * sqrt(periods_per_year)
```

#### step 6.1

A funcao deve aplicar raiz quadrada na variancia diaria e depois anualizar pelo numero de periodos.

Funcoes relacionadas:

```text
sqrt(portfolio_variance)
sqrt(periods_per_year)
```
~~~~
