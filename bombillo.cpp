#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

bool bombillo_encendido = false;

void subscriber_thread() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555");

    // Enviar el estado inicial del bombillo al broker
    std::string estado_inicial = bombillo_encendido ? "Bombillo encendido" : "Bombillo apagado";
    zmq::message_t estado_inicial_msg(estado_inicial.begin(), estado_inicial.end());
    publisher.send(estado_inicial_msg);

    while (true) {
        zmq::message_t update;
        subscriber.recv(&update);
        std::string update_str(static_cast<char*>(update.data()), update.size());
        std::cout << "Recibido: " << update_str << std::endl;

         if (update_str == "encendido" || update_str == "apagado") {
            bombillo_encendido = (update_str == "encendido");
            std::string nuevo_estado = bombillo_encendido ? "Bombillo encendido" : "Bombillo apagado";
            std::cout << "Nuevo estado: " << nuevo_estado << std::endl;

            // Enviar el nuevo estado al broker
            zmq::message_t nuevo_estado_msg(nuevo_estado.begin(), nuevo_estado.end());
            publisher.send(nuevo_estado_msg);
        }
    }
}

int main() {
    std::thread subscriber(subscriber_thread);
    subscriber.join();

    return 0;
}




