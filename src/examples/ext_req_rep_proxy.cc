#include <iostream>
#include <vector>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);

  zmq::socket_t frontend(context, ZMQ_ROUTER);
  std::string frontend_address = "tcp://*:5559";
  frontend.bind(frontend_address);
  std::cout << "Frontend listening on '" << frontend_address << "'."
            << std::endl;

  zmq::socket_t backend(context, ZMQ_DEALER);
  std::string backend_address = "tcp://*:5560";
  backend.bind(backend_address);
  std::cout << "Backend listening on '" << backend_address << "'." << std::endl;

  zmq::proxy(frontend, backend, nullptr /* capture */);
}
