//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_MESSAGESENT_H
#define CSV_HANDLER_MESSAGESENT_H

#include "position.h"
#include <map>

class MessageReceived;

class MessageSent {
public:
    MessageSent(float etsi_t, Position pos);
    const Position& get_position() const;
    const float& get_etsi_time() const;
    void complete_position(Position pos);
    void add_message_received(MessageReceived& messageReceived);
    bool operator<(const MessageSent &rhs) const;

    bool operator>(const MessageSent &rhs) const;

    bool operator<=(const MessageSent &rhs) const;

    bool operator>=(const MessageSent &rhs) const;

private:
    float etsi_time;
    Position position;
    std::map<int, MessageReceived*> message_received_;
};


#endif //CSV_HANDLER_MESSAGESENT_H
