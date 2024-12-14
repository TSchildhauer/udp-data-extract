#ifndef CLIENT1_HPP
#define CLIENT1_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>

struct Client {
    Client(const std::string& host, const std::vector<uint> & ports);

    // Spin function to handle receiving and printing data
    void spin();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    std::string host_;
    std::vector<uint> ports_;
};

#endif // CLIENT1_HPP
