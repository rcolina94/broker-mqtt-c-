#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
std::string topic_filter_a = "falso"; // Reemplazar con el filtro de topics deseado
std::string topic_filter_b = "luz";

void publisher_thread() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555");
   

    while (true) {
        std::string comando;
        std::cout << "Ingrese 'encendido' o 'apagado' para cambiar el estado del bombillo: ";
        std::getline(std::cin, comando);

        if (comando == "encendido" || comando == "apagado") {
            std::string message_a = topic_filter_a + " " + comando;
            std::string message_b = topic_filter_b + " " + comando;
            zmq::message_t zmq_message_a(message_a.begin(), message_a.end());
            zmq::message_t zmq_message_b(message_b.begin(), message_b.end());
            publisher.send(zmq_message_a);
            publisher.send(zmq_message_b);
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


