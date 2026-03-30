#pragma once
#include "trident.cpp"


class Executer
{
    Array<Functions> functions;
    Array<Scope> scopes;

    void run();

};
