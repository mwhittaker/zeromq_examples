#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  const std::string address = "tcp://localhost:5560";
  socket.connect(address);
  std::cout << "Server connected to '" << address << "'." << std::endl;

  for (int i = 0; true; i++) {
    const std::string request = recv_string(&socket);
    std::cout << "Received '" << request << "'." << std::endl;
    send_string(std::to_string(i), &socket);
    std::cout << "Sent '" << i << "'." << std::endl;
  }
}
