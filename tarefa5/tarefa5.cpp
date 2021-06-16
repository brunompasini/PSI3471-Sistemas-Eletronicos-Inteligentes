// tarefa5.cpp
#include <cekeikon.h>
int main()
{
    Mat_<FLT> a;
    le(a, "a.png"); //Matriz a representa a figura de ursinhos
    Mat_<FLT> q;
    le(q, "q.png");  //Matriz q representa o ursinho (template)

    Mat_<FLT> q_inv = q.clone();
    for (int l_q = 0; l_q < q.rows; l_q++)
        for (int c_q = 0; c_q < q.cols; c_q++)
                q_inv(l_q,c_q) =  1.0 - q(l_q,c_q);
                
    imp(q_inv, "q_inv.png");

    Mat_<FLT> corr_p;
    corr_p = matchTemplateSame(a, q, CV_TM_CCOEFF_NORMED);
    imp(corr_p, "correlao_p.png");

    Mat_<FLT> corr_p_inv;
    corr_p_inv = matchTemplateSame(a, q_inv, CV_TM_CCOEFF_NORMED);
    imp(corr_p_inv, "correlao_p_inv.png");

    Mat_<COR> p;
    converte(a, p);
    for (int l = 0; l < a.rows; l++)
        for (int c = 0; c < a.cols; c++)
            if (corr_p(l, c) >= 1.0 - 0.1 || corr_p_inv(l, c) >= 1.0 - 0.1) //foi utilizada uma tolerância Epsilon = 0.1
                //p(l, c) = COR(0, 0, 255);
                rectangle(p, Point(c - 2, l - 2), Point(c + 2, l + 2), Scalar(0, 0, 255), -1);
    imp(p, "p.png");
}
