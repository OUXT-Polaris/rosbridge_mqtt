// Headers in this package
#include <rosbridge_mqtt/rosbridge_mqtt_component.h>

namespace rosbridge_mqtt
{
    RosbridgeMqttComponent::RosbridgeMqttComponent(const rclcpp::NodeOptions & options)
    : Node("rosbridge_mqtt", options)
    {
        declare_parameter("host","localhost");
        get_parameter("host",host_);
        declare_parameter("port",8000);
        get_parameter("port",port_);
        declare_parameter("keepalive",60);
        get_parameter("keepalive",keepalive_);
        declare_parameter("with_certification",true);
        get_parameter("with_certification",with_certification_);
        if(with_certification_)
        {
            std::string package_share_directory = ament_index_cpp::get_package_share_directory("rosbridge_mqtt");
            declare_parameter("cafile",package_share_directory+"/config/ca.crt");
            get_parameter("cafile",cafile_);
            declare_parameter("certfile",package_share_directory+"/config/server.crt");
            get_parameter("certfile",certfile_);
            declare_parameter("keyfile",package_share_directory+"/config/server.key");
            get_parameter("keyfile",keyfile_);
        }
        mosquitto_lib_init();
    }
}