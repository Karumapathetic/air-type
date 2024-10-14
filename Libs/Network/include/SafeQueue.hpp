/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** SafeQueue
*/

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue {
    public:
        void push(T item)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _queue.push(item);
            _condVar.notify_one();
        }

        T pop(void)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _condVar.wait(lock, [this]() { return !_queue.empty(); });

            T item = _queue.front();
            _queue.pop();
            return item;
        }

        int size(void)
        {
            std::unique_lock<std::mutex> lock(_mutex);

            return _queue.size();
        }

    private:
        std::queue<T> _queue;
        std::mutex _mutex;
        std::condition_variable _condVar;
};
