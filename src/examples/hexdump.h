#ifndef EXAMPLES_HEXDUMP_H_
#define EXAMPLES_HEXDUMP_H_

#include <cstddef>
#include <ostream>

// `std::cout << HexDump(data, size)` pretty prints data, an array of bytes of
// length `size`, in a `hexdump -C` style.
class HexDump {
 public:
  HexDump(const unsigned char* const data, const std::size_t size)
      : data_(data), size_(size) {}

  friend std::ostream& operator<<(std::ostream& out, const HexDump& hexdump);

 private:
  const unsigned char* const data_;
  const std::size_t size_;
};

#endif  // EXAMPLES_HEXDUMP_H_
