#include "stdafx.h"
#include <args.hxx>

#include "logger.h"

std::string getCompilerStandard() {
    std::stringstream out;

    if (__cplusplus == 201703L) out << "C++17\n";
    else if (__cplusplus == 201402L) out << "C++14\n";
    else if (__cplusplus == 201103L) out << "C++11\n";
    else if (__cplusplus == 199711L) out << "C++98\n";
    else out << "Could not find out your C++ standard! '__cplusplus("
             << __cplusplus << ")'" << std::endl;

    return out.str();
}

/**
 * Sample verwendet folgendes Libs:
 *      Formatter:  https://github.com/fmtlib/fmt
 *      Logger: https://github.com/gabime/spdlog
 *      ArgParser: https://github.com/Taywee/args
 */
int main(int argc,const char *argv[]) {
    auto logger = DefaultLogger::get("application");

    args::ArgumentParser parser("This is a test program.",
            std::string("This goes after the options.\n")
                + std::string("Your compiler supports: ")
                + getCompilerStandard()
                );

    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::ValueFlag<int> integer(parser, "integer", "The integer flag", {'i'});
    args::ValueFlagList<char> characters(parser, "characters", "The character flag", {'c'});
    args::Positional<std::string> foo(parser, "foo", "The foo position");
    args::PositionalList<double> numbers(parser, "numbers", "The numbers position list");


    try {
        parser.ParseCLI(argc, argv);
        if(argc == 1) {
            throw args::Help("");
        }
    }
    catch (const args::Help& e) {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (const args::ValidationError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (integer) { std::cout << "Param i (integer): " << args::get(integer) << std::endl; }
    if (characters) { for (const auto ch: args::get(characters)) { std::cout << "Param c (characters): " << ch << std::endl; }}
    if (foo) { std::cout << "Param f (foo (positional)): " << args::get(foo) << std::endl; }
    if (numbers) { for (const auto nm: args::get(numbers)) { std::cout << "Param n (number): " << nm << std::endl; }}

    logger->info(getCompilerStandard());

    return 0;
}
