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
    [[nodiscard]] const Position& get_position() const;
    [[nodiscard]] const float& get_etsi_time() const;

    //void complete_position(Position pos);

    void add_message_received(MessageReceived& messageReceived);

    bool operator<(const MessageSent &rhs) const;

    bool operator>(const MessageSent &rhs) const;

    bool operator<=(const MessageSent &rhs) const;

    bool operator>=(const MessageSent &rhs) const;

    bool operator==(const MessageSent &rhs) const;

    bool operator!=(const MessageSent &rhs) const;

private:
    const float etsi_time;
    const Position position;
    std::map<long, MessageReceived*> message_received_;
};


#endif //CSV_HANDLER_MESSAGESENT_H
