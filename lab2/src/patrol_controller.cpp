#include "rclcpp/rclcpp.hpp"
#include "patrol_controller.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include <chrono>
#include "std_srvs/srv/empty.hpp"

using namespace std::chrono_literals;

PatrolController::PatrolController() : Node("patrol_controller"), linear_speed{0.0}, angular_speed{0.0} , stopped_{false}
{

    // Declare parameter with default value
    this->declare_parameter("linear_speed", 0.0);
    this->declare_parameter("angular_speed", 0.0);

    linear_speed = this->get_parameter("linear_speed").as_double();
    angular_speed = this->get_parameter("angular_speed").as_double();

    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

    stop_service_ = this->create_service<std_srvs::srv::Empty>(
        "/stop",
        std::bind(
            &PatrolController::stop_callback,
            this,
            std::placeholders::_1,
            std::placeholders::_2));

    continue_service_ = this->create_service<std_srvs::srv::Empty>(
        "/continue",
        std::bind(
            &PatrolController::continue_callback,
            this,
            std::placeholders::_1,
            std::placeholders::_2));

    timer_ = this->create_wall_timer(
        100ms,
        std::bind(&PatrolController::publish_control, this));
}

void PatrolController::publish_control()
{
    geometry_msgs::msg::Twist msg;

    if (!stopped_)
    {
        linear_speed =
            this->get_parameter("linear_speed").as_double();

        angular_speed =
            this->get_parameter("angular_speed").as_double();

        msg.linear.x = linear_speed;
        msg.angular.z = angular_speed;
    }
    else
    {
        msg.linear.x = 0.0;
        msg.angular.z = 0.0;
    }

    publisher_->publish(msg);
}

void PatrolController::stop_callback(
    const std::shared_ptr<std_srvs::srv::Empty::Request> request,
    std::shared_ptr<std_srvs::srv::Empty::Response> response)
{
    (void)request;
    (void)response;

    stopped_ = true;

    RCLCPP_INFO(this->get_logger(), "Patrol stopped");
}


void PatrolController::continue_callback(
    const std::shared_ptr<std_srvs::srv::Empty::Request> request,
    std::shared_ptr<std_srvs::srv::Empty::Response> response)
{
    (void)request;
    (void)response;

    stopped_ = false;

    RCLCPP_INFO(this->get_logger(), "Patrol resumed");
}