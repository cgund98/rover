#!/bin/bash

export ROS_IP=$(hostname -I) #Set ROS_IP to the IP of this computer

MASTER_IP=192.168.1.149 #IP of the pi/master node
export ROS_MASTER_URI=http://${MASTER_IP}:11311

python key_teleop.py
