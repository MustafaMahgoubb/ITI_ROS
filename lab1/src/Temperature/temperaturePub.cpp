#include <rclcpp/rclcpp.hpp>
#include "tempClass.hpp"
#include <chrono>
#include <memory>

using namespace std::chrono_literals;   // enables the "ms" literal

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);                          // 1. init FIRST

    auto myObj = std::make_shared<tempClass>();        // 2. shared_ptr node

    auto timer_ = myObj->create_wall_timer(            // 3. now '->' works
        1000ms,                                        //    no space!
        std::bind(&tempClass::publishMsg, myObj));     // 4. bind shared_ptr

    rclcpp::spin(myObj);                               // 5. spin SAME node
    rclcpp::shutdown();
    return 0;
}