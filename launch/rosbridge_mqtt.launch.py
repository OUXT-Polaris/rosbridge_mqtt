import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='rosbridge_mqtt',
            node_executable='rosbridge_mqtt_node',
            node_name='rosbridge_mqtt_node',
            output='screen')
    ])