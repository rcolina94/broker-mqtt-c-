#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void publisher_thread() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555");

    while (true) {
        std::string comando;
        std::cout << "Ingrese 'encendido' o 'apagado' para cambiar el estado del bombillo: ";
        std::getline(std::cin, comando);

        if (comando == "encendido" || comando == "apagado") {
            zmq::message_t message(comando.begin(), comando.end());
            publisher.send(message);
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



