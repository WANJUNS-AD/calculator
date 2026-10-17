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
#include <string>

#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
    RCLCPP_ERROR(
      rclcpp::get_logger("add_two_ints_client"),
      "用法：ros2 run calculator add_two_ints_client <整数1> <整数2>");
    rclcpp::shutdown();
    return 1;
  }

  auto node = std::make_shared<rclcpp::Node>("add_two_ints_client");
  auto client =
    node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "等待服务时被中断");
      rclcpp::shutdown();
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "正在等待加法服务...");
  }

  auto request =
    std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
  request->a = std::stoll(argv[1]);
  request->b = std::stoll(argv[2]);

  auto future = client->async_send_request(request);
  auto result = rclcpp::spin_until_future_complete(node, future);

  if (result == rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(node->get_logger(), "计算结果：%ld", future.get()->sum);
  } else {
    RCLCPP_ERROR(node->get_logger(), "调用服务失败");
  }

  rclcpp::shutdown();
  return 0;
}
