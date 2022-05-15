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
    Vehicle& create_vehicle(const long& station_id);
    Vehicle& get_vehicle(const long& station_id);
    void sort_data();
    std::map<long, std::list<long>> make_pairs();

private:
    std::map<long, Vehicle> vehicles_;
};


#endif //CSV_HANDLER_DATABASE_H
