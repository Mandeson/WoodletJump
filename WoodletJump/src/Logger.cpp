#include <iostream>
#include <Logger.h>

namespace Logger {

void log(MessageType message_type, const std::string &message) {
    switch (message_type) {
    case MessageType::kInfo:
        std::cout << "[Info] " << message << std::endl;
        break;
    case MessageType::kWarning:
        std::cerr << "[Warning] " << message << std::endl;
        break;
    case MessageType::kError:
        std::cerr << "[Error] " << message << std::endl;
        break;
    }
}

}
