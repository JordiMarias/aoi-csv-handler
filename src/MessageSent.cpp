//
// Created by jordimarias on 5/11/22.
//

#include "MessageSent.h"
#include "MessageReceived.h"
#include <iostream>

MessageSent::MessageSent(float etsi_t, Position pos) :
        position(pos), etsi_time(etsi_t) {}

const Position &MessageSent::get_position() const {
    return position;
}

const float &MessageSent::get_etsi_time() const {
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

void MessageSent::complete_position(Position pos) {
    std::cout << "In complete postion!" << std::endl;
    if (position.get_x() == pos.get_x() &&
        position.get_y() == pos.get_y() &&
        position.get_latitude() == pos.get_latitude() &&
        position.get_longitude() == pos.get_longitude() &&
        position.get_simulation_time() == pos.get_simulation_time()) {
        std::cout << "Renewing position" << std::endl;
        position = pos;
    }
}

void MessageSent::add_message_received(MessageReceived &messageReceived) {
    message_received_.insert(std::make_pair(messageReceived.get_destiny_station_id(), &messageReceived));
}