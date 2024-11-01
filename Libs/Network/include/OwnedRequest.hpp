/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** OwnedRequest
*/

#pragma once

#include <memory>
#include "Requests.hpp"

namespace Network {

    /**
     * @brief Define the UDPConnection class
     * 
     * @tparam T The type of Request
     */
    template <typename T> class UDPConnection;

    /**
     * @brief The struct that contains a request and the client associated
     * 
     * @tparam T The type of Request
     */
    template <typename T> struct OwnedRequest
    {

        std::shared_ptr<UDPConnection<T>> remoteConnection = nullptr;
        Network::Request<T> request;

        /**
         * @brief Function to print a Owned Request
         * 
         * @param os OStream to send data in
         * @param request Request to print
         * @return std::ostream& THe updated OStream
         */
        friend std::ostream &operator<<(std::ostream &os, const OwnedRequest<T> &request)
        {
            os << request.request;
            return os;
        }

    };

};