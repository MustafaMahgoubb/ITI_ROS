#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from nav_msgs.msg import Odometry


class odomPub(Node):
    def __init__(self):
        super().__init__("odomPublisher_Node")
        self.myPublisher_ = self.create_publisher(Odometry, '/odom' , 10)
        self.period_s = 0.1
        self.myTimer_ = self.create_timer(self.period_s, self.timerCallBack)
        
        # States 
        self.x = 0.0
        self.y = 0.0
        self.vx = 0.0
        
    def timerCallBack(self):
        msg = Odometry()
        
        new_X = self.x + 0.1
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "odom"
        msg._child_frame_id = "base_link"
        
        msg.pose.pose.position.x = self.x
        msg.pose.pose.position.y = self.y
        
        msg.pose.pose.orientation.w = 1.0
        
        self.myPublisher_.publish(msg)
        
        
def main(args=None):
    rclpy.init(args=args)
    
    sender = odomPub()
    rclpy.spin(sender)
    sender.destroy_node()
    rclpy.shutdown()
    

if __name__ == '__main__':
    main()