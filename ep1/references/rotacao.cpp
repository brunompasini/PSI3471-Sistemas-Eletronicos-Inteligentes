//rotacao.cpp grad2020
#include <cekeikon.h>
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("rotacao ent.pgm sai.pgm graus\n");
        erro("Erro: Numero de argumentos invalido");
    }
    double graus;
    sscanf(argv[3], "%lf", &graus);
    double radianos = deg2rad(graus);
    double co = cos(radianos);
    double se = sin(radianos);
    ImgXyb<GRY> a;
    le(a, argv[1]);
    a.centro(a.rows / 2, a.cols / 2);
    a.backg = 255;
    ImgXyb<GRY> b(a.rows, a.cols);
    b.centro(b.rows / 2, b.cols / 2);
    b.backg = 255;
    for (int xb = b.minx; xb <= b.maxx; xb++)
        for (int yb = b.miny; yb <= b.maxy; yb++)
        {
            int xa = cvRound(xb * co + yb * se);
            int ya = cvRound(-xb * se + yb * co);
            b(xb, yb) = a(xa, ya);
        }
    imp(b, argv[2]);
}
