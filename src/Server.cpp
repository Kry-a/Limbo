//
// Created by krasno on 2020-06-12.
//

#include "Server.hpp"
#include "Session.hpp"

Server::Server(boost::asio::io_context &io_context, short port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    doAccept();
}

void Server::doAccept() {
    acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                std::cout << "Connected " << socket.remote_endpoint().address() << ":" << socket.remote_endpoint().port() << std::endl;

                if (!ec)
                    std::make_shared<Session>(std::move(socket))->start();

                doAccept();
            });
}
