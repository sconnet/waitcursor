/*
  compile with:

  g++ -o wait main.cpp WaitCursor.cpp -pthread

 */

#include "WaitCursor.h"
#include <unistd.h>
#include <iostream>

int main()
{
    std::cout << "waiting 5 seconds...\n";

    WaitCursor wait;
    wait.start(0.05f);
    sleep(5);
    wait.stop();

    std::cout << "\nwaiting is over, program exiting\n";
    return 0;
}
