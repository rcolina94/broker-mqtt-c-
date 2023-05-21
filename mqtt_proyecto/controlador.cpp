#include <iostream>
#include <zmq.hpp>

int main() {
    // Crear un contexto ZeroMQ y un socket de tipo PUSH
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    socket.connect("tcp://localhost:5556");

    std::cout << "Controlador conectado al broker." << std::endl;

    while (true) {
        std::string estado;
        std::cout << "Ingrese el estado del bombillo (Encender/Apagar): ";
        std::cin >> estado;

        // Enviar el mensaje al socket
        zmq::message_t message(estado.size());
        memcpy(message.data(), estado.data(), estado.size());
        socket.send(message, zmq::send_flags::none);

        std::cout << "Mensaje enviado al bombillo: " << estado << std::endl;
    }

    return 0;
}

