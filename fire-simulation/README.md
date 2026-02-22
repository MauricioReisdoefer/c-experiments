# Fire Simulation

Este projeto é uma simulação de animação de fogo desenvolvida em C utilizando a biblioteca SDL. Ele gera um efeito visual de fogo dinâmico, onde a intensidade do fogo é calculada e mapeada para uma paleta de cores que simula chamas.

## Como funciona

A simulação cria uma matriz de pixels onde cada pixel representa uma intensidade de calor. A partir de uma linha base de calor máximo, a intensidade é propagada para cima, diminuindo aleatoriamente, criando o efeito de chamas que sobem e se dissipam. A cor de cada pixel é determinada pela sua intensidade de calor, variando de tons escuros (fumaça/base) a tons claros (chamas mais quentes).

## Demonstração

![Demo da Simulação de Fogo](demo.gif)

## Requisitos

Para compilar e executar este projeto, você precisará:

* Um compilador C (como GCC)
* A biblioteca SDL3

## Compilação e Execução

Para compilar o projeto, navegue até o diretório `fire-simulation` e execute:

```bash
gcc main.c fire.c color.c -IC:/libs/SDL3/include -LC:/libs/SDL3/lib -lSDL3 -o main.exe
```

Para executar a simulação:

```bash
./fire_simulation
```

Você pode opcionalmente passar um valor para a taxa de quadros (FPS):

```bash
./fire_simulation 120
```
