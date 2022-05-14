//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_MESSAGERECEIVED_H
#define CSV_HANDLER_MESSAGERECEIVED_H

#include "MessageSent.h"


class MessageReceived {
public:
    MessageReceived(float simulation_t, int origin_station_i);
    void set_message_received(MessageSent& message_sent);
    const float& get_simulation_time() const;
    const int& get_origin_station_id() const;
    bool operator<(const MessageReceived &rhs) const;
    bool operator>(const MessageReceived &rhs) const;
    bool operator<=(const MessageReceived &rhs) const;
    bool operator>=(const MessageReceived &rhs) const;

private:
    static MessageSent empty_message_sent;
    float simulation_time;
    int origin_station_id;
    MessageSent& message_send;
};


#endif //CSV_HANDLER_MESSAGERECEIVED_H
