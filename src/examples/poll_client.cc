#include <iostream>
#include <vector>

#include <zmq.hpp>

#include "examples/timer_file_descriptor.h"
#include "examples/zmq_util.h"

int main() {
  zmq::context_t context(1);

  zmq::socket_t subscriber(context, ZMQ_SUB);
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  const std::string subscriber_address = "tcp://localhost:5556";
  subscriber.connect(subscriber_address);
  std::cout << "Connected to '" << subscriber_address << "'." << std::endl;

  zmq::socket_t puller(context, ZMQ_PULL);
  const std::string puller_address = "tcp://localhost:5557";
  puller.connect(puller_address);
  std::cout << "Connected to '" << puller_address << "'." << std::endl;

  std::chrono::nanoseconds zero_seconds(0);
  std::chrono::nanoseconds one_second(std::chrono::seconds(1));
  TimerFileDescriptor after_a_second(one_second, zero_seconds);
  TimerFileDescriptor every_second(one_second, one_second);

  std::vector<zmq::pollitem_t> poll_items = {
      {subscriber, 0, ZMQ_POLLIN, 0},
      {puller, 0, ZMQ_POLLIN, 0},
      {nullptr, after_a_second.timerfd(), ZMQ_POLLIN, 0},
      {nullptr, every_second.timerfd(), ZMQ_POLLIN, 0},
  };

  while (true) {
    poll(-1, &poll_items);

    if (poll_items[0].revents & ZMQ_POLLIN) {
      std::string msg = recv_string(&subscriber);
      std::cout << "Subscriber received '" << msg << "'." << std::endl;
    }

    if (poll_items[1].revents & ZMQ_POLLIN) {
      std::string msg = recv_string(&puller);
      std::cout << "Puller received '" << msg << "'." << std::endl;
    }

    if (poll_items[2].revents & ZMQ_POLLIN) {
      std::cout << "After a second fired " << after_a_second.Read()
                << " time(s). " << std::endl;
    }

    if (poll_items[3].revents & ZMQ_POLLIN) {
      std::cout << "Every second fired " << every_second.Read() << " time(s)."
                << std::endl;
    }
  }
}
