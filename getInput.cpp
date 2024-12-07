#include "getInput.hpp"

void getInput::getLine ()
{
    // std::cout << "in getLine" << std::endl;
    std::cin.clear();
    line.clear();
    std::getline(std::cin, line);
    // std::cout << "line: " << line << std::endl;
}

std::vector<std::string> getInput::split()
{
    // std::cout << "in split function" << std::endl;
    std::vector<std::string> command;
    line_stream = std::stringstream();
    line_stream << line;
    word.clear();
    line_stream >> word;
    while (word != "")
    {
        command.push_back(word);
        word.clear();
        line_stream >> word;
    }
    return command;
}