//
// Created by jordimarias on 5/11/22.
//

#include "csv_parser.h"
#include <map>
#include <iostream>

const std::regex CSVParser::positioned_match_{"([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+)"};
const std::regex CSVParser::positioned_file_{"(\\d+)_positioned\\.csv"};
const std::regex CSVParser::sent_match_{"([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+)"};
const std::regex CSVParser::sent_file_{"(\\d+)_sent\\.csv"};
const std::regex CSVParser::received_match_{"([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+),([^,]+)"};
const std::regex CSVParser::received_file_{"(\\d+)_received\\.csv"};
CSVParser::CSVParser(){}

void CSVParser::parse_sent_positioned(const std::string& file_sent,const std::string& file_positioned, Database& database) {
    std::cout << "Parsing sent positioned" << std::endl;
    std::cout << "Sent: " << file_sent << std::endl;
    std::cout << "Positioned: " << file_positioned<< std::endl;
    std::fstream positioned_file;
    std::fstream sent_file;
    std::smatch sm;
    std::smatch sm_f;
    if (std::regex_match(file_positioned, sm, positioned_file_) &&
            std::regex_match(file_sent, sm_f, sent_file_) && sm.str(1) == sm_f.str(1)){
        /*
         * 1 station_id
         */
        // Stores simulation time and Etsi time
        std::cout << "Parsing sent positioned" << std::endl;
        long station_id = std::stol(sm.str(1));
        Vehicle& vehicle = database.get_vehicle(station_id);
        std::map<float, MessageSent&> sent_file_map;
        sent_file.open(file_sent);
        if (sent_file.is_open()) {
            std::string line;
            while (std::getline(sent_file, line)) {
                if (std::regex_match(line, sm_f, sent_match_)) {
                    /*
                     * 1 Sent Time (etsi time)
                     * 2 Simulation
                     * 3 latitude
                     * 4 longitude
                     * 5 X
                     * 6 Y
                     */
                    std::cout << " - Sent Time: " << sm_f.str(1) << std::endl;
                    std::cout << " - Simulation: " << sm_f.str(2) << std::endl;
                    std::cout << " - Latitude: " << sm_f.str(3) << std::endl;
                    std::cout << " - Longitude: " << sm_f.str(4) << std::endl;
                    std::cout << " - X: " << sm_f.str(5) << std::endl;
                    std::cout << " - Y: " << sm_f.str(6) << std::endl;
                    MessageSent& temp_message = vehicle.create_message_sent(Position(
                            std::stof(sm_f.str(2)),
                            std::stof(sm_f.str(5)),
                            std::stof(sm_f.str(6)),
                            std::stof(sm_f.str(3)),
                            std::stof(sm_f.str(4)),
                            0,0,0,0
                            ), std::stof(sm_f.str(1)));
                }
            }
            sent_file.close();
        }
        //Vehicle& vehicle = database.get_vehicle(station_id);
        positioned_file.open(file_positioned);
        if (positioned_file.is_open()) {
            std::string line;
            while (std::getline(positioned_file, line)) {
                if (std::regex_match(line, sm, positioned_match_)) {
                    /*
                     * 1 Simulation Time
                     * 2 Delta Time
                     * 3 Predicted Position X
                     * 4 Predicted Position Y
                     * 5 Real Postition X
                     * 6 Real Position Y
                     * 7 Real Position Latitude
                     * 8 Real Position Longitude
                     * 9 Predicted Speed X
                     * 10 Predicted Speed Y
                     * 11 Real Speed X
                     * 13 Real Speed Y
                     * 14 Real Acceleration X
                     * 15 Real Acceleration Y
                     * 16 L2 Norm
                     * 17 Penalty
                     * 18 CAM Sent
                     */
                    sm.str(0);
                    Position position = Position(std::stof(sm.str(1)),
                                                 std::stof(sm.str(5)),
                                                 std::stof(sm.str(6)),
                                                 std::stof(sm.str(7)),
                                                 std::stof(sm.str(8)),
                                                 std::stof(sm.str(11)),
                                                 std::stof(sm.str(13)),
                                                 std::stof(sm.str(14)),
                                                 std::stof(sm.str(15)));
                    vehicle.add_real_position(position);
                }
            }
            positioned_file.close();
        }
    }
}

void CSVParser::parse_received(const std::string &file_location, Database &database) {
    std::fstream received_file;
    std::smatch sm;

    if (std::regex_match(file_location, sm, received_file_))
    {
        long station_id = std::stol(sm.str(1));
        received_file.open(file_location);
        Vehicle& vehicle = database.get_vehicle(station_id);
        if (received_file.is_open()){
            std::string line;
            while (std::getline(received_file, line)) {
                if (std::regex_match(line, sm, received_match_)) {
                    /*
                     * 1 Station ID
                     * 2 Sent Time
                     * 3 Received Time
                     * 4 Received Simulation
                     * 5 Origin latitude
                     * 6 Origin longitude
                     * 7 Destiny latitude
                     * 8 Destiny longitude
                     * 9 Destiny X
                     * 10 Destiny Y
                     */
                    Position temp = Position(0,0,0,std::stof(sm.str(5)), std::stof(sm.str(6)),0,0,0,0);
                    MessageReceived& messageReceived = vehicle.create_message_received(std::stof(sm.str(4)), station_id, std::stol(sm.str(1)));
                    MessageSent& corresponding_message = database.get_vehicle(std::stol(sm.str(1))).get_message_sent(temp, std::stof(sm.str(2)));
                    if (corresponding_message.get_etsi_time() != 0){
                        corresponding_message.add_message_received(messageReceived);
                        messageReceived.set_message_sent(corresponding_message);
                    }
                }
            }
        }
    }
}
