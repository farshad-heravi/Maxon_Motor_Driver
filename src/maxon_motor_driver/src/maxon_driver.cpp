#include "MaxonMotor.cpp"
#include "iostream"

using namespace std;

int main()
{
    auto motor1 = MaxonMotor("motor1");


    // read motor position/velocity/current
    cout << motor1.read() << endl;

    // write to motor
    // command = 10.0;     // go to 10 deg position | rotation with 10 Deg/s velocity
    double command = 10.0;
    motor1.write(command);

    return 0;
}