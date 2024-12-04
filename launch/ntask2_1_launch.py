from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # joy ノードを起動
        Node(
            package='joy',
            executable='joy_node',  # publisher.cpp で作成した実行可能ファイル
            name='joy_node',
            output='screen',
        ),
        Node(
            package='ntask2_1',
            executable='joy_subscriber',
            name='joy_subscriber',
            output='screen',
        )
    ])
