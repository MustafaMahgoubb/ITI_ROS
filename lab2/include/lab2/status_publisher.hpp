#ifndef STATUS_PUBLISHER_HEADER
#define STATUS_PUBLISHER_HEADER

#include <rclcpp/rclcpp.hpp>
#include <lab2/msg/robot_status.hpp>
#include <turtlesim/msg/pose.hpp>



class StatusPublisher : public rclcpp::Node
{

public:
    // Constructor
    StatusPublisher();

    // Destructor = default
    ~StatusPublisher() = default;

    void topic_callback(turtlesim::msg::Pose msg);

    void publish_status();


private:
    rclcpp::Publisher<lab2::msg::RobotStatus>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriper_;
    rclcpp::TimerBase::SharedPtr timer_;


    double x;
    double y;
    double accumlateTheta;
    double theta;


    std::string state;
    float temperature;
    int32_t lap_count;
};

#endif