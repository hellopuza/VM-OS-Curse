#include "ThreadPool.h"

namespace puza {

ThreadPool::ThreadPool(size_t threads_num) : stop_(false)
{
    for (size_t i = 0; i < threads_num; i++)
    {
        workers_.emplace_back([this] {
            while (true)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex_);
                    this->continuation_.wait(lock, [this]{ return this->stop_ || !this->tasks_.empty(); });

                    if (this->stop_ && this->tasks_.empty())
                    {
                        return;
                    }

                    task = std::move(this->tasks_.front());
                    this->tasks_.pop();
                }

                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    join();
}

void ThreadPool::join()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }

    continuation_.notify_all();
    for (auto &worker: workers_)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}

} // namespace puza