#include "Poco/AutoPtr.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include "Poco/Logger.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Message.h"
#include <iostream>

using Poco::AutoPtr;
using Poco::BasicEvent;
using Poco::Delegate;
using Poco::Logger;
using Poco::Message;
using Poco::ConsoleChannel;
using Poco::PatternFormatter;
using Poco::FormattingChannel;

class Source {
public:
    BasicEvent<int> theEvent;

    void fireEvent(int n) {
        theEvent(this, n);
    }
};

class Target {
public:
    void onEvent(const void *pSender, int &arg) {
        std::cout << "onEvent: " << arg << std::endl;
    }
};

int main(int argc, char **argv) {
    AutoPtr<PatternFormatter> pPatternFormatter(new PatternFormatter("%s: %p: %t"));
    AutoPtr<FormattingChannel> pFCConsole(new FormattingChannel(pPatternFormatter));
    AutoPtr<ConsoleChannel> pConsoleChannel(new ConsoleChannel());
    pFCConsole->setChannel(pConsoleChannel);
    pFCConsole->open();

    Logger& logger = Poco::Logger::create("ConsoleLogger", pFCConsole, Message::PRIO_INFORMATION);

    Source source;
    Target target;

    source.theEvent += Delegate<Target, int>(&target, &Target::onEvent);

    source.fireEvent(42);

    source.theEvent -= Delegate<Target, int>(&target, &Target::onEvent);

    logger.information("An information message");
    logger.error("An error message");

    return 0;
}