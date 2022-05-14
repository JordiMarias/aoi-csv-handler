//
// Created by jordimarias on 5/11/22.
//

#include "MessageReceived.h"


MessageSent MessageReceived::empty_message_sent(0, Position(0,0,0,0,0,0,0,0,0));

MessageReceived::MessageReceived(float simulation_t, int source_station_i, int origin_station_i):
simulation_time(simulation_t), source_station_id(source_station_i) ,origin_station_id(origin_station_i), message_send(empty_message_sent){}

void MessageReceived::set_message_sent(MessageSent &message_s) {
    message_send = message_s;
}

const float& MessageReceived::get_simulation_time() const{
    return simulation_time;
}
const int& MessageReceived::get_origin_station_id() const{
    return origin_station_id;
}
const int& MessageReceived::get_source_station_id() const{
    return source_station_id;
}

bool MessageReceived::operator<(const MessageReceived &rhs) const {
    return simulation_time < rhs.simulation_time;
}

bool MessageReceived::operator>(const MessageReceived &rhs) const {
    return rhs < *this;
}

bool MessageReceived::operator<=(const MessageReceived &rhs) const {
    return !(rhs < *this);
}

bool MessageReceived::operator>=(const MessageReceived &rhs) const {
    return !(*this < rhs);
}

const MessageSent& MessageReceived::get_message_send() const{
    return message_send;
}
