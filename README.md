# Maxon_Motor_Driver
a Cpp-based driver for position and velocity control of maxon motors using EPOS controllers, integrated with ROS1.

The implemented node `maxon_node` position controls an EC45 flat maxon motor having a hall sensor, as shown in the figure below.

<img style="float:right;" src="https://github.com/farshad-heravi/Maxon_Motor_Driver/blob/master/media/ec45_maxon_motor.jpg?raw=true" width="50%"/>

The position command is published on `/maxon_command` topic, and the actual position of the motor is being published in `/maxon_state` topic. Below is a simple trial of sending severla position command via `/maxon_command` topic.

https://github.com/farshad-heravi/Maxon_Motor_Driver/assets/72828518/d33042a0-6287-46eb-8bc2-7ab2e4c41996
