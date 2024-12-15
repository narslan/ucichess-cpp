#pragma once
#include <coroutine>
#include <fmt/core.h>

namespace pgn2sqlite {
  struct ReturnObject {
    struct promise_type {
      ReturnObject get_return_object() {
        return {};
      }
      std::suspend_never initial_suspend() {
        fmt::print("co ---- initial suspend   --- co\n");
        return {};
      }
      std::suspend_never final_suspend() noexcept {
        fmt::print("co ---- final suspend   --- co\n");
        return {};
      }
      void unhandled_exception() { }
    };
  };

  struct Awaiter {
    std::coroutine_handle<>* hp_;
    constexpr bool await_ready() const noexcept {
      return false;
    }
    void await_suspend(std::coroutine_handle<> h) {
      *hp_ = h;
    }
    constexpr void await_resume() const noexcept { }
  };

  ReturnObject counter(std::coroutine_handle<>* continuation_out);
  void coprint();
} // namespace pgn2sqlite
