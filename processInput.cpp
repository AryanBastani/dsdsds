#include "processInput.hpp"

void defineIterator (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box)
{
    switch (current_box)
    {
        case MONTHLY_BOX:
            if(leitner_box->monthly_box.size()!=0)
            {
                card_it = leitner_box->monthly_box.begin();
            }
            else
            {
                card_it = leitner_box->monthly_box.end();
                determineIterator(current_box, card_it, leitner_box);
            }    
            break;
        case WEEKLY_BOX:
            if(leitner_box->weekly_box.size()!=0)
            {
                card_it = leitner_box->weekly_box.begin();
            }    
            else
            {
                card_it = leitner_box->weekly_box.end();
                determineIterator(current_box, card_it, leitner_box);
            }  
            break;
        case THREE_DAY_BOX:
            if(leitner_box->every_three_day_box.size()!=0)
            {
                card_it = leitner_box->every_three_day_box.begin();
            }
            else
            {
                card_it = leitner_box->every_three_day_box.end();
                determineIterator(current_box, card_it, leitner_box);
            } 
            break; 
        case EVERY_DAY_BOX:
            if(leitner_box->every_day_box.size()!=0)
            {
                // std::cout << "in define every day box" << std::endl;
                card_it = leitner_box->every_day_box.begin();
            }
            else
                card_it = leitner_box->every_day_box.end();
            break;
        default:
            break;              
    }
}

void determineIterator (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box)
{
    std::map<int, box_review_today>::iterator box_it;
    switch (current_box)
    {
    case NOT_INITIALIZED:
        // std::cout << "in determine in not initialized" << std::endl;
        box_it = find_if(leitner_box->boxes_to_review_today.begin(), leitner_box->boxes_to_review_today.end(),
            [](std::pair<int, box_review_today> box){return box.second.must_review;});
        current_box = box_it->first; 
        defineIterator (current_box, card_it, leitner_box);    
        break;
    case MONTHLY_BOX:
        if (card_it == leitner_box->monthly_box.end())
        {
            box_it = find_if(leitner_box->boxes_to_review_today.begin(), leitner_box->boxes_to_review_today.end(), 
            [](std::pair<int, box_review_today> box){if(box.first>MONTHLY_BOX) return box.second.must_review;return false;});
            current_box = box_it->first;
            defineIterator (current_box, card_it, leitner_box);    
        }
        break;
    case WEEKLY_BOX:
        if (card_it == leitner_box->weekly_box.end())
        {
            box_it = find_if(leitner_box->boxes_to_review_today.begin(), leitner_box->boxes_to_review_today.end(), 
            [](std::pair<int, box_review_today> box){if(box.first>WEEKLY_BOX) return box.second.must_review;return false;});    
            current_box = box_it->first;
            defineIterator (current_box, card_it, leitner_box);    
        }
        break; 
    case THREE_DAY_BOX:
        if (card_it == leitner_box->every_three_day_box.end())
        {
            box_it = find_if(leitner_box->boxes_to_review_today.begin(), leitner_box->boxes_to_review_today.end(), 
            [](std::pair<int, box_review_today> box){if(box.first>THREE_DAY_BOX) return box.second.must_review;return false;});    
            current_box = box_it->first;
            defineIterator (current_box, card_it, leitner_box);    
        }
        break;    
    default:
        break;
    }
}

void moveCards (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box)
{
    // std::cout << "in move cards" << std::endl;
    if ((*card_it)->wrong_count == 0)
    {
        // std::cout << "erong cpount = 0" << std::endl;
        switch (current_box)
        {
            case MONTHLY_BOX:
                leitner_box->mastered_cards_num += 1;
                card_it = leitner_box->monthly_box.erase(card_it);
                break;
            case WEEKLY_BOX: 
                leitner_box->monthly_box.push_back(*card_it);
                card_it = leitner_box->weekly_box.erase(card_it);
                break;
            case THREE_DAY_BOX:
                leitner_box->weekly_box.push_back(*card_it);
                card_it = leitner_box->every_three_day_box.erase(card_it);
                break; 
            case EVERY_DAY_BOX:
                leitner_box->every_three_day_box.push_back(*card_it);
                card_it = leitner_box->every_day_box.erase(card_it);
                break;
            default:
                break; 
        }
    }
    else if ((*card_it)->wrong_count == 2)
    {
        // std::cout << "wrong count = 2" << std::endl;
        (*card_it)->wrong_count = 0;
        switch (current_box)
        {
            case MONTHLY_BOX:
                leitner_box->weekly_box.push_back(*card_it);
                card_it = leitner_box->monthly_box.erase(card_it);
                break;
            case WEEKLY_BOX: 
                leitner_box->every_three_day_box.push_back(*card_it);
                card_it = leitner_box->weekly_box.erase(card_it);
                break;
            case THREE_DAY_BOX:
                leitner_box->every_day_box.push_back(*card_it);
                card_it = leitner_box->every_three_day_box.erase(card_it);
                break; 
            case EVERY_DAY_BOX:
                card_it++;
                break;
            default:
                break; 
        }
    }
    else
    {
        // std::cout << "non of above increment the iterator" << std::endl;
        card_it++;
    }
    determineIterator(current_box, card_it, leitner_box);
}

void reviewCards (int max_card_num, leitner* leitner_box)
{
    int count{0};
    std::vector<flashcard*>::iterator card_it;
    int current_box{NOT_INITIALIZED};
    std::string user_answer;
    while (count < max_card_num)
    {
        determineIterator(current_box, card_it, leitner_box);
        if (card_it == leitner_box->every_day_box.end())
        {
            std::cout << "no more cards to review" << std::endl;
            abort();
        }
        if ((*card_it)->last_day_reviewed != leitner_box->today)
        {
            std::cout << output::REVIEW_TODAY_FIRST_LINE;
            std::cout << (*card_it)->question;
            std::cout << output::REVIEW_TODAY_SECOND_LINE;
            std::cin.clear();
            std::getline(std::cin, user_answer);
            if (user_answer == (*card_it)->answer)
            {
                std::cout << output::REVIEW_TODAY_CORRECT;
                (*card_it)->wrong_count = 0;
                (*card_it)->last_day_reviewed = leitner_box->today;
                leitner_box->every_day_activity[leitner_box->today].correct_num += 1;
            }
            else
            {
                std::cout << output::REVIEW_TODAY_WRONG_FIRST;
                std::cout << (*card_it)->answer;
                std::cout << output::REVIEW_TODAY_WRONG_SECOND;
                (*card_it)->wrong_count += 1;
                (*card_it)->last_day_reviewed = leitner_box->today;
                leitner_box->every_day_activity[leitner_box->today].wrong_num += 1;
            }
            moveCards (current_box, card_it, leitner_box);
            count++;
        }
    }
}

void endofDayMoveCards(leitner* leitner_box)
{
    for (auto i : leitner_box->boxes_to_review_today)
    {
        if (i.second.must_review == true)
        {
            std::vector<flashcard*>::iterator box_it = leitner_box->boxes_map[i.first]->begin();
            while (box_it != leitner_box->boxes_map[i.first]->end() && i.first != EVERY_DAY_BOX)
            {
                if ((*box_it)->last_day_reviewed != leitner_box->today)
                {
                    leitner_box->boxes_map[i.first+1]->push_back(*box_it);
                    box_it = leitner_box->boxes_map[i.first]->erase(box_it);
                }
                else
                {
                    box_it++;
                }
            }  
        }
    } 
}

void nesseceryChanges(leitner* leitner_box)
{ 
    if (leitner_box->every_day_activity[leitner_box->today].reviewed == false)
        leitner_box->streak = 0;

    leitner_box->today += 1;
    leitner_box->every_day_activity[leitner_box->today].correct_num = 0;
    leitner_box->every_day_activity[leitner_box->today].wrong_num = 0;
    leitner_box->every_day_activity[leitner_box->today].reviewed = false;
    leitner_box->every_day_activity[leitner_box->today].participated = 0;

    for (int i=1; i<=EVERY_DAY_BOX; i++)
    {
        leitner_box->boxes_to_review_today[i].reviewed_today = false;
        switch (i)
        {
        case MONTHLY_BOX:
            if (leitner_box->today%30 == 0)
                leitner_box->boxes_to_review_today[i].must_review = true;
            else
                leitner_box->boxes_to_review_today[i].must_review = false;    
            break;
        case WEEKLY_BOX:
            if (leitner_box->today%7 == 0)
                leitner_box->boxes_to_review_today[i].must_review = true;
            else
                leitner_box->boxes_to_review_today[i].must_review = false;    
            break;
        case THREE_DAY_BOX:
            if (leitner_box->today%3 == 0)
                leitner_box->boxes_to_review_today[i].must_review = true;
            else
                leitner_box->boxes_to_review_today[i].must_review = false;    
            break; 
        case EVERY_DAY_BOX:
                leitner_box->boxes_to_review_today[i].must_review = true;    
            break;       
        default:
            break;
        }
    }
}

std::map <std::string_view, processInput::command_func> processInput::command_functions;
std::string processInput::return_value;

processInput::processInput()
{
    command_functions.emplace(commands::STREAK, &streakFunc);
    command_functions.emplace(commands::ADD_FLASHCARD, &addFunc);
    command_functions.emplace(commands::REVIEW_TODAY, &reviewFunc);
    command_functions.emplace(commands::GET_REPORT, &reportFunc);
    command_functions.emplace(commands::GET_PROGRESS_REPORT, &prgReportFunc);
    command_functions.emplace(commands::NEXT_DAY, &nextdayFunc);
}

std::string_view processInput::identifyCommand (std::vector<std::string> command, leitner* leitner_box)
{
    auto it = command_functions.find(command[0]);
    if (it != command_functions.end())
    {
        return it->second(command, leitner_box);
    }
    return "";
}

std::string_view processInput::streakFunc (std::vector<std::string> command, leitner* leitner_box)
{
    return_value.clear();
    return_value += output::STREAK_FIRST_LINE;
    return_value += std::to_string(leitner_box->streak);
    return_value += output::END_OF_LINE;
    return_value += output::STREAK_SECOND_LINE;
    return std::string_view{return_value};
}

std::string_view processInput::addFunc (std::vector<std::string> command, leitner* leitner_box)
{
    int card_num{stoi(command[1])};
    for (int i=0; i < card_num; i++)
    {
        flashcard* fc = new flashcard;
        std::cin.clear();
        std::getline(std::cin, fc->question);
        std::getline(std::cin, fc->answer);
        fc->last_day_reviewed = 0;
        fc->wrong_count = 0;
        leitner_box->every_day_box.push_back(fc);
    }
    return output::ADD_FLASHCARD;
}

std::string_view processInput::reviewFunc (std::vector<std::string> command, leitner* leitner_box)
{
    int card_numbers = std::stoi(command[1]);
    reviewCards(card_numbers, leitner_box);
    if (leitner_box->every_day_activity[leitner_box->today].reviewed == false)
    {
        leitner_box->streak += 1;
        leitner_box->total_day_participated += 1;
        leitner_box->every_day_activity[leitner_box->today].reviewed = true;
    }
    return output::REVIEW_TODAY_LAST_MESSAGE;
}

std::string_view processInput::reportFunc (std::vector<std::string> command, leitner* leitner_box)
{
    int start_day = stoi(command[1]);
    int end_day = stoi(command[2]);
    return_value.clear();
    return_value += output::GET_REPORT_FIRST_LINE;
    return_value += ([start_day, end_day](){if(start_day==end_day)return std::to_string(start_day)+"\n";return std::to_string(start_day)+" to "+std::to_string(end_day)+"\n";})();
    return_value += output::GET_REPORT_SECOND_LINE;
    int correct_sum = [leitner_box, start_day, end_day](){int correct_sum{0};for(int i=start_day;i<=end_day;i++){correct_sum+=leitner_box->every_day_activity[i].correct_num;}return correct_sum;}();
    return_value += std::to_string(correct_sum)+"\n";
    return_value += output::GET_REPORT_THIRD_LINE;
    int wrong_sum = [leitner_box, start_day, end_day](){int wrong_sum{0};for(int i=start_day;i<=end_day;i++){wrong_sum+=leitner_box->every_day_activity[i].wrong_num;}return wrong_sum;}();
    return_value += std::to_string(wrong_sum)+"\n";
    return_value += output::GET_REPORT_FORTH_LINE;
    return_value += std::to_string(correct_sum+wrong_sum)+"\n";
    return std::string_view{return_value};
}

std::string_view processInput::prgReportFunc (std::vector<std::string> command, leitner* leitner_box)
{
    return_value.clear();
    return_value += output::GET_PRG_RPT_FIRST_LINE;
    return_value += [leitner_box](){return std::to_string(leitner_box->today)+"\n";}();
    return_value += output::GET_PRG_RPT_SECOND_LINE;
    return_value += [leitner_box](){return std::to_string(leitner_box->streak)+"\n";}();
    return_value += output::GET_PRG_RPT_THIRD_LINE;
    return_value += [leitner_box](){return std::to_string(leitner_box->total_day_participated)+"\n";}();
    return_value += output::GET_PRG_RPT_FORTH_LINE;
    return_value += [leitner_box](){return std::to_string(leitner_box->mastered_cards_num)+"\n";}();
    return_value += output::GET_PRG_RPT_FIFTH_LINE;
    return_value += output::GET_PRG_RPT_SIXTH_LINE;
    return std::string_view{return_value};
}

std::string_view processInput::nextdayFunc (std::vector<std::string> command, leitner* leitner_box)
{  
    endofDayMoveCards (leitner_box);
    nesseceryChanges (leitner_box);
    return_value.clear();
    return_value += output::NEXT_DAY_FIRST_LINE1;
    return_value += std::to_string(leitner_box->today);
    return_value += output::NEXT_DAY_FIRST_LINE2;
    return_value += output::NEXT_DAY_SECOND_LINE;
    return_value += std::to_string(leitner_box->streak)+"\n";
    return_value += output::NEXT_DAY_THIRD_LINE;
    return std::string_view{return_value};
}