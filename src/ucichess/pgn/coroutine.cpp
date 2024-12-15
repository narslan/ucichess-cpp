#include "coroutine.hpp"
#include <fstream>

const std::string random_hex_id() {

  unsigned long long int random_value = 0; //Declare value to store data into
  size_t size = sizeof(random_value); //Declare size of data
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary); //Open stream
  if(urandom) //Check if stream is open
  {
    urandom.read(reinterpret_cast<char*>(&random_value), size); //Read from urandom
    if(urandom) //Check if stream is ok, read succeeded
    {
      return fmt::format("{:x}\n", random_value);
    }
    else //Read failed
    {
      return fmt::format("err: failed to read from /dev/urandom\n");
    }
    urandom.close(); //close stream
  }
  else //Open failed
  {
    return fmt::format("err: failed to open /dev/urandom\n");
  }
  return 0;
}

namespace pgn2sqlite {

  ReturnObject counter(std::coroutine_handle<>* continuation_out) {
    Awaiter a{continuation_out};
    for(unsigned i = 0;; ++i) {
      co_await a;
      fmt::print("{} {}\n", i, random_hex_id());
    }
  }

  void coprint() {

    std::coroutine_handle<> h;
    counter(&h);
    for(int i = 0; i < 5; ++i) {
      fmt::print("in main \n");
      h();
    }
    h.destroy();
  }
} // namespace pgn2sqlite
