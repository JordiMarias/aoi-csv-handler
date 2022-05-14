//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_MESSAGESENT_H
#define CSV_HANDLER_MESSAGESENT_H

#include "position.h"
#include "MessageReceived.h"
#include <map>

class MessageSent {
public:
    MessageSent(float etsi_t, Position pos);
    const Position& get_position() const;
    const float& get_etsi_time() const;

    bool operator<(const MessageSent &rhs) const;

    bool operator>(const MessageSent &rhs) const;

    bool operator<=(const MessageSent &rhs) const;

    bool operator>=(const MessageSent &rhs) const;

private:
    float etsi_time;
    Position position;
    std::map<int, MessageReceived&> message_received_;
};


#endif //CSV_HANDLER_MESSAGESENT_H
