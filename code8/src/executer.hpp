#pragma once
#include "trident.hpp"


class Executer
{
    std::vector<Functions> functions;
    std::vector<Scope> scopes;

    void run();

};
