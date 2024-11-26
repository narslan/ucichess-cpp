#include "error.hpp"
#include <fmt/core.h>
#include <netdb.h>

using namespace chessbird;

/**
	Stream operator to output Error.
*/
std::ostream& chessbird::operator<<(std::ostream& s, const Error& e) {
  s << "[ERROR: " << e.what() << "]";
  return s;
}

/**
	Required what function for subclasses of exception.
*/
const char* Error::what() const throw() {
  switch(get_type()) {
  case EC_EAI:
    return gai_strerror(get_code());
  case EC_RESOURCE:
    return "who is invalid";
  default:
    return gai_strerror(get_code());
  }
}
