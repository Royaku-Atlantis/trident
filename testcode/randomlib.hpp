#pragma once

using namespace std;

//std::variant<>

class foo{
public:
        void dothing();
};

class bar : public foo{
public:
        void dothing();
private:
        int val;
};