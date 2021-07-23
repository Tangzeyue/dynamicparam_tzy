
#include "../include/DynamicParam.hpp"
//启动节点dynamic_param
//by tzy

/**********
int main(int argc, char **argv)
{
    ros::init(argc, argv, "dynamic_param");
    
    dynamic_param::DynamicParam  dynamicparam(ros::NodeHandle(), ros::NodeHandle("~"));
    
    
    ROS_INFO("dynamic_param_node!!!");
    ros::spin();
    return 0;   

}
******/


/**********

int main(int argc, char **argv)
{
    ros::init(argc, argv, "dynamic_param");
    
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");
    ros::Rate loop_rate(10);
    while(ros::ok){
        //dynamic_param::DynamicParam  dynamicparam(ros::NodeHandle(), ros::NodeHandle("~"));
        dynamic_param::DynamicParam  dynamicparam(nh,private_nh);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    ROS_INFO("dynamic_param_node!!!");
    
    return 0;   

}
******/


int main(int argc, char **argv)
{
    ros::init(argc, argv, "dynamic_param");
    
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");
    dynamic_param::DynamicParam  dynamicparam(nh,private_nh);
    
    ros::Rate loop_rate(10);
    while(ros::ok){
	dynamicparam.dynamic_param_pub_.publish(dynamicparam.dynamic_param_);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    ROS_INFO("dynamic_param_node!!!");
    
    return 0;   

}
