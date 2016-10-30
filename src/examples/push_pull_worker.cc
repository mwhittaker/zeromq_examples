#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);

  zmq::socket_t puller(context, ZMQ_PULL);
  const std::string puller_address = "tcp://localhost:5557";
  puller.connect(puller_address);
  std::cout << "Puller connected to '" << puller_address << "'." << std::endl;

  zmq::socket_t pusher(context, ZMQ_PUSH);
  const std::string pusher_address = "tcp://localhost:5558";
  pusher.connect(pusher_address);
  std::cout << "Puller connected to '" << pusher_address << "'." << std::endl;

  while (true) {
    const std::string msg = recv_string(&puller);
    std::cout << "Received '" << msg << "'." << std::endl;
    send_string(msg, &pusher);
    std::cout << "Sent '" << msg << "'." << std::endl;
  }
}
