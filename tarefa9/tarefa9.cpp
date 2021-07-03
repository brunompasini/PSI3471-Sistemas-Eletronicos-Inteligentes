//Tarefa 9
//Pedro Henrique Gianjoppe dos Santos - 10774055
//Bruno Mucha Pasini - 10845791
#include <cekeikon.h>
int main()
{
    MNIST mnist(12, true, true);
    mnist.le("C:/cekeikon5/tiny_dnn/data");
    TimePoint t1 = timePoint();
    flann::Index ind(mnist.ax, flann::KDTreeIndexParams(16));
    mostra(mnist.ax[0]);
    TimePoint t2 = timePoint();
    vector<int> indices(1);
    vector<float> dists(1);
    for (int l = 0; l < mnist.qx.rows; l++)
    {
        ind.knnSearch(mnist.qx.row(l), indices, dists, 1, flann::SearchParams(1024));
        mnist.qp(l) = mnist.ay(indices[0]);
    }
    TimePoint t3 = timePoint();
    printf("Erros=%10.2f%%\n", 100.0 * mnist.contaErros() / mnist.nq);
    printf("Tempo de treinamento: %f\n", timeSpan(t1, t2));
    printf("Tempo de predicao: %f\n", timeSpan(t2, t3));
} 
