// 1/2/2024 - nyandisk :D
//do whatever your heart desires with this code
//it might even be better if you do
//since i'm not the best at writing C++

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
namespace quiz{

    // Constants for different strings | not necessarily needed but making changes is easier.
    const std::string CORRECT = "[*] You are correct!";
    const std::string INCORRECT = "[!] Nuh uh. It is in fact: ";
    const std::string INT_CONVERSION_ERROR = "Couldn't convert your answer into an integer. Try again.";
    const std::string RANGE_EXCEPTION = "Your answer is out of range. Try again.";

    /// <summary>
    /// Abstract base class to be inherited by different question types.
    /// </summary>
    class Question {
    private:
        std::string prompt;
    public:
        Question(const std::string& prompt) : prompt(prompt) {}
        virtual bool ask() const = 0;
        virtual ~Question() {}
        std::string getPrompt() const {
            return prompt;
        }
        void delim() const {
            std::cout << "##################################################" << std::endl;
        }
    };
    /// <summary>
    /// A simple typing question with a prompt and one correct (case-sensitive or insensitive) answer.
    /// </summary>
    class TypingQuestion : public Question {
    private:
        std::string correctAnswer;
        bool caseSensitive;
    public:
        /// <summary>
        /// Default constructor for TypingQuestion
        /// </summary>
        /// <param name="prompt">The question to prompt the user with</param>
        /// <param name="correctAnswer">The correct answer</param>
        /// <param name="caseSensitive">Is the answer case sensitive?</param>
        TypingQuestion(const std::string& prompt, const std::string& correctAnswer, const bool caseSensitive) :
            Question(prompt), correctAnswer(correctAnswer), caseSensitive(caseSensitive) {}
        bool ask() const override {
            delim();
            std::cout << "[?] Typing Question:" << std::endl;
            std::cout << getPrompt() << std::endl;
            std::cout << "-> ";
            std::string userGuess;
            std::cin >> userGuess;
            delim();
            bool correct = (caseSensitive ? (correctAnswer == userGuess) : (toLowercase(correctAnswer) == toLowercase(userGuess)));
            if (correct) {
                std::cout << CORRECT << std::endl;
            }
            else {
                std::cout << INCORRECT << correctAnswer << std::endl;
            }
            return correct;
        }
    private:
        std::string toLowercase(const std::string& str) const {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(),
                [](unsigned char c) { return std::tolower(c); });
            return result;
        }
    };
    /// <summary>
    /// A simple multiple choice question that has one correct choice, and other filler choices.
    /// </summary>
    class MSQuestion : public Question {
    private:
        std::vector<std::string> choices;
        std::string correctChoice;
    public:
        /// <summary>
        /// Default constructor
        /// </summary>
        /// <param name="prompt">The question to prompt the user with</param>
        MSQuestion(const std::string& prompt) : Question(prompt) {}
        bool ask() const override {
            unsigned int userGuess = 1;
            while (true) {
                if (choices.empty()) {
                    std::cerr << "WARN: Your question has no answers" << std::endl;
                }
                delim();
                std::cout << "[?] Multiple Choice Question:" << std::endl;
                std::cout << getPrompt() << std::endl;
                for (size_t i = 0; i < choices.size(); ++i) {
                    std::cout << i + 1 << ") " << choices[i] << std::endl;
                }
                std::cout << "-> ";
                std::string userGuessString;
                std::cin >> userGuessString;
                try {
                    userGuess = std::stoi(userGuessString);
                    if (userGuess <= 0 || userGuess > choices.size()) {
                        std::cerr << RANGE_EXCEPTION << std::endl;
                        continue;
                    }
                    else {
                        delim();
                        bool correct = isCorrect(choices[userGuess - 1]);
                        if (correct) {
                            std::cout << CORRECT << std::endl;
                        }
                        else {
                            std::cout << INCORRECT << correctChoice << std::endl;
                        }
                        return correct;
                    }
                }
                catch (std::exception) {
                    std::cerr << INT_CONVERSION_ERROR << std::endl;
                    continue;
                }
            }
        }
        /// <summary>
        /// Add a choice into the filler choices, and mark it as the correct choice if needed
        /// </summary>
        /// <param name="choice">Choice to add</param>
        /// <param name="isCorrect">Is it the correct choice?</param>
        void addChoice(const std::string& choice, const bool isCorrect) {
            choices.push_back(choice);
            if (isCorrect) { correctChoice = choice; }
        }
        /// <summary>
        /// Checks if the provided string matches the answer string
        /// </summary>
        /// <param name="choice">Case-sensitive string to check</param>
        /// <returns>Whether the provided string matches the answer string or not</returns>
        bool isCorrect(const std::string& choice) const {
            return correctChoice == choice;
        }
    };
}
