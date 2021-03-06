#include <iostream>

#include <zmq.hpp>

#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);
  zmq::socket_t router(context, ZMQ_ROUTER);
  const std::string address = "tcp://*:5555";
  router.bind(address);
  std::cout << "Router bound to '" << address << "'." << std::endl;

  EnvelopedMessage a;
  EnvelopedMessage b;
  for (int i = 0; true; ++i) {
    if (i % 2 == 0) {
      a = recv_envoloped_msg(&router);
      std::cout << "EnvelopedMessage " << i << std::endl << a << std::endl;
    } else {
      b = recv_envoloped_msg(&router);
      std::cout << "EnvelopedMessage " << i << std::endl << b << std::endl;

      std::swap(a.connection_ids, b.connection_ids);
      send_envoloped_msg(std::move(a), &router);
      send_envoloped_msg(std::move(b), &router);
    }
  }
}
