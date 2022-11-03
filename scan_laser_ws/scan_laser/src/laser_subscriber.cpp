#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      initparam();
      subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      topic, Rio, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) 
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg);
    }
    void initparam(){
    this->declare_parameter<float>("queue_size");
    this->declare_parameter<std::string>("scantopic");
    this->get_parameter_or<float>("queue_size", Rio, 10);
    this->get_parameter_or<std::string>("scantopic", topic, "/scan");
  }  
    std::string topic;
    float Rio;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
