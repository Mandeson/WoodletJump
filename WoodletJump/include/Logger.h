#pragma once

#include <string>

namespace Logger {

enum MessageType {
    kInfo,
    kWarning,
    kError
};

void log(MessageType message_type, const std::string &message);

}
