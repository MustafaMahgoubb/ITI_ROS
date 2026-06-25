#ifndef VELOCITY_LIMITER_HEADER
#define VELOCITY_LIMITER_HEADER

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>


class velocityLimiter : public rclcpp::Node
{

    public:
    //  Costructor
    velocityLimiter();

    // default Destructor 
    ~velocityLimiter() = default;
    private:

    // publisher

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

    // subscriber
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriper_;


};

#endif