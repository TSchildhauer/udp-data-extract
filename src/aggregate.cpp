#include "aggregate.hpp"

#include <boost/asio.hpp>
// #include <boost/json.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
// #include <chrono>
#include <thread>

using boost::asio::ip::tcp;
// namespace json = boost::json;

Aggregate::Aggregate(boost::asio::io_context& io_context, const std::chrono::milliseconds& window_ms, const std::string& host, const std::vector<std::pair<uint16_t, std::string>>& inputs)
    : window_ms_(window_ms)
    , timer_(io_context, window_ms)
{
    for (const auto& [port, name] : inputs) {
        clients_.emplace_back(std::make_unique<Client>(io_context, host, port, name));
    }
}

void Aggregate::spin()
{
    for (auto& client : clients_) {
        client->start();
    }
    schedule_next_spin();
}

void Aggregate::schedule_next_spin()
{
    timer_.expires_after(window_ms_);
    timer_.async_wait([this](boost::system::error_code ec) {
        if (!ec) {
            // Create the JSON object
            // json::object output;
            // output["timestamp"] = current_timestamp();

            std::string out = "t: " + std::to_string(steady_synced_clock_.steady_now_ms().count()) + ", ";

            // extract_data destroys it, so this reference can't be const
            for (auto& c : clients_) {
                out += c->get_name() + ": " + c->get_last_data() + ", ";
            }

            // Print the JSON object as a line
            // std::cout << json::serialize(output) << std::endl;
            std::cout << out << std::endl;

            // Schedule the next spin
            schedule_next_spin();
        }
    });
}
