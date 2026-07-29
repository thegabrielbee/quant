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

## Estrutura recomendada do README

### 1. Titulo

Use o formato:

```text
# Item - Nome concreto do exercicio
```

Exemplo:

```text
# Vetores - Retorno, risco e similaridade como operacoes vetoriais
```

### 2. Contexto

Explique o assunto em linguagem simples, assumindo que a pessoa ainda nao sabe fazer.

Inclua:

- onde o topico aparece no roadmap;
- por que ele importa para quant;
- qual intuicao o exercicio quer construir;
- qual problema pratico ele ajuda a resolver.

### 3. Pergunta do exercicio

Escreva uma pergunta concreta, de preferencia ligada a uma situacao real.

Exemplos:

- A estrategia ganhou dinheiro por alpha proprio ou so porque andou junto com o mercado?
- A matriz de covariancia e valida para usar em otimizacao?
- O primeiro componente principal parece um fator de mercado?
- O backtest esta usando informacao do futuro?

### 4. Traducao para linguagem quant

Crie uma ponte entre o conceito matematico e o uso financeiro/computacional.

Inclua um glossario curto com termos como:

- retorno;
- excesso de retorno;
- beta;
- alpha;
- residual;
- volatilidade;
- covariancia;
- fator de risco;
- drawdown;
- leakage;
- out-of-sample.

Cada termo deve ter uma explicacao de uma ou duas linhas.

### 5. Dados de partida

Forneca dados pequenos e fechados para a pessoa nao comecar do vazio.

Regras:

- use vetores/matrizes pequenas;
- deixe os dados hardcoded no README;
- explique a unidade dos numeros;
- inclua pelo menos um caso que tenha interpretacao clara.

Exemplo:

```text
strategy = [0.012, -0.004, 0.006]
market   = [0.010, -0.006, 0.004]
risk_free_daily = 0.0002
```

### 6. Objetivo final

Liste exatamente o que deve ser calculado ou produzido.

Exemplo:

1. calcular excesso de retorno;
2. calcular beta;
3. calcular componente explicada pelo mercado;
4. calcular residual;
5. concluir se parece alpha ou beta.

### 7. Formulas

Inclua as formulas necessarias antes do codigo.

Cada formula deve ter:

- nome;
- para que serve aquele passo no calculo final;
- funcao correspondente no codigo;
- expressao;
- interpretacao;
- cuidado comum.

Antes de mostrar a formula, explique em uma ou duas frases o papel daquele calculo. A pessoa precisa entender por que esta fazendo aquele passo antes de implementar.

Exemplo:

```text
Funcao no codigo:
projection_beta(strategy_excess, market_excess)
```

Formula:

```text
beta = dot(strategy_excess, market_excess) / dot(market_excess, market_excess)
```

Interpretacao: mede a exposicao da estrategia ao mercado.

Regra importante: a relacao entre explicacao e codigo precisa ser direta. Se o texto mostra um exemplo numerico, diga de qual funcao aquele exemplo saiu.

Exemplo:

```text
Esse exemplo sai da funcao `scale_vector`, recebendo `beta` e `market_excess`.
```

### 8. O que implementar em Python

Liste funcoes especificas, nao comandos vagos.

Bom:

```python
def dot(u: list[float], v: list[float]) -> float:
    ...
```

Ruim:

```text
implemente uma analise em Python
```

O roteiro deve dizer:

1. quais dados criar;
2. quais funcoes implementar;
3. quais calculos fazer;
4. o que imprimir;
5. como interpretar a saida.

### 9. O que implementar em C++

Faca o mesmo para C++, mencionando as estruturas e bibliotecas esperadas.

Exemplo:

```cpp
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
```

Inclua assinaturas sugeridas, mas nao entregue o corpo da funcao no starter. A ideia e deixar a pessoa treinar C++ escrevendo a implementacao.

```cpp
double dot(const std::vector<double>& u, const std::vector<double>& v);
double norm_l2(const std::vector<double>& u);
```

No arquivo `cpp/main.cpp`, prefira este padrao:

```cpp
double dot(const std::vector<double>& u, const std::vector<double>& v);

// Escreva a implementacao abaixo.
```

Evite este padrao em starters de exercicio:

```cpp
double dot(const std::vector<double>& u, const std::vector<double>& v) {
    return /* solucao pronta */;
}
```

### 10. Resultado de referencia

Sempre que possivel, inclua valores aproximados para conferir a implementacao.

Exemplo:

```text
beta              = 0.971204
cosine_similarity = 0.975899
norm_residual     = 0.004433
```

Isso evita que a pessoa implemente tudo e fique sem saber se esta certo.

### 11. Como saber se entendeu

Inclua perguntas conceituais curtas.

Exemplo:

1. O que significa residual pequeno?
2. Por que beta perto de 1 indica exposicao ao mercado?
3. Qual erro aconteceria se eu esquecesse de subtrair a taxa livre de risco?

### 12. Termos para pesquisar

Inclua termos em portugues e ingles.

Portugues:

- produto interno algebra linear;
- projecao de vetor;
- beta de mercado;
- risco sistematico;
- excesso de retorno.

Ingles:

- dot product linear algebra;
- vector projection;
- market beta CAPM;
- systematic risk;
- excess return.

### 13. Referencias

Use referencias confiaveis e diretamente relacionadas.

Prioridade:

1. documentacao oficial;
2. cursos abertos de universidades;
3. livros ou notas academicas;
4. artigos tecnicos reconhecidos.

Evite jogar links genericos demais. A referencia precisa ajudar naquele exercicio.

### 14. Como rodar

Inclua comandos concretos.

```powershell
python .\python\main.py
g++ -std=c++20 -O2 -Wall -Wextra .\cpp\main.cpp -o .\cpp\main.exe
.\cpp\main.exe
```

### 15. Entregavel

Diga exatamente o que preencher em `notes.md`.

Exemplo:

```text
A estrategia parece alpha proprio ou apenas exposicao ao mercado?
Use beta, cosine similarity e norm_residual para justificar.
```

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
- os starters mostram assinaturas/declaracoes de funcoes, mas nao entregam a implementacao;
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

Troque por instrucoes fechadas:

- quais dados usar;
- quais funcoes criar;
- quais metricas calcular;
- quais valores esperar;
- qual conclusao escrever.

## Exemplo completo do padrao

Use este exemplo como referencia de nivel de detalhe. Repare que cada topico comeca explicando para que o passo serve antes de mostrar formula ou codigo.

~~~~markdown
# Matrizes - Vetor intermediario Cw no risco do portfolio

Este exercicio mostra como transformar uma matriz de covariancia e um vetor de pesos em um passo intermediario para calcular a variancia do portfolio.

## Pergunta do exercicio

Queremos saber quanto cada ativo contribui para o risco combinado antes de calcular a variancia final `w' C w`.

## Dados de partida

```text
C = [
    [0.000100, 0.000040],
    [0.000040, 0.000090],
]

w = [0.60, 0.40]
```

`C` e a matriz de covariancia dos ativos.

`w` e o vetor de pesos do portfolio.

## 1. Vetor intermediario Cw

O vetor `Cw` serve para aplicar os pesos do portfolio na matriz de covariancia e preparar o calculo final da variancia `w' C w`.

Funcao no codigo:

```text
matvec(C, w)
```

Formula:

```text
Cw[0] = C[0][0] * w[0] + C[0][1] * w[1]
Cw[1] = C[1][0] * w[0] + C[1][1] * w[1]
```

Calculo manual:

```text
Cw[0] = 0.000100 * 0.60 + 0.000040 * 0.40
Cw[0] = 0.000060 + 0.000016
Cw[0] = 0.000076

Cw[1] = 0.000040 * 0.60 + 0.000090 * 0.40
Cw[1] = 0.000024 + 0.000036
Cw[1] = 0.000060
```

Resultado:

```text
Cw = [0.000076, 0.000060]
```

Interpretacao:

```text
Cw[0] mostra como o ativo 0 se relaciona com o risco do portfolio ponderado.
Cw[1] mostra como o ativo 1 se relaciona com o risco do portfolio ponderado.
```

## 2. Variancia do portfolio

A variancia do portfolio transforma `Cw` em um unico numero de risco usando novamente os pesos `w`.

Funcao no codigo:

```text
dot(w, Cw)
```

Formula:

```text
portfolio_variance = w[0] * Cw[0] + w[1] * Cw[1]
```

Calculo manual:

```text
portfolio_variance = 0.60 * 0.000076 + 0.40 * 0.000060
portfolio_variance = 0.0000456 + 0.0000240
portfolio_variance = 0.0000696
```

Resultado:

```text
portfolio_variance = 0.0000696
```

Interpretacao:

```text
Esse numero e a variancia diaria do portfolio considerando o risco individual dos ativos e a covariancia entre eles.
```

## O que implementar em Python

```python
def matvec(matrix: list[list[float]], vector: list[float]) -> list[float]:
    ...

def dot(u: list[float], v: list[float]) -> float:
    ...
```

## O que implementar em C++

```cpp
using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

Vector matvec(const Matrix& matrix, const Vector& vector);
double dot(const Vector& u, const Vector& v);
```

## Resultado de referencia

```text
Cw = [0.000076, 0.000060]
portfolio_variance = 0.0000696
```

## Como saber se voce entendeu

1. Por que `Cw` ainda nao e a variancia final?
2. Por que os pesos aparecem duas vezes em `w' C w`?
3. O que aconteceria com a variancia se a covariancia entre os ativos fosse negativa?
~~~~

## Template rapido

~~~~markdown
# [Item] - [Nome concreto do exercicio]

Semana X: [Tema].

## Contexto

[Explique o assunto e por que ele importa.]

## Pergunta do exercicio

[Pergunta pratica que o codigo vai responder.]

## Traducao para linguagem quant

- `termo`: explicacao curta.

## Dados de partida

```text
[dados pequenos e fechados]
```

## Objetivo final

1. [calculo/produto]
2. [calculo/produto]

## Formulas que voce vai usar

### [Formula]

```text
[expressao]
```

Interpretacao: [explicacao].

## O que implementar em Python

1. [passo especifico]
2. [passo especifico]

## O que implementar em C++

1. [passo especifico]
2. [passo especifico]

## Resultado de referencia

```text
[valor] = [numero aproximado]
```

## Como saber se voce entendeu

1. [pergunta conceitual]
2. [pergunta conceitual]

## Termos para pesquisar

Portugues:

- [termo]

Ingles:

- [term]

## Referencias

- [Nome](https://exemplo.com)

## Como rodar

```powershell
python .\python\main.py
g++ -std=c++20 -O2 -Wall -Wextra .\cpp\main.cpp -o .\cpp\main.exe
.\cpp\main.exe
```

## Entregavel

[O que preencher no notes.md.]
~~~~
