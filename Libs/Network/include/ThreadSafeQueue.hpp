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

    /**
     * @brief Thread-safe Queue class
     * 
     * @tparam T Type of data stored in the queue
     */
    template <typename T>
    class ThreadSafeQueue
    {
        public:
            /**
             * @brief Construct a new Thread Safe Queue object
             * 
             * Constructor of the class
             */
            ThreadSafeQueue() = default;

            /**
             * @brief Construct a new Thread Safe Queue object
             * 
             * @param other The other queue
             * 
             * Refuse the creation of a new TSQueue with another
             */
            ThreadSafeQueue(const ThreadSafeQueue<T> &other) = delete;

            /**
             * @brief Destroy the Thread Safe Queue object
             * 
             * Destructor of the class
             */
            virtual ~ThreadSafeQueue() { clearQueue(); }

            /**
             * @brief Return the front element of the queue
             * 
             * @return const T& Front element
             */
            const T &front()
            {
                std::scoped_lock lock(_mutex);
                return _queue.front();
            }

            /**
             * @brief Return the back element of the queue
             * 
             * @return const T& Back element
             */
            const T &back()
            {
                std::scoped_lock lock(_mutex);
                return _queue.back();
            }

            /**
             * @brief Delete the front element from the queue
             * 
             * @return T The deleted element
             */
            T popFront()
            {
                std::scoped_lock lock(_mutex);
                auto item = std::move(_queue.front());
                _queue.pop_front();
                return item;
            }

            /**
             * @brief Delete the back element from the queue
             * 
             * @return T The deleted element
             */
            T popBack()
            {
                std::scoped_lock lock(_mutex);
                auto item = std::move(_queue.back());
                _queue.pop_back();
                return item;
            }

            /**
             * @brief Add an element at front of the queue
             * 
             * @param item Element to add
             */
            void pushFront(const T &item)
            {
                std::scoped_lock lock(_mutex);
                auto movedItem = std::move(item);
                _queue.emplace_front(movedItem);
                std::unique_lock<std::mutex> blockingLock(_blockingMutex);
                _blockingCondVar.notify_one();
            }

            /**
             * @brief Add an element at the back of the queue
             * 
             * @param item Element to add
             */
            void pushBack(const T &item)
            {
                std::scoped_lock lock(_mutex);
                auto movedItem = std::move(item);
                _queue.emplace_back(movedItem);
                std::unique_lock<std::mutex> blockingLock(_blockingMutex);
                _blockingCondVar.notify_one();
            }

            /**
             * @brief Check if the queue is empty or not
             * 
             * @return true If the queue is empty
             * @return false If the queue is not empty
             */
            bool isEmpty()
            {
                std::scoped_lock lock(_mutex);
                return _queue.empty();
            }

            /**
             * @brief Get the Size object
             * 
             * @return size_t The size of the queue
             */
            size_t getSize()
            {
                std::scoped_lock lock(_mutex);
                return _queue.size();
            }

            /**
             * @brief Clear the queue
             * 
             */
            void clearQueue()
            {
                std::scoped_lock lock(_mutex);
                _queue.clear();
            }

            /**
             * @brief Wait for the queue to be usable
             * 
             */
            void wait()
            {
                while (isEmpty())
                {
                    std::unique_lock<std::mutex> blockingLock(_blockingMutex);
                    _blockingCondVar.wait(blockingLock);
                }
            }

        protected:
            /**
             * @brief Variable that store the mutex of the queue
             * 
             */
            std::mutex _mutex;

            /**
             * @brief Variable that store the blocking mutex of the queu
             * 
             */
            std::mutex _blockingMutex;

            /**
             * @brief Variable that store the queue
             * 
             */
            std::deque<T> _queue;

            /**
             * @brief Variable that store the conditional variable
             * 
             */
            std::condition_variable _blockingCondVar;
    };

};