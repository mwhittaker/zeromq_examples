#include <chrono>
#include <iostream>
#include <thread>

#include <zmq.hpp>

#include "examples/zmq_util.h"

void worker(const int thread_id, zmq::context_t* const context) {
  zmq::socket_t socket(*context, ZMQ_REP);
  const std::string address = "inproc://workers";
  socket.connect(address);
  std::cout << "Worker connected to '" << address << "'." << std::endl;

  for (int i = 0; true; i++) {
    const std::string request = recv_string(&socket);
    std::cout << "Received '" << request << "'." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    const std::string reply =
        "Thread " + std::to_string(thread_id) + " message " + std::to_string(i);
    send_string(reply, &socket);
    std::cout << "Sent '" << reply << "'." << std::endl;
  }
}

int main() {
  zmq::context_t context(1);

  zmq::socket_t clients(context, ZMQ_ROUTER);
  const std::string clients_address = "tcp://*:5555";
  clients.bind(clients_address);
  std::cout << "Clients listening on '" << clients_address << "'." << std::endl;

  zmq::socket_t workers(context, ZMQ_DEALER);
  const std::string workers_address = "inproc://workers";
  workers.bind(workers_address);
  std::cout << "Workers listening on '" << workers_address << "'." << std::endl;

  const int num_threads = 4;
  std::vector<std::thread> worker_threads;
  for (int i = 0; i < num_threads; ++i) {
    worker_threads.push_back(std::thread(worker, i, &context));
  }

  zmq::proxy(clients, workers, nullptr /* capture */);
}
