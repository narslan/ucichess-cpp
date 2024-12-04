#include <unifex/scheduler_concepts.hpp>
#include <unifex/static_thread_pool.hpp>
#include <unifex/sync_wait.hpp>
#include <unifex/then.hpp>
#include <unifex/when_all.hpp>

#include <atomic>

using namespace unifex;

template <typename Scheduler, typename F>
auto run_on(Scheduler&& s, F&& func) {
  return then(schedule((Scheduler&&)s), (F&&)func);
}

int main() {
  static_thread_pool tpContext;
  auto tp = tpContext.get_scheduler();
  std::atomic<int> x = 0;

  sync_wait(when_all(run_on(tp,
                            [&] {
                              ++x;
                              std::printf("task 1\n");
                            }),
                     run_on(tp,
                            [&] {
                              ++x;
                              std::printf("task 2\n");
                            }),
                     run_on(tp, [&] {
                       ++x;
                       std::printf("task 3\n");
                     })));

  UNIFEX_ASSERT(x == 3);

  return 0;
}
