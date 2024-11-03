/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Requests
*/

#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <cstring>

namespace Network {

    /**
     * @brief The struct of a request header
     * 
     * @tparam T The type of the header
     * 
     * This struct contains the type of request, and the size of the body
     */
    template <typename T>
    struct RequestHeader
    {
        T id{};
        uint32_t size = 0;
    };

    /**
     * @brief The struct of a request
     * 
     * @tparam T The type of the header
     * 
     * This struct contains the header and the body of the request
     */
    template <typename T>
    struct Request
    {
        RequestHeader<T> header{};
        std::vector<uint8_t> body;

        /**
         * @brief Get the Size of the body
         * 
         * @return size_t The size of the body
         */
        size_t getSize() const
        {
            return body.size();
        }

        /**
         * @brief Function to print the type of request and the size of the body
         * 
         * @param os OStream to send the data
         * @param request The request to print
         * @return std::ostream& The updated OStream
         */
        friend std::ostream &operator<<(std::ostream &os, const Request<T> &request)
        {
            os << "Request ID: " << static_cast<int>(request.header.id) << ", Size: " << request.header.size;
            return os;
        }

        /**
         * @brief Add an other datatype to the body of the request
         * 
         * @tparam DataType The new DataType to store
         * @param request The Request to store in
         * @param data The Data to store in the request
         * @return Request<T>& The updated Request
         */
        template <typename DataType>
        friend Request<T> &operator<<(Request<T> &request, const DataType &data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

            size_t bodySize = request.body.size();
            request.body.resize(bodySize + sizeof(DataType));
            std::memcpy(request.body.data() + bodySize, &data, sizeof(DataType));
            request.header.size = request.getSize();
            return request;
        }

        /**
         * @brief Remove an other datatype of the body of the request
         * 
         * @tparam DataType The new DataType to extract
         * @param request The Request to extract from
         * @param data The Data to extract of the request
         * @return Request<T>& The update Request
         */
        template <typename DataType>
        friend Request<T> &operator>>(Request<T> &request, DataType &data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to pulled from vector");

            size_t bodySize = request.body.size() - sizeof(DataType);
            std::memcpy(&data, request.body.data() + bodySize, sizeof(DataType));
            request.body.resize(bodySize);
            request.header.size = request.getSize();
            return request;
        }

    };

};