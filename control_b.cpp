#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
std::string topic_filter = "falso"; // Reemplazar con el filtro de topics deseado

void publisher_thread() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555");
   

    while (true) {
        std::string comando;
        std::cout << "Ingrese 'encendido' o 'apagado' para cambiar el estado del bombillo: ";
        std::getline(std::cin, comando);

        if (comando == "encendido" || comando == "apagado") {
            std::string message = topic_filter + " " + comando;
            zmq::message_t zmq_message(message.begin(), message.end());
            publisher.send(zmq_message);
        } else {
            std::cout << "Comando inválido. Ingrese 'encendido' o 'apagado'." << std::endl;
        }
    }
}

int main() {
    std::thread publisher(publisher_thread);
    publisher.join();

    return 0;
}


