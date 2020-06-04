# Graph Tool
                                                                                               
Códigos desenvolvidos para a máteria de Computação Gráfica do curso de Ciência da Computação da Pontifícia Católica de Minas Gerais. O objetivo da aplicação é possibilitar o uso dos algoritmos de curvas paramétricas em um ambiente gráfico.


## Como testar na própria máquina?

Para baixar, basta clonar este repositório na sua máquina:

```sh
git clone https://github.com/jorgejrluiz/bezier.git
```

## Bibliotecas
O projeto foi desenvolvido na linguagem C++. As seguintes bibliotecas foram utilizadas na implementação do projeto:
- [OPEN GL](https://www.opengl.org) - O OpenGL é uma API livre utilizada na computação gráfica, para desenvolvimento de aplicativos gráficos, ambientes 3D, jogos, entre outros.
- [GLUT](https://pt.wikipedia.org/wiki/GLUT) - GLUT é uma biblioteca de funcionalidades para OpenGL cujo principal objetivo é a abstração do sistema operacional fazendo com que os aplicativos sejam multiplataforma.

## Algoritmos
Os algoritmos foram utilizados na implementação do projeto:
- [Curvas Paramétricas Interpoladas](http://professor.unisinos.br/ltonietto/jed/cgr/curvas)
- [Curvas Paramétricas Hermite](http://www.ic.uff.br/~aconci/Hermite-Splines.pdf)
- [Curvas Paramétricas Bézier](https://pt.wikipedia.org/wiki/Curva_de_Bézier)

## Inicialização da aplicação
O C++ foi a linguagem utilizada nesse projeto. Na pasta bin, existe uma executável pronto caso não deseje compilar. Caso deseje compilar:

### Dentro da pasta
Digite o seguitne comando no terminal:
```
g++ main.cpp -o main
```
Após a compilação, execute o seguinte comando:
```
./main
```
Ou se preferir, abra o arquivo bezier.cbp no CodeBlocks para rodar o programa.

