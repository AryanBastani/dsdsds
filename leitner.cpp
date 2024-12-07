#include "leitner.hpp"

leitner::leitner()
{
    today = 1;
    streak = 0;
    total_day_participated = 0;
    mastered_cards_num = 0;

    every_day_activity[1].correct_num = 0;
    every_day_activity[1].wrong_num = 0;
    every_day_activity[1].reviewed = false;
    every_day_activity[1].participated = false;

    box_review_today box{false, false};
    boxes_to_review_today[MONTHLY_BOX] = box;
    boxes_to_review_today[WEEKLY_BOX] = box;
    boxes_to_review_today[THREE_DAY_BOX] = box;
    box = {true, false};
    boxes_to_review_today[EVERY_DAY_BOX] = box;

    boxes_map = {
        {MONTHLY_BOX, monthly_box},
        {WEEKLY_BOX, weekly_box},
        {THREE_DAY_BOX, every_three_day_box},
        {EVERY_DAY_BOX, every_day_box}
    };
}

leitner::~leitner()
{
    for (auto i : monthly_box)
    {
        delete i;
    }
    for (auto i : weekly_box)
    {
        delete i;
    }
    for (auto i : every_three_day_box)
    {
        delete i;
    }
    for (auto i : every_day_box)
    {
        delete i;
    }
}