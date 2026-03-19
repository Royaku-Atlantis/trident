#include <iostream>
using namespace std;

enum type : char {A, B, C, D};

struct a{
        a (){t = A;}
        string display(){
                return "[Type:" + to_string((int)t) + ", val1:" + to_string(val1) + "]";
        }

        type t;
        int val1 = 0;
};

struct b : public a
{
        b (){t = B;}
        string display(){
                return "[Type:" + to_string((int)t) + ", val1:" + to_string(val1) + ", val2:" + to_string(val2) + "]";
        }

        int val2 = 5;
};

struct c : public a
{
        c (){t = C;}
        string display(){
                return "[Type:" + to_string((int)t) + ", val1:" + to_string(val1) + ", val2:" + to_string(val2) + ", val3:" + to_string(val2) + ", val4:"+val4 +"]";
        }

        int val2 = 0;
        int val3 = -1;
        char val4 = 'c';
};

struct d : public b
{
        d (){t = D;}
        string display(){
                return "[Type:" + to_string((int)t) + ", val1:" + to_string(val1) + ", val2:" + to_string(val2) + ", myvec:<"+to_string(myvec[0])+','+to_string(myvec[1])+','+to_string(myvec[2])+','+to_string(myvec[3])+">]";
        }

        float myvec[4] = {0.0, 4.36, 9674.42, -15.2};
};

int main(int argc, char * argv[])
{

        void * alist[4];
        alist[0] = (void*) new a();
        alist[1] = (void*) new b();  
        alist[2] = (void*) new c(); 
        alist[3] = (void*) new d();

        for (int i=0; i<4; i++)
        {
                type t = ((a*)alist[i])->t;
                cout << "type = " << (int)t << " -> ";
                switch(t)
                {
                        case A:
                                cout << ((a*)alist[i])->display() << endl;
                                break;
                        case B:
                                cout << ((b*)alist[i])->display() << endl;
                                break;
                        case C:
                                cout << ((c*)alist[i])->display() << endl;
                                break;
                        case D:
                                cout << ((d*)alist[i])->display() << endl;
                                break;
                }
        }

        for (int i=0; i<4; i++)
        {
                switch(((a*)alist[i])->t)
                {
                        case A:
                                delete (a*)alist[i];
                                break;
                        case B:
                                delete (b*)alist[i];
                                break;
                        case C:
                                delete (c*)alist[i];
                                break;
                        case D:
                                delete (d*)alist[i];
                                break;
                }
        }

        return 0;
}