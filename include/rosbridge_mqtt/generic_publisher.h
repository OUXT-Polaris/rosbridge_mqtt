#ifndef ROSBRIDGE_MQTT_GENERIC_PUBLISHER_H_INCLUDED
#define ROSBRIDGE_MQTT_GENERIC_PUBLISHER_H_INCLUDED

#include <rclcpp/rclcpp.hpp>

namespace rosbridge_mqtt
{
    class GenericPublisher: public rclcpp::PublisherBase
    {
        GenericPublisher(
            rclcpp::node_interfaces::NodeBaseInterface * node_base,
            const std::string & topic,
            const rosidl_message_type_support_t & type_support);
        void publish(std::shared_ptr<rmw_serialized_message_t> message);
    };
}

#endif  //ROSBRIDGE_MQTT_GENERIC_PUBLISHER_H_INCLUDED