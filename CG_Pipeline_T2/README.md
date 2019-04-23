Esse trabalho é a continuação do trabalho anterior, no qual fizemos a rasterização de pontos e linhas. Agora, vamos implementar o pipeline gráfico, que consiste em uma sequência de transformações, ou seja, uma sequência de passos de modelos matemáticos até chegar a rasterização, aplicando rotações, escala e translação.

ESPAÇO DO OBJETO:
Modelos tridimensionais que são definidos no seu próprio sistema de coordenadas. É interessante posicionar seu objeto no centro (origem) para facilitar os cálculos nas transformações.

O que isso quer dizer? Quer dizer que é nesse espaço que efetuamos as transformações de:Escala
,Rotação, Translação,Espelhamento (mirroring), Shear.
Essas transformações são realizadas através da manipulação de matrizes e isso é facilitado com o objeto na origem.

Temos aqui a matriz model, na qual leva o objeto do espaço do objeto para o espaço do universo.

ESPAÇO DO UNIVERSO:

Espaço que reúne todos os objetos em um espaço só. É através desse espaço que podemos visualizar o objeto na tela.

ESPAÇO DA CÂMERA:

Expõe os vértices com a câmera na origem. A nossa câmera possui:

Posição (px, py, pz)

Direção (dx, dy, dz)

Vetor up (ux, uy, uz)
Obs.: Nesse espaço há a simplificação das projeções 3D para 2D, pois usamos coordenadas homogêneas (esse conceito será visto mais a frente).

Para a construção do sistema de coordenadas da máquina de lavar a câmara, o X está apontando para o seguinte na imagem a seguir:
Detalhes
