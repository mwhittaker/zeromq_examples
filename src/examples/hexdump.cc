#include "examples/hexdump.h"

#include <cctype>
#include <iomanip>
#include <ios>

namespace {

void print_hex(std::ostream& out, const unsigned char* const data,
               const std::size_t size) {
  for (std::size_t i = 0; i < size; ++i) {
    if (i != 0) {
      out << ' ';
    }
    out << std::setw(2) << std::setfill('0') << std::hex << +data[i];
  }
}

void print_ascii(std::ostream& out, const unsigned char* const data,
                 const std::size_t size) {
  for (std::size_t i = 0; i < size; ++i) {
    if (std::isprint(data[i])) {
      out << data[i];
    } else {
      out << ".";
    }
  }
}

}  // namespace

std::ostream& operator<<(std::ostream& out, const HexDump& hexdump) {
  const std::size_t row_width = 16;
  const std::size_t half_row_width = row_width / 2;

  if (hexdump.size_ == 0) {
    out << std::setw(8) << std::setfill('0') << 0
        << std::string(3 * row_width + 4, ' ') << "||";
    return out;
  }

  std::size_t i = 0;
  for (i = 0; i + row_width < hexdump.size_; i += row_width) {
    if (i != 0) {
      out << std::endl;
    }
    out << std::setw(8) << std::setfill('0') << i << "  ";

    print_hex(out, &hexdump.data_[i], half_row_width);
    out << "  ";
    print_hex(out, &hexdump.data_[i + half_row_width], half_row_width);

    out << "  |";
    print_ascii(out, &hexdump.data_[i], row_width);
    out << "|";
  }

  if (i < hexdump.size_) {
    const std::size_t num_chars_left = hexdump.size_ - i;
    const bool two_columns = num_chars_left > half_row_width;

    if (i != 0) {
      out << std::endl;
    }
    out << std::setw(8) << std::setfill('0') << i << "  ";

    print_hex(out, &hexdump.data_[i], std::min(half_row_width, num_chars_left));
    if (two_columns) {
      out << "  ";
      print_hex(out, &hexdump.data_[i + half_row_width],
                num_chars_left - half_row_width);
    }

    for (std::size_t j = 0; j < row_width - num_chars_left; ++j) {
      out << "   ";
    }
    if (!two_columns) {
      out << " ";
    }

    out << "  |";
    print_ascii(out, &hexdump.data_[i], num_chars_left);
    out << "|";
  }

  return out;
}
