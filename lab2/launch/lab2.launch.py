from launch import LaunchDescription
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():

    package_name = "lab2"

    params_file = os.path.join(
        get_package_share_directory(package_name),
        "params",
        "patrol_params.yaml"
    )

    status_publisher_node = Node(
        package=package_name,
        executable="statusPublisher",
        name="status_publisher",
        output="screen",
        parameters=[params_file]
    )

    patrol_controller_node = Node(
        package=package_name,
        executable="PatrolController",
        name="patrol_controller",
        output="screen",
        parameters=[params_file]
    )
    
    turtlesim_node = Node(
        package="turtlesim",
        executable="turtlesim_node",
        name="turtlesim_node",
        output="screen"
    )

    return LaunchDescription([
        status_publisher_node,
        patrol_controller_node,
        turtlesim_node
    ])