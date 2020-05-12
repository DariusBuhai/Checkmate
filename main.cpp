#include "include/draw.h"

using namespace std;

#if defined(_WIN32)
#include "draw.cpp"

#endif // defined

int main(){

    unique_ptr<Draw> drawPtr(Draw::getInstance());
    return 0;
}
