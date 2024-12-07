#ifndef __LEITNER__
#define __LEITNER__

#include "global.hpp"

struct box_review_today
{
    bool must_review;
    bool reviewed_today;
};

class leitner  
{
        int today;
        std::map<int, box_review_today> boxes_to_review_today;
        std::map <int, day_activity> every_day_activity;
        std::map <int, std::vector<flashcard*>> boxes_map;
        int streak;
        int total_day_participated;
        int mastered_cards_num;
        std::vector<flashcard*> monthly_box;
        std::vector<flashcard*> weekly_box;
        std::vector<flashcard*> every_three_day_box;
        std::vector<flashcard*> every_day_box;
    public:
        leitner();
        ~leitner();
        friend class processInput;
        friend void reviewCards (int max_card_num, leitner* leitner_box);
        friend void determineIterator (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box);
        friend void moveCards (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box);
        friend void defineIterator (int &current_box, std::vector<flashcard*>::iterator &card_it, leitner* leitner_box);
        friend void endofDayMoveCards(leitner* leitner_box);
        friend void nesseceryChanges(leitner* leitner_box);
};

#endif