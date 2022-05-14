//
// Created by jordimarias on 5/11/22.
//

#include "Vehicle.h"
#include <functional>


MessageSent Vehicle::empty_message_sent(0, Position(0,0,0,0,0,0,0,0,0));

Vehicle::Vehicle(int station_i) : station_id(station_i) {
}

MessageSent& Vehicle::create_message_sent(Position position, float etsi_time) {
    messages_sent.insert(messages_sent.end(),MessageSent(etsi_time, position));
    return messages_sent.back();
}

MessageReceived& Vehicle::create_message_received(float simulation_time, int source_station_id, int origin_station_id){
    messages_received.insert(messages_received.end(), MessageReceived(simulation_time, source_station_id,origin_station_id));
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
    for (MessageSent& messageSent : messages_sent)
    {
        if (messageSent.get_position() == position){
            messageSent.complete_position(position);
        }
    }
    real_positions.insert(real_positions.end(), position);
}

const int& Vehicle::get_station_id() const{
    return station_id;
}

void Vehicle::sort_data() {
    messages_sent.sort();
    messages_received.sort();
    real_positions.sort();
}

std::list<const MessageReceived*> Vehicle::get_messages_received_from(const int& station_id) const{
    std::list<const MessageReceived*> to_return;
    for(const MessageReceived& message_received : messages_received){
        if (message_received.get_origin_station_id() == station_id){
            to_return.push_back(&message_received);
        }
    }
    return to_return;
}

const std::list<Position>& Vehicle::get_positions() const{
    return real_positions;
}
