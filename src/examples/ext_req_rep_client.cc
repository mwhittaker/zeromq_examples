#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REQ);
  const std::string address = "tcp://localhost:5559";
  socket.connect(address);
  std::cout << "Client connected to '" << address << "'." << std::endl;

  std::string line;
  std::cout << "> " << std::flush;
  while (std::getline(std::cin, line)) {
    send_string(line, &socket);
    std::cout << "Sent '" << line << "'." << std::endl;
    std::string reply = recv_string(&socket);
    std::cout << "Received '" << reply << "'." << std::endl;
    std::cout << "> " << std::flush;
  }
}
