#include <iostream>
#include <zmq.hpp>

int main() {
    // Crear un contexto ZeroMQ y dos sockets, uno para el cliente y otro para el controlador
    zmq::context_t context(1);
    zmq::socket_t clientSocket(context, ZMQ_PUSH);
    zmq::socket_t controllerSocket(context, ZMQ_PULL);
    clientSocket.bind("tcp://*:5555");
    controllerSocket.bind("tcp://*:5556");

    std::cout << "Broker MQTT (ZeroMQ) iniciado." << std::endl;

    while (true) {
        // Verificar si se recibió un mensaje del cliente
        zmq::pollitem_t items[] = {
            { static_cast<void*>(controllerSocket), 0, ZMQ_POLLIN, 0 }
        };
        zmq::poll(items, 1, -1);

        if (items[0].revents & ZMQ_POLLIN) {
            zmq::message_t message;
            controllerSocket.recv(message, zmq::recv_flags::none);

            // Enviar el mensaje recibido desde el controlador al cliente
            clientSocket.send(message, zmq::send_flags::none);

            std::cout << "Mensaje enviado al cliente: " << std::string(static_cast<char*>(message.data()), message.size()) << std::endl;
        }
    }

    return 0;
}


