#include <iostream>
#include <string>
#include <zmq.hpp>
#include <thread>

int main() {
    zmq::context_t context(1);
    zmq::socket_t client(context, ZMQ_REQ);
    client.connect("tcp://localhost:5555");  // Connect to the broker

    std::cout << "Client connected to the broker." << std::endl;

    // Prepare the message
    std::string topic = "mytopic";
    std::string payload = "Hello, MQTT!";

    // Send the message to the broker
    zmq::message_t identity;
    zmq::message_t message;

    identity.rebuild(topic.size());
    memcpy(identity.data(), topic.data(), topic.size());

    message.rebuild(payload.size());
    memcpy(message.data(), payload.data(), payload.size());

    client.send(identity, zmq::send_flags::sndmore);
    client.send(message, zmq::send_flags::none);

    // Wait for the response from the broker
    zmq::message_t response;
    client.recv(&response);

    std::string reply = std::string(static_cast<char*>(response.data()), response.size());
    std::cout << "Received reply from the broker: " << reply << std::endl;

    return 0;
}

