//
// Created by krasno on 2020-06-12.
//

#include <iomanip>
#include "Session.hpp"

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {

}

void Session::start() {
    doRead();
}

void Session::doRead() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](boost::system::error_code ec, std::size_t length) {
        const unsigned long sizeUwu = length / sizeof(char);

        if (!ec)
            doWrite(length);
    });
}

void Session::doWrite(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec)
            doRead();
    });
}
