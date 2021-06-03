//removeruido.cpp
#include <cekeikon.h>

bool detectaRuido(Mat_<GRY> a, int l, int c){
    int cont_brancos = 0;
    for (int i = l-1; i < l+2; i++){
        for (int j = c-1; j < c+2; j++){
            if (i==l && j==c){continue;}
            if(a(i,j) == 255){
                cont_brancos++;
            }
        }
    }
    if (cont_brancos < 3){
        return true;
    }
    return false;
}

int main()
{
    Mat_<GRY> a;
    le(a, "mickey.bmp");                    
    Mat_<GRY> b(a.rows, a.cols, 255);       
    for (int l = 1; l < a.rows - 1; l++)    
        for (int c = 1; c < a.cols - 1; c++)
            if(c == 0){ // Primeira coluna
                if (a(l-1, c) == 0      && a(l-1, c+1)   == 0 
                    && a(l, c)   == 255 && a(l, c+1)     == 0
                    && a(l+1, c) == 0   && a(l+1, c+1)   == 0)
                {
                    a(l, c) = 0;
                } 
            } else if (c == a.cols -1) { // Última coluna
                if (a(l-1, c-1) == 0   && a(l-1, c) == 0   && 
                     a(l, c-1)   == 0   && a(l, c)   == 255 &&
                     a(l+1, c-1) == 0   && a(l+1, c) == 0)
                {
                    a(l, c) = 0;
                }  
            }
            else if (l == 0) { // Primeira linha
                if (a(l, c-1)   == 0   && a(l, c)   == 255 && a(l, c+1)     == 0 &&
                    a(l+1, c-1) == 0   && a(l+1, c) == 0   && a(l+1, c+1)   == 0)
                {
                    a(l, c) = 0;
                }
            } else if (l == a.rows -1) { // Última Linha
                if (a(l-1, c-1) == 0   && a(l-1, c) == 0   && a(l-1, c+1)   == 0 && 
                     a(l, c-1)   == 0  && a(l, c)   == 255 && a(l, c+1)     == 0)
                {
                    a(l, c) = 0;
                } 
            } else { // Tudo entre segunda e penúltima coluna                 
                if (detectaRuido(a,l,c) == true) {
                    a(l,c) = 0;
                }
            }
        

    imp(a, "mickeysemruido.bmp");
}


