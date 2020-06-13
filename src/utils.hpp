//
// Created by krasno on 2020-06-13.
//

#ifndef LIMBO_UTILS_HPP
#define LIMBO_UTILS_HPP


#include <stdexcept>
#include <boost/asio.hpp>

namespace utilsP {

    struct Packet {
        int id;
        std::vector<char> data;
    };

    struct VarInt {
        int size;
        int data;
    };

    int readVarInt(boost::asio::ip::tcp::socket *socket) {
        int numRead = 0;
        int result = 0;
        char read[1];

        do {
            socket->read_some(boost::asio::buffer(read, 1));
            int value = read[0] & 0b01111111;
            result |= value << (7 * numRead);

            numRead++;
            if (numRead > 5) {
                throw std::runtime_error("VarInt is too big");
            }
        } while ((read[0] & 0b10000000) != 0);

        return result;
    }

    VarInt readVarInt(char buf[]) {
        VarInt result{};
        char read;

        do {
            read = buf[result.size];
            int value = read & 0b01111111;
            result.data |= value << (7 * result.size);

            result.size++;
            if (result.size > 5) {
                throw std::runtime_error("VarInt is too big");
            }
        } while ((read & 0b10000000) != 0);

        return result;
    }

    std::string readString(boost::asio::ip::tcp::socket *socket) {
        int length = readVarInt(socket);
        char buf[length];
        socket->read_some(boost::asio::buffer(buf, length));
        return std::string(buf);
    }

    unsigned short readUShort(boost::asio::ip::tcp::socket *socket) {
        char buf[2];
        socket->read_some(boost::asio::buffer(buf, 2));
        return (unsigned short) (buf[0] << 8 | buf[1]);
    }

    Packet readPacket(boost::asio::ip::tcp::socket *socket) {
        Packet packet_{};
        int length = readVarInt(socket);
        char buf[length];
        socket->read_some(boost::asio::buffer(buf, length));
        VarInt i = readVarInt(buf);
        packet_.id = i.data;
        for (int j = i.size; j < length; j++) {
            packet_.data.push_back(buf[j]);
        }

        return packet_;
    }
}

#endif //LIMBO_UTILS_HPP
