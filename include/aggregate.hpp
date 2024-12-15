#ifndef AGGREGATE_HPP
#define AGGREGATE_HPP

#include "client.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <memory>

class Aggregate {
public:
    Aggregate(boost::asio::io_context& io_context, const std::chrono::milliseconds& window_ms, const std::string& host, const std::vector<std::pair<uint16_t,std::string>>& inputs);

    // Start the aggregation process
    void spin();

private:
    // config
    const std::chrono::milliseconds window_ms_;
    boost::asio::steady_timer timer_;
    std::vector<std::unique_ptr<Client>> clients_;

    void schedule_next_spin();
};

#endif // AGGREGATE_HPP
