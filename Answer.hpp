// Answer.hpp
#pragma once
#include <SFML/Graphics.hpp>

class Answer
{
private:
    std::string AnswerChoice;
    bool RightAnswer;
    unsigned int Id;
    std::vector<std::string> AnswerText;

public:
    Answer() = default;
    Answer(std::string AnswerChoice, std::vector<std::string> AnswerText, unsigned int Id);

    std::string getChoice(){
        return AnswerChoice;
    }

    unsigned int getId(){
        return Id;
    }

    std::vector<std::string> getText(){
        return AnswerText;
    }

    ~Answer() = default;
};

