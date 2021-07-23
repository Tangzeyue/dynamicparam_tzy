#include "../include/DynamicParam.hpp"

//--------------------------------------
//定义类中的与参数初始化、结果发布相关的功能函数
//--------------------------------------
//by tzy
namespace dynamic_param {

    DynamicParam::DynamicParam(const ros::NodeHandle &node_handle, const ros::NodeHandle &private_node_handle)
    :testSrv_{private_node_handle}, params_{private_node_handle}
    {
        this->nh_ = node_handle;
        this->private_nh_ = private_node_handle;

        this->dynamic_param_pub_=this->nh_.advertise<dynamic_param_msgs::dynamic_param>("/dynamic_param", 1);

        this->testSrv_.setCallback(boost::bind(&DynamicParam::callback, this, _1, _2));
        
        
    }

    // void callback(dynamic_param::testConfig &config, uint32_t level){
    //     this->params_.is_foggy=config.is_foggy;
    //     this->params_.re_planning=config.re_planning;
    //     this->publish();
    // };

    // bool DynamicParam::publish()
    // {
    //     dynamic_param_.is_foggy=
    //     this->dynamic_param_pub_.publish(this->dynamic_param_);
    //     return true;

    // }

    void DynamicParam::callback(dynamic_param::testConfig &config, uint32_t level){
        params_.fromConfig(config);
        this->dynamic_param_.is_foggy=config.is_foggy;
        this->dynamic_param_.re_planning=config.re_planning;
	this->dynamic_param_.dynamic_obstacle=config.dynamic_obstacle;
        this->dynamic_param_.vehicle_meeting=config.vehicle_meeting; 
        this->dynamic_param_.vehicle_overtaking=config.vehicle_overtaking; 
  
        //this->dynamic_param_pub_.publish(this->dynamic_param_);
        ROS_WARN_STREAM("FUN------callback------is_foggy："<<(int)dynamic_param_.is_foggy);
        ROS_WARN_STREAM("FUN------callback------re_planning："<<(int)dynamic_param_.re_planning);
        ROS_WARN_STREAM("FUN------callback------dynamic_obstacle："<<(int)dynamic_param_.dynamic_obstacle);
        ROS_WARN_STREAM("FUN------callback------vehicle_meeting："<<(int)dynamic_param_.vehicle_meeting);
        ROS_WARN_STREAM("FUN------callback------vehicle_overtaking："<<(int)dynamic_param_.vehicle_overtaking);

    };
    



} 
