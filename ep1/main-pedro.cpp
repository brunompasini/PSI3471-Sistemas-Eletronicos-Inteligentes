//ep1.cpp
//Exercício Programa
//Pedro Henrique Gianjoppe dos Santos - 10774055
//Bruno Mucha Pasini - 10845791
#include "cekeikon.h"
#include <string>
#include <cmath>
//1) Ler imagem do canhoto como Mat_ <FLT>
int main(int argc, char **argv)
{ // ep , entrada.jpg , saida.png

    if (argc != 3)
    {
        printf("ep entrada.jpg saida.png\n");
        erro("Erro: Numero de argumentos invalido");
    }
    string pathCanhoto;
    pathCanhoto.append("POD/");
    pathCanhoto.append(argv[1]);
    Mat_<FLT> canhoto;
    le(canhoto, pathCanhoto);

    //2) Redimensionar para 750 colunas e linhas proporcionais (manter aspect ratio para linhas)

    Mat_<FLT> A; //A = canhoto redimensionado
    double fator = 750 / canhoto.cols;
    resize(canhoto, A, Size(0, 0), fator, fator, INTER_LANCZOS4);

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

    //4.3) Gerar vector< Mat_<FLT> >  todas as combinações de Q redimensionadas nas escalas de 0,88 a 1,1 (21 passos - PG - q = 1.01068253859)
    //                                                                              e rotacionadas de -3 a +3 graus (17 passos - PA r = 0,3529411).

    //5) Laço loop para calcular template matching CC (modo same) entre A e cada Q de cada modelo (m2,m3,m4)
    //5.1) Armazenar cada correlação na matriz corr(i) => pegar valor máximo max(corr(i)) e salvar índice i

    double escalas[] = {0.88, 0.8898732928778292, 0.8998573606559442, 0.9099534461900652, 0.9201628062803204, 0.9304867118276965, 0.94092647992245, 0.9514833143530671, 0.9621586250700848, 0.9729537090476376, 0.9838699100999075, 0.9949085871182028, 1.006071114240118, 1.0173588810205916, 1.0287732926048836, 1.0403157699034935, 1.0519877497690409, 1.0637906851751298, 1.0757260453972215, 1.087795316195535, 1.09};
    double rotacao[] = {-3.0, -2.625, -2.25, -1.875, -1.5, -1.125, -0.75, -0.375, 0.0, 0.375, 0.75, 1.125, 1.5, 1.875, 2.25, 2.625, 3.0};

    double corr_m2_med[21 * 17];
    double corr_m2_max[21 * 17];
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

            Mat_<FLT> q = somaAbsDois(dcReject(Q_temp));

            Mat_<FLT> corr_temp = matchTemplateSame(A_moldura, q, CV_TM_CCORR);

            if (i == 9 && j == 10) //Apenas para fase de testes (colocar em i = iescalas e j = irotacao )
            {
                imp(Q_temp, "Q_temp.png");
                imp(corr_temp, "corr_temp.png");
                cout << "corr_temp.rows = " << corr_temp.rows << endl;
                cout << "corr_temp.cols = " << corr_temp.cols << endl;
            }

            //calculo do max
            double min, max;
            cv::minMaxLoc(corr_temp, &min, &max);

            corr_m2_med[ind] = mean(corr_temp)[0];
            cout << "corr_m2_med = " << corr_m2_med[ind] << endl;

            corr_m2_max[ind] = max;
            cout << "corr_m2_max = " << corr_m2_max[ind] << endl;

            ind++;
        }
    }

    //6) Pegar a maior correção entre os 3 modelos assim como seu índice i
    //      Imprimir saída do formato : " Maior correlacao entre m2_001.jpg e m2.pgm: 0.147 "
    //indice(corr_m2_med) / 17: Quociente = i, Resto = j

    //7) Coletar distorção de escala (fator(i)) e de rotacao(graus(i)) e deslocamento (desloc(i,j))
    //      Imprimir saída do formato : " melhorModelo=2 corr= 0.147 graus= 0.750 fator= 1.006 desloc(x,y)=[ -2, -2] "
    float corr_max = corr_m2_max[0];
    int icorr_max = 0;

    for (int c = 1; c < 21 * 17; c++)
    {
        if (corr_m2_max[c] > corr_max)
        {
            corr_max = corr_m2_max[c];
            icorr_max = c;
        }
    }

    cout << "Maxima correlacao no indice icorr_max = "<< icorr_max << " e valor corr_max = " << corr_max << endl;

    //indice(corr_m2_med) / 17: Quociente = i, Resto = j
    int iescalas= icorr_max/17;
    int irotacao = icorr_max%17;

    cout << "iescalas = " << iescalas << endl;
    cout << "irotacao = " << irotacao << endl;

    cout << "melhorModelo = 2" << ", corr = " << corr_max << ", graus = " << rotacao[irotacao] << ", fator = " << escalas[iescalas] << endl;

    //8) Imprimir imagem inicial

    //9) Imprimir canhoto padrão distocido (fator, graus e desloc) e colorido (vermelho, azul) sobreposto à imagem inicial*/

    
}