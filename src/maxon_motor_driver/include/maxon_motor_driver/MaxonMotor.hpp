#ifndef MAXONMOTOR_HPP
#define MAXONMOTOR_HPP

#include <string>
#include "maxon_epos/EposManager.hpp"

class MaxonMotor
{
    private:
        double _Tick2Deg;
        double _Deg2Tick;  
        int _position;
        int _velocity;
        int _current;

        EposManager _epos_manager;
        std::string _motor_name;        // name for the controlled motor
        std::string _EposModel;
        std::string _protocol_stack;
        std::string _interface;
        std::string _port;
        int _baudrate;
        int _timeout;
        std::string _control_mode;
        int _encoder_type;
        int _encoder_resolution;
        int _gear_ratio;
        bool _encoder_inverted_polarity;
        int _max_qc;
        int TickPerRound;               // number of total ticks per round
        int _home_qc;                   // home position of the motor in ticks

    public:
        MaxonMotor(std::string motor_namemotor_name);
        bool init();                // initialize the epos controller for the motor
        double read();              // returns the current position or velocity based on the control type

        void write(double value);
        bool set_velocity(double velocity);
        bool set_state(int state);
        void setZero();
        void start();
        void stop();


};

#endif // MAXONMOTOR_HPP