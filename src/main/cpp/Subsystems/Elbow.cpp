#include "subsystems/Elbow.h"
#include <iostream>


ELBOW::Elbow()
{
    m_moter.SetPosition(0_tr);
    ctre::phoenix6::configs::TalonFXConfiguration configs{};
    configs.Slot0.kP = 60; 
    configs.Slot0.kI = 0;  
    configs.Slot0.kD = 6;  
    configs.TorqueCurrent.PeakForwardTorqueCurrent = 120;
    configs.TorqueCurrent.PeakReverseTorqueCurrent = -120;

    m_moter.SetPosition(0_tr);

}

frc2::CommandPtr Elbow:IdleCommand() {
      return frc2::cmd::Run([this]
                                move(CONSTANTS::Elbow::STOWED);,
                          {this});
}

frc2::CommandPtr Elbow:PickupFloor() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Elbow::PICKUP_FLOOR);,
                          {this});
}

frc2::CommandPtr Elbow:pickup_subst() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Elbow::PICKUP_SUBST);,
                          {this});
}

frc2::CommandPtr Elbow:score_floor() {
     return frc2::cmd::Run([this]
                                
                                move(CONSTANTS::Elbow::SCORE_FLOOR);,
                          {this});
}

frc2::CommandPtr Elbow:score_mid() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Elbow::SCORE_MID);,
                          {this});
}

frc2::CommandPtr Elbow:score_high() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Elbow::SCORE_HIGH);,
                          {this});
}