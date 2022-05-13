//
// Created by jordimarias on 5/11/22.
//


#include <boost/program_options.hpp>
#include <vector>
#include <string>


namespace po = boost::program_options;


int main(int argc, char * argv[])
{
    po::options_description options("Allowed options");
    std::vector<std::string> files;
    options.add_options()
            ("help", "Print out available options.")
            ("FILES", po::value<std::vector<std::string>>(&files)->multitoken()->required(), "List of CSV files to process")
            ;
    po::positional_options_description positional_options;
    positional_options.add("interface", 1);


    try {
        po::store(
                po::command_line_parser(argc, argv)
                        .options(options)
                        .positional(positional_options)
                        .run(),
                vm
        );
        po::notify(vm);
    } catch (po::error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << options << std::endl;
        return 1;
    }

    if (vm.count("help")) {
        std::cout << options << std::endl;
        return 1;
    }

    po::variables_map vm;
}