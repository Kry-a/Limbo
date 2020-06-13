//
// Created by krasno on 2020-06-12.
//

#include <iomanip>
#include "Session.hpp"
#include "Buffer.hpp"

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {

}

void Session::start() {
    doRead();
}

void Session::doRead() {
    auto self(shared_from_this());

    auto buf = Buffer(&socket_);

    int packetId = buf.readVarInt();
    std::cout << packetId << std::endl;

    if (packetId == 0) { // Handshake
        int protocolVersion = buf.readVarInt();
        std::cout << "Protocol: " << protocolVersion << std::endl;
        std::string serverAddress = buf.readString();
        std::cout << "Server Address: " << serverAddress << std::endl;
        unsigned short serverPort = buf.readUShort();
        std::cout << "Server Port: " << serverPort << std::endl;
        state = buf.readVarInt();
        std::cout << "Next state: " << state << std::endl;
    }

    /* socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](boost::system::error_code ec, std::size_t length) {
        const unsigned long sizeUwu = length / sizeof(char);

        if (!ec)
            doWrite(length);
    }); */
}

void Session::doWrite(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec)
            doRead();
    });
}
