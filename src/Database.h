//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_DATABASE_H
#define CSV_HANDLER_DATABASE_H

#include <map>
#include "Vehicle.h"

class Database {
public:
    Database();
    Vehicle& create_vehicle(const int& station_id);
    Vehicle& get_vehicle(const int& station_id);
    void sort_data();
    std::map<int, std::list<int>> make_pairs();

private:
    std::map<int, Vehicle> vehicles_;
};


#endif //CSV_HANDLER_DATABASE_H
