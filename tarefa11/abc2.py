#abc1.py - pos2021
import os; os.environ['TF_CPP_MIN_LOG_LEVEL']='3'
import tensorflow.keras as keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras import optimizers
import numpy as np
import sys


model = Sequential()
model.add(Dense(3, activation='sigmoid', input_dim=1))
model.add(Dense(3, activation='sigmoid'))
sgd=optimizers.SGD(learning_rate=10);
model.compile(optimizer=sgd, loss='mse', metrics=['accuracy'])

ax = np.matrix('4; 15; 65; 5; 18; 70 ',dtype="float32")
ax=ax/100
ay = np.matrix('0 1 0; 0 0 1; 1 0 0; 0 1 0; 0 0 1; 1 0 0',dtype="float32")
model.fit(ax, ay, epochs=500, batch_size=2, verbose=True)

qx = np.matrix('16; 3; 75 ',dtype="float32")
qx=qx/100
qy = np.matrix('0 0 1; 0 1 0; 1 0 0',dtype="float32")
teste = model.evaluate(qx,qy)
print("Custo e acuracidade de teste:",teste)

qp=model.predict(qx)
print("Classificacao de teste:\n",qp)
qp = qp.argmax(axis=-1)
print("Rotulo de saida:\n",qp)

model.summary()