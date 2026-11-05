#include "uincampus/version.hpp"

#include <print>

int main() {
    std::println("UIN-Campus - Systeme de gestion academique");
    std::println("Version {}", uin::version());

    return 0;
}