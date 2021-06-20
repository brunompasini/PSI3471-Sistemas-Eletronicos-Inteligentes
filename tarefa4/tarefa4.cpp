// tarefa4.cpp
// Bruno Mucha Pasini nUSP 10845791
// Pedro Henrique Gianjoppe dos Santos nUSP 10774055
#include <cekeikon.h>
int main() {
    Mat_<FLT> a; le(a,"quadrado.png");
    Mat_<FLT> sx,sy,ox,oy;
    Sobel(a,sx,-1,1,0,3); ox=sx/4.0+0.5; imp(ox,"ox.png");
    Sobel(a,sy,-1,0,1,3); oy=sy/4.0+0.5; imp(oy,"oy.png");

    imp(sx, "sx.png");imp(sy, "sy.png");
    
    Mat_<FLT> todo_hor, hor_sup, hor_inf, todo_ver, ver_esq, ver_dir;

    hor_sup = sy.clone(); imp(hor_sup, "hor_sup.png");
    ver_esq = sx.clone(); imp(ver_esq, "ver_esq.png");

    flip(hor_sup, hor_inf, 0); imp(hor_inf, "hor_inf.png"); // funcao flip do openCV
    flip(ver_esq, ver_dir, 1); imp(ver_dir, "ver_dir.png"); // idem

    bitwise_and(hor_sup, hor_inf, todo_hor); imp(todo_hor, "todo_hor.jpg"); // bitwise_and do openCV
    bitwise_and(ver_esq, ver_dir, todo_ver); imp(todo_ver, "todo_ver.jpg"); // idem
}