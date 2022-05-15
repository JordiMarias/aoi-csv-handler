//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_MESSAGERECEIVED_H
#define CSV_HANDLER_MESSAGERECEIVED_H

#include "MessageSent.h"



class MessageReceived {
public:
    MessageReceived(float simulation_t, long source_station_i, long origin_station_i);
    void set_message_sent(MessageSent& message_sent);
    [[nodiscard]] const float& get_simulation_time() const;
    [[nodiscard]] const long& get_origin_station_id() const;
    [[nodiscard]] const long& get_source_station_id() const;
    [[nodiscard]] const MessageSent& get_message_send() const;
    bool operator<(const MessageReceived &rhs) const;
    bool operator>(const MessageReceived &rhs) const;
    bool operator<=(const MessageReceived &rhs) const;
    bool operator>=(const MessageReceived &rhs) const;

private:
    static MessageSent empty_message_sent;
    float simulation_time;
    long origin_station_id;
    long source_station_id;
    MessageSent& message_send;
};


#endif //CSV_HANDLER_MESSAGERECEIVED_H
