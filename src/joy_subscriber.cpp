#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"

class JoySubscriber : public rclcpp::Node
{
public:
    JoySubscriber() : Node("joy_subscriber")
    {
        // サブスクリプションの作成
        subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "/joy", 10, std::bind(&JoySubscriber::joyCallback, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "JoySubscriber has been started.");
    }

private:
    void joyCallback(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        // ジョイスティックのボタンと軸の値をログに出力
        RCLCPP_INFO(this->get_logger(), "Axes: [%s]", 
            std::accumulate(msg->axes.begin(), msg->axes.end(), std::string(),
                            [](std::string a, float b) { return a + (a.empty() ? "" : ", ") + std::to_string(b); }).c_str());
        RCLCPP_INFO(this->get_logger(), "Buttons: [%s]", 
            std::accumulate(msg->buttons.begin(), msg->buttons.end(), std::string(),
                            [](std::string a, int b) { return a + (a.empty() ? "" : ", ") + std::to_string(b); }).c_str());
    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JoySubscriber>());
    rclcpp::shutdown();
    return 0;
}
