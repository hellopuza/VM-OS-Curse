#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace puza {

class ThreadPool final
{
public:
    using Task = std::function<void()>;

    explicit ThreadPool(size_t threads_num);
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool &) = delete;
    ThreadPool& operator=(ThreadPool&&) noexcept = delete;
    ~ThreadPool();

    template<typename Func, typename... Args>
    void create_task(Func&& func, Args&&... args);

 private:
    std::vector<std::thread> workers_;
    std::queue<Task> tasks_;

    std::mutex queue_mutex_;
    std::condition_variable condition_;
    bool stop_;
};

template<typename Func, typename... Args>
void ThreadPool::create_task(Func&& func, Args&&... args)
{
    auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        tasks_.emplace(std::move(task));
    }

    condition_.notify_one();
}

} // namespace puza

#endif // THREADPOOL_H