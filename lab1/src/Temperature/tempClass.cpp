#include "tempClass.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/temperature.hpp>
#include <fstream>

tempClass::tempClass() : Node("temp_Class_Node") , m_temp{0} ,m_file("/sys/class/thermal/thermal_zone0/temp")
{
    publisher_ = this->create_publisher<sensor_msgs::msg::Temperature>("/cpu_temp", 10);
    RCLCPP_INFO(this->get_logger(), "Created Temp Class Node");
}

double tempClass::getTemp()
{
    std::ifstream f("/sys/class/thermal/thermal_zone0/temp");
    if (!f.is_open()) {
        RCLCPP_ERROR(this->get_logger(), "Cannot open thermal_zone0/temp");
        return m_temp;
    }

    std::string txt;
    std::getline(f, txt);

    if (txt.empty()) {
        RCLCPP_WARN(this->get_logger(), "Empty temp string");
        return m_temp;
    }

    m_temp = std::stoi(txt) / 1000.0;
    return m_temp;
}

void tempClass::publishMsg()
{
    publisher_ = this->create_publisher<sensor_msgs::msg::Temperature>("/cpu_temp", 10);
    auto message = sensor_msgs::msg::Temperature();
    message.header.stamp = this->get_clock()->now();
    message.temperature =  getTemp();

    std::cout << "Temp" << message.temperature <<std::endl;
    publisher_ ->publish(message);
}