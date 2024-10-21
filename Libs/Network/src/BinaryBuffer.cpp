/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** BinaryBuffer
*/

#include <sstream>

#include "BinaryBuffer.hpp"

BinaryBuffer::BinaryBuffer()
{
}

BinaryBuffer::~BinaryBuffer()
{
}

std::vector<char> BinaryBuffer::getBinaryBuffer()
{
    return this->_binary_data;
}

std::string BinaryBuffer::getStringBuffer()
{
    return this->_string_data;
}

void BinaryBuffer::setBinaryBuffer(std::vector<char> buf)
{
    this->_binary_data = buf;
    binaryToString();
}

void BinaryBuffer::setStringBuffer(std::string buf)
{
    this->_string_data = buf;
    stringToBinary();
}

void BinaryBuffer::binaryToString()
{
}

void BinaryBuffer::stringToBinary()
{
    std::vector<std::string> parsedData = split(_string_data, " ");

    std::cout << "Binary data: ";
    for (auto i : parsedData) {
        std::cout << "'";
        if (isInt(i)) {
            std::vector<char> data = intToChar(std::stoi(i));
            _binary_data.insert(_binary_data.end(), data.begin(), data.end());
            for (char tmp : data)
                std::cout << tmp;
        } else if (isFloat(i)) {
            std::vector<char> data = floatToChar(std::stof(i));
            _binary_data.insert(_binary_data.end(), data.begin(), data.end());
            for (char tmp : data)
                std::cout << tmp;
        } else {
            std::vector<char> data;
            if (i == "player") {
                data.push_back('p');
            }
            if (i == "enemy") {
                data.push_back('e');
            }
            _binary_data.insert(_binary_data.end(), data.begin(), data.end());
            for (char tmp : data)
                std::cout << tmp;
        }
        std::cout << "' ";
    }
    std::cout << std::endl;
    std::cout << "Final binary data: ";
    for (char tmp : _binary_data)
        std::cout << "'" << (size_t)tmp << "' ";
    std::cout << std::endl;
}

std::vector<std::string> BinaryBuffer::split(std::string s, std::string delimiter)
{
    size_t pos_start = 0;
    size_t pos_end = 0;
    size_t delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    for (auto &str : res)
        str.resize(strlen(str.c_str()));
    return res;
}

std::vector<char> BinaryBuffer::floatToChar(float value)
{
    std::vector<char> result(4);
    std::memcpy(result.data(), &value, sizeof(float));
    return result;
}

float BinaryBuffer::charToFloat(std::vector<char> value)
{
    float result;
    std::memcpy(&result, value.data(), sizeof(float));
    return result;
}

std::vector<char> BinaryBuffer::intToChar(int value)
{
    std::vector<char> result(4);
    std::memcpy(result.data(), &value, sizeof(int));
    return result;
}

int BinaryBuffer::charToInt(std::vector<char> value)
{
    int result;
    std::memcpy(&result, value.data(), sizeof(int));
    return result;
}

bool BinaryBuffer::isInt(const std::string& data)
{
    std::istringstream iss(data);
    int value;
    char leftover;
    return (iss >> value) && !(iss >> leftover);
}

bool BinaryBuffer::isFloat(const std::string& data)
{
    std::istringstream iss(data);
    float value;
    char leftover;
    return (iss >> value) && !(iss >> leftover);
}