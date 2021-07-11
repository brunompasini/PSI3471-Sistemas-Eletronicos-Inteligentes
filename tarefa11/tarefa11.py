import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import tensorflow.keras as keras
from keras.datasets import fashion_mnist
from keras.models import Sequential
from keras.layers import Dense, Flatten
from keras.utils import to_categorical
import numpy as np
import sys
import matplotlib.pyplot as plt

# carregando dataset
(AX, AY), (QX, QY) = fashion_mnist.load_data()

AX = 255-AX
QX = 255-QX
AX = (AX.astype('float32')/255.0) - 0.5
QX = (QX.astype('float32')/255.0) - 0.5

nl, nc = AX.shape[1], AX.shape[2]

# categoricos
classes = ["Camiseta", "Calça", "Pulôver", "Vestido", "Casaco", "Sandália", "Camiseta", "Tênis", "Bolsa", "Botins"]
nclasses = len(classes) # 10 nesse caso

AY2 = to_categorical(AY, nclasses)
QY2 = to_categorical(QY, nclasses)

model = Sequential()
model.add(  Flatten(input_shape=(nl,nc)) )
model.add(  Dense(512, activation='relu') )
model.add(  Dense(128, activation='relu') )
model.add(  Dense(nclasses, activation='softmax') )

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

print(model.summary())

history = model.fit(AX, AY2, batch_size=100, epochs=30, verbose=1)
#plt.plot(history.history['accuracy'])
#plt.show()

score = model.evaluate(QX, QY2, verbose=False)
print('Test loss: %.4f'%(score[0]))
print('Test accuracy: %.2f %%'%(100*score[1]))
print('Test error: %.2f %%'%(100*(1-score[1])))

qx = QX[0:21]
QP = model.predict(qx)
 
f = plt.figure()
for i in range(20):
    f.add_subplot(4,5,i+1)
    plt.imshow(QX[i], cmap='gray')
    plt.axis('off')
    plt.text(0,-3,classes[QY[i]], color='b')
    plt.text(0,2,classes[QP[i].argmax(axis=-1)], color='r')
plt.savefig("predicoes.png")