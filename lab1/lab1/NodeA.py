#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import numpy as np
import random

from sensor_msgs.msg import Range

class Sensor(Node):
    def __init__(self):
        super().__init__("Sensor_Publisher")
        self.publisher_ = self.create_publisher(Range, 'sensor/distance', 10)
        timer_period = 0.1 # Seconds
        self.timer_ = self.create_timer(timer_period , self.timer_callBack)
        
    def timer_callBack(self):
        msg = Range()
        
        msg.range = random.uniform(0.03,5.0)
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "Mahgoub_ID"
        
        # Publish Message
        self.publisher_.publish(msg)
        
def main(args=None):
    rclpy.init(args=args)
    
    sender = Sensor()
    rclpy.spin(sender)
    sender.destroy_node()
    rclpy.shutdown()
    
    
if __name__ == '__main__':
    main()