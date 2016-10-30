#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_PULL);
  const std::string address = "tcp://*:5558";
  socket.bind(address);
  std::cout << "Sink listening on '" << address << "'." << std::endl;

  while (true) {
    const std::string msg = recv_string(&socket);
    std::cout << "Received '" << msg << "'." << std::endl;
  }
}
