//
// Created by jordimarias on 5/11/22.
//

#include "MessageSent.h"

//MessageSent::MessageSent(){}
MessageSent::MessageSent(float etsi_t, Position pos) :
        position(pos), etsi_time(etsi_t){}

const Position& MessageSent::get_position() const{
    return position;
}

const float& MessageSent::get_etsi_time() const{
    return etsi_time;
}

bool MessageSent::operator<(const MessageSent &rhs) const {
    return position < rhs.position;
}

bool MessageSent::operator>(const MessageSent &rhs) const {
    return rhs < *this;
}

bool MessageSent::operator<=(const MessageSent &rhs) const {
    return !(rhs < *this);
}

bool MessageSent::operator>=(const MessageSent &rhs) const {
    return !(*this < rhs);
}
