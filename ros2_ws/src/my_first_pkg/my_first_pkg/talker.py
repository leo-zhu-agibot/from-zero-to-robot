import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class talker(Node):

    def __init__(self):
        self.i = 0
        super().__init__('talker')
        self.publisher_ = self.create_publisher
        (String, 'chatter', 10)
        self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        msg = String()
        msg.data = 'Hello, world!'
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)


def main():
    rclpy.init()
    talk = talker()
    rclpy.spin(talk)
    talk.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
