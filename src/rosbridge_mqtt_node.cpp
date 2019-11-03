// Headers in this package
#include <rosbridge_mqtt/rosbridge_mqtt_component.h>
// Headers in RCLCPP
#include <rclcpp/rclcpp.hpp>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto component = std::make_shared<rosbridge_mqtt::RosbridgeMqttComponent>(options);
    rclcpp::spin(component);
    rclcpp::shutdown();
    return 0;
}