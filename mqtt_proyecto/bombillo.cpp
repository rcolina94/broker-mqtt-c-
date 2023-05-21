#include <iostream>
#include <zmq.hpp>

int main() {
    // Crear un contexto ZeroMQ y un socket de tipo PULL
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PULL);
    socket.connect("tcp://localhost:5555");

    std::cout << "Cliente (Bombillo) conectado al broker." << std::endl;

    while (true) {
        // Esperar y recibir un mensaje del socket
        zmq::message_t message;
        socket.recv(message, zmq::recv_flags::none);

        // Convertir el mensaje recibido a un string
        std::string msg(static_cast<char*>(message.data()), message.size());
        std::cout << "Mensaje recibido: " << msg << std::endl;

        // Cambiar el estado del bombillo según el mensaje recibido
        if (msg == "Encender") {
            std::cout << "El bombillo está encendido." << std::endl;
            // Aquí puedes agregar el código para encender el bombillo
        } else if (msg == "Apagar") {
            std::cout << "El bombillo está apagado." << std::endl;
            // Aquí puedes agregar el código para apagar el bombillo
        }
    }

    return 0;
}


