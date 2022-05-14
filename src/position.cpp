//
// Created by jordimarias on 5/11/22.
//

#include "position.h"

//Position::Position() {}

Position::Position(float simulation_time, float x, float y, float latitude, float longitude): simulation_time(simulation_time),
x(x), y(y), latitude(latitude), longitude(longitude){}

const float& Position::get_x() const{
    return x;
}

const float& Position::get_y() const{
    return y;
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
