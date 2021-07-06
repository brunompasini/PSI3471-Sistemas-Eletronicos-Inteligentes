//Tarefa 9
//Pedro Henrique Gianjoppe dos Santos - 10774055
//Bruno Mucha Pasini - 10845791
#include <cmath>
#include <cekeikon.h>
#include <vector>
Mat_<GRY> moveCima(Mat_<GRY> img) {
    for (int l=0; l<img.rows; l++){
        for (int c=0; c<img.cols; c++){
            if (l!=0){
                img(l-1, c) = img(l,c);
            } 
        }
    }
    return img;
}
Mat_<GRY> moveBaixo(Mat_<GRY> img) {
    for (int l=img.rows-1; l=0; l--){
        for (int c=0; c<img.cols; c++){
            if (l!=img.rows-1){
                img(l, c) = img(l-1,c);
            } 
        }
    }
    return img;
}
Mat_<GRY> moveEsquerda(Mat_<GRY> img) {
    for (int l=0; l<img.rows; l++){
        for (int c=0; c<img.cols; c++){
            if (c!=0){
                img(l, c-1) = img(l,c);
            } 
        }
    }
    return img;
}
Mat_<GRY> moveDireita(Mat_<GRY> img) {
    for (int l=0; l<img.rows; l++){
        for (int c=img.cols-1;c>0; c++){
            if (c!=img.cols-1){
                img(l, c) = img(l,c-1);
            } 
        }
    }
    return img;
}

int main()
{
    
    int n = 12;
    MNIST mnist(n, true, true);
    mnist.le("C:/cekeikon5/tiny_dnn/data");
    vector < Mat_<GRY> > mnist_GRY_AX;

    vector<int> mnist_AY;

    for (int i = 0; i < 60000; i++)
    {
        mnist_GRY_AX.push_back(mnist.AX[i]); mnist_AY.push_back(mnist.AY[i]);
        mnist_GRY_AX.push_back(moveCima(mnist.AX[i])); mnist_AY.push_back(mnist.AY[i]);
        mnist_GRY_AX.push_back(moveBaixo(mnist.AX[i])); mnist_AY.push_back(mnist.AY[i]);
        mnist_GRY_AX.push_back(moveEsquerda(mnist.AX[i])); mnist_AY.push_back(mnist.AY[i]);
        mnist_GRY_AX.push_back(moveDireita(mnist.AX[i])); mnist_AY.push_back(mnist.AY[i]);

    }

    //Temos 60000*5 imagens!
    Mat_<FLT> mnist_FLT(300000,n*n); //60000*5 X (n*n colunas)
    //mnist_GRY_AX => FLT = ax
    for (int l=0; l<300000; l++){
        for (int c=0;c<n*n; c++){
            Mat_<GRY> temp = mnist_GRY_AX[l];
            mnist_FLT(l,c) = temp(c)/255.0; 
            cout << l << "   " << c << endl;
            
        }
    }

    //mnist_AY => FLT = ay
    //float a  = (float) numeroemint;

    TimePoint t1 = timePoint();
    flann::Index ind(mnist_FLT, flann::KDTreeIndexParams(16));
    TimePoint t2 = timePoint();
    vector<int> indices(1);
    vector<float> dists(1);
    for (int l = 0; l < mnist.qx.rows; l++)
    {
        ind.knnSearch(mnist.qx.row(l), indices, dists, 1, flann::SearchParams(1024));
        for (int i=0; i<5; i++)
            mnist.qp(l) = mnist.ay(indices[0]);
    }
    TimePoint t3 = timePoint();
    printf("Erros=%10.2f%%\n", 100.0 * mnist.contaErros() / mnist.nq);
    printf("Tempo de treinamento: %f\n", timeSpan(t1, t2));
    printf("Tempo de predicao: %f\n", timeSpan(t2, t3));
}
