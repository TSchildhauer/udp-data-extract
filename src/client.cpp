#include "client.hpp"

#include <boost/asio.hpp>
// #include <boost/json.hpp>
// #include <iostream>
#include <string>
#include <vector>
// #include <memory>
#include <mutex>
// #include <chrono>
// #include <thread>

using boost::asio::ip::tcp;

Client::Client(boost::asio::io_context& io_context, const std::string& host, uint16_t port, const std::string& name)
    : socket_(io_context)
    , host_(host)
    , port_(port)
    , name_(name)
{
    // Resolve and connect to the server. Throw on error.
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, std::to_string(port));
    boost::asio::connect(socket_, endpoints);
}

void Client::start()
{
    do_read();
}

std::string Client::get_last_data()
{
    std::lock_guard<std::mutex> lock(data_mutex_);
    std::string ret = "";//"--";
    if (last_data_.size()) {
        ret = last_data_;
        last_data_.clear();
    }
    return ret;
}

void Client::do_read()
{
    // TODO: Choose appropriate buffer size
    // Buffer is a shared pointer to avoid copies in the lambda.
    auto buffer = std::make_shared<std::vector<char>>(1024);
    socket_.async_read_some(
        boost::asio::buffer(*buffer),
        [this, buffer](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                // Store the most recent data
                std::lock_guard<std::mutex> lock(data_mutex_);
                if (buffer->at(length-1) == '\n') {
                    last_data_ = std::string(buffer->data(), length-1);
                } else {
                    last_data_ = std::string(buffer->data(), length);
                }

                // Continue reading
                do_read();
            }
        });
}
