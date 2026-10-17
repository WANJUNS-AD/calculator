#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class CalculatorPublisher : public rclcpp::Node
{
public:
  CalculatorPublisher()
  : Node("calculator_publisher"), number_(1)
  {
    publisher_ = create_publisher<std_msgs::msg::Int64>(
      "calculator/result", 10);

    timer_ = create_wall_timer(
      1s, [this]()
      {
        std_msgs::msg::Int64 message;
        message.data = number_ + (number_ + 1);

        RCLCPP_INFO(
          get_logger(), "发布计算结果：%ld", message.data);
        publisher_->publish(message);
        number_++;
      });
  }

private:
  rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int64_t number_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CalculatorPublisher>());
  rclcpp::shutdown();
  return 0;
}
