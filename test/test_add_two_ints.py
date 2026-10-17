import pytest
import rclpy
from example_interfaces.srv import AddTwoInts


@pytest.mark.launch_test
def generate_test_description():
    import launch
    import launch_ros.actions
    import launch_testing.actions

    server = launch_ros.actions.Node(
        package='calculator',
        executable='add_two_ints_server',
        output='screen',
    )

    return (
        launch.LaunchDescription([
            server,
            launch_testing.actions.ReadyToTest(),
        ]),
        {'server': server},
    )


class TestAddTwoInts:
    @classmethod
    def setup_class(cls):
        rclpy.init()
        cls.node = rclpy.create_node('test_add_two_ints_client')
        cls.client = cls.node.create_client(AddTwoInts, 'add_two_ints')
        assert cls.client.wait_for_service(timeout_sec=10.0), \
            '等待 add_two_ints 服务超时'

    @classmethod
    def teardown_class(cls):
        cls.node.destroy_node()
        rclpy.shutdown()

    @pytest.mark.parametrize(
        'a, b, expected',
        [
            (1, 2, 3),
            (0, 0, 0),
            (-2, 5, 3),
            (-4, -6, -10),
            (100, 200, 300),
        ],
    )
    def test_add_two_ints(self, a, b, expected):
        request = AddTwoInts.Request()
        request.a = a
        request.b = b

        future = self.client.call_async(request)
        rclpy.spin_until_future_complete(
            self.node, future, timeout_sec=5.0
        )

        assert future.done(), f'调用服务超时：{a} + {b}'
        response = future.result()
        assert response is not None, '服务没有返回结果'
        assert response.sum == expected
