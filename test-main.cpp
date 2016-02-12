/**
Copyright (c) 2016 Mariano Gonzalez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <iostream>
#include <string>
#include "singleton.h"

class Test_Singleton : public patterns::Singleton<Test_Singleton> {
public:
    void print_something() {
        std::cout << "Hey! I'm printing from the singleton instance!\n"
            << "Here is my first constructor parameter: \"" << m_fp
            << "\" and here is the second one \"" << m_sp << "\"!\n";
    }

protected:
    friend class patterns::Singleton<Test_Singleton>;
    Test_Singleton(int firstParam, std::string secondParam)
        : m_fp(firstParam)
        , m_sp(secondParam) {}

private:
    int m_fp;
    std::string m_sp;
};

void use_the_singleton() {
    std::cout << "Here's the Singleton doing something:\n";
    Test_Singleton::get().print_something();
    std::cout << "Now, here is the singleton doing the same, but called from a pointer, instead of a reference:\n";
    Test_Singleton::getp()->print_something();
}

int main() {
    if (!Test_Singleton::exists()) {
        std::cout << "As you can see, the singleton doesn't exists at this point.\n";
    } else {
        SPL_FALSE_ASSERT("Something went wrong, the singleton should not exists at this point.");
    }

    Test_Singleton::init(42, "Is the answer");

    if (Test_Singleton::exists()) {
        std::cout << "As you can see, the singleton exists now.\n";
    } else {
        SPL_FALSE_ASSERT("Something went wrong, the singleton should exists at this point.");
    }

    //Now, use the singleton as a singleton is :), no need to pass it around.
    use_the_singleton();

    // Time to destroy the singleton, so we don't leak its resources.
    Test_Singleton::destroy();

    if (!Test_Singleton::exists()) {
        std::cout << "As you can see, the singleton doesn't exists anymore and its resources were released.\n";
    } else {
        SPL_FALSE_ASSERT("Something went wrong, the singleton should not exists at this point.");
    }
}
