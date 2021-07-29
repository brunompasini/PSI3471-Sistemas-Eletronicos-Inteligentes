//ep1.cpp
//Exercício Programa
//Pedro Henrique Gianjoppe dos Santos - 10774055
//Bruno Mucha Pasini - 10845791
#include "cekeikon.h"
#include <string>
#include <cmath>


Mat_<FLT> newDcReject(Mat_<FLT> a, float dontcare)
{
    float epsilon = 0.2;
    Mat_<FLT> b = a.clone();
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < b.total(); i++){
        if (b(i)-epsilon < dontcare && b(i)+epsilon > dontcare) {} // faz nada
        else {
            sum += b(i);
            count++;
        }
    }

    double mean = sum / count;
    for (int j = 0; j < b.total(); j++){
        if (b(j)-epsilon < dontcare && b(j)+epsilon > dontcare) {
            b(j) = 0.0;
        } else {
            b(j) -= mean;
        }
    }
    return b;
}

//1) Ler imagem do canhoto como Mat_ <FLT>
int main(int argc, char **argv)
{ // ep , entrada.jpg , saida.png

    if (argc != 3)
    {
        printf("ep entrada.jpg saida.png\n");
        erro("Erro: Numero de argumentos invalido");
    }
    string pathCanhoto;
    //pathCanhoto.append("POD/");
    //pathCanhoto.append(argv[1]);
    Mat_<FLT> canhoto;
    le(canhoto, argv[1]);

    //2) Redimensionar para 750 colunas e linhas proporcionais (manter aspect ratio para linhas)

    Mat_<FLT> A; //A = canhoto redimensionado
    resize(canhoto, A, Size(0, 0), 750.0 / canhoto.cols, 750.0 / canhoto.cols, INTER_NEAREST);
    //OBS: NÃO FUNCIONA SE IMAGEM TIVER COLUNAS > 750

    //A = canhoto redimensionado e Q = canhoto padrão
    //3) Colocar A no centro de uma moldura cinza (128/255) 310x1150

    Mat_<FLT> A_moldura; //(310,1150);

    int ver = ceil((310 - A.rows) / 2);
    int hor = ceil((1150 - A.cols) / 2);

    double cinza = 128.0 / 255.0;

    copyMakeBorder(A, A_moldura, ver, ver, hor, hor, BORDER_CONSTANT, Scalar(cinza));
    imp(A_moldura, "A_moldura.png");

    //4) Para cada canhoto padrão Q = m?.pgm
    //4.1) Ler m?.pgm como Mat_ <FLT>
    Mat_<FLT> m2, m3, m4;
    le(m2, "POD/m2.pgm");
    le(m3, "POD/m3.pgm");
    le(m4, "POD/m4.pgm");

    int Q_ver = ceil((210 - m2.rows) / 2);
    int Q_hor = ceil((1050 - m2.cols) / 2);

    //Q = m2 (Canhoto padrão m2)--------------------------------------------------------------
    //4.2) Coloca Q no centro de uma moldura cinza (128/255) 210x1050
    Mat_<FLT> m2_moldura; //(210,1050);

    copyMakeBorder(m2, m2_moldura, Q_ver, Q_ver, Q_hor, Q_hor, BORDER_CONSTANT, cinza);
    imp(m2_moldura, "m2_moldura.png");

    Mat_<FLT> m3_moldura; //(210,1050);

    copyMakeBorder(m3, m3_moldura, Q_ver, Q_ver, Q_hor, Q_hor, BORDER_CONSTANT, cinza);
    imp(m3_moldura, "m3_moldura.png");

    Mat_<FLT> m4_moldura; //(210,1050);

    copyMakeBorder(m4, m4_moldura, Q_ver, Q_ver, Q_hor, Q_hor, BORDER_CONSTANT, cinza);
    imp(m4_moldura, "m4_moldura.png");

    //4.3) Gerar vector< Mat_<FLT> >  todas as combinações de Q redimensionadas nas escalas de 0,88 a 1,1 (21 passos - PG - q = 1.01068253859)
    //                                                                              e rotacionadas de -3 a +3 graus (17 passos - PA r = 0,3529411).

    double escalas[] = {0.88, 0.8898732928778292, 0.8998573606559442, 0.9099534461900652, 0.9201628062803204, 0.9304867118276965, 0.94092647992245, 0.9514833143530671, 0.9621586250700848, 0.9729537090476376, 0.9838699100999075, 0.9949085871182028, 1.006071114240118, 1.0173588810205916, 1.0287732926048836, 1.0403157699034935, 1.0519877497690409, 1.0637906851751298, 1.0757260453972215, 1.087795316195535, 1.09};
    double rotacao[] = {-3.0, -2.625, -2.25, -1.875, -1.5, -1.125, -0.75, -0.375, 0.0, 0.375, 0.75, 1.125, 1.5, 1.875, 2.25, 2.625, 3.0};

    //5) Laço loop para calcular template matching CC (modo same) entre A e cada Q de cada modelo (m2,m3,m4)
    //5.1) Armazenar cada correlação na matriz corr(i) => pegar valor máximo max(corr(i)) e salvar índice i

    //MODELO M2
    double corr_m2_max[21 * 17];
    int deslocamentox_m2[21 * 17];
    int deslocamentoy_m2[21 * 17];
    //indice(corr_m2_med) / 17: Quociente = i, Resto = j

    int ind = 0;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            Mat_<FLT> Q_temp;

            resize(m2_moldura, Q_temp, Size(0, 0), escalas[i], escalas[i], INTER_NEAREST);

            Mat_<double> m = getRotationMatrix2D(Point2f(Q_temp.cols / 2, Q_temp.rows / 2), rotacao[j], 1);

            warpAffine(Q_temp, Q_temp, m, Q_temp.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(cinza));

            Mat_<FLT> q = somaAbsDois(newDcReject(Q_temp, cinza));

            Mat_<FLT> corr_temp = matchTemplateSame(A_moldura, q, CV_TM_CCORR);

            //calculo do max
            double min, max;

            Point minLoc, maxLoc;
            cv::minMaxLoc(corr_temp, &min, &max, &minLoc, &maxLoc);

            corr_m2_max[ind] = max;
            //cout << "corr_m2_max = " << corr_m2_max[ind] << endl;

            deslocamentox_m2[ind] = maxLoc.x - corr_temp.cols / 2.0;

            deslocamentoy_m2[ind] = maxLoc.y - corr_temp.rows / 2.0;

            ind++;
        }
    }

    //MODELO M3
    double corr_m3_max[21 * 17];
    int deslocamentox_m3[21 * 17];
    int deslocamentoy_m3[21 * 17];
    //indice(corr_m3_med) / 17: Quociente = i, Resto = j

    ind = 0;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            Mat_<FLT> Q_temp;

            resize(m3_moldura, Q_temp, Size(0, 0), escalas[i], escalas[i], INTER_NEAREST);

            Mat_<double> m = getRotationMatrix2D(Point2f(Q_temp.cols / 2, Q_temp.rows / 2), rotacao[j], 1);

            warpAffine(Q_temp, Q_temp, m, Q_temp.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(cinza));

            Mat_<FLT> q = somaAbsDois(newDcReject(Q_temp, cinza));

            Mat_<FLT> corr_temp = matchTemplateSame(A_moldura, q, CV_TM_CCORR);

            //calculo do max
            double min, max;

            Point minLoc, maxLoc;
            cv::minMaxLoc(corr_temp, &min, &max, &minLoc, &maxLoc);

            corr_m3_max[ind] = max;
            //cout << "corr_m3_max = " << corr_m3_max[ind] << endl;

            deslocamentox_m3[ind] = maxLoc.x - corr_temp.cols / 2.0;

            deslocamentoy_m3[ind] = maxLoc.y - corr_temp.rows / 2.0;

            ind++;
        }
    }

    //MODELO m4
    double corr_m4_max[21 * 17];
    int deslocamentox_m4[21 * 17];
    int deslocamentoy_m4[21 * 17];
    //indice(corr_m4_med) / 17: Quociente = i, Resto = j

    ind = 0;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            Mat_<FLT> Q_temp;

            resize(m4_moldura, Q_temp, Size(0, 0), escalas[i], escalas[i], INTER_NEAREST);

            Mat_<double> m = getRotationMatrix2D(Point2f(Q_temp.cols / 2, Q_temp.rows / 2), rotacao[j], 1);

            warpAffine(Q_temp, Q_temp, m, Q_temp.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(cinza));

            Mat_<FLT> q = somaAbsDois(newDcReject(Q_temp, cinza));

            Mat_<FLT> corr_temp = matchTemplateSame(A_moldura, q, CV_TM_CCORR);

            //calculo do max
            double min, max;

            Point minLoc, maxLoc;
            cv::minMaxLoc(corr_temp, &min, &max, &minLoc, &maxLoc);

            corr_m4_max[ind] = max;
            //cout << "corr_m4_max = " << corr_m4_max[ind] << endl;

            deslocamentox_m4[ind] = maxLoc.x - corr_temp.cols / 2.0;

            deslocamentoy_m4[ind] = maxLoc.y - corr_temp.rows / 2.0;

            ind++;
        }
    }

    //6) Pegar a maior correção entre os 3 modelos assim como seu índice i
    //      Imprimir saída do formato : " Maior correlacao entre m2_001.jpg e m2.pgm: 0.147 "
    //indice(corr_m2_med) / 17: Quociente = i, Resto = j

    double m2_corr_max = corr_m2_max[0];
    double m3_corr_max = corr_m3_max[0];
    double m4_corr_max = corr_m4_max[0];

    int m2_icorr_max, m3_icorr_max, m4_icorr_max = 0;

    for (int c = 1; c < 21 * 17; c++)
    {
        if (corr_m2_max[c] > m2_corr_max)
        {
            m2_corr_max = corr_m2_max[c];
            m2_icorr_max = c;
        }

        if (corr_m3_max[c] > m3_corr_max)
        {
            m3_corr_max = corr_m3_max[c];
            m3_icorr_max = c;
        }

        if (corr_m4_max[c] > m4_corr_max)
        {
            m4_corr_max = corr_m4_max[c];
            m4_icorr_max = c;
        }
    }

    cout << "Maior correlacao entre " << argv[1] << " e m2.pgm: " << m2_corr_max << endl;
    cout << "Maior correlacao entre " << argv[1] << " e m3.pgm: " << m3_corr_max << endl;
    cout << "Maior correlacao entre " << argv[1] << " e m4.pgm: " << m4_corr_max << endl;

    //7) Coletar distorção de escala (fator(i)) e de rotacao(graus(i)) e deslocamento (desloc(i,j))
    //      Imprimir saída do formato : " melhorModelo=2 corr= 0.147 graus= 0.750 fator= 1.006 desloc(x,y)=[ -2, -2] "

    int deslocamentox;
    int deslocamentoy;
    int modelo = 0;
    int icorr_max;
    double corr_max;
    Mat_<FLT> moldura;

    if (m2_corr_max > m3_corr_max)
    {
        if (m2_corr_max > m4_corr_max)
        {
            //cout << m2_corr_max;
            corr_max = m2_corr_max;
            icorr_max = m2_icorr_max;
            deslocamentox = deslocamentox_m2[icorr_max];
            deslocamentoy = deslocamentoy_m2[icorr_max];
            moldura = m2_moldura.clone();
            modelo = 2;
        }
    }

    if (m3_corr_max > m2_corr_max)
    {
        if (m3_corr_max > m4_corr_max)
        {
            //cout << m3_corr_max;
            corr_max = m3_corr_max;
            icorr_max = m3_icorr_max;
            deslocamentox = deslocamentox_m3[icorr_max];
            deslocamentoy = deslocamentoy_m3[icorr_max];
            moldura = m3_moldura.clone();
            modelo = 3;
        }
    }
    if (m4_corr_max > m3_corr_max)
    {
        if (m4_corr_max > m2_corr_max)
        {
            //cout << m4_corr_max;
            corr_max = m4_corr_max;
            icorr_max = m4_icorr_max;
            deslocamentox = deslocamentox_m4[icorr_max];
            deslocamentoy = deslocamentoy_m4[icorr_max];
            moldura = m4_moldura.clone();
            modelo = 4;
        }
    }

    //indice(corr_m2_med) / 17: Quociente = i, Resto = j
    int iescalas = icorr_max / 17;
    int irotacao = icorr_max % 17;

    //cout << "iescalas = " << iescalas << endl;
    //cout << "irotacao = " << irotacao << endl;

    cout << "melhorModelo = " << modelo << ", corr = " << corr_max << ", graus = " << rotacao[irotacao] << ", fator = " << escalas[iescalas] << ", desloc(x,y) = "
         << "[ " << deslocamentox << ", " << deslocamentoy << "]" << endl;

    //FALTA SELECIONAR MELHOR MODELO E IMPRIMIR DESLOCAMENTO!

    //8) Imprimir imagem inicial
    imp(canhoto, argv[1]);

    //9) Imprimir canhoto padrão distocido (fator, graus e desloc) e colorido (vermelho, azul) sobreposto à imagem inicial*/
    Mat_<FLT> Q;
    resize(moldura, Q, Size(0, 0), escalas[iescalas], escalas[iescalas], INTER_NEAREST);
    Mat_<double> m = getRotationMatrix2D(Point2f(Q.cols / 2, Q.rows / 2), rotacao[irotacao], 1);
    warpAffine(Q, Q, m, Q.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(cinza));

    //cout << "Q.rows = " << Q.rows << " Q.cols = " << Q.cols << endl;
    //cout << "canhotoA.rows = " << A_moldura.rows << " canhotoA.cols = " << A_moldura.cols << endl;

    Mat_<COR> A_cor;
    converte(A_moldura, A_cor);

    Mat_<COR> Q_cor;
    converte(Q, Q_cor);

    int cor_ver = ceil((A_cor.rows - Q_cor.rows) / 2);
    int cor_hor = ceil((A_cor.cols - Q_cor.cols) / 2);

    copyMakeBorder(Q_cor, Q_cor, cor_ver, cor_ver, cor_hor, cor_hor, BORDER_CONSTANT, Scalar(cinza));

    Mat_<FLT> Q_cinza = Q.clone();
    copyMakeBorder(Q_cinza, Q_cinza, cor_ver, cor_ver, cor_hor, cor_hor, BORDER_CONSTANT, Scalar(cinza));

    for (int l = cor_ver; l < Q_cinza.rows - cor_ver; l++)
    {
        for (int c = cor_hor; c < Q_cinza.cols - cor_hor; c++)
        {
            if (Q_cinza(l, c) == 0) // Pintando de vermelho
            {                       //foi utilizada uma tolerância Epsilon = 0.1
                A_cor(l + deslocamentoy, c + deslocamentox)[0] /= 2;
                A_cor(l + deslocamentoy, c + deslocamentox)[1] /= 2;
                A_cor(l + deslocamentoy, c + deslocamentox)[2] = 255; //componente vermelha
            }
            else if (Q_cinza(l, c) != 1) //Pintando de azul
            {
                A_cor(l + deslocamentoy, c + deslocamentox)[0] = 255; //componente azul
                A_cor(l + deslocamentoy, c + deslocamentox)[1] /= 2;
                A_cor(l + deslocamentoy, c + deslocamentox)[2] /= 2;
            }
        }
    }

    imp(Q_cor, "Q_cor.png");
    imp(Q_cinza, "Q_cinza.png");

    imp(A_cor, argv[2]);
    // */
}
