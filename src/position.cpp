//
// Created by jordimarias on 5/11/22.
//

#include "position.h"
#include <iostream>
#include <cmath>

Position::Position(float simulation_time, float x, float y, float latitude, float longitude,
                   float speed_x, float speed_y, float acceleration_x, float acceleration_y): simulation_time(simulation_time),
x(x), y(y), latitude(latitude), longitude(longitude), speed_x(speed_x),
speed_y(speed_y), acceleration_x(acceleration_x), acceleration_y(acceleration_y){}

Position::Position(const Position& position) : simulation_time(position.simulation_time),
                                               x(position.x), y(position.y), latitude(position.latitude),
                                               longitude(position.longitude), speed_x(position.speed_x),
                                               speed_y(position.speed_y), acceleration_x(position.acceleration_x),
                                               acceleration_y(position.acceleration_y){}

const float& Position::get_x() const{
    return x;
}

const float& Position::get_y() const{
    return y;
}

const float& Position::get_speed_x() const{
    return speed_x;
}

const float& Position::get_speed_y() const{
    return speed_y;
}

const float& Position::get_acceleration_x() const{
    return acceleration_x;
}

const float& Position::get_acceleration_y() const{
    return acceleration_y;
}


const float& Position::get_latitude() const{
    return latitude;
}

const float& Position::get_longitude() const{
    return longitude;
}

const float& Position::get_simulation_time() const{
    return simulation_time;
}

bool Position::operator<(const Position &rhs) const {
    if (simulation_time < rhs.simulation_time)
        return true;
    return false;
}

bool Position::operator>(const Position &rhs) const {
    return rhs < *this;
}

bool Position::operator<=(const Position &rhs) const {
    return !(rhs < *this);
}

bool Position::operator>=(const Position &rhs) const {
    return !(*this < rhs);
}

bool Position::operator==(const Position &rhs) const {
    std::cout << "using position operator==" << std::endl;
    int simulation_time_int = (int)(simulation_time*std::pow(10, 5));
    int rhs_simulation_time_int = (int)(rhs.simulation_time*std::pow(10, 5));
    std::cout << simulation_time_int << "==" << rhs_simulation_time_int << " "<< (simulation_time_int == rhs_simulation_time_int)<< std::endl;
    std::cout << (int)latitude << "==" << (int)rhs.latitude << " "<< ((int)latitude == (int)rhs.latitude)<< std::endl;
    std::cout << (int)longitude << "==" << (int)rhs.longitude << " "<< ((int)longitude == (int)rhs.longitude)<< std::endl;
    return simulation_time_int == rhs_simulation_time_int &&
            (int)latitude == (int)rhs.latitude &&
            (int)longitude == (int)rhs.longitude;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}

Position Position::operator=(const Position& other){
    return Position(other.simulation_time, other.x, other.y, other.latitude, other.longitude, other.speed_x, other.speed_y, other.acceleration_x, other.acceleration_y);
}
