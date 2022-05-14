//
// Created by jordimarias on 5/11/22.
//


#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <list>
#include <map>
#include <regex>
#include "Database.h"
#include "csv_parser.h"
#include "AoICalculator.h"

namespace po = boost::program_options;


int main(int argc, char * argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("folder", po::value<std::string>()->required(), "The folder where all the CSV files are stored");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 1;
        }
    } catch (std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        exit(1);
    }
    Database database = Database();
    CSVParser csv_parser = CSVParser();
    try {
        std::map<int, std::string> positioned_file_map;
        std::map<int, std::string> received_file_map;
        std::map<int, std::string> sent_file_map;
        std::regex positioned_regex("(\\d+)_positioned\\.csv$");
        std::regex received_regex("(\\d+)_positioned\\.csv$");
        std::regex sent_regex("(\\d+)_positioned\\.csv$");
        std::smatch sm;

        for (const auto &entry: std::filesystem::directory_iterator(vm["folder"].as<std::string>())) {
            std::cout << entry.path() << std::endl;
            std::string path = entry.path();
            if (std::regex_search(path, sm, positioned_regex)) {
                positioned_file_map.insert(std::make_pair(std::stoi(sm[1]), path));
            } else if (std::regex_search(path, sm, sent_regex)) {
                sent_file_map.insert(std::make_pair(std::stoi(sm[1]), path));
            } else if (std::regex_search(path, sm, received_regex)) {
                received_file_map.insert(std::make_pair(std::stoi(sm[1]), path));
            }
        }
        for (const auto &positioned_file: positioned_file_map) {
            const int &station_id = positioned_file.first;
            csv_parser.parse_sent_positioned(sent_file_map[station_id], positioned_file.second, database);
            csv_parser.parse_received(received_file_map[station_id], database);
        }
    } catch (std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        exit(1);
    }
    database.sort_data();
    AoICalculator calculator = AoICalculator();
    calculator.compute_and_dump_values(database);
}
