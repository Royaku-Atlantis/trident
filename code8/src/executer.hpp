#pragma once
#include "trident.hpp"


class Executer
{
    Array<Functions> functions;
    Array<Scope> scopes;

    void run();

};
