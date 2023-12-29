// Answer.hpp
#pragma once
#include <SFML/Graphics.hpp>

class Answer
{
private:
    std::string AnswerText;
    bool RightAnswer;
public:
    Answer() = default;
    Answer(std::string AnswerText, bool RightAnswer);

    std::string getText(){
        return AnswerText;
    }

    bool getBool(){
        return RightAnswer;
    }
    ~Answer() = default;
};

