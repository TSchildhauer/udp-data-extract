#include "control_channel.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

std::shared_ptr<std::vector<uint8_t>> read_message_t::serialize() const {
    auto buffer = std::make_shared<std::vector<uint8_t>>(6); // 2 bytes for operation, 2 bytes for object, 2 bytes for property

    uint16_t operation_be = htons(static_cast<uint16_t>(operation));
    uint16_t object_be = htons(object);
    uint16_t property_be = htons(property);

    std::memcpy(buffer->data(), &operation_be, 2);
    std::memcpy(buffer->data() + 2, &object_be, 2);
    std::memcpy(buffer->data() + 4, &property_be, 2);

    return buffer;
}

std::shared_ptr<std::vector<uint8_t>> write_message_t::serialize() const {
    auto buffer = std::make_shared<std::vector<uint8_t>>(8); // 2 bytes for operation, 2 bytes for object, 2 bytes for property

    uint16_t operation_be = htons(static_cast<uint16_t>(operation));
    uint16_t object_be = htons(object);
    uint16_t property_be = htons(property);
    uint16_t value_be = htons(value);

    std::memcpy(buffer->data(), &operation_be, 2);
    std::memcpy(buffer->data() + 2, &object_be, 2);
    std::memcpy(buffer->data() + 4, &property_be, 2);
    std::memcpy(buffer->data() + 6, &value_be, 2);

    return buffer;
}

ControlChannel::ControlChannel(boost::asio::io_context& io_context, const std::string& host, uint16_t port)
    : socket_(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
      host_(host),
      port_(port)
{
}

void ControlChannel::sendMessage(const message_t& message) {
    auto serialized_message = message.serialize();
    socket_.async_send_to(boost::asio::buffer(*serialized_message), remote_endpoint_);
}

