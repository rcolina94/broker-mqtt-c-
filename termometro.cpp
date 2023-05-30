#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <chrono>

std::string topic_filter = "temperatura"; // Cambiar el filtro de topics

void publisher_thread() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555");

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(23.0, 25.0);

    while (true) {
        // Generar un número aleatorio entre 23 y 25
        double temperatura = dis(gen);
        std::string message = topic_filter + " " + std::to_string(temperatura);
        zmq::message_t zmq_message(message.begin(), message.end());
        publisher.send(zmq_message);

        // Esperar 1 segundo antes de enviar el siguiente mensaje
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::thread publisher(publisher_thread);
    publisher.join();

    return 0;
}

