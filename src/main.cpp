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
    std::cout << "Starting the AoI CSV Handler" << std::endl;
    Database database = Database();
    std::cout << "Internal DB created" << std::endl;
    CSVParser csv_parser = CSVParser();
    std::cout << "CSVParser created" << std::endl;
    try {
        std::map<long, std::string> positioned_file_map;
        std::map<long, std::string> received_file_map;
        std::map<long, std::string> sent_file_map;
        std::regex positioned_regex("(\\d+)_positioned\\.csv$");
        std::regex received_regex("(\\d+)_received\\.csv$");
        std::regex sent_regex("(\\d+)_sent\\.csv$");
        std::smatch sm;
        std::cout << "Checking all files" << std::endl;
        for (const auto &entry: std::filesystem::directory_iterator(vm["folder"].as<std::string>())) {
            std::string path = entry.path();
            if (std::regex_search(path, sm, positioned_regex)) {
                positioned_file_map.insert(std::make_pair(std::stol(sm[1]), path));
            } else if (std::regex_search(path, sm, sent_regex)) {
                sent_file_map.insert(std::make_pair(std::stol(sm[1]), path));
            } else if (std::regex_search(path, sm, received_regex)) {
                received_file_map.insert(std::make_pair(std::stol(sm[1]), path));
            }
        }
        std::cout << "Starting to parse the CSV" << std::endl;
        for (const auto &positioned_file: positioned_file_map) {
            const long &station_id = positioned_file.first;
            csv_parser.parse_sent_positioned(sent_file_map[station_id], positioned_file.second, database);
        }
        for (const auto &positioned_file: positioned_file_map) {
            const long &station_id = positioned_file.first;
            csv_parser.parse_received(received_file_map[station_id], database);
        }
    } catch (std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        exit(1);
    }
    std::cout << "Sorting data" << std::endl;
    database.sort_data();
    std::cout << "Create calculator" << std::endl;
    AoICalculator calculator = AoICalculator();
    std::cout << "Computing and dumping values" << std::endl;
    calculator.compute_and_dump_values(database, vm["folder"].as<std::string>());
    std::cout << "Everything done!" << std::endl;
}
