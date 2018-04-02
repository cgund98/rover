#!/bin/bash

source ~/catkin_ws/devel/setup.bash

export ROS_IP=$(hostname -I) #Set to ip of this machine

MASTER_IP=$(hostname -I) #Current ip of the pi

export ROS_MASTER_URI=http://${MASTER_IP}:11311

echo "Creating core node..."
tmux new -d -s roscore 'roscore' #Start roscore in tmux terminal
#roscore &
sleep 8
echo "Creating cam node..."
tmux new -d -s cam_server 'roslaunch raspicam_node camerav1_1280x720.launch' #Start camera node

echo "Creating Arduino serial node..."
tmux new -d -s arduino_serial 'rosrun rosserial_python serial_node.py /dev/ttyACM0'
