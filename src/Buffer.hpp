//
// Created by krasno on 2020-06-13.
//

#ifndef LIMBO_BUFFER_HPP
#define LIMBO_BUFFER_HPP


#include <boost/asio.hpp>

class Buffer {
public:
    explicit Buffer(boost::asio::ip::tcp::socket *socket);
    char nextByte();
    void readBytes(char buffer[], int length);
    int size();

    int readVarInt();
    long readLongInt();
    std::string readString();
    unsigned short readUShort();

private:
    int currentIndex = 0;
    int size_;
    char buf[];
};


#endif //LIMBO_BUFFER_HPP
