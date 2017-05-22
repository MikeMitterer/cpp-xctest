#include <uWS.h>
#include <iostream>
#include "json.hpp"

// for convenience
using json = nlohmann::json;

const bool isServer = true;

namespace ns {
    // a simple struct to model a person
    struct person {
        std::string name;
        std::string address;
        int age;
    };

    void to_json(json& j, const person& p) {
        j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
    }

    void from_json(const json& j, person& p) {
        p.name = j.at("name").get<std::string>();
        p.address = j.at("address").get<std::string>();
        p.age = j.at("age").get<int>();
    }
}

int main() {
    uWS::Hub hub;


    hub.onConnection([](uWS::WebSocket<isServer>* ws, uWS::HttpRequest req) {
        std::cout << "Client established a remote connection" << std::endl;
    });

    hub.onMessage([](uWS::WebSocket<isServer>* ws, char* message, size_t length, uWS::OpCode opCode) {
        std::cout << "Sending back\n";
        //ws->send(message, length, opCode);

        // create object from string literal
        json j2 = R"({ "happy": true, "pi": 3.141 })"_json;

    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

    json j;
    to_json(j,p);

        ws->send(j2.dump(4).c_str(), opCode);
    });

    hub.onDisconnection([](uWS::WebSocket<isServer>* ws, int code, char* message, size_t length) {
        std::cout << "Disconnecting!\n";
    });

    std::cout << "Listening on port 3000!" << std::endl;
    hub.listen(3000);

    hub.run();

//    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
//
//    json j;
//    to_json(j,p);
//    std::cout << j.dump().c_str() << std::endl;
    
}