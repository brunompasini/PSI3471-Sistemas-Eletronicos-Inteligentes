//pers.cpp grad-2018
#include <cekeikon.h>
int main()
{
    Mat_<FLT> src = (Mat_<FLT>(4, 2) << 
                     142, 49,
                     318, 38,
                     109, 294,
                     348, 292);
    Mat_<FLT> dst = (Mat_<FLT>(4, 2) << 
                     100, 0,
                     354, 0,
                     100, 323,
                     354, 323);
    Mat_<double> m = getPerspectiveTransform(src, dst);
    cout << m << endl;

    //Corrige a perspectiva
    Mat_<COR> a;
    le(a, "calib_result.jpg");
    Mat_<COR> b;
    warpPerspective(a, b, m, a.size());
    imp(b, "tabuleiro.jpg");
    //Refaz a perspectiva
    m = m.inv();
    warpPerspective(b, a, m, a.size());
    imp(a, "tabuleiro_inv.jpg");
}
