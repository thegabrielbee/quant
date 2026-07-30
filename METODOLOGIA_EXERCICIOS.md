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

Outro exemplo ruim:

```python
def daily_volatility(portfolio_variance: float) -> float:
    return sqrt(portfolio_variance)
```

Nesse caso, a conta direta e mais clara porque a funcao apenas embrulha `sqrt`:

```python
daily_vol = sqrt(portfolio_variance)
```

Outro exemplo ruim:

```python
def annualized_volatility(daily_vol: float, periods_per_year: int) -> float:
    return daily_vol * sqrt(periods_per_year)
```

Nesse caso, a conta direta e mais clara porque a funcao apenas embrulha uma multiplicacao simples:

```python
annual_vol = daily_vol * sqrt(periods_per_year)
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

## Regras para criar tipos

Crie tipos novos somente quando eles carregarem uma regra de dominio, uma validacao ou uma semantica que o tipo nativo nao mostra sozinho.

Regra principal:

```text
Nao crie tipo redundante quando ele for apenas um wrapper de um tipo simples ja existente.
```

Isso vale para:

- aliases em C++, como `using Vector = std::vector<double>`;
- aliases em Python, como `Vector = list[float]`;
- `struct`, `class`, `dataclass` ou `NewType` que so guardam um valor sem validar nada;
- tipos auxiliares como `Shape` quando `std::pair<std::size_t, std::size_t>` ou `tuple[int, int]` ja deixam o contrato claro no exercicio.

Um tipo e redundante quando:

- so renomeia `list`, `tuple`, `std::vector`, `std::pair` ou outro container comum;
- nao valida invariantes;
- nao adiciona comportamento proprio;
- nao deixa uma regra de dominio mais clara;
- so existe para encurtar assinatura em um exercicio pequeno.

Exemplo ruim:

```cpp
using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;
using Shape = std::pair<std::size_t, std::size_t>;
```

Nesse caso, use os tipos diretamente nas assinaturas:

```cpp
std::vector<double> column_means(const std::vector<std::vector<double>>& matrix);
std::pair<std::size_t, std::size_t> matrix_shape(const std::vector<std::vector<double>>& matrix);
```

Exemplo aceitavel:

```cpp
struct PortfolioWeights {
    std::vector<double> values;
};
```

Esse tipo so e aceitavel se a implementacao validar uma regra real, por exemplo soma dos pesos, tamanho esperado ou ausencia de pesos negativos quando o exercicio exigir isso.

Regra de decisao:

```text
Se o tipo apenas renomeia outro tipo, nao crie o tipo.
Se o tipo valida invariantes, protege uma regra de dominio ou reduz complexidade real em um codigo maior, ele pode existir.
```

## Regras obrigatorias de testes

Todo exercicio com codigo precisa vir com arquivos de teste prontos para validar as funcoes implementadas.

Nao basta escrever no README quais testes deveriam existir. O agente deve criar os arquivos de teste do exercicio junto com o codigo.

Regra principal:

```text
Teste nao e TODO. Teste e arquivo pronto.
```

Os testes nao podem validar apenas o dataset principal do README. Eles precisam validar tambem o funcionamento matematico das funcoes.

Regra de cobertura:

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

Os testes devem estar completos para rodar desde a primeira entrega do exercicio. Se o arquivo principal for starter incompleto, os testes podem falhar ate o estudante implementar, mas nao podem estar ausentes, vazios ou descritos apenas em texto.

## Regras obrigatorias de animacoes e videos

Todo exercicio com codigo precisa vir com animacoes geradas pelo proprio agente.

O agente nao deve apenas sugerir que o estudante faca o video depois. O agente deve criar o codigo das animacoes, renderizar o video final e deixar o artefato pronto para assistir.

Biblioteca padrao:

```text
Manim Community Edition
```

Estrutura obrigatoria:

```text
animations/
  scenes.py
  README.md
  roteiro.md
  generate_voice.ps1
```

O arquivo `animations/scenes.py` deve conter:

- uma cena completa do exercicio, chamada `FullExerciseScene`;
- cenas ou segmentos para cada step/função matemática relevante;
- visualizacao dos dados de entrada;
- visualizacao da formula matematica;
- visualizacao da funcao do codigo que implementa a formula;
- animacao dos valores mudando ate chegar no resultado;
- interpretacao curta do que o valor significa em quant.

Cada funcao importante do exercicio deve ter uma explicacao animada.

Cada funcao, step ou operacao matematica exibida no video deve permanecer em tela por tempo suficiente para leitura.

Regra de tempo minimo:

```text
Cada funcao/operação animada deve durar pelo menos 5 segundos do inicio ao fim.
```

Esse tempo inclui:

- entrada visual do bloco;
- formula matematica;
- nome da funcao do codigo;
- transformacao dos valores;
- resultado final;
- pausa para leitura.

Nao compacte varios steps em poucos segundos. Se o usuario precisa pausar para entender, a animacao esta rapida demais.

Exemplo:

```text
column_means      -> anima soma das colunas e divisao por n
center_matrix     -> anima retorno menos media de cada ativo
transpose         -> anima linhas virando colunas
matmul            -> anima produto linha x coluna
matvec            -> anima C * w
dot               -> anima multiplicacao posicao com posicao
annualizacao      -> anima daily_vol * sqrt(periods_per_year)
```

Regra de fonte de verdade:

```text
A animacao deve usar os mesmos dados, formulas e nomes de funcoes do README e do codigo.
```

Nao crie uma matematica paralela so para o video. Se a cena precisar calcular valores, ela deve reutilizar as funcoes do exercicio quando isso for pratico, ou repetir apenas contas pequenas explicitamente mostradas na propria animacao.

Regra contra wrappers:

```text
Nao crie funcao wrapper so para animar outra funcao simples.
```

Helpers visuais sao permitidos:

```text
make_matrix_table(...)
highlight_cell(...)
show_formula_step(...)
```

Wrappers matematicos redundantes nao sao permitidos:

```text
animated_dot(u, v) chamando apenas dot(u, v)
```

O agente deve renderizar pelo menos:

```text
FullExerciseScene
```

Qualidade padrao para entrega:

```text
-qm
```

Nao mantenha duas versoes do mesmo video como entrega. O artefato final deve ser apenas o render em `720p30`, salvo pelo Manim quando usado `-qm`.

O README do exercicio deve informar onde o video final foi gerado.

## Regras obrigatorias de roteiro e voz

Todo video deve ter um roteiro de narracao gerado pelo agente.

Estrutura obrigatoria:

```text
animations/roteiro.md
animations/generate_voice.ps1
```

O roteiro deve ter um bloco de narracao para:

- introducao;
- cada funcao/operacao matematica importante;
- conclusao.

Por padrao, a voz deve ser gerada sem custo por ferramenta local/offline quando houver uma voz disponivel no sistema.

No Windows, use a voz local SAPI quando estiver disponivel, por exemplo:

```text
Microsoft Maria Desktop pt-BR
```

O agente deve:

- gerar o roteiro;
- gerar os arquivos de voz;
- encaixar a voz na cena Manim;
- renderizar o MP4 final ja com audio;
- ajustar o tempo do video para a narracao nao ficar cortada.

Nao use API paga por padrao para narracao. So use API externa se o usuario pedir explicitamente.

Se a maquina nao tiver voz local disponivel, registre o bloqueio e deixe o roteiro pronto.

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

Inclua comandos concretos para rodar Python, C++, testes das duas linguagens e render das animacoes.

Os comandos de teste sao obrigatorios. O README precisa deixar claro como validar:

- execucao normal do exercicio;
- testes das funcoes Python;
- testes das funcoes C++;
- quais propriedades matematicas os testes cobrem.

Os comandos de animacao tambem sao obrigatorios. O README precisa deixar claro:

- como gerar a voz local/offline;
- qual cena renderiza o video completo;
- quais cenas renderizam funcoes especificas, se existirem;
- onde o arquivo `.mp4` final fica salvo;
- se o render foi feito em baixa, media ou alta qualidade.

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
### step X
explicacao geral do topico
matematica em alto nivel do topico
interpretacao geral do que este topico entrega

#### step X.Y
calculo de uma unica operacao especifica deste topico
formula matematica exata deste substep
chamada, funcao ou trecho do codigo que executa essa conta
resultado esperado deste substep, quando houver
```

Regra:

- o step principal `step X` explica o que o topico faz, por que ele existe e como ele se conecta com o resultado final;
- explicacoes gerais, intuicao, contexto quant e interpretacao ficam no `step X`;
- cada substep `step X.Y` deve ser o calculo de uma unica operacao especifica;
- cada substep `step X.Y` deve ter formula matematica e relacao direta com o codigo;
- a relacao com codigo precisa citar a funcao, chamada ou linha conceitual que executa a conta;
- os nomes das funcoes precisam aparecer dentro dos substeps, nao escondidos no final;
- se um topico tiver mais de uma operacao, separe em mais de um substep.

Exemplo: matriz de covariancia nao deve ter um substep generico dizendo apenas "calcule a covariancia". Ela deve separar as contas:

```text
#### step X.1
centered_t = transpose(centered)

#### step X.2
M = matmul(centered_t, centered)

#### step X.3
covariance[a][b] = M[a][b] / (n - 1)
```

Anti-regra:

```text
Substep X.Y que so explica conceito, sem formula e sem relacao com codigo, esta errado.
```

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
- cada substep `step X.Y` calcula uma unica operacao especifica;
- cada substep `step X.Y` tem formula matematica e relacao direta com funcao, chamada ou trecho do codigo;
- explicacoes gerais ficam no `step X`, nao nos substeps `step X.Y`;
- cada formula/exemplo aponta para a funcao correspondente no codigo;
- os passos de Python e C++ tem funcoes especificas;
- as funcoes sugeridas nao sao wrappers redundantes de chamadas simples ja existentes;
- nenhuma funcao do codigo existe apenas para chamar outra funcao simples;
- os tipos sugeridos nao sao aliases ou wrappers redundantes de tipos simples ja existentes;
- nenhum tipo do codigo existe apenas para renomear `list`, `tuple`, `std::vector`, `std::pair` ou outro container comum;
- os starters mostram assinaturas/declaracoes de funcoes, mas nao entregam a implementacao;
- existem testes para Python quando houver codigo Python;
- existem testes para C++ quando houver codigo C++;
- os arquivos de teste foram criados de verdade, nao apenas descritos no README;
- os arquivos de teste tem asserts/verificacoes prontas para rodar;
- os testes chamam funcoes diretamente, nao apenas comparam o print final;
- os testes cobrem propriedades matematicas, nao apenas os dados de input do README;
- existe pasta `animations/` quando houver codigo;
- existe `animations/scenes.py`;
- existe `animations/roteiro.md`;
- existe script para gerar voz local/offline quando houver voz disponivel;
- existe cena `FullExerciseScene`;
- cada funcao matematica relevante aparece no video completo ou em uma cena propria;
- as animacoes mostram formula matematica, funcao do codigo, mudanca nos valores e interpretacao quant;
- cada funcao, step ou operacao exibida no video dura pelo menos 5 segundos;
- a narracao acompanha o que aparece na tela e nao e cortada antes do fim do audio;
- o agente renderizou o video final ou registrou claramente o bloqueio tecnico;
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
- criar substep `step X.Y` que so explica o conceito, sem calculo especifico, sem formula matematica e sem relacao com codigo.
- juntar duas operacoes diferentes no mesmo substep, como `matmul` e divisao por `n - 1`, quando elas podem ser validadas separadamente.
- criar funcao que apenas chama outra funcao simples, sem validacao, composicao ou ganho real de clareza.
- manter no codigo uma funcao wrapper que so repassa para outra funcao simples.
- criar tipo, alias, struct, class ou dataclass que apenas embrulha um tipo nativo sem validacao ou ganho semantico real.
- usar `Vector`, `Matrix` ou `Shape` em exercicio pequeno quando `std::vector<double>`, `std::vector<std::vector<double>>` ou `std::pair<std::size_t, std::size_t>` deixam o contrato claro.
- entregar codigo sem testes.
- dizer no README quais testes fazer, mas nao criar `python/tests/test_main.py` e `cpp/tests.cpp`.
- criar arquivo de teste vazio ou com placeholders como "TODO".
- testar apenas o exemplo principal do README sem validar propriedades matematicas das funcoes.
- entregar exercicio com codigo sem animacao.
- criar apenas script de animacao sem renderizar o video final.
- fazer video que mostra formula, mas nao mostra a funcao do codigo correspondente.
- fazer video que mostra codigo, mas nao mostra o impacto nos valores.
- criar matematica paralela no video que diverge do README ou do codigo.
- entregar video sem roteiro de narracao.
- usar API paga para voz sem pedido explicito do usuario.
- renderizar video com audio cortado ou fora de sincronia com o step.

Troque por instrucoes fechadas:

- quais dados usar;
- quais funcoes criar;
- quais metricas calcular;
- quais valores esperar;
- quais cenas renderizar;
- onde fica o video final;
- como gerar a voz local/offline;
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
std::vector<double> column_means(const std::vector<std::vector<double>>& matrix);
std::vector<std::vector<double>> center_matrix(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& means
);
std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& matrix);
std::vector<std::vector<double>> matmul(
    const std::vector<std::vector<double>>& a,
    const std::vector<std::vector<double>>& b
);
std::vector<double> matvec(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& vector
);
double dot(const std::vector<double>& u, const std::vector<double>& v);
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

Animacoes:

```powershell
python -m pip install manim
powershell -ExecutionPolicy Bypass -File .\animations\generate_voice.ps1
manim -qm --media_dir .\animations\media .\animations\scenes.py FullExerciseScene
```

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
- interpretacao quant do resultado.

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

Este substep calcula `centered_t`, a transposta da matriz centralizada que sera usada no produto `Xc' Xc`.

```text
centered_t[j][i] = centered[i][j]

centered   tem formato dias x ativos
centered_t tem formato ativos x dias
```

Relacao no codigo:

```text
centered_t = transpose(centered)
```

#### step 3.2

Este substep calcula `M`, o produto matricial entre a transposta centralizada e a matriz centralizada.

```text
M = centered_t * centered

M[a][b] =
    soma centered_t[a][k] * centered[k][b]
    para k percorrendo a dimensao compartilhada
```

Neste tipo de `matmul`, `k` e o indice da dimensao interna:

```text
centered_t tem formato ativos x dias
centered   tem formato dias x ativos

k percorre os dias.
```

Cuidado comum:

```text
No terceiro loop de `matmul`, k nao deve ir ate a.size().

a.size()    = quantidade de linhas de a
a[0].size() = quantidade de colunas de a
b.size()    = quantidade de linhas de b

Use k indo ate a[0].size(), que deve ser igual a b.size().
```

Relacao no codigo:

```text
M = matmul(centered_t, centered)

for i in range(a.size()):
    for j in range(b[0].size()):
        for k in range(a[0].size()):
            result[i][j] += a[i][k] * b[k][j]
```

#### step 3.3

Este substep calcula `covariance`, dividindo cada celula de `M` por `n - 1` para obter covariancia amostral.

```text
covariance[a][b] = M[a][b] / (n - 1)
```

Relacao no codigo:

```text
covariance = covariance_matrix(centered)
```

Dentro de `covariance_matrix`, a operacao precisa ficar equivalente a:

```text
M = matmul(transpose(centered), centered)
covariance[a][b] = M[a][b] / (len(centered) - 1)
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
