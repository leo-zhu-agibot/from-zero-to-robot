#include <chrono>      // 为了用 1s 这种时间字面量
#include <memory>      // 为了用 std::make_shared（智能指针）
#include "rclcpp/rclcpp.hpp"          // ← 对应 Python: import rclpy
#include "std_msgs/msg/string.hpp"    // ← 对应 Python: from std_msgs.msg import String

using namespace std::chrono_literals; // ← 让下面能写 1s（1秒），否则得写 std::chrono::seconds(1)

// ← 对应 Python: class Talker(Node):
class Talker : public rclcpp::Node
{
public:
  // ← 对应 Python 的 __init__。 ": Node("talker"), count_(0)" 是初始化列表：
  //    Node("talker") 对应 super().__init__('talker')；count_(0) 对应 self.i = 0
  Talker()
  : Node("talker"), count_(0)
  {
    // ← 对应 self.publisher_ = self.create_publisher(String, 'chatter', 10)
    //    注意 C++ 用 <std_msgs::msg::String> 这个模板参数指定消息类型
    publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);

    // ← 对应 self.create_timer(1.0, self.timer_callback)
    //    std::bind(&Talker::timer_callback, this) 就是「把本对象的这个方法交给定时器」
    timer_ = this->create_wall_timer(
      1s, std::bind(&Talker::timer_callback, this));
  }

private:
  // ← 对应 Python 的 def timer_callback(self):
  void timer_callback()
  {
    auto msg = std_msgs::msg::String();               // ← msg = String()
    msg.data = "Hello ROS2: " + std::to_string(count_++); // ← msg.data = 'Hello ROS2: %d' % self.i; self.i += 1
    publisher_->publish(msg);                          // ← self.publisher_.publish(msg)
    // ← 对应 self.get_logger().info(...)。%s 要配 .c_str() 把 std::string 转成 C 字符串
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.data.c_str());
  }

  // ↓↓↓ 这三行是 C++ 特有的「成员变量声明」，Python 不需要，因为 Python 动态类型
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

// ← 对应 Python 的 def main() + rclpy.init/spin/shutdown
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);                        // ← rclpy.init()
  rclcpp::spin(std::make_shared<Talker>());        // ← node = Talker(); rclpy.spin(node)
  rclcpp::shutdown();                              // ← rclpy.shutdown()
  return 0;
}
