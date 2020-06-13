//
// Created by krasno on 2020-06-12.
//

#ifndef LIMBO_SERVER_HPP
#define LIMBO_SERVER_HPP


#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, short port);

private:
    void doAccept();
    tcp::acceptor acceptor_;

};


#endif //LIMBO_SERVER_HPP
