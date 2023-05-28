#include <zmq.hpp>
#include <iostream>
#include <string>
#include <sstream>

std::string create_message(const std::string& topic, const std::string& content) {
    std::string message = topic;
    message += " ";
    message += content;
    return message;
}

int main() {
    zmq::context_t context(1);
    zmq::socket_t frontend(context, ZMQ_SUB);
    zmq::socket_t backend(context, ZMQ_PUB);

    frontend.bind("tcp://*:5555");
    backend.bind("tcp://*:5556");

    // Subscribe to all topics
    frontend.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    zmq::message_t message;
    while (true) {
        frontend.recv(&message);
        std::string received_message(static_cast<char*>(message.data()), message.size());
        std::istringstream iss(received_message);
        std::string topic;
        std::string content;
        std::getline(iss, topic, ' ');
        std::getline(iss, content);

        std::cout << "Recibido mensaje del topic: " << topic << " con el contenido: " << content << std::endl;

        zmq::message_t backend_message(received_message.data(), received_message.size());
        backend.send(backend_message);
    }

    return 0;
}



