// Answer.hpp
#pragma once
#include <SFML/Graphics.hpp>

class Answer
{
private:
    std::string AnswerText;
    bool RightAnswer;
    unsigned int Id;
public:
    Answer() = default;
    Answer(std::string AnswerText, bool RightAnswer, unsigned int Id);

    std::string getText(){
        return AnswerText;
    }

    bool getBool(){
        return RightAnswer;
    }

    unsigned int getId(){
        return Id;
    }
    ~Answer() = default;
};

