# LP1 Projeto 3

Neste projeto você irá fazer um simulador para o jogo snaze, melhores informações podem ser encontradas no [documento de especificação](https://www.overleaf.com/read/prcdstrjrdjr);

## Sistema de build

Escolha um dos sistemas de build que melhor agradar você, lembre que já vimos exemplos com [Makefile](https://www.gnu.org/software/make/manual/make.html) 
e [Cmake](https://cmake.org/). Esta versão usa compilação básica usando a linha de comando, mas fica a ~~obrigação~~ sugestão, caso você queira mudar.

## Organização

Este repositório tem algumas classes iniciais que podem te ajudar a fazer o projeto, porém, fique à vontade para explorar as possibilidades.

## Compilando e executando o exemplo

No linux você pode compilar usando o g++. Apenas faça clone do projeto, e faça:

```bash
g++ src/*.cpp -o main -I../include
./main
```

No windows você pode compilar usando o g++ ou o cl de forma análoga:

```bash
g++ src/*.cpp -o main -I../include
.\main.exe
```
ou usando o CL

```bash
cl src/*.cpp -I../include
.\Snaze.exe
```

__Observação sobre o windows__: Ao realizar testes meu sistema detectou o programa como um virus, para conseguir executar eu tive que usar a versão compilada com o g++ ou configurar o windows defender para ignorar o executável que está na pasta do projeto (o problema só ocorre com a versão compilada pelo CL).
