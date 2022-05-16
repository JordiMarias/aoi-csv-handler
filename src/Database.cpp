//
// Created by jordimarias on 5/11/22.
//

#include "Database.h"
#include <iostream>

Database::Database(): vehicles_() {}

Vehicle &Database::create_vehicle(const long &station_id) {
    if (vehicles_.find(station_id) == vehicles_.end()) {
        vehicles_.insert(std::make_pair(station_id, Vehicle(station_id)));
    }
    Vehicle& to_return = vehicles_.at(station_id);
    return to_return;
}

Vehicle &Database::get_vehicle(const long &station_id) {
    if (vehicles_.find(station_id) != vehicles_.end()) {
        return vehicles_.at(station_id);
    }
    return create_vehicle(station_id);
}

void Database::sort_data() {
    std::cout << vehicles_.size() << std::endl;
    for (auto& veh_pair : vehicles_){
        veh_pair.second.sort_data();
    }
}

std::map<long, std::list<long>> Database::make_pairs(){
    std::map<long, std::list<long>> to_return;
    for (const auto& vehicle : vehicles_){
        std::list<long> related_stations;
        for (const auto& vehicle2 : vehicles_){
            if (vehicle2.first != vehicle.first){
                related_stations.push_back(vehicle2.first);
            }
        }
        to_return.insert(std::make_pair(vehicle.first,related_stations));
    }
    return to_return;
}