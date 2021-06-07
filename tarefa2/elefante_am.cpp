//.cpp grad-2018
#include <cekeikon.h>

/* //A funcao abaixo ja esta incluida na biblioteca Cekeikon
double distancia(COR a, COR b)
{
    return cvRound(sqrt(double(elev2(a[0] - b[0]) +
                               elev2(a[1] - b[1]) +
                               elev2(a[2] - b[2]))));
} */

int main()
{
    Mat_<COR> a;
    le(a, "elefante.jpg");
    Mat_<COR> b;
    COR amarelo(20, 200, 200);
    //b=a; // Esta errado. b e a sao dois nomes para mesma imagem.
    b = a.clone(); // OU a.copyTo(b); Aqui temos duas imagens diferentes.
    for (int l = 0; l < a.rows; l++)
        for (int c = 0; c < a.cols; c++)
            if (distancia(amarelo, a(l, c)) < 70) //função distância (biblioteca cekeikon) calcula a distância euclidiana entre duas cores. Limiar inicialmente escolhido como 70.
                b(l, c) = COR(255, 255, 255);
    imp(b, "elefante_am.png");
}
