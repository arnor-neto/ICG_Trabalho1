# Introdução à Computação Gráfica

## Trabalho 1: Algoritmo para rasterização de pontos e linhas
O objetivo deste trabalho é implementar funções usando algoritmos de rasterização, que permitam a formação de pontos e retas na tela simulando o acesso direto à memória de vídeo.
Para tal simulação, utilizamos o framework  fornecido pelo professor Christian Azambuja Pagot.

Trabalho desenvolvido pelos alunos:

Arnôr Martiniano da Silva Neto - Matrícula: 20170011130

Dandara Estrela Braga - Matrícula: 20170000870

### Introdução: O conceito de rasterização, o que são pixels e do que são formados
A rasterização é um processo essencial para a formação de qualquer tipo de imagem em um monitor. A partir dela, é possível a conversão das informações recebidas (de tipo vetorial) para o tipo matricial; onde são salvas pela memória do computador e representadas graficamente.
Durante esse processo, acontece a escolha dos pixels que serão “pintados” na tela, com coordenadas e cores específicas. A imagem abaixo representa a formação de uma linha.

![raster](https://user-images.githubusercontent.com/42072854/43996645-82b96912-9d9d-11e8-9fc8-101c06b2f0be.png)

Para a representação gráfica são usados os pixels: que são os menores elementos de uma imagem. Cada pixel possui três bytes que contém valores para as cores: vermelho, verde e azul (RGB, do inglês red green and blue).

![pixel-e-sistema-rgb-02](https://user-images.githubusercontent.com/42072854/43997586-05d8bf10-9db6-11e8-98ea-29e83bdc5536.png)

Com essas três cores primárias, podemos formar exatas 16.777.216, simplesmente mudando a intensidade de cada uma numa variação de 0 à 255, para cada cor. Algumas representações utilizam mais do que essas três cores, como o sistema RGBA que usam o “Alpha” para adicionar transparência à imagem.
## Funções implementadas:
Primeiramente, criamos uma estrutura que guarda os elementos do pixel, para simplificar os parâmetros das funções.
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

![putpixel print](https://user-images.githubusercontent.com/42072854/43998040-918a35e6-9dc2-11e8-8e18-37f9d59fad06.png)

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

![octantesreal](https://user-images.githubusercontent.com/42072854/44034421-70416a68-9ee3-11e8-9c48-87ef83776796.gif)

Para fazer as alterações, é muito importante a percepção de em qual octante está localizada a linha proposta. Usamos uma função recursiva, que inverte a ordem dos pontos quando a linha pertence inicialmente ao lado esquerdo dos octantes, para que assim a linha esteja sempre do lado direito (entre os quadrantes 1, 2, 7 e 8).
Desta forma, a próxima preocupação é com os sinais e com os elementos usados para formar a variável de decisão, além dos incrementos leste e nordeste.

![drawline print](https://user-images.githubusercontent.com/42072854/43997621-096ebbd8-9db7-11e8-8c5e-5649f850b89c.png)

<details><summary> Parâmetros </summary><p>
    
    pixel P1 = {256, 256, 50, 50, 50, 255};
    pixel P2 = {0, 0, 255, 0, 0, 255};
    pixel P3 = {256, 0, 0, 255, 0, 255};
    pixel P4 = {512, 0, 0, 0, 255, 255};
    pixel P5 = {512, 256, 242, 141, 19, 255};
    pixel P6 = {512, 512, 255, 0, 255, 255};
    pixel P7 = {256, 512, 255, 255, 0, 255};
    pixel P8 = {0, 512, 0, 255, 255, 255};
    pixel P9 = {0, 256, 199, 0, 255, 255};
    
    drawLine(P1, P2);
    drawLine(P1, P3);
    drawLine(P1, P4);
    drawLine(P1, P5);
    drawLine(P1, P6);
    drawLine(P1, P7);
    drawLine(P1, P8);
    drawLine(P1, P9);
    
</p></details>

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

![drawtriangle print](https://user-images.githubusercontent.com/42072854/43997698-7c15dda4-9db9-11e8-9b7a-28eecee5ee0f.png)

<details><summary> Parâmetros </summary><p>
    
    pixel P1 = {336, 30, 255, 0, 0, 255};
    pixel P2 = {196, 450, 0, 255, 0, 255};
    pixel P3 = {456, 450, 0, 0, 255, 255};
    pixel P4 = {70, 30, 255, 255, 0, 255};
    pixel P5 = {70, 430, 255, 0, 255, 255};
    pixel P6 = {270, 30, 0, 255, 255, 255};

    drawTriangle(P1, P2, P3);
    drawTriangle(P4, P5, P6);
    
</p></details>

### Interpolação de cores

Para a interpolação linear das cores na reta, a lógica usada foi: 

1. Obter a diferença entre as cores dos dois pontos que delimitam a reta;
2. Dividir esse valor pelo número de pixels usados para desenhar a reta e assim obter a taxa de variação de cor entre os pontos ;
3. E, por último, efetuar gradativamente o aumento/decremento dos níveis de intensidade da cor de cada pixel desenhado ao longo da reta.

```
if (abs(dx) >= abs(dy))
    {
        changeR = (float)(P2.R - P1.R) / abs(dx);
        changeG = (float)(P2.G - P1.G) / abs(dx);
        changeB = (float)(P2.B - P1.B) / abs(dx);
        changeA = (float)(P2.A - P1.A) / abs(dx);
    }
    else
    {
        changeR = (float)(P2.R - P1.R) / abs(dy);
        changeG = (float)(P2.G - P1.G) / abs(dy);
        changeB = (float)(P2.B - P1.B) / abs(dy);
        changeA = (float)(P2.A - P1.A) / abs(dy);
    }
    
     ...
    
while (P1.X != P2.X || P1.Y != P2.Y){
    
     ...
     
      //Interpolação de cores
        red += changeR;
        green += changeG;
        blue += changeB;
        alpha += changeA;
           P1.R = red;
           P1.G = green;
           P1.B = blue;
           P1.A = alpha;

           putPixel(P1);
       }
 ```
## Resultados e dificuldades encontradas
O trabalho conseguiu executar tudo o que foi pedido, com resultados muito satisfatórios. 
A maior dificuldade foi a difusão do algoritmo de Bresenham para todos os octantes, tarefa principal durante o desenvolvimento.

## Referências

http://www.demic.fee.unicamp.br/~jeff/ArquivosIndex/Bresenham

https://slideplayer.com.br/slide/366939/https://slideplayer.com.br/slide/366939/

http://disciplinas.ist.utl.pt/leic-cg/textos/livro/Rasterizacao.pdf

# Trabalho 2

Repositório do trabalho 2: https://github.com/arnor-neto/ICG_Trabalho2
