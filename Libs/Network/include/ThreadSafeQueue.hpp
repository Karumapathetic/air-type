/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ThreadSafeQueue
*/

#pragma once

#include <mutex>
#include <deque>
#include <thread>
#include <condition_variable>

namespace Network {

    template <typename T>
    class ThreadSafeQueue
    {
        public:
            ThreadSafeQueue() = default;
            ThreadSafeQueue(const ThreadSafeQueue<T> &other) = delete;
            virtual ~ThreadSafeQueue() { clearQueue(); }

            const T &front()
            {
                std::scoped_lock lock(_mutex);
                return _queue.front();
            }

            const T &back()
            {
                std::scoped_lock lock(_mutex);
                return _queue.back();
            }

            T popFront()
            {
                std::scoped_lock lock(_mutex);
                auto item = std::move(_queue.front());
                _queue.pop_front();
                return item;
            }

            T popBack()
            {
                std::scoped_lock lock(_mutex);
                auto item = std::move(_queue.back());
                _queue.pop_back();
                return item;
            }

            void pushFront(const T &item)
            {
                std::scoped_lock lock(_mutex);
                auto movedItem = std::move(item);
                _queue.emplace_front(movedItem);
                std::unique_lock<std::mutex> blockingLock(_blockingMutex);
                _blockingCondVar.notify_one();
            }

            void pushBack(const T &item)
            {
                std::scoped_lock lock(_mutex);
                auto movedItem = std::move(item);
                _queue.emplace_back(movedItem);
                std::unique_lock<std::mutex> blockingLock(_blockingMutex);
                _blockingCondVar.notify_one();
            }

            bool isEmpty()
            {
                std::scoped_lock lock(_mutex);
                return _queue.empty();
            }

            size_t getSize()
            {
                std::scoped_lock lock(_mutex);
                return _queue.size();
            }

            void clearQueue()
            {
                std::scoped_lock lock(_mutex);
                _queue.clear();
            }

            void wait()
            {
                while (isEmpty())
                {
                    std::unique_lock<std::mutex> blockingLock(_blockingMutex);
                    _blockingCondVar.wait(blockingLock);
                }
            }

        protected:
            std::mutex _mutex;
            std::mutex _blockingMutex;
            std::deque<T> _queue;
            std::condition_variable _blockingCondVar;
    };

};