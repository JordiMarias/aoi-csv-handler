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
    explicit Vehicle(long station_id);
    MessageSent& create_message_sent(Position position, float etsi_time);
    MessageReceived& create_message_received(float simulation_time, long destiny_station_id, long origin_station_id, MessageSent& message_sent);
    void add_real_position(Position position);
    [[nodiscard]] const long& get_station_id() const;
    MessageSent& get_message_sent(const Position& position, const float& sent_etsi_time);
    void sort_data();
    [[nodiscard]] std::list<const MessageReceived*> get_messages_received_from(const long& station_id) const;
    [[nodiscard]] const std::list<Position>& get_positions() const;
private:
    static MessageSent empty_message_sent;
    long station_id;
    std::list<MessageSent> messages_sent;
    std::list<MessageReceived> messages_received;
    std::list<Position> real_positions;
};


#endif //CSV_HANDLER_VEHICLE_H
