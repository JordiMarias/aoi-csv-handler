//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_POSITION_H
#define CSV_HANDLER_POSITION_H


class Position {
public:
    //Position();
    Position(float simulation_time, float x, float y, float latitude, float longitude,
             float speed_x, float speed_y, float acceleration_x, float acceleration_y);
    Position(const Position& position);
    Position operator=(const Position& other);

    const float& get_x() const;
    const float& get_y() const;
    const float& get_latitude() const;
    const float& get_longitude() const;
    const float& get_simulation_time() const;
    const float& get_speed_x() const;
    const float& get_speed_y() const;
    const float& get_acceleration_x() const;
    const float& get_acceleration_y() const;

    bool operator==(const Position &rhs) const;
    bool operator!=(const Position &rhs) const;
    bool operator<(const Position &rhs) const;
    bool operator>(const Position &rhs) const;
    bool operator<=(const Position &rhs) const;
    bool operator>=(const Position &rhs) const;
private:
    const float simulation_time;
    const float x;
    const float y;
    const float latitude;
    const float longitude;
    const float speed_x;
    const float speed_y;
    const float acceleration_x;
    const float acceleration_y;
};


#endif //CSV_HANDLER_POSITION_H
