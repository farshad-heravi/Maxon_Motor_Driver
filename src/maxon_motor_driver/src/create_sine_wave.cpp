#include "iostream"
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <cmath>

using namespace std;


int main(int argc, char** argv)
{
    ros::init(argc, argv, "sine_wave_generator");
    ros::NodeHandle nh;
    ros::Rate sleep_rate(100);

    ros::Publisher pub = nh.advertise<sensor_msgs::JointState>("/maxon_command", 5);
    
    ros::AsyncSpinner spinner(1);
    spinner.start();

    double start_time = ros::Time::now().nsec;
    double freq = 0.5;

    while (ros::ok()) {
        sensor_msgs::JointState msg;
        msg.header.stamp = ros::Time::now();
        msg.position = {5 * sin( freq * 2 * M_PI * (ros::Time::now().nsec - start_time) * 1e-9), 0, 0};
        pub.publish(msg);

        sleep_rate.sleep();
    }
    spinner.stop();
    return 0;
}