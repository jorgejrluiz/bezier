# Graph Tool
                                                                                               
Códigos desenvolvidos para a máteria de Computação Gráfica do curso de Ciência da Computação da Pontifícia Católica de Minas Gerais. O objetivo da aplicação é possibilitar o uso dos algoritmos de curvas paramétricas em um ambiente gráfico.


## Como testar na própria máquina?

Para baixar, basta clonar este repositório na sua máquina:

```sh
git clone https://github.com/jorgejrluiz/bezier.git
```
## Instruções de uso
Para plotar uma curva utilizando um dos algoritmos implementados, basta pressionar o botão direito do mouse na interface gráfica e escolher as opções disponíveis na aba tipo de Curva.

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
O C++ foi a linguagem utilizada nesse projeto. Caso deseje compilar:

### Dentro da pasta
Digite o seguinte comando no terminal:
```
g++ main.cpp -o main -IGL -IGLU -IGLEW -Iglut
```
Após a compilação, execute o seguinte comando:
```
./main
```
### Observação
Pode ser necessário a instalação das seguintes dependências para compilação:
```
sudo at-get install libgl1-mesa-dev
```
```
sudo at-get install libglew1.5-dev freeglut3-dev libglm-dev
```

Após esses passos, será possível utilizar o programa.
