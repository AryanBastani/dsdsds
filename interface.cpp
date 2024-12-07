#include "interface.hpp"

std::vector<std::string> interface::inputHandle()
{
    get_input.getLine();
    return get_input.split();
}

std::string_view interface::commandHandle (std::vector<std::string> command, leitner* leitner_box)
{
    return process_input.identifyCommand(command, leitner_box);
}

void interface::initiate (leitner* leitner_box)
{
    std::vector<std::string> command;
    std::string respond;
    while (true)
    {
        std::cin.clear();
        command = inputHandle();
        // std::cout << "in interface: command vector: " << std::endl;
        // for (auto i : command)
        // {
        //     std::cout << i << std::endl;
        // }
        
        if (command.size() == 0)
            break;
        respond = commandHandle(command, leitner_box);
        std::cout << respond;
    }
}