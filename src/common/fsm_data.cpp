//
// Created by luotinkai on 2022/3/2.
//

#include "rm_fsm/common/fsm_data.h"

FsmData::FsmData(ros::NodeHandle &nh) {
    joint_state_sub_ = nh.subscribe<sensor_msgs::JointState>("/joint_states", 10, &FsmData::jointStateCallback, this);
    dbus_sub_ = nh.subscribe<rm_msgs::DbusData>("/dbus_data", 10, &FsmData::dbusDataCallback, this);
    lower_track_sub_ =
            nh.subscribe<rm_msgs::TrackDataArray>("/controllers/lower_gimbal_controller/track", 10,
                                                  &FsmData::lowerTrackCallback, this);
    lower_gimbal_des_error_sub_ =
            nh.subscribe<rm_msgs::GimbalDesError>("/controllers/lower_gimbal_controller/error_des", 10,
                                                  &FsmData::lowerGimbalDesErrorCallback, this);
    referee_.referee_pub_ = nh.advertise<rm_msgs::Referee>("/referee", 1);
    initSerial();
}

void FsmData::update(const ros::Time &time) {
    geometry_msgs::TransformStamped odom2baselink;
    try { odom2baselink = tf_buffer_.lookupTransform("odom", "base_link", ros::Time(0)); }
    catch (tf2::TransformException &ex) { ROS_ERROR_ONCE("%s", ex.what()); }
    pos_x_ = odom2baselink.transform.translation.x;
    try {
        if (serial_.available()) {
            referee_.rx_len_ = (int) serial_.available();
            serial_.read(referee_.rx_buffer_, referee_.rx_len_);
        }
    }
    catch (serial::IOException &e) {}
    referee_.read();
    try {
        serial_.write(referee_.tx_buffer_, referee_.tx_len_);
    }
    catch (serial::PortNotOpenedException &e) {}
    referee_.clearBuffer();
}
