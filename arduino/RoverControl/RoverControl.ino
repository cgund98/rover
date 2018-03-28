
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;

Servo servo;
Servo leftDrive, rightDrive;
int leftDefaultAngle, rightDefaultAngle;

void servo_cb( const std_msgs::UInt16& cmd_msg){
  servo.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}

void tel_cb( const geometry_msgs::Twist& teleop_msg){
  servo.write(90 + teleop_msg.linear.x * 90);
  leftDrive.write(leftDefaultAngle + teleop_msg.linear.x * 90 - teleop_msg.angular.z * 90);
  rightDrive.write(rightDefaultAngle - teleop_msg.linear.x * 90 - teleop_msg.angular.z * 90);
  // digitalWrite(13, HIGH-digitalRead(13));
}

// ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);
ros::Subscriber<geometry_msgs::Twist> tel_sub("key_vel", tel_cb);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
//  nh.subscribe(sub);
  nh.subscribe(tel_sub);
  
  servo.attach(11); //attach it to pin 9
  leftDrive.attach(10);
  rightDrive.attach(9);
  
  leftDefaultAngle = 94;
  rightDefaultAngle = 94;
  
  leftDrive.write(leftDefaultAngle);
  rightDrive.write(rightDefaultAngle);
  
}

void loop(){
  nh.spinOnce();
  delay(1);
}
