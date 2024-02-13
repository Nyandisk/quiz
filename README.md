# quiz

A simple library I made for creating short multiple choice or typing questions. It is in no way perfect, but works enough to make my inefficient study methods somewhat efficient.

# Usage
 - Copy `question.hpp` into your project and include it
 - Instantiate a question (`quiz::MSQuestion` or `quiz::TypingQuestion`)
 - Call the question instance's `.ask()` function
   - *Optional: Store the `.ask()` function's return value (whether the question was answered correctly or not) in a variable for later use*

# Example
```cpp
#include "question.hpp"
int main()
{
	quiz::MSQuestion exampleMSQ("1+1=?");
	exampleMSQ.addChoice("2", true);
	exampleMSQ.addChoice("1", false);
	exampleMSQ.addChoice("0", false);
	exampleMSQ.ask();
	quiz::TypingQuestion exampleTyping("Hello _____!", "world", true);
	bool correct = exampleTyping.ask();
	return 0;
}
```
