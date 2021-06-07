//tarefa2.cpp
#include <cekeikon.h>
#include <queue>
Mat_<COR> pintaVermelho(Mat_<COR> a, int ls, int cs, int t)
{
    COR amarelo(20, 200, 200);
    Mat_<COR> b = a.clone(); //criando uma cópia de a para manter a imagem a original sem alterações!
    queue<int> q; //fila q com números inteiros (índice dos pixeis)
    q.push(ls);
    q.push(cs); //(1) Coloque o pixel-semente no conjunto V dos pixels a serem visitados. 
    while (!q.empty()) //enquanto a fila q não estiver vazia
    { //(2) Se o conjunto V for vazio, termine o programa.
        int l = q.front();//l recebe quem está na frente da fila
        q.pop(); //(3) //retira primeiro elemento da fila q
        int c = q.front();//c recebe quem está na frente da fila
        q.pop(); //(3) //retira primeiro elemento da fila
        if (distancia(amarelo, a(l, c)) < t) //se for branco
        {                             //(4)
            b(l, c) = COR(0, 0, 255); //(5)
            q.push(l - 1);
            q.push(c); //6-acima
            q.push(l + 1);
            q.push(c); //6-abaixo
            q.push(l);
            q.push(c + 1); //6-direita
            q.push(l);
            q.push(c - 1); //6-esq
        }
    }
    return b;
}
int main()
{
    Mat_<COR> a;
    le(a, "elefante.jpg");
    Mat_<COR> b = pintaVermelho(a, 120, 120, 10); //semente é pixel localizado em (120,120)
    imp(b, "elefante_vermelho.png");
}
