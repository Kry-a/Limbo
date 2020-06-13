//
// Created by krasno on 2020-06-13.
//

#include "Buffer.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>

Buffer::Buffer(boost::asio::ip::tcp::socket *socket) {
    int length = utilsP::readVarInt(socket);
    size_ = length;
    socket->read_some(boost::asio::buffer(buf, length));
}

char Buffer::nextByte() {
    if (1 > size())
        throw std::out_of_range("Length bigger than the available bytes");
    char result = buf[currentIndex];
    currentIndex++;
    return result;
}

void Buffer::readBytes(char buffer[], int length) {
    if (length > size())
        throw std::out_of_range("Length bigger than the available bytes");

    std::cout << std::hex;
    for (int i = 0; i < size_; i++) {
        std::cout << std::setfill('0') << std::setw(2) << (int)buf[i] << " ";
    }
    std::cout << std::dec << std::endl;

    memcpy(buffer, buf + currentIndex, length);
    currentIndex += length;
}

int Buffer::size() {
    return size_ - currentIndex;
}

int Buffer::readVarInt() {
    int numRead = 0;
    int result = 0;
    char read;

    do {
        read = nextByte();
        int value = read & 0b01111111;
        result |= value << (7 * numRead);

        numRead++;
        if (numRead > 5) {
            throw std::runtime_error("VarInt is too big");
        }
    } while ((read & 0b10000000) != 0);

    return result;
}

long Buffer::readLongInt() {
    return 0;
}

std::string Buffer::readString() {
    std::cout << "Total: " << size_ << " | Remaining: " << size() << " | Current index: " << currentIndex << std::endl;
    int length = readVarInt();
    char data[length];
    data[0] = '\0';

    strncat(data, buf + currentIndex, length);
    currentIndex += length - 1;
    std::cout << "Total: " << size_ << " | Remaining: " << size() << " | Current index: " << currentIndex << std::endl;
    return std::string(data);
}

unsigned short Buffer::readUShort() {
    char data[2];
    readBytes(data, 2);
    std::cout << std::hex << (int)data[0] << (int)data[1] << std::dec << std::endl;
    std::cout << "Total: " << size_ << " | Remaining: " << size() << " | Current index: " << currentIndex << std::endl;
    return (unsigned short) ((data[0] << 8) | (data[1]));
}
