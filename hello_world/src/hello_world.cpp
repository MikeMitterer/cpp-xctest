#include "spdlog/spdlog.h"
#include <iostream>
#include <args.hxx>

/**
 * Sample verwendet folgendes Libs:
 *      Formatter:  https://github.com/fmtlib/fmt
 *      Logger: https://github.com/gabime/spdlog
 *      ArgParser: https://github.com/Taywee/args
 */
namespace spd = spdlog;
int main(int argc,const char *argv[]) {
    auto logger = spd::stdout_color_mt("console");

    args::ArgumentParser parser("This is a test program.", "This goes after the options.");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::ValueFlag<int> integer(parser, "integer", "The integer flag", {'i'});
    args::ValueFlagList<char> characters(parser, "characters", "The character flag", {'c'});
    args::Positional<std::string> foo(parser, "foo", "The foo position");
    args::PositionalList<double> numbers(parser, "numbers", "The numbers position list");


    logger->info(fmt::format("Hello, {}!", "world"));

    try {
        parser.ParseCLI(argc, argv);
        if(argc == 1) {
            throw args::Help("");
        }
    }
    catch (args::Help e) {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (integer) { std::cout << "Param i (integer): " << args::get(integer) << std::endl; }
    if (characters) { for (const auto ch: args::get(characters)) { std::cout << "Param c (characters): " << ch << std::endl; }}
    if (foo) { std::cout << "Param f (foo (positional)): " << args::get(foo) << std::endl; }
    if (numbers) { for (const auto nm: args::get(numbers)) { std::cout << "Param n (number): " << nm << std::endl; }}

    return 0;
}