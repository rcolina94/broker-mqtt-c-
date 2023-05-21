#include <iostream>
#include <string>
#include <zmq.hpp>
#include <thread>

int main() {
    zmq::context_t context(1);
    zmq::socket_t broker(context, ZMQ_ROUTER);
    broker.bind("tcp://*:5555");  // Bind to a specific port

    std::cout << "Broker started. Listening on port 5555..." << std::endl;

    while (true) {
        zmq::message_t identity;
        zmq::message_t message;

        broker.recv(&identity);
        broker.recv(&message);

        // Process the message
        std::string client = std::string(static_cast<char*>(identity.data()), identity.size());
        std::string content = std::string(static_cast<char*>(message.data()), message.size());

        std::cout << "Received message from client: " << client << std::endl;
        std::cout << "Message content: " << content << std::endl;

        // Forward the message to the destination client (based on topic)

        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Send the response back to the client
        broker.send(identity, zmq::send_flags::sndmore);
        broker.send(message, zmq::send_flags::none);
    }

    return 0;
}

