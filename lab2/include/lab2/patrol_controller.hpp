#ifndef PATROL_CONTROLLER_HEADER
#define PATROL_CONTROLLER_HEADER

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include "std_srvs/srv/empty.hpp"


class PatrolController : public rclcpp::Node
{

public:

    // Constructor
    PatrolController();

    // Default Destructor
    ~PatrolController() = default;

    void publish_control();


    void stop_callback(
    const std::shared_ptr<std_srvs::srv::Empty::Request> request,
    std::shared_ptr<std_srvs::srv::Empty::Response> response);

    void continue_callback(
    const std::shared_ptr<std_srvs::srv::Empty::Request> request,
    std::shared_ptr<std_srvs::srv::Empty::Response> response);

private:

    double linear_speed;
    double angular_speed;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr stop_service_;
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr continue_service_;
    rclcpp::TimerBase::SharedPtr timer_;

    bool stopped_;
};

#endif