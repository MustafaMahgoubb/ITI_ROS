#include "rclcpp/rclcpp.hpp"
#include "lab2/msg/robot_status.hpp"
#include "status_publisher.hpp"
#include <turtlesim/msg/pose.hpp>
#include <chrono>
#include <cmath>


using namespace std::chrono_literals;

StatusPublisher::StatusPublisher() : Node("status_publisher"), x{0.0}, y{0.0},
                                     theta{0.0}, state{"stopped"}, temperature{25}, lap_count{0}
{

    // Declare parameter with default value
    this->declare_parameter("status_rate", 5.0);

    double status_rate = this->get_parameter("status_rate").as_double();

    auto period = std::chrono::milliseconds(static_cast<int>(1000.0 / status_rate));

    publisher_ = this->create_publisher<lab2::msg::RobotStatus>("/robot/status", 10);

    subscriper_ = this->create_subscription<turtlesim::msg::Pose>(
        "/turtle1/pose",
        10,
        std::bind(&StatusPublisher::topic_callback, this, std::placeholders::_1));

    timer_ = this->create_wall_timer(
        period,
        std::bind(&StatusPublisher::publish_status, this));
}

void StatusPublisher::topic_callback(turtlesim::msg::Pose msg)
{
    x = msg.x;
    y = msg.y;

    double delta_theta = msg.theta - theta;

    // Handle angle wrapping
    if (delta_theta > M_PI)
    {
        delta_theta -= 2 * M_PI;
    }
    else if (delta_theta < -M_PI)
    {
        delta_theta += 2 * M_PI;
    }

    accumlateTheta += std::abs(delta_theta);

    lap_count = accumlateTheta / (2 * M_PI);

    
    theta = msg.theta;

    if((msg.linear_velocity > 0.000 ) || (msg.angular_velocity > 0.000 ) )
    {
        state = "running";
    }

    else
    {
        state = "stopped";
    }
}

void StatusPublisher::publish_status()
{
    lab2::msg::RobotStatus msg;

    msg.pose.x = x;
    msg.pose.y = y;
    msg.pose.theta = theta;

    msg.state = state;
    msg.temperature = temperature;
    msg.lap_count = lap_count;

    publisher_->publish(msg);
}