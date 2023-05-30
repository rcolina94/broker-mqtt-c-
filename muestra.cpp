#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void subscriber_thread() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "temperatura", 11); // Suscribirse al topic "temperatura"

    zmq::message_t update;
    while (true) {
        subscriber.recv(&update);
        std::string update_str(static_cast<char*>(update.data()), update.size());
        std::cout << "Recibido: " << update_str << std::endl;

        size_t pos = update_str.find(" ");
        if (pos != std::string::npos) {
            std::string temperatura_str = update_str.substr(pos + 1);
            double temperatura_celsius = std::stod(temperatura_str);
            std::cout << "Temperatura: " << temperatura_celsius << " grados Celsius" << std::endl;

            // Convertir Celsius a Fahrenheit
            double temperatura_fahrenheit = (1.8 * temperatura_celsius) + 32;
            std::cout << "Temperatura: " << temperatura_fahrenheit << " grados Fahrenheit" << std::endl;
        }
    }
}

int main() {
    std::thread subscriber(subscriber_thread);
    subscriber.join();

    return 0;
}



