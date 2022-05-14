//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_POSITION_H
#define CSV_HANDLER_POSITION_H


class Position {
public:
    //Position();
    Position(float simulation_time, float x, float y, float latitude, float longitude);
    const float& get_x() const;
    const float& get_y() const;
    const float& get_latitude() const;
    const float& get_longitude() const;
    const float& get_simulation_time() const;
    bool operator<(const Position &rhs) const;
    bool operator>(const Position &rhs) const;
    bool operator<=(const Position &rhs) const;
    bool operator>=(const Position &rhs) const;
private:
    float simulation_time;
    float x;
    float y;
    float latitude;
    float longitude;
};


#endif //CSV_HANDLER_POSITION_H
