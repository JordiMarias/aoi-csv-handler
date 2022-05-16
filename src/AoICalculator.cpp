//
// Created by jordimarias on 5/14/22.
//

#include "AoICalculator.h"
#include <cmath>
#include <iostream>


AoICalculator::AoICalculator() {}

std::map<float, float> AoICalculator::compute_aoi(const Vehicle& vehicle_a, const Vehicle& vehicle_b){
    std::cout << "Starting to compute the AoI" << std::endl;
    std::map<float, float> to_return;
    std::list<const MessageReceived*> messages_recv = vehicle_b.get_messages_received_from(vehicle_a.get_station_id());
    std::cout << "Message Received size: " << messages_recv.size() << std::endl;
    if (messages_recv.size()>2){
        float starting_point = messages_recv.front()->get_simulation_time();
        float ending_point = messages_recv.back()->get_simulation_time();
        starting_point = std::round(starting_point*100)/100+0.1;
        float timepoint = starting_point;
        std::cout << "Starting point: " << starting_point << std::endl;
        std::cout << "Ending point: " << ending_point << std::endl;
        std::list<const MessageReceived*>::iterator it =messages_recv.begin();
        while (timepoint<ending_point){
            const MessageReceived* current_message = *it;
            ++it;
            const MessageReceived* new_message = *it;
            --it;
            if(timepoint<new_message->get_simulation_time()){
                float aoi = timepoint-current_message->get_message_send().get_position().get_simulation_time();
                std::cout << "Computed AoI Point: "<< aoi << std::endl;
                to_return.insert(std::make_pair(timepoint, aoi));
            }else {
                float aoi = timepoint - new_message->get_message_send().get_position().get_simulation_time();
                std::cout << "Computed AoI Point: "<< aoi << std::endl;
                to_return.insert(std::make_pair(timepoint, aoi));
                ++it;
                if (it == messages_recv.end()) {
                    --it;
                }
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
        float starting_point = messages_recv.front()->get_simulation_time();
        float ending_point = messages_recv.back()->get_simulation_time();
        starting_point = std::round(starting_point*100)/100+0.1;
        const std::list<Position>& positions = vehicle_a.get_positions();
        std::list<Position>::iterator pos_iterator;
        while ((*pos_iterator).get_simulation_time()<starting_point){
            ++pos_iterator;
        }
        //starting_point = pos_iterator->get_simulation_time();
        //float timepoint = starting_point;
        std::list<const MessageReceived*>::iterator it =messages_recv.begin();
        while (pos_iterator->get_simulation_time()<ending_point){
            const MessageReceived* current_message = *it;
            ++it;
            const MessageReceived* new_message = *it;
            --it;
            if(pos_iterator->get_simulation_time()<new_message->get_simulation_time()){
                const Position& sent_position = current_message->get_message_send().get_position();
                const Position& actual_postition = *pos_iterator;
                float aoi = actual_postition.get_simulation_time()-sent_position.get_simulation_time();
                Position predicted = predict_position(aoi, sent_position);
                float paoi = compute_distance(actual_postition, predicted);
                to_return.insert(std::make_pair(pos_iterator->get_simulation_time(), paoi));
            }else {
                const Position& sent_position = new_message->get_message_send().get_position();
                const Position& actual_postition = *pos_iterator;
                float aoi = actual_postition.get_simulation_time()-sent_position.get_simulation_time();
                Position predicted = predict_position(aoi, sent_position);
                float paoi = compute_distance(actual_postition, predicted);
                to_return.insert(std::make_pair(pos_iterator->get_simulation_time(), paoi));
                ++it;
                if (it == messages_recv.end()) {
                    --it;
                }
            }
            ++pos_iterator;
        }
    }
    return to_return;
}

Position AoICalculator::predict_position(float timepoint, const Position& position){
    float t = timepoint-position.get_simulation_time();
    float speed_x = position.get_speed_x()+t*position.get_acceleration_x();
    float speed_y = position.get_speed_y()+t*position.get_acceleration_x();
    float x = position.get_x()+position.get_speed_x()*t+0.5*position.get_acceleration_x()*t*t;
    float y = position.get_y()+position.get_speed_y()*t+0.5*position.get_acceleration_y()*t*t;
    return Position(timepoint, x, y, 0, 0, speed_x, speed_y, position.get_acceleration_x(), position.get_acceleration_y());
}

float AoICalculator::compute_distance(const Position& pos1, const Position& pos2) {
    return std::sqrt( (pos1.get_x()-pos2.get_x())*(pos1.get_x()-pos2.get_x())+(pos1.get_y()-pos2.get_y())*(pos1.get_y()-pos2.get_y()));
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
            dump_values(aoi, aoi_file);
            dump_values(aoi, paoi_file);
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