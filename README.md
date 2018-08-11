# Introdução à Computação Gráfica
## Trabalho 1: Algoritmo para rasterização de pontos e linhas
O objetivo deste trabalho é implementar funções usando algoritmos de rasterização, que permitam a formação de pontos e retas na tela simulando o acesso direto à memória de vídeo.
Para tal simulação, utilizamos o framework  fornecido pelo professor Christian Azambuja Pagot.
### Introdução: O conceito de rasterização, o que são pixels e do que são formados
A rasterização é um processo essencial para a formação de qualquer tipo de imagem em um monitor. A partir dela, é possível a conversão das informações recebidas (de tipo vetorial) para o tipo matricial; onde são salvas pela memória do computador e representadas graficamente.
Durante esse processo, acontece a escolha dos pixels que serão “pintados” na tela, com coordenadas e cores específicas. A imagem abaixo representa a formação de uma linha.

![raster](https://user-images.githubusercontent.com/42072854/43996645-82b96912-9d9d-11e8-9fc8-101c06b2f0be.png)

Para a representação gráfica são usados os pixels, que são os menores elementos de uma imagem. Cada pixel possui três bytes que contém valores para as cores: vermelho, verde e azul (RGB, do inglês red green and blue).

Imagem de cores.

Com essas três cores primárias, podemos formar exatas 16.777.216, simplesmente mudando a intensidade de cada uma numa variação de 0 à 255, para cada cor. Algumas representações utilizam mais do que essas três cores, como o sistema RGBA que usam o “Alpha” para adicionar transparência à imagem.
## Funções implementadas:
Primeiramente, Criamos uma estrutura que guarda os elementos do pixel, para simplificar os parâmetros das funções.
```
struct pixel
{
    int X, Y;
    int R, G, B, A;
};
```
### 1 - putPixel
Essa função permite que sejam representados, no framework utilizado, pixels a partir do conjunto de coordenadas e cores dadas pelo usuário.
```
void putPixel(struct pixel P)
{
    FBptr[4 * P.X + 4 * P.Y * IMAGE_WIDTH + 0] = P.R;
    FBptr[4 * P.X + 4 * P.Y * IMAGE_WIDTH + 1] = P.G;
    FBptr[4 * P.X + 4 * P.Y * IMAGE_WIDTH + 2] = P.B;
    FBptr[4 * P.X + 4 * P.Y * IMAGE_WIDTH + 3] = P.A;
}
```
“FBptr” - É a posição de cada bit na malha do framework.

“[4 * x + 4 * y * IMAGE_WIDTH + 0]” - É o cálculo do offset,  que determina a posição certa das cores RGBA na memória de vídeo para que elas formem um pixel completo.
### 2 - drawLine
Essa é a função que processa a rasterização de linhas, a partir de um ponto inicial e um ponto final. Para tal, o algoritmo de Bresenham é o de melhor desempenho por não precisar de multiplicação de ponto flutuante, diferente do Digital Differential Analyzer (DDA).

O algoritmo inicialmente tem a limitação de funcionalidade apenas para o primeiro octante, por isso, não é possível desenhar retas com inclinação diferente de 0 < m < 1.
```
drawLine(struct pixel P1, struct pixel P2) {
 int dx = P2.X – P1.X;
 int dy = P2.Y – P1.Y;
 
 int d = 2 * dy – dx;
 int incr_e = 2 * dy;
 int incr_ne = 2 * (dy – dx);
 
 PutPixel(P1);
 
  while (P1.X < P2.X) {
    if (d <= 0) {
      d += incr_e; 
      P1.X++;
    } else {
      d += incr_ne; 
      P1.X++;
      P1.Y++; 
    } 
   PutPixel(P1); 
   }
}
```
Tendo o vista a limitação desse algoritmo, fez-se necessário descobrir, matematicamente, como utilizá-lo para os outros 7 octantes, usando troca de coordenadas e adaptando as operações efetuadas. Um dos pontos essenciais para efetuar a adaptação foi analisar os valores de variação de distância nos dois eixos da representação (X e Y), comparando tais valores e alterando-os quando necessário.
### 3 - drawTriangle
Depois de implementar a rasterização de retas, desenhar um triângulo torna-se uma tarefa simples. Tendo em vista que todo triângulo é formado por três retas que se conectam. Essa  função recebe como parâmetros os três pontos pelos quais as arestas serão determinadas.
```
void drawTriangle(struct pixel P1, struct pixel P2, struct pixel P3)
{
    drawLine(P1, P2);
    drawLine(P2, P3);
    drawLine(P3, P1);
}
```
