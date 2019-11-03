#include <rosbridge_mqtt/generic_subscription.h>

namespace rosbridge_mqtt
{
    GenericSubscription::GenericSubscription(
       std::shared_ptr<rcl_node_t> node_handle,
        const rosidl_message_type_support_t & ts,
        const std::string & topic_name,
        std::function<void(std::shared_ptr<rmw_serialized_message_t>)> callback)
        : rclcpp::SubscriptionBase(
            node_handle,
            ts,
            topic_name,
            rcl_subscription_get_default_options())
        {
            default_allocator_ = rcutils_get_default_allocator();
            callback_ = callback;
        }

    void GenericSubscription::handle_message(std::shared_ptr<void> & message, const rmw_message_info_t & message_info)
    {
        (void) message_info;
        auto typed_message = std::static_pointer_cast<rmw_serialized_message_t>(message);
        callback_(typed_message);
    }

    void GenericSubscription::return_message(std::shared_ptr<void> & message)
    {
        auto typed_message = std::static_pointer_cast<rmw_serialized_message_t>(message);
        return_serialized_message(typed_message);
    }

    void GenericSubscription::return_serialized_message(std::shared_ptr<rmw_serialized_message_t> & message)
    {
        message.reset();
    }
}