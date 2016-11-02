#include "examples/zmq_util.h"

#include <iomanip>
#include <ios>

#include "examples/hexdump.h"

std::ostream& operator<<(std::ostream& out, const zmq::message_t& msg) {
  out << HexDump(reinterpret_cast<const unsigned char*>(msg.data()),
                 msg.size());
  return out;
}

std::string message_to_string(const zmq::message_t& message) {
  return std::string(static_cast<const char*>(message.data()), message.size());
}

void send_string(const std::string& s, zmq::socket_t* socket) {
  zmq::message_t message(s.size());
  memcpy(message.data(), s.c_str(), s.size());
  socket->send(message);
}

std::string recv_string(zmq::socket_t* socket) {
  zmq::message_t message;
  socket->recv(&message);
  return message_to_string(message);
}

int poll(long timeout, std::vector<zmq::pollitem_t>* items) {
  return zmq::poll(items->data(), items->size(), timeout);
}
