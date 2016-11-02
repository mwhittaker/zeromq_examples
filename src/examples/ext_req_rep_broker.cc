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

  std::vector<zmq::pollitem_t> poll_items = {
      {frontend, 0, ZMQ_POLLIN, 0}, {backend, 0, ZMQ_POLLIN, 0},
  };

  while (true) {
    poll(-1, &poll_items);

    if (poll_items[0].revents & ZMQ_POLLIN) {
      int more = true;
      std::size_t more_size = sizeof(more);
      std::cout << std::string(80, '=') << std::endl;
      std::cout << "frontend --> backend:" << std::endl;
      while (more) {
        zmq::message_t msg;
        frontend.recv(&msg);
        std::cout << msg << std::endl;
        frontend.getsockopt(ZMQ_RCVMORE, static_cast<void*>(&more), &more_size);
        backend.send(msg, more ? ZMQ_SNDMORE : 0);
      }
      std::cout << std::endl;
    }

    if (poll_items[1].revents & ZMQ_POLLIN) {
      int more = true;
      std::size_t more_size = sizeof(more);
      std::cout << "backend --> frontend" << std::endl;
      while (more) {
        zmq::message_t msg;
        backend.recv(&msg);
        std::cout << msg << std::endl;
        backend.getsockopt(ZMQ_RCVMORE, static_cast<void*>(&more), &more_size);
        frontend.send(msg, more ? ZMQ_SNDMORE : 0);
      }
      std::cout << std::string(80, '=') << std::endl;
    }
  }
}
