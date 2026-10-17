# Calculator 软件包测试报告

## 1. 测试目的

验证 ROS 2 Calculator 软件包能否正常编译、提供加法服务、发布和接收计算结果，并检查启动文件、代码风格和软件包配置。

## 2. 测试环境

- 操作系统：Ubuntu 22.04.5 LTS（运行于 WSL）
- ROS 2 版本：Humble
- 构建工具：colcon
- 软件包名称：calculator
- 服务接口：example_interfaces/srv/AddTwoInts
- 话题消息：std_msgs/msg/Int64

## 3. 测试内容与结果

| 编号 | 测试内容 | 测试方法 | 预期结果 | 实际结果 |
|---|---|---|---|---|
| 1 | 软件包编译 | 运行 `colcon build --packages-select calculator` | 编译成功，无错误 | 通过 |
| 2 | 加法服务：正整数 | 输入 2 和 3 | 返回 5 | 通过 |
| 3 | 加法服务：较大整数 | 输入 10 和 20 | 返回 30 | 通过 |
| 4 | 加法服务：一般正数 | 自动化测试输入 1 和 2 | 返回 3 | 通过 |
| 5 | 加法服务：零值 | 自动化测试输入 0 和 0 | 返回 0 | 通过 |
| 6 | 加法服务：正负数 | 自动化测试输入 -2 和 5 | 返回 3 | 通过 |
| 7 | 加法服务：两个负数 | 自动化测试输入 -4 和 -6 | 返回 -10 | 通过 |
| 8 | 加法服务：较大正数 | 自动化测试输入 100 和 200 | 返回 300 | 通过 |
| 9 | 话题发布与订阅 | 运行 Calculator launch 文件，观察 `calculator/result` 话题 | 发布者持续发布结果，订阅者能够收到消息 | 通过 |
| 10 | 代码与配置检查 | 运行完整 `colcon test` | 自动化测试及 lint 检查通过 | 9 项测试全部通过 |

## 4. 自动化测试说明

自动化测试位于 `test/test_add_two_ints.py`，通过 ROS 2 launch testing 启动加法服务并发送请求。测试覆盖了普通正数、零、正负数、两个负数和较大正数等输入情况，并逐项检查返回值是否符合预期。

## 5. 执行命令

在工作空间根目录 `~/ros2_ws` 执行：

colcon build --packages-select calculator
colcon test --packages-select calculator --event-handlers console_direct+

## 6. 测试结论

Calculator 软件包编译成功。加法服务的手动测试和五组自动化测试结果符合预期；话题发布、订阅及 launch 文件运行正常。完整测试套件显示 9/9 项通过，0 项失败，代码风格和软件包配置检查通过。

## 7. English Summary

The Calculator package built successfully in Ubuntu 22.04.5 with ROS 2 Humble. The add service passed five automated cases covering positive numbers, zero, mixed signs, negative numbers, and larger values. Manual service checks and the topic publisher/subscriber launch test also passed. The complete test suite reported 9 tests passed and 0 failures.
