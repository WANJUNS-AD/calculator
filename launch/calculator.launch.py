from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='calculator',
            executable='calculator_publisher',
            name='calculator_publisher',
            output='screen'
        ),
        Node(
            package='calculator',
            executable='calculator_subscriber',
            name='calculator_subscriber',
            output='screen'
        ),
    ])
