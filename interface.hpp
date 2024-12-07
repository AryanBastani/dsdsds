#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "getInput.hpp"
#include "leitner.hpp"
#include "global.hpp"
#include "processInput.hpp"

class interface
{
    public:
        void initiate (leitner* leitner_box);
        std::vector<std::string> inputHandle();
        std::string_view commandHandle (std::vector<std::string> command, leitner* leitner_box);
        getInput get_input;
        processInput process_input;
};

#endif