//--------------------------------------
//定义DynamicParam类
//--------------------------------------
//by tzy

#ifndef DYNAMIC_PARAM_DYNAMICPARAM_HPP
#define DYNAMIC_PARAM_DYNAMICPARAM_HPP
 
//  #include <dynamic_reconfigure/server.h>
//  #include <dynamic_param/testConfig.h> 
#include "Defines.hpp"

namespace dynamic_param {
    // struct params
    // {
    //     bool is_foggy; /*!<烟雾区>*/
    //     bool re_planning; /*!<重规划>*/
    // };

    class DynamicParam 
    {
    public:
        DynamicParam(const ros::NodeHandle &node_handle, const ros::NodeHandle &private_node_handle);
		
        /// \brief  ros msg of dynamic_param
        dynamic_param_msgs::dynamic_param dynamic_param_;

        /// \brief Publisher, dynamic_param
        ros::Publisher dynamic_param_pub_;    
    
    private:

        // params params_;

        /// \brief ros nodehandle
        ros::NodeHandle nh_;

        /// \brief ros private nodehandle
        ros::NodeHandle private_nh_;

        /// \brief Dynamic reconfiguration service
        dynamic_reconfigure::Server<dynamic_param::testConfig> testSrv_; 

        /// \brief  configurable parameters
        dynamic_param::testParameters params_;

        /// \brief Define the callback
        void callback(dynamic_param::testConfig &config, uint32_t level);

    


    };


} 

#endif 
