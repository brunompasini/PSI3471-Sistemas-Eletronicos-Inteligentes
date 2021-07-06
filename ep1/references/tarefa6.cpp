//tarefa6.cpp
//Tarefa 6
//Pedro Henrique Gianjoppe dos Santos - 10774055
//Bruno Mucha Pasini - 10845791
#include <cekeikon.h>
int main()
{
    Mat_<GRY> a;
    le(a, "lennag.jpg");
    double fator = 3.6;

    Mat_<GRY> vizinho, linear, bicubico, lanczos;
    resize(a, vizinho, Size(0,0), fator, fator, INTER_NEAREST);
    resize(a, linear, Size(0,0), fator, fator, INTER_LINEAR);
    resize(a, bicubico, Size(0,0), fator, fator, INTER_CUBIC);
    resize(a, lanczos, Size(0,0), fator, fator, INTER_LANCZOS4);

    imp(vizinho, "vizinho.jpg");
    imp(linear, "linear.jpg");
    imp(bicubico, "bicubico.jpg");
    imp(lanczos, "lanczos.jpg");
}