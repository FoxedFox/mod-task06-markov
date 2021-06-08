#include <iostream>
#include <fstream>
#include "textgen.h"
using namespace std;
int main()
{
    //setlocale(LC_ALL, "Russian");
    textgen gener{ 2 };
    gener.StreamDatEntry("text.txt");
    gener.DataBasePrint();
    std::cout << gener.TextGenerator(100, 5);
}