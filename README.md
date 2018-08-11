# Introdução à Computação Gráfica
## Trabalho 1: Algoritmo para rasterização de pontos e linhas
O objetivo deste trabalho é implementar funções usando algoritmos de rasterização, que permitam a formação de pontos e retas na tela simulando o acesso direto à memória de vídeo.
Para tal simulação, utilizamos o framework  fornecido pelo professor Christian Azambuja Pagot.
### Introdução: O conceito de rasterização, o que são pixels e do que são formados
A rasterização é um processo essencial para a formação de qualquer tipo de imagem em um monitor. A partir dela, é possível a conversão das informações recebidas (de tipo vetorial) para o tipo matricial; onde são salvas pela memória do computador e representadas graficamente.
Durante esse processo, acontece a escolha dos pixels que serão “pintados” na tela, com coordenadas e cores específicas. A imagem abaixo representa a formação de uma linha.

![raster](https://user-images.githubusercontent.com/42072854/43996645-82b96912-9d9d-11e8-9fc8-101c06b2f0be.png)

Para a representação gráfica são usados os pixels, que são os menores elementos de uma imagem. Cada pixel possui três bytes que contém valores para as cores: vermelho, verde e azul (RGB, do inglês red green and blue).
