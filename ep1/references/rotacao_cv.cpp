// rotacao_cv.cpp pos2016
#include <cekeikon.h>
int main()
{ Mat_<GRY> ent; le(ent,"lennag.jpg");
 Mat_<GRY> sai;
 Mat_<double> m=getRotationMatrix2D(Point2f(ent.cols/2,ent.rows/2), 30, 1);
 cout << m << endl;
 warpAffine(ent, sai, m, ent.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(255));
 imp(sai);
}

O programa 7 (rotacao_cv.cpp) rotaciona a imagem lennag.jpg de 30 graus em sentido antihorário
 em torno do seu centro. Na linha 6, a função getRotationMatrix2D cria uma matriz
afim 2×3 que converte coordenada (xa, ya) da imagem de entrada a para coordenada (xb, yb) da
imagem de saída b. A linha 7 do programa imprime a matriz m que faz transformação direta
(xa, ya) para (xb, yb):