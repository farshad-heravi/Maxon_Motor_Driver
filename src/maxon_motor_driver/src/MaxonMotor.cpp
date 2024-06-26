#include "MaxonMotor.hpp"
#include <iostream>

MaxonMotor::MaxonMotor(std::string motor_name) : _motor_name(motor_name)
{
    // information for Maxon motor model ,,,
    _EposModel = "EPOS4";
    _protocol_stack = "MAXON SERIAL V2";
    _interface = "USB";
    _port = "USB0";
    _baudrate = 0;
    _timeout = 0;
    _encoder_type = 1;                          // 1 | 2
    _control_mode = "profile_position";         // profile_position | profile_velocity
    _encoder_resolution = 4096;
    _encoder_inverted_polarity = true;          // true | false
    _gear_ratio = 18;                           // takes into account the ratio between the encoder shaft and output shaft

    _Tick2Deg = _encoder_resolution / 360.0;
    _Deg2Tick = 1.0 / _Tick2Deg;
}

double MaxonMotor::read()
{
    std::vector<double> new_read = _epos_manager.read();
    _position = new_read[0];
    _velocity = new_read[1];
    _current = new_read[2];

    if (_control_mode == "profile_position"){
        return _position * _Tick2Deg;
    } else if (_control_mode == "profile_velocity"){
        return _velocity * _Tick2Deg;
    }
    std::cout << "Not Valid Controller has been set!" << std::endl;
    return 0;
}

bool MaxonMotor::init()
{
    _epos_manager = EposManager( _EposModel, _motor_name, _protocol_stack, _interface, _port, _baudrate, _timeout,
        _encoder_type, _encoder_resolution, _gear_ratio, _encoder_inverted_polarity, _control_mode );
    if (!_epos_manager.init())
    {
        std::cout << "Failed to initialize EposManager" << std::endl;
        return false;
    }

    std::cout << "Maxon Controller Initialized successfully." << std::endl;
    return true;
}

/*
* @param value would be position (in profile_position active mode) or velocity (in profile_velocity) in Deg or Deg/s
*/
void MaxonMotor::write(double value)
{
    std::vector<double> command = {0.0, 0.0, 0.0};
    if (_control_mode == "profile_position"){
        command[0] = value * _Deg2Tick;
    } else if (_control_mode == "profile_velocity"){
        command[1] = value * _Deg2Tick;
    }
    _epos_manager.write(command);
}


bool MaxonMotor::set_velocity(double velocity)
{
    int velocity_tick = (int) (velocity * _Deg2Tick);
    _epos_manager.set_velocity(velocity_tick);
    return true;
}

bool MaxonMotor::set_state(int state)
{
    return true;
    // TODO
}