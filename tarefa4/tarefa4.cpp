#include <cekeikon.h>
int main()
{
    Mat_<FLT> a; //Matriz ponto flutuante (0 = preto e 1 = branco)
    le(a, "quadrado.png");
    Mat_<FLT> sx, sy, ox, oy;
    Sobel(a, sx, -1, 1, 0, 3);
    ox = sx / 4.0 + 0.5;
    imp(ox, "ox.png");
    Sobel(a, sy, -1, 0, 1, 3);
    oy = sy / 4.0 + 0.5;
    imp(oy, "oy.png");

    Mat_<FLT> todo_hor, hor_sup, hor_inf, todo_ver, ver_esq, ver_dir;
    todo_hor = a.clone();
    hor_sup  = a.clone();
    hor_inf  = a.clone();
    todo_ver = a.clone();
    ver_esq  = a.clone();
    ver_dir  = a.clone();

    for (int l = 0; l < a.rows; l++) {
        for (int c = 0; c < a.cols; c++) {
            
        }        
    }
    /*Complete o programa aqui utilizando matrizes sx e sy
    Complete o programa, fazendo operações com as matrizes sx e sy, para obter as imagens com:
     • Todas bordas horizontais: todo_hor.png 
    • A borda horizontal superior: hor_sup.png
    • A borda horizontal inferior: hor_inf.png
    • Todas as bordas verticais: todo_ver.png
    • A borda vertical esquerda: ver_esq.png
    • A borda vertical direita: ver_dir.png. */
}

/* toda_hor = aplicar módulo

hor_sup = valor negativo de sy  => '0' (preto). Assim todos os valores de saída são positivos ou zero (só borda superior)

hor_inf = valor positivo de sy  => '0' (preto). Assim todos os valores de saída são negativos ou zero (só borda inferior) */