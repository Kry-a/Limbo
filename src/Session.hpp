//
// Created by krasno on 2020-06-12.
//

#ifndef LIMBO_SESSION_HPP
#define LIMBO_SESSION_HPP


#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket);
    void start();

private:
    void doRead();
    void doWrite(std::size_t length);

    tcp::socket socket_;
    enum {max_length = 1024};
    char data_[max_length];

    int state;
};


#endif //LIMBO_SESSION_HPP
