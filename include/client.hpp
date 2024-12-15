#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <string>

struct Client {
    // Client to listen to a single tcp port
    Client(boost::asio::io_context& io_context, const std::string& host, uint16_t port, const std::string& name);

    // Start async read
    void start();

    // Get the last data received
    std::string get_last_data();

    // Get the name of the client
    const std::string & get_name() { return name_; };

private:
    // config
    boost::asio::ip::tcp::socket socket_;
    const std::string host_;
    const uint port_;
    const std::string name_;

    // data
    std::string last_data_;
    mutable std::mutex data_mutex_;

    // methods
    void do_read();
};

#endif // CLIENT_HPP
