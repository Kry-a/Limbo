//
// Created by krasno on 2020-06-10.
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "Server.hpp"

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context ioContext;

        Server s(ioContext, std::atoi("25565"));

        std::cout << "Started Limbo server!" << std::endl;

        ioContext.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
