# Telescoping Robot
Designed to accomplish tasks from the FRC 2023 game [CHARGED UP](https://firstfrc.blob.core.windows.net/frc2024/Manual/2024GameManual.pdf).

## Requirements
* Shall be able to pickup cones from both the floor and DOUBLE SUBSTATION
* Shall be able to place cones at all of the following levels: floor, CONE NODE (Middle Row), CONE Node (Top Row)
* When a cone is detected in the Intake, the arm/wrist shall automatically move to the "stowed" position

All pickup/place actions shall require a single controller action to initiate and complete:
* Left Bumper (Toggle Floor Pickup Mode)
* Right Bumper (Toggle SUBSTATION Pickup Mode)
* Button A (Place on cone on Floor)
* Button B (Place cone on CONE NODE, Middle Row)
* Button Y (Place cone on CONE NODE, Top Row)
  
## Components

The motors and sensors to be managed by software:
* Arm Rotation (2 Kraken X60, 1 CTRE CANcoder)
* Arm Extension (2 Kraken X60)
* Wrist Rotation (1 Kraken X60, 1 CTRE CANcoder)
* Intake (1 Kraken X60, 1 PwF Proximity Sensor)

[CAD Model](https://cad.onshape.com/documents/4d710722a1c08d2223b9b94e/w/f9fa40dc0aa2859fc1ab7423/e/14256537db7ab81e47c7cd3b)

## Actions
* Rotate Arm to value
* Telescope Arm to value
* Rotate Hand to value
* Set rollers to Intake/Eject/None

