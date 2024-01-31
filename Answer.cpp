// answer.cpp
#include "Answer.hpp"

Answer::Answer(std::string AnswerChoice, std::vector<std::string> AnswerText, unsigned int Id):
    AnswerChoice(AnswerChoice),
    Id(Id),
    AnswerText(AnswerText)
{
}