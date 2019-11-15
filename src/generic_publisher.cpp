#include <rosbridge_mqtt/generic_publisher.h>

namespace rosbridge_mqtt
{
    GenericPublisher::GenericPublisher(
        rclcpp::node_interfaces::NodeBaseInterface * node_base,
        const std::string & topic,
        const rosidl_message_type_support_t & type_support)
        : rclcpp::PublisherBase(node_base, topic, type_support, rcl_publisher_get_default_options())
    {}

    void GenericPublisher::publish(std::shared_ptr<rmw_serialized_message_t> message)
    {
        auto return_code = rcl_publish_serialized_message(
        get_publisher_handle(), message.get(), NULL);

        if (return_code != RCL_RET_OK) 
        {
            rclcpp::exceptions::throw_from_rcl_error(return_code, "failed to publish serialized message");
        }
    }
}