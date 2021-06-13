// Bruno Mucha Pasini                   nUSP: 10845791
// Pedro Henrique Gianjoppe dos Santos  nUSP: 10774055

#include <cekeikon.h>
Mat_<GRY> mediana(Mat_<GRY> a) {
    Mat_<GRY> b(a.rows,a.cols);
    medianBlur(a,b,11);
    return b;
}

int main() {
    Mat_<GRY> a;
    le(a,"fever-2.pgm");
    Mat_<GRY> b = mediana(a);
    imp(b,"ex3.png");
}