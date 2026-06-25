#ifndef TEMP_CLASS_HEADER
#define TEMP_CLASS_HEADER

#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <sensor_msgs/msg/temperature.hpp>

class tempClass : public rclcpp::Node
{

public:
    // Constructor
    tempClass();

    // Destructor
    ~tempClass() = default;

    double getTemp();
    void publishMsg();

private:
    double m_temp;
    rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr publisher_;
    std::fstream m_file;


};

#endif
