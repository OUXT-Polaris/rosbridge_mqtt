#ifndef ROSBRIDGE_MQTT_GENERIC_SUBSCRIPTION_H_INCLUDED
#define ROSBRIDGE_MQTT_GENERIC_SUBSCRIPTION_H_INCLUDED


#include <rclcpp/macros.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/any_subscription_callback.hpp>
#include <rclcpp/message_memory_strategy.hpp>

namespace rosbridge_mqtt
{
    class GenericSubscription: public rclcpp::SubscriptionBase
    {
    public:
        RCLCPP_SMART_PTR_DEFINITIONS(GenericSubscription)
        GenericSubscription(
            std::shared_ptr<rcl_node_t> node_handle,
            const rosidl_message_type_support_t & ts,
            const std::string & topic_name,
            std::function<void(std::shared_ptr<rmw_serialized_message_t>)> callback);
        void handle_message(std::shared_ptr<void> & message, const rmw_message_info_t & message_info) override;
        void return_message(std::shared_ptr<void> & message) override;
        void return_serialized_message(std::shared_ptr<rmw_serialized_message_t> & message) override;
    private:
        RCLCPP_DISABLE_COPY(GenericSubscription)
        std::shared_ptr<rmw_serialized_message_t> borrow_serialized_message(size_t capacity);
        rcutils_allocator_t default_allocator_;
        std::function<void(std::shared_ptr<rmw_serialized_message_t>)> callback_;
    };
}

#endif  //ROSBRIDGE_MQTT_GENERIC_SUBSCRIPTION_H_INCLUDED