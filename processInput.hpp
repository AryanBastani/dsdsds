#ifndef __PROCESS_INPUT__
#define __PROCESS_INPUT__
#include <functional>
#include <string>
#include "global.hpp"
#include "leitner.hpp"

void reviewCards (int max_card_num, leitner* leitner_box);
void determineIterator (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box);
void moveCards (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box);
void defineIterator (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box);
void endofDayMoveCards(leitner* leitner_box);
void nesseceryChanges(leitner* leitner_box);

class processInput
{
        using command_func = std::function<std::string_view(std::vector<std::string>, leitner*)>;
        static std::map <std::string_view, command_func> command_functions;
        static std::string return_value;
    public:
        processInput();
        static std::string_view identifyCommand (std::vector<std::string> command, leitner* leitner_box);
        static std::string_view streakFunc (std::vector<std::string> command, leitner* leitner_box);
        static std::string_view addFunc (std::vector<std::string> command, leitner* leitner_box);
        static std::string_view reviewFunc (std::vector<std::string> command, leitner* leitner_box);
        static std::string_view reportFunc (std::vector<std::string> command, leitner* leitner_box);
        static std::string_view prgReportFunc (std::vector<std::string> command, leitner* leitner_box);
        static std::string_view nextdayFunc (std::vector<std::string> command, leitner* leitner_box);

        friend class leitner;
};


#endif