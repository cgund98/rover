#!/bin/bash

export ROS_IP=$(hostname -I) #Set to ip of this machine

MASTER_IP=$(hostname -I) #Current ip of the pi

export ROS_MASTER_URI=http://${MASTER_IP}:11311

tmux new -d -s roscore 'roscore' #Start roscore in tmux terminal
#roscore &
sleep 8
roslaunch raspicam_node camerav1_1280x720.launch #Start camera node
