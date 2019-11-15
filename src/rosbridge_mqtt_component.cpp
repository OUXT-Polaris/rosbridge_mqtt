// Headers in this package
#include <rosbridge_mqtt/rosbridge_mqtt_component.h>

namespace rosbridge_mqtt
{
    RosbridgeMqttComponent::RosbridgeMqttComponent(const rclcpp::NodeOptions & options)
    : Node("rosbridge_mqtt", options)
    {
        mosq_ = NULL;
        declare_parameter("host","localhost");
        get_parameter("host",host_);
        declare_parameter("port",8000);
        get_parameter("port",port_);
        declare_parameter("keepalive",60);
        get_parameter("keepalive",keepalive_);
        declare_parameter("with_certification",true);
        get_parameter("with_certification",with_certification_);
        declare_parameter("client_id","");
        get_parameter("client_id",client_id_);
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
        declare_parameter("topic_config_path","");
        get_parameter("topic_config_path",topic_config_path_);
        if(!parseConfig())
        {
            return;
        }
        mosquitto_lib_init();
        if(client_id_ == "")
        {
            mosq_ = mosquitto_new(NULL,false,NULL);
        }
        else
        {
            mosq_ = mosquitto_new(client_id_.c_str(),false,NULL);
        }
    }

    bool RosbridgeMqttComponent::parseConfig()
    {
        namespace fs = boost::filesystem;
        const fs::path path(topic_config_path_);
        boost::system::error_code error;
        const bool result = fs::exists(path, error);
        if (!result || error)
        {
            return false;
        }
        using namespace boost::property_tree;
        ptree pt;
        read_json(topic_config_path_, pt);
        return true;
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(rosbridge_mqtt::RosbridgeMqttComponent)