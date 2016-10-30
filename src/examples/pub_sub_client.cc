#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_SUB);
  socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  const std::string address = "tcp://localhost:5555";
  socket.connect(address);
  std::cout << "Connected to '" << address << "'." << std::endl;

  while (true) {
    std::string msg = recv_string(&socket);
    std::cout << "Received '" << msg << "'." << std::endl;
  }
}
