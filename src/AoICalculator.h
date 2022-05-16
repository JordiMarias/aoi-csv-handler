//
// Created by jordimarias on 5/14/22.
//

#ifndef CSV_HANDLER_AOICALCULATOR_H
#define CSV_HANDLER_AOICALCULATOR_H

#include <map>
#include <fstream>
#include "Vehicle.h"
#include "Database.h"
class AoICalculator {
public:
    AoICalculator();
    std::map<float, float> compute_aoi(const Vehicle& vehicle_a, const Vehicle& vehicle_b);
    std::map<float, float> compute_paoi(const Vehicle& vehicle_a, const Vehicle& vehicle_b);
    void compute_and_dump_values(Database& db, const std::string& folder);
private:
    Position predict_position(float timepoint, const Position& position);
    float compute_distance(const Position& pos1, const Position& pos2);
    float calc_gps_distance(float latitud1, float longitud1, float latitud2, float longitud2);
    void dump_values(const std::map<float,float>& values, const std::string& file_name);
};


#endif //CSV_HANDLER_AOICALCULATOR_H
