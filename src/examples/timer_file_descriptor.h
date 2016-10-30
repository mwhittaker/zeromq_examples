#ifndef EXAMPLES_TIMER_FILE_DESCRIPTOR_H_
#define EXAMPLES_TIMER_FILE_DESCRIPTOR_H_

// http://man7.org/linux/man-pages/man2/timerfd_create.2.html
// https://austinmarton.wordpress.com/2012/07/13/linux-timers-using-file-descriptors/

#include <chrono>
#include <cstdint>

class TimerFileDescriptor {
 public:
  TimerFileDescriptor(std::chrono::nanoseconds value,
                      std::chrono::nanoseconds interval);
  ~TimerFileDescriptor();
  TimerFileDescriptor(const TimerFileDescriptor& timer) = delete;
  TimerFileDescriptor(TimerFileDescriptor&& timer);
  TimerFileDescriptor& operator=(const TimerFileDescriptor& timer) = delete;
  TimerFileDescriptor& operator=(TimerFileDescriptor&& timer);

  int timerfd() { return timerfd_; }
  const std::chrono::nanoseconds& value() { return value_; }
  const std::chrono::nanoseconds& interval() { return interval_; }
  uint64_t Read();

 private:
  std::chrono::nanoseconds value_;
  std::chrono::nanoseconds interval_;
  int timerfd_;
};

#endif  // EXAMPLES_TIMER_FILE_DESCRIPTOR_H_
