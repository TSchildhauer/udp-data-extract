#ifndef CONTROL_CHANNEL_HPP
#define CONTROL_CHANNEL_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <memory>

struct message_t {
    enum class operation_t : uint16_t { UNKNOWN = 0u,
        READ = 1u,
        WRITE = 2u };
    const operation_t operation = operation_t::UNKNOWN;
    uint16_t object = 0u;
    uint16_t property = 0u;

    // pure virtual function that specific messages need to implement
    std::shared_ptr<std::vector<uint8_t>> serialize() const = 0; 
};


struct read_message_t : public message_t {
    read_message_t()
        : operation(operation_t::READ)
    {
    }

    std::shared_ptr<std::vector<uint8_t>> serialize() const override;
};

struct write_message_t : public message_t {
    write_message_t()
        : operation(operation_t::WRITE)
    {
    }
    uint16_t value = 0u;

    std::shared_ptr<std::vector<uint8_t>> serialize() const override;
};

class ControlChannel {
public:
    // ControlChannel to listen to a single UDP port
    ControlChannel(boost::asio::io_context& io_context, const std::string& host, uint16_t port);

    void sendMessage(const message_t& message);

private:
    // config
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    const std::string host_;
    const uint16_t port_;
};

#endif // CONTROL_CHANNEL_HPP