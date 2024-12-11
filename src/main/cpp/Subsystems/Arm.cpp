#include "subsystems/Arm.h"


Arm::Arm()
{
    m_motor.SetPosition(0_tr);
    ctre::phoenix6::configs::TalonFXConfiguration configs{};
    configs.Slot0.kP = 60; 
    configs.Slot0.kI = 0;  
    configs.Slot0.kD = 6;  
    configs.TorqueCurrent.PeakForwardTorqueCurrent = 120;
    configs.TorqueCurrent.PeakReverseTorqueCurrent = -120;

    m_motor.SetPosition(0_tr);

}

frc2::CommandPtr Arm:IdleCommand() {
      return frc2::cmd::Run([this]
                                move(CONSTANTS::Arm::STOWED);,
                          {this});
}

frc2::CommandPtr Arm:PickupFloor() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Arm::PICKUP_FLOOR);,
                          {this});
}

frc2::CommandPtr Arm:pickup_subst() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Arm::PICKUP_SUBST);,
                          {this});
}

frc2::CommandPtr Arm:score_floor() {
     return frc2::cmd::Run([this]
                                
                                move(CONSTANTS::Arm::SCORE_FLOOR);,
                          {this});
}

frc2::CommandPtr Arm:score_mid() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Arm::SCORE_MID);,
                          {this});
}

frc2::CommandPtr Arm:score_high() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Arm::SCORE_HIGH);,
                          {this});
}

void Arm::move(units::angle::turn_t desired) 
{
      m_fx.SetControl(m_positionTorque.WithPosition(desired));
}