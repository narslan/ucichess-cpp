#include <coroutine>
#include <fmt/core.h>

namespace pgn2sqlite {

  struct promise;

  struct coroutine : std::coroutine_handle<promise> {
    using promise_type = ::pgn2sqlite::promise;
  };

  struct promise {
    coroutine get_return_object() {
      return {coroutine::from_promise(*this)};
    }
    std::suspend_always initial_suspend() noexcept {
      return {};
    }
    std::suspend_always final_suspend() noexcept {
      return {};
    }
    void return_void() { }
    void unhandled_exception() { }
  };

  struct S {
    int i;
    coroutine f() {
      fmt::print("{}\n", i);
      co_return;
    }
  };

  void good() {
    coroutine h = [](int i) -> coroutine // make i a coroutine parameter
    {
      fmt::print("{}\n", i);
      co_return;
    }(0);
    // lambda destroyed
    h.resume(); // no problem, i has been copied to the coroutine
        // frame as a by-value parameter
    h.destroy();
  }
} // namespace pgn2sqlite
