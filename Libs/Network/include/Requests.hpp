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

    template <typename T>
    struct RequestHeader
    {
        T id{};
        uint32_t size = 0;
    };

    template <typename T>
    struct Request
    {
        RequestHeader<T> header{};
        std::vector<uint8_t> body;

        size_t getSize() const
        {
            return body.size();
        }

        friend std::ostream &operator<<(std::ostream &os, const Request<T> &request)
        {
            os << "Request ID: " << static_cast<int>(request.header.id) << ", Size: " << request.header.size;
            return os;
        }

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