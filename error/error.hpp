#pragma once
#include <exception>
#include <iostream>

typedef enum {
  EC_ERRNO = 0,
  EC_EAI = 1,
  EC_GETDATE = 2,
  EC_NONE = 3,
  EC_RESOURCE = 4,
  EC_FCNTL = 5
} EC_ERRTYPE;

#define EC_CAUGHT(e) ec_push(__func__, __FILE__, __LINE__, "EC_CAUGHT", e.get_code());

#define EC_EXIT(e)                                                                                 \
  {                                                                                                \
    fmt::print("{} {} {}", __func__, __FILE__, __LINE__);                                          \
    ::exit(EXIT_FAILURE);                                                                          \
  }

#define EC__EXIT(e)                                                                                \
  {                                                                                                \
    fmt::print("{} {} {}", __func__, __FILE__, __LINE__);                                          \
    EC_FLUSH("EC__EXIT")                                                                           \
    ::_exit(EXIT_FAILURE);                                                                         \
  }

#define EC_CATCH(s)                                                                                \
  try {                                                                                            \
    s;                                                                                             \
  }                                                                                                \
  catch(chessbird::Error e) {                                                                      \
    EC_EXIT(e)                                                                                     \
  }

namespace chessbird {

  class Error : public std::exception {
    protected:
    EC_ERRTYPE e_type;
    int e_code;
    char str[50];

    public:
    Error(int c = 0, EC_ERRTYPE t = EC_ERRNO)
        : e_type(t)
        , e_code(c) { }
    void set(int c, EC_ERRTYPE t = EC_ERRNO) {
      e_type = t;
      e_code = c;
    }
    EC_ERRTYPE get_type(void) const {
      return e_type;
    }
    int get_code(void) const {
      return e_code;
    }
    operator int() const {
      return e_code;
    }
    operator const std::string() const {
      return what();
    }
    virtual const char* what() const throw();
  };

  //@{
  /** \name ostream Operators
Operator to display Error.
*/
  std::ostream& operator<<(std::ostream& s, const Error& e);
  //@}

} // namespace chessbird
