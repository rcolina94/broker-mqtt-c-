# broker-mqtt-c-
Proyecto realizado para la materia sistemas distribuidos


Para compilar los codigos se utiliza los siguientes comandos en terminales independientes

g++ -o broker broker.cpp -lzmq
g++ -o control control.cpp -lzmq
g++ -o bombillo bombillo.cpp -lzmq

y se ejecutan

./broker
./control
./bombillo

Se puedes ejecutar n cantidad de bombillos, y todos ellos se apagaran o encenderan segun la instruccion del control
