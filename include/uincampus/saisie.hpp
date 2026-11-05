#pragma once

#include <string>
#include <string_view>

namespace uin {

int lireEntier(std::string_view invite, int minimum, int maximum);

double lireNote(std::string_view invite);

} // namespace uin