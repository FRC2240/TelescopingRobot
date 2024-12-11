#include <units/length.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/ConditionalCommand.h>
#include "ctre/phoenix6/TalonFX.hpp"
#include "Constants.h"



class Hand : public frc2::SubsystemBase
{
    public:
    frc2::CommandPtr IdleCommand();
    frc2::CommandPtr PickupFloor();
    frc2::CommandPtr pickup_subst();
    frc2::CommandPtr score_floor();
    frc2::CommandPtr score_mid();
    frc2::CommandPtr score_high();

    private:
        ctre::phoenix6::hardware::TalonFX m_motor{CONSTANTS::ARM::CAN_ID_MOTOR, "rio"};
        
        void move(units::angle::turn_t desired);


};