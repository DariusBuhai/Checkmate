#include "include/draw.h"
#include "draw.cpp"
using namespace std;


int main(){

    unique_ptr<Draw> drawPtr(Draw::getInstance());

    return 0;
}
