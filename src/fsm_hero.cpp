//
// Created by bruce on 2021/1/29.
//

#include "rm_fsm/fsm_hero.h"

template<typename T>
FsmHero<T>::FsmHero(ros::NodeHandle &node_handle) : Fsm<T>(node_handle) {
  state_passive_ = new StatePassive<T>(&this->data_, "passive", node_handle, this->pc_control_);
  state_raw_ = new StateRaw<T>(&this->data_, "raw", node_handle, this->pc_control_);
  this->string2state.insert(std::pair<std::string, State<T> *>("passive", state_passive_));
  this->string2state.insert(std::pair<std::string, State<T> *>("raw", state_raw_));
  this->current_state_ = this->string2state["passive"];
}

template<typename T>
std::string FsmHero<T>::getDesiredState() {

  if (this->pc_control_) { // pc control
    if (this->data_.dbus_data_.key_ctrl
        && this->data_.dbus_data_.key_q) { // ctrl + q change state to passive
      return "passive";
    } else if (this->data_.dbus_data_.key_ctrl
        && this->data_.dbus_data_.key_w) { // ctrl + w change state to raw
      return "raw";
    } else {
      return this->current_state_->state_name_;
    }
  } else { // rc control
    if (this->data_.dbus_data_.s_r == this->data_.dbus_data_.DOWN) {
      return "passive";
    } else if (this->data_.dbus_data_.s_r == this->data_.dbus_data_.MID) {
      return "raw";
    } else {
      return "passive";
    }
  }
}

template
class FsmHero<double>;
template
class FsmHero<float>;
