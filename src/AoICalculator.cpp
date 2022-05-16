//
// Created by jordimarias on 5/14/22.
//

#include "AoICalculator.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#define PI 3.14159265358979323846
#define RADIO_TERRESTRE 6372797.56085
#define GRADOS_RADIANES PI / 180

AoICalculator::AoICalculator() {}

std::map<float, float> AoICalculator::compute_aoi(const Vehicle& vehicle_a, const Vehicle& vehicle_b){
    std::map<float, float> to_return;
    std::list<const MessageReceived*> messages_recv = vehicle_b.get_messages_received_from(vehicle_a.get_station_id());
    if (messages_recv.size()>2){
        float starting_point = messages_recv.front()->get_simulation_time();
        float ending_point = messages_recv.back()->get_simulation_time();
        starting_point = std::round(starting_point*100)/100+0.1;
        float timepoint = starting_point;
        std::list<const MessageReceived*>::iterator it =messages_recv.begin();
        std::list<const MessageReceived*>::iterator itend =messages_recv.end();
        --itend;
        while (timepoint<ending_point && it != itend){
            const MessageReceived* current_message = *it;
            ++it;
            const MessageReceived* new_message = *it;
            --it;
            if(timepoint<new_message->get_simulation_time()){
                float aoi = timepoint-current_message->get_message_send().get_position().get_simulation_time();
                to_return.insert(std::make_pair(timepoint, aoi));
            }else {
                float aoi = timepoint - new_message->get_message_send().get_position().get_simulation_time();
                to_return.insert(std::make_pair(timepoint, aoi));
                ++it;
            }
            timepoint += 0.1;
        }
    }
    return to_return;
}

std::map<float, float> AoICalculator::compute_paoi(const Vehicle& vehicle_a, const Vehicle& vehicle_b){
    std::map<float, float> to_return;
    std::list<const MessageReceived*> messages_recv = vehicle_b.get_messages_received_from(vehicle_a.get_station_id());
    if (messages_recv.size()>2){
        for (const MessageReceived* m : messages_recv){
            std::cout << m->get_simulation_time() << std::endl;
            std::cout << "Expected origin" << vehicle_a.get_station_id() << std::endl;
            std::cout << "origin station " << m->get_origin_station_id() << std::endl;
            std::cout << "destiny station " << m->get_destiny_station_id() << std::endl;
        }
        float starting_point = messages_recv.front()->get_simulation_time();
        starting_point = std::round(starting_point*100)/100+0.1;
        const std::list<Position>& positions = vehicle_a.get_positions();
        std::list<Position>::const_iterator pos_iterator = positions.cbegin();
        float temp_sim_time = 0;
        while (temp_sim_time<starting_point && pos_iterator!=positions.cend()){
            ++pos_iterator;
            temp_sim_time =(*pos_iterator).get_simulation_time();
        }
        std::cout << "Positions iterator starting point " << pos_iterator->get_simulation_time() << std::endl;

        std::list<const MessageReceived*>::iterator it =messages_recv.begin();
        std::cout << "Messages iterator starting point" << (*it)->get_simulation_time() << std::endl;
        while((*it)->get_simulation_time()<pos_iterator->get_simulation_time() && it != messages_recv.end()){
            ++it;
        }
        --it;
        std::cout << "Messages iterator fixed starting point" << (*it)->get_simulation_time() << std::endl;
        std::list<const MessageReceived*>::iterator itend =messages_recv.end();
        --itend;
        while ( std::next(pos_iterator, 2) != positions.end() && it != itend){
            const MessageReceived* current_message = *it;
            ++it;
            const MessageReceived* new_message = *it;
            --it;
            const Position& actual_postition = *pos_iterator;
            std::cout << "New computation" << std::endl;
            std::cout << "Position time" << actual_postition.get_simulation_time() << std::endl;
            if(pos_iterator->get_simulation_time()<new_message->get_simulation_time()){
                if (it != messages_recv.begin()) {
                    --it;
                    std::cout << "Packet time (previous): " << (*it)->get_simulation_time() << std::endl;
                    ++it;
                }
                std::cout << "Packet time (current): "<< current_message->get_simulation_time() << std::endl;
                std::cout << "Packet time (post): "<< new_message->get_simulation_time() << std::endl;
                const Position& sent_position = current_message->get_message_send().get_position();
                Position predicted = predict_position(actual_postition.get_simulation_time(), sent_position);
                float paoi = compute_distance(actual_postition, predicted);
                to_return.insert(std::make_pair(pos_iterator->get_simulation_time(), paoi));
            }else {
                std::cout << "Packet time: "<< current_message->get_simulation_time();
                const Position& sent_position = new_message->get_message_send().get_position();
                Position predicted = predict_position(actual_postition.get_simulation_time(), sent_position);
                float paoi = compute_distance(actual_postition, predicted);
                to_return.insert(std::make_pair(pos_iterator->get_simulation_time(), paoi));
                ++it;
            }
            ++pos_iterator;
        }
    }
    return to_return;
}

Position AoICalculator::predict_position(float timepoint, const Position& position){
    float t = timepoint-position.get_simulation_time();
    std::cout << "time difference: "<< t << std::endl;
    float speed_x = position.get_speed_x()+t*position.get_acceleration_x();
    float speed_y = position.get_speed_y()+t*position.get_acceleration_y();
    float x = position.get_x()+position.get_speed_x()*t+0.5*position.get_acceleration_x()*t*t;
    float y = position.get_y()+position.get_speed_y()*t+0.5*position.get_acceleration_y()*t*t;
    std::cout << "Position: " << std::endl;
    std::cout << "X: "<< x << std::endl;
    std::cout << "Y: "<< y << std::endl;
    return Position(timepoint, x, y, 0, 0, speed_x, speed_y, position.get_acceleration_x(), position.get_acceleration_y());
}

float AoICalculator::compute_distance(const Position& pos1, const Position& pos2) {
    std::cout << "Position 1" << std::endl;
    std::cout << "X = " << pos1.get_x() << std::endl;
    std::cout << "Y = " << pos1.get_y() << std::endl;
    std::cout << "Position 2" << std::endl;
    std::cout << "X = " << pos2.get_x() << std::endl;
    std::cout << "Y = " << pos2.get_y() << std::endl;
    float x_to_2 = std::pow(pos1.get_x()-pos2.get_x(),2.0);
    float y_to_2 = std::pow(pos1.get_y()-pos2.get_y(),2.0);
    float result = std::sqrt(x_to_2+y_to_2);
    std::cout << result << std::endl;
    return result;
}


void AoICalculator::compute_and_dump_values(Database& db, const std::string& folder){
    std::map<long, std::list<long>> pairs = db.make_pairs();
    for (const auto& vehicles : pairs){
        for(const long& vehicles2 : vehicles.second){
            Vehicle& vehicle_a = db.get_vehicle(vehicles.first);
            Vehicle& vehicle_b = db.get_vehicle(vehicles2);
            std::map<float, float> aoi = compute_aoi(vehicle_a, vehicle_b);
            std::map<float, float> paoi = compute_paoi(vehicle_a, vehicle_b);
            std::string aoi_file = folder+"/"+std::to_string(vehicles.first)+"_"+std::to_string(vehicles2)+"_aoi.csv";
            std::string paoi_file = folder+"/"+std::to_string(vehicles.first)+"_"+std::to_string(vehicles2)+"_paoi.csv";
            std::cout << "Dumping to: " << aoi_file << std::endl;
            std::cout << "Dumping to: " << paoi_file << std::endl;
            dump_values(aoi, aoi_file);
            dump_values(paoi, paoi_file);
        }
    }
}

void AoICalculator::dump_values(const std::map<float,float>& values, const std::string& file_name){
    std::fstream file_stream;
    file_stream.open(file_name, std::fstream::in | std::fstream::out | std::fstream::app);
    if(file_stream.is_open()){
        file_stream << "Time,AoI" << std::endl;
        for (const auto& line : values){
            file_stream << line.first << "," << line.second << std::endl;
        }
    }
    file_stream.close();

}


float AoICalculator::calc_gps_distance(float latitud1, float longitud1, float latitud2, float longitud2){
    using namespace std;
    double haversine;
    double temp;
    double distancia_puntos;
    std::cout << latitud1 << " " << longitud1 << " " << latitud2 << " " << longitud2 << std::endl;
    latitud1  = latitud1  * GRADOS_RADIANES;
    longitud1 = longitud1 * GRADOS_RADIANES;
    latitud2  = latitud2  * GRADOS_RADIANES;
    longitud2 = longitud2 * GRADOS_RADIANES;

    haversine = (pow(sin((1.0 / 2) * (latitud2 - latitud1)), 2)) + ((cos(latitud1)) * (cos(latitud2)) * (pow(sin((1.0 / 2) * (longitud2 - longitud1)), 2)));
    temp = 2 * asin(min(1.0, sqrt(haversine)));
    distancia_puntos = RADIO_TERRESTRE * temp;

    return distancia_puntos;
}
