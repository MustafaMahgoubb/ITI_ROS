#!/usr/bin/env pyhton3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='lab1',
            executable="NodeA.py",
            name="Sender",
            output="screen"
        ),
        Node(
            package='lab1',
            executable="NodeB.py",
            name="Sender",
            output="screen"
        )
    ])
