This gizmo manipulates an RGB LED in three dimensions, allowing the user to draw a light sculpture of their choosing. A camera positioned pointing at the gizmo will be taking a series of photos and compiling them together in order for the user to see the light trail. The manipulation of the LED will be done via two joy sticks - one controlling the Z axis and the other controlling the X and Y axis.

# CABLE DRIVEN PARALLEL ROBOTS

## BACKGROUND

Cable driven parallel robots are a type of parallel manipulator often used in industry to allow for movement in six degrees of freedom X, Y, Z in the cartesian coordinate system (linear transformation), and pitch, roll, yaw polar system (rotational transformation). They are typically made from powerful stepper motors with encoders to allow precision movement and tracking. Faster versions of cable driven parallel robots use DC motors with encoders to allow for faster movement of the end-effector. For this project, a similar 8 motor stepper motor system will be used to manipulate the end-effector in three dimensions.

## REVISION

For this project (due to budget limitation), it will be constructed using 28BYJ-48 5V stepper motors and ULN2003 motor driver boards. These motors are the cheapest stepper motors available online, and despite their low torque and low speed, they should still allow me to achieve the desired end result as I will be using an external camera to compile the movement. I will also not be using an external tracking camera to track movements, making my system an open-loop system - my solution to this problem will be a software algorithmic based solution to ensure all cables are kept in constant tension. 

## MATH

Inverse kinematics are potentially needed in order for accurate control over all 6 axis. However, due to the Arduino limitation in file size and computational ability, some simplifications had to be made. Going off a more positional based system, the end effector will be controlled by a more rudimentary approach to manipulate the end effector. 

# CODE

The code was written primarily in functions, and OOP was used to group hardware inputs and outputs such as the stepper motors, RBG LED and the joysticks. 

Global variables are used such as the current co-ordinate (stored as an array), and the step size of the motor - this is done to adjust the resolution of the coordinate system. 

## TIGHTENING ALGORITHM

Due to redundancy in some of the motors, if one of the motors loses tension, that tension can be brought back. This is happening when the user is not interacting with the gizmo - each motor is tightened a certain amount, which causes cables that are already taught to remain taught and ones that have slack in the cables to pick it up and increase the tension. Each motor is moved individually so that if the cable is taught, it will be unable to rotate as it will not be powerful enough to overcome the torque of the other motors on the other sides of the gizmo. This mechanism only allows loose or less tensioned cables corresponding motor to rotate.

# ELECTRONICS

The main system has 8 stepper motors with driver boards that are all connected to the Arduino, driven using PWM signals. The power consumption of each motor is high and requires 2 12V 3A power supply, and each one is used to drive 4 stepper motors. This was done so that each motor gets sufficient current and voltage preventing under-volting which prevents stuttering in the motors. The increased stuttering made the movement of the end effector less steady and causes increased vibration in the end effector. 

The 3 potentiometers are joy sticks: each one for one axis of the system X,Y,Z. These run on 5V logic and are connected to the analogue pins for input into the system.

The end effect was made into another circuit as this part moves and hence is isolated from the static components, creating an easier system for debugging. The 3 potentiometers on the left of the diagram have control over RGB values of the LED, allowing the user to make any colour of their choosing.  

# DESIGN REASONING

Increased Diameter of Shaft - Using the 3D printed spindles allows the cable to be wrapped around a larger diameter, which makes a difference as when the cable wraps around the spindle, due to the thickness of the cable, the diameter will increase. The percentage increase over the larger diameter designed will be less, causing the amount of rope to be released (calculated by the arc length for every angle the motor spins) to be more accurate. Comparing this to if the cable was wound around the motor shaft, the percentage increase would be significantly greater. 

6mm Plywood with Reinforcements at the Top and Bottom - 6mm was used compared to the 4mm plywood given that this material had too much flex to it and started bending under tension when the motors where pulling the end effector, extorting a force onto the frame. The top and bottom parts allow for reinforcements to all motors preventing any bending moments from occurring. 

Running the LED light on a Separate Circuit - This made the wiring of the system a lot easier and reduced the length of the wires. Since the LEDs RGB values are controlled by rotation of a knob, a potentiometer could be used to limit the voltage and current to each of the colours therefore allowing the user to change colours while drawing. This makes the response significantly quicker than using interrupts which prevents the motors from moving for the other user input. 
