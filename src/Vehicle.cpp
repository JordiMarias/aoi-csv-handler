//
// Created by jordimarias on 5/11/22.
//

#include "Vehicle.h"

MessageSent Vehicle::empty_message_sent(0, Position(0,0,0,0,0));

Vehicle::Vehicle(int station_id) : station_id(station_id) {
}

MessageSent& Vehicle::create_message_sent(Position position, float etsi_time) {
    messages_sent.insert(messages_sent.end(),MessageSent(etsi_time, position));
    return messages_sent.back();
}

MessageReceived& Vehicle::create_message_received(float simulation_time, int origin_station_id){
    messages_received.insert(messages_received.end(), MessageReceived(simulation_time, origin_station_id));
    return messages_received.back();
}

MessageSent& Vehicle::get_message_sent(const Position& position, const float& sent_etsi_time){
    const float& p_latitude = position.get_latitude();
    const float& p_longitude = position.get_longitude();
    for(MessageSent& messageSent : messages_sent){
        if (p_latitude==messageSent.get_position().get_latitude() &&
            p_longitude==messageSent.get_position().get_longitude() &&
            sent_etsi_time == messageSent.get_etsi_time()
        ){
            return messageSent;
        }
    }
    return empty_message_sent;
}

void Vehicle::add_real_position(Position position) {
    real_positions.insert(real_positions.end(), position);
}
