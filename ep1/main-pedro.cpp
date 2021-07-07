#include "cekeikon.h"

//1) Ler imagem do canhoto como Mat_ <FLT>

//2) Redimensionar para 750 colunas e linhas proporcionais

//A = canhoto redimensionado e Q = canhoto padrão
//3) Colocar A no centro de uma moldura cinza (128/255) 310x1150

//4) Para cada canhoto Q = m?.pgm
//4.1) Ler m?.pgm como Mat_ <FLT>
//4.2) Coloca Q no centro de uma moldura cinza (128/255) 210x1050
//4.3) Gerar vector< Mat_<FLT> >  todas as combinações de Q redimensionadas nas escalas de 0,88 a 1,1 (21 passos - PG - q = 1.01068253859) 
//                                                                              e rotacionadas de -3 a +3 graus (17 passos - PA r = 0,3529411).
// Usar vizinho mais próximo!
//      Pensar no porquê (???)

//5) Laço loop para calcular template matching CC (modo same) entre A e cada Q de cada modelo (m2,m3,m4)
//5.1) Armazenar cada correlação na matriz corr(i) => pegar valor máximo max(corr(i)) e salvar índice i

//6) Pegar a maior correção entre os 3 modelos assim como seu índice i
//      Imprimir saída do formato : " Maior correlacao entre m2_001.jpg e m2.pgm: 0.147 "

//7) Coletar distorção de escala (fator(i)) e de rotacao(graus(i)) e deslocamento (desloc(i,j))
//      Imprimir saída do formato : " melhorModelo=2 corr= 0.147 graus= 0.750 fator= 1.006 desloc(x,y)=[ -2, -2] "

//8) Imprimir imagem inicial

//9) Imprimir canhoto padrão distocido (fator, graus e desloc) e colorido (vermelho, azul) sobreposto à imagem inicial
