#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_PUB);
  const std::string address = "tcp://*:5555";
  socket.bind(address);
  std::cout << "Server listenning on '" << address << "'." << std::endl;

  std::string line;
  std::cout << "> " << std::flush;
  while (std::getline(std::cin, line)) {
    send_string(line, &socket);
    std::cout << "Sent '" << line << "'." << std::endl;
    std::cout << "> " << std::flush;
  }
}
