// Headers in this package
#include <rosbridge_mqtt/rosbridge_mqtt_component.h>

namespace rosbridge_mqtt
{
    RosbridgeMqttComponent::RosbridgeMqttComponent(const rclcpp::NodeOptions & options)
    : Node("rosbridge_mqtt", options)
    {
        mosquitto_lib_init();
    }
}