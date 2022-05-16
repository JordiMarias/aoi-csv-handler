//
// Created by jordimarias on 5/11/22.
//

#include "MessageReceived.h"



MessageReceived::MessageReceived(float simulation_t, long rename_station_i, long origin_station_i, MessageSent& message_sent):
        simulation_time(simulation_t), destiny_station_id(rename_station_i) , origin_station_id(origin_station_i), message_send(message_sent){}


const float& MessageReceived::get_simulation_time() const{
    return simulation_time;
}
const long& MessageReceived::get_origin_station_id() const{
    return origin_station_id;
}
const long& MessageReceived::get_destiny_station_id() const{
    return destiny_station_id;
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
