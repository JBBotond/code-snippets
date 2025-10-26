//
// Created by boti on 10/24/25.
//

#ifndef CODE_SNIPPETS_STRINGTOCLOCK_H
#define CODE_SNIPPETS_STRINGTOCLOCK_H

#include <iostream>

inline void numToClock(long long int numberSec) {
    long long int minutes = 0;
    long long int seconds = 0;

    //case only seconds
    if (numberSec > 0 && numberSec < 60) {
        seconds = numberSec;
        std::cout << "00:00:" << seconds << std::endl;
    }
    //case only minutes
    else if (numberSec >= 60 && numberSec < 3600) {
        minutes = numberSec / 60;
        seconds = (numberSec - minutes) % 60;
        std::cout << "00:" << minutes << ":" << seconds << std::endl;
    }
    //case hours too
    else if (numberSec >= 3600) {
        long long int hours = 0;
        hours = numberSec /3600;
        minutes = numberSec/60 - hours*60;
        seconds = numberSec - (hours * 3600) - (minutes * 60);
        std::cout << hours << ':' << minutes << ':' << seconds << std::endl;
    }
}
#endif //CODE_SNIPPETS_STRINGTOCLOCK_H