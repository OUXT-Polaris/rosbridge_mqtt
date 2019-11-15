#ifndef ROSBRIDGE_MQTT_ROSBRIDGE_MQTT_COMPONENT_H_INCLUDED
#define ROSBRIDGE_MQTT_ROSBRIDGE_MQTT_COMPONENT_H_INCLUDED

#if __cplusplus
extern "C" {
#endif

// The below macros are taken from https://gcc.gnu.org/wiki/Visibility and from
// demos/composition/include/composition/visibility_control.h at https://github.com/ros2/demos
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSBRIDGE_MQTT_EXPORT __attribute__ ((dllexport))
    #define ROSBRIDGE_MQTT_IMPORT __attribute__ ((dllimport))
  #else
    #define ROSBRIDGE_MQTT_EXPORT __declspec(dllexport)
    #define ROSBRIDGE_MQTT_IMPORT __declspec(dllimport)
  #endif
  #ifdef ROSBRIDGE_MQTT_BUILDING_DLL
    #define ROSBRIDGE_MQTT_PUBLIC ROSBRIDGE_MQTT_EXPORT
  #else
    #define ROSBRIDGE_MQTT_PUBLIC ROSBRIDGE_MQTT_IMPORT
  #endif
  #define ROSBRIDGE_MQTT_PUBLIC_TYPE ROSBRIDGE_MQTT_PUBLIC
  #define ROSBRIDGE_MQTT_LOCAL
#else
  #define ROSBRIDGE_MQTT_EXPORT __attribute__ ((visibility("default")))
  #define ROSBRIDGE_MQTT_IMPORT
  #if __GNUC__ >= 4
    #define ROSBRIDGE_MQTT_PUBLIC __attribute__ ((visibility("default")))
    #define ROSBRIDGE_MQTT_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ROSBRIDGE_MQTT_PUBLIC
    #define ROSBRIDGE_MQTT_LOCAL
  #endif
  #define ROSBRIDGE_MQTT_PUBLIC_TYPE
#endif

#if __cplusplus
} // extern "C"
#endif

// Headers in ROS2
#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>

// Headers in STL
#include <map>

// Headers in Mosquitto
#include <mosquitto.h>

// Headers in this package
#include <rosbridge_mqtt/generic_subscription.h>
#include <rosbridge_mqtt/generic_publisher.h>

namespace rosbridge_mqtt
{
    class RosbridgeMqttComponent: public rclcpp::Node
    {
    public:
        ROSBRIDGE_MQTT_PUBLIC
        explicit RosbridgeMqttComponent(const rclcpp::NodeOptions & options);
    private:
        std::string host_;
        int port_;
        int keepalive_;
        std::string cafile_;
        std::string certfile_;
        std::string keyfile_;
        bool with_certification_;
        std::map<std::string,std::unique_ptr<GenericSubscription> > subs_;
        std::map<std::string,std::unique_ptr<GenericPublisher> > pubs_;
    };
}

#endif  //ROSBRIDGE_MQTT_ROSBRIDGE_MQTT_COMPONENT_H_INCLUDED