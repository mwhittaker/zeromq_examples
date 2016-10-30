#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_PUSH);
  const std::string address = "tcp://*:5557";
  socket.bind(address);
  std::cout << "Source listening on '" << address << "'." << std::endl;

  std::cout << "> " << std::flush;
  std::string line;
  while (std::getline(std::cin, line)) {
    send_string(line, &socket);
    std::cout << "Sent '" << line << "'." << std::endl;
    std::cout << "> " << std::flush;
  }
}
