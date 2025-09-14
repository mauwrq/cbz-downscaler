#include <argument_parser.hpp>
#include <boost/program_options.hpp>
#include <vector>
#include <iostream>

namespace po = boost::program_options;

ArgumentParser::args ArgumentParser::parse_args(int argc, char* argv[]) {
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("input", po::value< std::vector<std::string> >(), "input file");
  
  po::positional_options_description p;
  p.add("input", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).
            options(desc).positional(p).run(), vm);
  po::notify(vm);
  
  ArgumentParser::args args;
  
  if (vm.count("help")) {
    std::cout << desc << "\n";
    return args;
  }

  if (vm.count("input")) {
    args.input = vm["input"].as<std::vector<std::string>>();
  }
  return args;
}