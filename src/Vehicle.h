//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_VEHICLE_H
#define CSV_HANDLER_VEHICLE_H

#include <list>
#include "MessageSent.h"
#include "MessageReceived.h"

class Vehicle {
public:
    Vehicle(int station_id);
    MessageSent& create_message_sent(Position position, float etsi_time);
    MessageReceived& create_message_received(float simulation_time, int origin_station_id);
    void add_real_position(Position position);

    MessageSent& get_message_sent(const Position& position, const float& sent_etsi_time);

private:
    static MessageSent empty_message_sent;
    int station_id;
    std::list<MessageSent> messages_sent;
    std::list<MessageReceived> messages_received;
    std::list<Position> real_positions;
};


#endif //CSV_HANDLER_VEHICLE_H
