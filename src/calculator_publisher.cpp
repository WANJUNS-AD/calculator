// Copyright 2026 Calculator Project Contributors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

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
