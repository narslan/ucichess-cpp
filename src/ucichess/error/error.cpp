/*
	Error-checking support functions
	AUP2, Sec. 1.04.2

	Copyright 2003 by Marc J. Rochkind. All rights reserved.
	May be copied only for purposes and under conditions described
	on the Web page www.basepath.com/aup/copyright.htm.

	The Example Files are provided "as is," without any warranty;
	without even the implied warranty of merchantability or fitness
	for a particular purpose. The author and his publisher are not
	responsible for any damages, direct or incidental, resulting
	from the use or non-use of these Example Files.

	The Example Files may contain defects, and some contain deliberate
	coding mistakes that were included for educational reasons.
	You are responsible for determining if and how the Example Files
	are to be used.

*/
#include "error.hpp"
#include <netdb.h>

using namespace ux;

/**
	Stream operator to output Error.
*/
std::ostream& ux::operator<<(std::ostream& s, const Error& e) {
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
  case EC_PIPE:
    return "pipe call is invalid";
  case EC_CLOSE:
    return "close call is invalid";
  default:
    return gai_strerror(get_code());
  }
}
