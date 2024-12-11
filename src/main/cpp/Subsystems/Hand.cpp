#include "subsystems/Hand.h"



Hand::Hand()
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

frc2::CommandPtr Hand:IdleCommand() {
      return frc2::cmd::Run([this]
                                move(CONSTANTS::Hand::STOWED);,
                          {this});
}

frc2::CommandPtr Hand:PickupFloor() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Hand::PICKUP_FLOOR);,
                          {this});
}

frc2::CommandPtr Hand:pickup_subst() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Hand::PICKUP_SUBST);,
                          {this});
}

frc2::CommandPtr Hand:score_floor() {
     return frc2::cmd::Run([this]
                                
                                move(CONSTANTS::Hand::SCORE_FLOOR);,
                          {this});
}

frc2::CommandPtr Hand:score_mid() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Hand::SCORE_MID);,
                          {this});
}

frc2::CommandPtr Hand:score_high() {
     return frc2::cmd::Run([this]
                                move(CONSTANTS::Hand::SCORE_HIGH);,
                          {this});
}

void Hand::move(units::angle::turn_t desired) 
{
      m_fx.SetControl(m_positionTorque.WithPosition(desired));
}