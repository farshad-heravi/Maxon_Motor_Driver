#include "MaxonMotor.hpp"
#include <iostream>
#include <unistd.h>

MaxonMotor::MaxonMotor(std::string motor_name) : _motor_name(motor_name), _home_qc(0)
{
    // information for Maxon motor model ,,,
    _EposModel = "EPOS4";
    _protocol_stack = "MAXON SERIAL V2";
    _interface = "USB";
    _port = "USB0";
    _baudrate = 1000000;
    _timeout = 500; // ms
    _encoder_type = 2;                          // 1 | 2
    _control_mode = "profile_position";         // profile_position | profile_velocity
    _encoder_resolution = 2048;
    _encoder_inverted_polarity = false;          // true | false
    _gear_ratio = 18;                           // takes into account the ratio between the encoder shaft and output shaft

    // _max_qc = 4 * _encoder_resolution * _gear_ratio;
    // hard code for Maxon Motor 706863
    _max_qc = 144700;
    _Deg2Tick = _max_qc / 360.0;
    _Tick2Deg = 1.0 / _Deg2Tick;
}


void MaxonMotor::start()
{
    _epos_manager.start();
}

void MaxonMotor::stop()
{
    _epos_manager.stop();
}

double MaxonMotor::read()
{
    std::vector<int> new_read = _epos_manager.read();
    _position = new_read[0] - _home_qc;
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
    sleep(2);
    setZero();
    start();
    std::cout << "Maxon Controller Initialized successfully." << std::endl;
    return true;
}

void MaxonMotor::setZero()
{
    std::vector<int> new_read = _epos_manager.read();
    _home_qc = new_read[0];
}

/*
* @param value would be position (in profile_position active mode) or velocity (in profile_velocity) in Deg or Deg/s
*/
void MaxonMotor::write(double value)
{
    std::vector<int> command = {0, 0, 0};
    if (_control_mode == "profile_position"){
        command[0] = (int) (value * _Deg2Tick) + _home_qc;
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