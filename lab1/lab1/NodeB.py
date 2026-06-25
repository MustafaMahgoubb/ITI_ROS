#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import numpy as np
import random

from sensor_msgs.msg import Range
from std_msgs.msg import Bool

class Control(Node):
    def __init__(self):
        super().__init__("Control_Publisher")
        self.subscription = self.create_subscription(
            Range,
            'sensor/distance',
            self.callback,
            10)
        self.publisher_ = self.create_publisher(Bool, 'cmd/stop', 10)
        
    def callback(self , msg):
        distance = msg.range
        control_Msg = Bool()
        if distance < 2.0 :
            control_Msg.data = True
        else:
            control_Msg.data = False
            
        self.publisher_.publish(control_Msg)
        
def main(args=None):
    rclpy.init(args=args)
    
    myNode = Control()
    rclpy.spin(myNode)
    myNode.destroy_node()
    rclpy.shutdown()
    
    
if __name__ == '__main__':
    main()