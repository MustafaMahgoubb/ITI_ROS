#include <rclcpp/rclcpp.hpp>
#include "status_publisher.hpp"
#include <memory>

 // enables the "ms" literal

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);                          // 1. init FIRST
    rclcpp::spin(std::make_shared<StatusPublisher>());                               // 5. spin SAME node
    rclcpp::shutdown();
    return 0;
}