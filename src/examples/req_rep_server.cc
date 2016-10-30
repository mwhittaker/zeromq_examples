#include <chrono>
#include <iostream>
#include <thread>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  const std::string address = "tcp://*:5555";
  socket.bind(address);
  std::cout << "Server listening on '" << address << "'." << std::endl;

  for (int i = 0; true; i++) {
    const std::string request = recv_string(&socket);
    std::cout << "Received '" << request << "'." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    send_string(std::to_string(i), &socket);
    std::cout << "Sent '" << i << "'." << std::endl;
  }
}
