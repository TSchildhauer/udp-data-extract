#include "aggregate.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <vector>

int main()
{
    try {
        boost::asio::io_context io_context;

        // Ports to connect to
        const std::vector<std::pair<uint16_t, std::string>> ports = { { 4001, "out1" }, { 4002, "out2" }, { 4003, "out3" } };
        const std::string host{"127.0.0.1"};
        const std::chrono::milliseconds window_ms{100};

        Aggregate aggregate_client(io_context, window_ms, host, ports);

        // Start spinning
        aggregate_client.spin();

        // Run the Boost.Asio event loop
        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
