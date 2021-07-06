//tarefa8.cpp
//Tarefa 8
//Pedro Henrique Gianjoppe dos Santos - 10774055
//Bruno Mucha Pasini - 10845791
#include <cekeikon.h>

Mat_<GRY> mediana(Mat_<GRY> a)
{
    Mat_<GRY> b(a.rows,a.cols);
    medianBlur(a,b,9);
    return b;
}


int main()
{

    Mat_<GRY> ax;
    le(ax, "janei.pgm");
    Mat_<GRY> ay;
    le(ay, "janei-1.pgm");
    Mat_<GRY> qx;
    le(qx, "julho.pgm");
    if (ax.size() != ay.size())
        erro("Erro dimensao");
    Mat_<GRY> qp(qx.rows, qx.cols);
    //Cria as estruturas de dados para alimentar OpenCV
    Mat_<FLT> features(ax.rows * ax.cols, 9);
    Mat_<FLT> saidas(ax.rows * ax.cols, 1);
    int i = 0;
    for (int l = 0; l < ax.rows; l++)
        for (int c = 0; c < ax.cols; c++)
        {
            features(i, 0) = ax(l - 1, c - 1) / 255.0;
            features(i, 1) = ax(l, c - 1) / 255.0;
            features(i, 2) = ax(l + 1, c - 1) / 255.0;
            features(i, 3) = ax(l - 1, c) / 255.0;
            features(i, 4) = ax(l, c) / 255.0;
            features(i, 5) = ax(l + 1, c) / 255.0;
            features(i, 6) = ax(l - 1, c + 1) / 255.0;
            features(i, 7) = ax(l, c + 1) / 255.0;
            features(i, 8) = ax(l + 1, c + 1) / 255.0;
            saidas(i) = ay(l, c) / 255.0;
            i = i + 1;
        }
    flann::Index ind(features, flann::KDTreeIndexParams(10));
    // Aqui, as 4 arvores estao criadas
    Mat_<FLT> query(1, 9);
    vector<int> indices(1);
    vector<FLT> dists(1);
    for (int l = 0; l < qp.rows; l++)
        for (int c = 0; c < qp.cols; c++)
        {
            query(0, 0) = qx(l - 1, c - 1) / 255.0;
            query(0, 1) = qx(l, c - 1) / 255.0;
            query(0, 2) = qx(l + 1, c - 1) / 255.0;
            query(0, 3) = qx(l - 1, c) / 255.0;
            query(0, 4) = qx(l, c) / 255.0;
            query(0, 5) = qx(l + 1, c) / 255.0;
            query(0, 6) = qx(l - 1, c + 1) / 255.0;
            query(0, 7) = qx(l, c + 1) / 255.0;
            query(0, 8) = qx(l + 1, c + 1) / 255.0; // Zero indica sem backtracking
            ind.knnSearch(query, indices, dists, 1, flann::SearchParams(20));
            // Saida e' um numero entre 0 e 255
            qp(l, c) = 255 * saidas(indices[0]);
        }
    imp(qp, "julho_flann.png");

    
    // filtro mediana   

    Mat_<GRY> julho_filt = mediana(qp);
    imp(julho_filt, "julho_filt.png");

    Mat_<COR> julho_cor;
    le(julho_cor,"julho.pgm");

    Mat_<COR> julho_vermelho = julho_cor.clone();

    for (int l = 0; l < julho_filt.rows; l++)
        for (int c = 0; c < julho_filt.cols; c++)
             if ( julho_filt(l, c) < 30) {
                 julho_vermelho(l,c)[2] = 255;
             }

    imp(julho_vermelho, "julho_vermelho.png");


}