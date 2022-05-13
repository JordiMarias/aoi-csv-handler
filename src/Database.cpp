//
// Created by jordimarias on 5/11/22.
//

#include "Database.h"

Database::Database(): vehicles_() {

}

Vehicle &Database::create_vehicle(const int &station_id) {
    if (vehicles_.find(station_id) == vehicles_.end()) {
        vehicles_.insert(std::make_pair(station_id, Vehicle(station_id)));
    }
    return vehicles_[station_id];
}

Vehicle &Database::get_vehicle(const int &station_id) {
    if (vehicles_.find(station_id) != vehicles_.end()) {
        return vehicles_[station_id];
    }
    return create_vehicle(station_id);
}