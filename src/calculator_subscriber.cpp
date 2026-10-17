#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

#include <memory>

class CalculatorSubscriber : public rclcpp::Node
{
public:
  CalculatorSubscriber()
  : Node("calculator_subscriber")
  {
    subscription_ = create_subscription<std_msgs::msg::Int64>(
      "calculator/result", 10,
      [this](std_msgs::msg::Int64::SharedPtr message)
      {
        RCLCPP_INFO(
          get_logger(), "收到计算结果：%ld", message->data);
      });
  }

private:
  rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CalculatorSubscriber>());
  rclcpp::shutdown();
  return 0;
}
