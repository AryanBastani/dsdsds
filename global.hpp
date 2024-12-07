#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <string_view>
#include <string>
#include <iostream>
#include <vector>
#include <map>

enum box_name_proirity
{
    NOT_INITIALIZED,
    MONTHLY_BOX,
    WEEKLY_BOX,
    THREE_DAY_BOX,
    EVERY_DAY_BOX
};

namespace commands {
    const std::string_view STREAK = "streak";
    const std::string_view ADD_FLASHCARD = "add_flashcard";
    const std::string_view REVIEW_TODAY = "review_today";
    const std::string_view GET_REPORT = "get_report";
    const std::string_view GET_PROGRESS_REPORT = "get_progress_report";
    const std::string_view NEXT_DAY = "next_day";
}

namespace output {
    const std::string_view STREAK_FIRST_LINE = "Your current streak is: ";
    const std::string_view STREAK_SECOND_LINE = "Keep going!\n";

    const std::string_view ADD_FLASHCARD = "flashcards added to the daily box\n";

    const std::string_view REVIEW_TODAY_FIRST_LINE = "Flashcard: ";
    const std::string_view REVIEW_TODAY_SECOND_LINE = "\nYour answer: ";
    const std::string_view REVIEW_TODAY_CORRECT = "Your answer was correct! Well done, keep it up!\n";
    const std::string_view REVIEW_TODAY_WRONG_FIRST = "Your answer was incorrect. Don't worry! The correct answer is: ";
    const std::string_view REVIEW_TODAY_WRONG_SECOND = ". Keep practicing!\n";
    const std::string_view REVIEW_TODAY_LAST_MESSAGE = "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!\n";

    const std::string_view GET_REPORT_FIRST_LINE = "Day: ";
    const std::string_view GET_REPORT_SECOND_LINE = "Correct Answers: ";
    const std::string_view GET_REPORT_THIRD_LINE = "Incorrect Answers: ";
    const std::string_view GET_REPORT_FORTH_LINE = "Total: ";

    const std::string_view GET_PRG_RPT_FIRST_LINE = "Challenge Progress Report:\n\nDay of the Challenge: ";
    const std::string_view GET_PRG_RPT_SECOND_LINE = "Streak: ";
    const std::string_view GET_PRG_RPT_THIRD_LINE = "Total Days Participated: ";
    const std::string_view GET_PRG_RPT_FORTH_LINE = "Mastered Flashcards: ";
    const std::string_view GET_PRG_RPT_FIFTH_LINE = "\n";
    const std::string_view GET_PRG_RPT_SIXTH_LINE = "Keep  up  the  great  work!  You're  making  steady  progress  toward mastering your flashcards.\n";

    const std::string_view NEXT_DAY_FIRST_LINE1 = "Good morning! Today is day ";
    const std::string_view NEXT_DAY_FIRST_LINE2 = " of our journey.\n";
    const std::string_view NEXT_DAY_SECOND_LINE = "Your current streak is: ";
    const std::string_view NEXT_DAY_THIRD_LINE = "Start reviewing to keep your streak!\n";

    const std::string_view END_OF_LINE = "\n";
}

struct flashcard
{
    std::string question;
    std::string answer;
    int last_day_reviewed;
    int wrong_count;
};

struct day_activity {
    int correct_num;
    int wrong_num;
    bool reviewed;
    bool participated;
};

#endif