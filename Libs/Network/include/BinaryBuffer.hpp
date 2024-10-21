/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** BinaryBuffer
*/

#ifndef BINARYBUFFER_HPP_
#define BINARYBUFFER_HPP_

#include <iostream>
#include <array>
#include <vector>
#include <cstring>

class BinaryBuffer {
    public:
        BinaryBuffer();
        ~BinaryBuffer();

        std::vector<char> getBinaryBuffer();
        std::string getStringBuffer();

        void setBinaryBuffer(std::vector<char> buf);
        void setStringBuffer(std::string buf);

    protected:
    private:
        void binaryToString();
        void stringToBinary();
        std::vector<std::string> split(std::string s, std::string delimiter);
        std::vector<char> floatToChar(float value);
        float charToFloat(std::vector<char> value);
        std::vector<char> intToChar(int value);
        int charToInt(std::vector<char> value);

        bool isInt(const std::string& data);
        bool isFloat(const std::string& data);

        std::string _string_data;
        std::vector<char> _binary_data;
};

#endif /* !BINARYBUFFER_HPP_ */
