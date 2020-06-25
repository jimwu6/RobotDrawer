# RobotDrawer
Robot built with Arduino which can draw various shapes on a rotating base. Frame and additional components (e.g. base) are all handmade from wood, cardboard, and duct tape. Made for TER4M1 summative assignment.

# How It Functions
The robot has a linear x-axis which holds the writing device (i.e. a Sharpie) which draws onto a rotating base with a sheet of paper on top, like a polar plotting machine. The rotating base is very accurate, however due to the nature of the parts, the linear axis is not completely accurate.

## Linear Axis
The linear axis is a long piece of wood that is rotated on one end by a stepper motor, but because of the quality of the wood and the setup, one direction takes less force than the other and this cannot be easily corrected with the materials. The writing utensil is lifted up and down using a servo motor.

## Rotating Base
The base runs off a stepper motor with stacked pieces of cardboard elevated on the shaft of the motor. A piece of paper is placed on top, secured with masking tape which can be easily replaced. Due to the nature of the stepper motor, the precision and accuracy of the base is very high.

# Components
* Arduino Mega
* Stepper Motors
* Servo Motors
* LEDs, buttons
* Sensors (temperature, potentiometer, photoresistor)

# Demos
[Link to video demos](https://drive.google.com/drive/folders/10LKjf0HPIh4MJo_LpWxrhHgVhxMwzTxT)

Demos include pre-programmed shapes (e.g. line, circles, spirals) and shapes that can be modified using the different sensors attached. To pick which action is selected, there is a "control panel" of buttons on the breadboard which is used to connect the different components of the robot.
