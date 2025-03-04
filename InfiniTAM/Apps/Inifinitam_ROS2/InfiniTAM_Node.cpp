
#include <memory>

#include "rclcpp/rclcpp.hpp"


class InfiniTAM_Node : public rclcpp::Node
{
public:
    InfiniTAM_Node(/* args */) : Node("infinitam_node"){
        //init here
    }

    ~InfiniTAM_Node(){
        
    }

private:


};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<InfiniTAM_Node>());
    rclcpp::shutdown();
    return 0;
}

