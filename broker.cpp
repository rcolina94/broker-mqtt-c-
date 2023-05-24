#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>

void broker_thread() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.bind("tcp://*:5555");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5556");

    zmq::proxy(subscriber, publisher, nullptr);
}

int main() {
    std::thread broker(broker_thread);
    broker.join();

    return 0;
}


