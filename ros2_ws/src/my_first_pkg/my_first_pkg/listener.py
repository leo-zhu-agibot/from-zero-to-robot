import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class listener(Node):

    def __init__(self):
        self.i = 0
        super().__init__('listener')
        self.subscription_ = self.create_subscription
        (String, 'chatter', self.listener_callback, 10)

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)


def main():
    rclpy.init()
    listen = listener()
    rclpy.spin(listen)
    listen.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
