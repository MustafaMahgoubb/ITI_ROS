#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using std::placeholders::_1;

class SumSub : public rclcpp::Node {
public:
    SumSub() : Node("sum_subscriber"){
        sub_No1_ = this->create_subscription<std_msgs::msg::Int32>("/Number1", 5, std::bind(&SumSub::callback_No1, this, _1));
        sub_No2_ = this->create_subscription<std_msgs::msg::Int32>("/Number2", 5, std::bind(&SumSub::callback_No2, this, _1));

        publisher_ = this->create_publisher<std_msgs::msg::Int32>("/Sum", 5);

        got_No1_ = false;
        got_No2 = false;
    }

private:
    void callback_No1(const std_msgs::msg::Int32 & msg){
        No1_ = msg.data;
        got_No1_ = true;

        RCLCPP_INFO(this->get_logger(), "Received Number1: %d", No1_);
        compute_sum();
    }

    void callback_No2(const std_msgs::msg::Int32 & msg){
        No2_ = msg.data;
        got_No2 = true;

        RCLCPP_INFO(this->get_logger(), "Received Number2: %d", No2_);
        compute_sum();
    }

    void compute_sum(){
        if(got_No1_ && got_No2){
            int sum = No1_ + No2_;
            RCLCPP_INFO(this->get_logger(), "Sum: %d + %d = %d", No1_, No2_, sum);

            // Publish the sum
            auto message = std_msgs::msg::Int32();
            message.data = sum;
            RCLCPP_INFO(this->get_logger(), "Published Sum: %d", sum);
            publisher_->publish(message);
        }
    }

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_No1_;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_No2_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;

    int No1_;
    int No2_;
    bool got_No1_;
    bool got_No2;
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SumSub>());
    rclcpp::shutdown();
    return 0;
}