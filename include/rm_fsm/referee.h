//
// Created by luohx on 20-2-19.
//
#ifndef SRC_RM_BRIDGE_INCLUDE_RT_RT_REFEREE_H_
#define SRC_RM_BRIDGE_INCLUDE_RT_RT_REFEREE_H_
//Referee System
#include <cstdint>
#include "rm_fsm/protocol.h"
#include <serial/serial.h>

namespace referee {
struct RefereeData {
  GameStatus game_status_;
  GameResult game_result_;
  GameRobotHp game_robot_hp_;
  DartStatus dart_status_;
  IcraBuffDebuffZoneStatus icra_buff_debuff_zone_status;
  EventData event_data_;
  SupplyProjectileAction supply_projectile_action_;
  RefereeWarning referee_warning_;
  DartRemainingTime dart_remaining_time_;
  GameRobotStatus game_robot_status_;
  PowerHeatData power_heat_data_;
  GameRobotPos game_robot_pos_;
  Buff buff_;
  AerialRobotEnergy aerial_robot_energy_;
  RobotHurt robot_hurt_;
  ShootData shoot_data_;
  BulletRemaining bullet_remaining_;
  RfidStatus rfid_status_;
  DartClientCmd dart_client_cmd_;
  StudentInteractiveHeaderData student_interactive_header_data_;
  RobotInteractiveData robot_interactive_data_;
  ClientCustomGraphicDelete client_custom_graphic_delete_;
  GraphicDataStruct graphic_data_struct_;
  ClientCustomGraphicSingle client_custom_graphic_single_;
  ClientCustomGraphicDouble client_custom_graphic_double_;
  ClientCustomGraphicFive client_custom_graphic_five_;
  ClientCustomGraphicSeven client_custom_graphic_seven_;
  ClientCustomCharacter client_custom_character_;
  int performance_system_; // Performance level system
};

class Referee {
 public:
  Referee() = default;
  ~Referee() = default;
  void init();
  void read();
  RefereeData referee_data_{};
  bool flag = false;

 private:
  serial::Serial serial_;
  int rx_len_{};
  UnpackData referee_unpack_obj{};
  const int kProtocolFrameLength = 128, kProtocolHeaderLength = sizeof(FrameHeaderStruct),
      kProtocolCmdIdLength = sizeof(uint16_t), kProtocolTailLength = 2;
  void unpack(const std::vector<uint8_t> &rx_buffer);
  void getData(uint8_t *frame);

};
}

#endif //SRC_RM_BRIDGE_INCLUDE_RT_RT_REFEREE_H_