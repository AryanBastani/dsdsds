#ifndef __GET_INPUT__
#define __GET_INPUT__

#include "global.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include<vector>

class getInput
{
    public:
        std::string line;
        std::string word; 
        std::stringstream line_stream;
    
        void getLine ();
        std::vector<std::string> split();
};

#endif