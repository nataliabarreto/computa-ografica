Esse trabalho é a continuação do trabalho anterior, no qual fizemos a rasterização de pontos e linhas. Agora, vamos implementar o pipeline gráfico, que consiste em uma sequência de transformações, ou seja, uma sequência de passos de modelos matemáticos até chegar a rasterização, aplicando rotações, escala e translação.
imagem

ESPAÇO DO OBJETO: Modelos tridimensionais que são definidos no seu próprio sistema de coordenadas. É interessante posicionar seu objeto no centro (origem) para facilitar os cálculos nas transformações.

O que isso quer dizer? Quer dizer que é nesse espaço que efetuamos as transformações de:Escala
,Rotação, Translação,Espelhamento (mirroring), Shear.
Essas transformações são realizadas através da manipulação de matrizes e isso é facilitado com o objeto na origem.

Temos aqui a matriz model, na qual leva o objeto do espaço do objeto para o espaço do universo.

ESPAÇO DO UNIVERSO: Espaço que reúne todos os objetos em um espaço só. É através desse espaço que podemos visualizar o objeto na tela.

ESPAÇO DA CÂMERA: Expõe os vértices com a câmera na origem. A nossa câmera possui:

Posição (px, py, pz)
Direção (dx, dy, dz)
Vetor up (ux, uy, uz)
Obs.: Nesse espaço há a simplificação das projeções 3D para 2D, pois usamos coordenadas homogêneas (esse conceito será visto mais a frente).

Para a construção do sistema de coordenadas da máquina de lavar a câmara, o X está apontando para o seguinte na imagem a seguir:
 imagem
 
Diante disso, vamos calcular :

    Para calcular o Zc iniciamos subtraindo a posição da câmera com a câmera lookat e  dividimos pela norma.
    Para calcular o Xc pegamos vetor Up e fazemos o produto vetorial com o Zc, dividindo pela sua norma.
    Para calcular o Yc fazemos o produto vetorial de Zc e Xc e dividimos pela norma.

Logo abaixo temos respectivamente essas operações:
imagem

Sendo assim, temos a Matriz View, na qual leva do espaço do universo para o espaço da câmera. Ela se encarrega da posição e da direção para onde a câmera aponta

Para a construção dessa matriz usamos as coordenadas encontradas anteriormente:

(Xcx, Xcy, Xcz)

(Ycx, Ycy, Ycz)

(Zcx, Zcy, Zcz)

Então,
    |   Xcx    Ycx    Zcx   |

B = |   Xcy    Ycy     Zcy  |

    |   Xcz    Ycz     Zcz  |
    
    imagem
    
ESPAÇO DE RECORTE (Clipping):

O espaço de recorte está entre o espaço da câmera e o espaço canônico (definiremos mais a frente).

Sendo assim, temos que após as transformações das nossas primitivas posicionamos nossa câmera e tudo que estiver ao alcance dela é renderizado e o que estiver fora de seu plano é recortado, ou seja, será removido. Isso influencia diretamente no processamento gráfico.

Abaixo podemos visualizar melhor  o que é realizado nesse espaço:
imagem

ESPAÇO CANÔNICO:

É nesse espaço que asseguramos o que vai exibir na tela, pois é aqui onde ocorre o mapeamento dos vértices para centralizar o volume obtido no espaço da câmera para o espaço canônico.

ESPAÇO DE TELA
Nesse espaço trabalharemos com as coordenadas no espaço canônico e é onde nosso objeto irá ser rasterizado.

TRANSFORMAÇÕES GEOMÉTRICAS

Após alguns conceitos importantes vamos começar a falar das transformações geométricas. Seus tipos já foram citados no espaço do objeto e, além disso, também falaremos de algumas definições que ficaram em aberto em algumas ocasiões no nosso texto.

As transformações geométricas podem ser classificadas em:

  Transformações lineares: que são aquelas que podem ser expressas em forma de matriz. E como exemplo desse tipo de transformações temos: escala, rotação e shear.
  Transformações afins: preserva o paralelismo entre duas linhas e além de possuir todas as transformações lineares possui também a translação.
  Transformação projetiva: não preserva o paralelismo entre duas linhas e além de possuir todas as transformações afins também possui coordenadas homogêneas.

Após descritas como as transformações podem ser classificadas, iremos detalhar seus tipos.

1. ESCALA
Altera as dimensões do objeto em estudo, isto é, quando queremos diminuir ou aumentar o tamanho do objeto.
Há dois tipos de escalas,

    Isotrópica: quando os fatores de escala são iguais (Sx = Sy).
    Anisotrópica: quando os fatores de escala são diferentes (Sx ≠ Sy).

 
2. ESPELHAMENTO (MIRRORING)

Nessa  característica temos que o nosso objeto quando atribuido a isso, espelhamos um de nossos eixos ou os dois eixos:

    Eixo x: Sx = -1 e Sy = 1;
    Eixo y: Sx = 1 e Sy = -1;
    Ambos os eixos: Sx = -1 e Sy = -1;
    
 3. SHEAR

Nessa transformação distorcemos o objeto em um eixo ou em ambos. Sendo assim,  podemos fixar um ponto e mudar a coordenada de outro eixo.

4. ROTAÇÃO

Nesse tipo de transformação temos a alteração da direção do objeto. Desse modo, rotacionamos o nosso objeto com um ângulo θ em relação à origem.

5. TRANSLAÇÃO

A translação é exemplo de uma transformação que não pode ser expressa por matriz, porém representamos a  combinação de muitas transformações em uma única matriz e sendo assim, temos que arrumar alguma forma de representar a translação em uma multiplicação de matriz e a solução é usar as coordenadas homogêneas (HC).

As coordenadas homogêneas tem por função colocar mais uma dimensão na matriz, no qual em 2D será representado por: (x,y,h). Se o valor de h for diferente de 1, dividimos o x e o y pelo valor de h (x/h, y/h, 1).

Até aqui só falamos das transformações em 2D, mas também podemos representá-las em 3D. Nessa dimensão também expressamos com as coordenadas homogêneas e dessa forma vamos ter 4 elementos no espaço euclidiano (x,y,z) –> (x,y,z,h).

MATRIZ DE PROJEÇÃO

Sabendo da transformação da matriz View, vamos passar o sistema de coordenadas que possuímos para o espaço projetivo. Para conseguir essa transformação usamos a matriz de projeção, na qual irá projetar os nossos pontos  que estão no espaço da câmera para o View Plane.

Temos como matriz de projeção:

imagem

DESENVOLVIMENTO

Com as transformações, que podemos aplicar ao nosso objeto devidamente explicadas iremos usá-las.

Vamos sair do espaço do objeto para o espaço do universo (matriz model), isto é, reunir o que temos de objetos em um só espaço para poder visualizar na tela, aplicando as transformações: rotação, translação e escala.

Sendo assim, escrevemos a matriz de posição, matriz de rotação em torno do eixo x, matriz de rotação em torno do eixo y, matriz de rotação em torno do eixo z e a matriz de escala.

Após, queremos passar do espaço do universo para o espaço da câmera, com os produtos vetoriais que foram explicados anteriormente, isto é, a matriz view.

(coloca essa matriz aqui)

Logo depois, partiremos do espaço da câmera para o espaço de recorte, para isso usamos a matriz de projeção:
(coloca essa matriz aqui)

E sendo assim, iremos para a tela:
(coloca essa matriz aqui)

Realizada todas essas aplicações podemos gerar o nosso objeto:
(coloca o objeto gerado)

Logo abaixo temos o resultado final com a comparação do projeto com o disponível pelo professor Christian Pagot.

Do lado esquerdo está o do professor e do lado direito o desenvolvido.

(coloca a comparação dos objetos)
