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

Se puedes ejecutar n cantidad de bombillos, se pueden tratar topics por separado.
Se cargaron los archivos publisher y subscriber con el topic luz
Se cargaron los archivos publisher2 y subscriber2 con el topic falso

El broker exitosamente puede tratarlos por separado
