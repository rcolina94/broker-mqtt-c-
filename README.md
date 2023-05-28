# broker-mqtt-c-
Proyecto realizado para la materia sistemas distribuidos


Para compilar los codigos se utiliza los siguientes comandos en terminales independientes

g++ -o broker broker.cpp -lzmq
g++ -o publisher publisher.cpp -lzmq
g++ -o subscribersubscriber.cpp -lzmq

y se ejecutan

./broker
./publisher
./suscriber

Se puedes ejecutar n cantidad de bombillos, y todos ellos se apagaran o encenderan segun la instruccion del control
