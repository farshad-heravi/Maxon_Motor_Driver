#include "MaxonMotor.cpp"
#include "iostream"
#include <unistd.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <cmath>

using namespace std;
MaxonMotor motor1 = MaxonMotor("motor1");

void motor_command_callback(const sensor_msgs::JointStateConstPtr& msg)
{
    motor1.write(msg->position[0]);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "maxon_node");
    ros::NodeHandle nh;
    ros::Rate sleep_rate(40);

    ros::Publisher pub = nh.advertise<sensor_msgs::JointState>("/maxon_state", 5);
    ros::Subscriber subs = nh.subscribe("/maxon_command", 5, motor_command_callback);

    motor1 = MaxonMotor("motor1");

    motor1.init();
    double readings;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    double start_time = ros::Time::now().nsec;

    while (ros::ok()) {
        readings = motor1.read();
        sensor_msgs::JointState msg;
        msg.header.stamp = ros::Time::now();
        msg.position = {readings, 0, 0};
        pub.publish(msg);

        sleep_rate.sleep();
    }
        motor1.write( 360 );
    spinner.stop();


    return 0;
}