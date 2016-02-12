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

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "non-copyable.h"
#include "simple-assert.h"
#include <utility>

namespace patterns {
    template<typename Base_Type>
    class Singleton : public Non_Copyable {
    public:
        template<typename... Base_Type_Arguments>
        static void init(Base_Type_Arguments&& ...args) {
            SPL_ASSERT(!m_pInst, "An instance exists when calling Singleton::init");
            m_pInst = new Base_Type(std::forward<Base_Type_Arguments>(args)...);
        }

        virtual ~Singleton() {
            SPL_ASSERT(m_pInst, "No instance exists when calling Singleton::~Singleton");
            m_pInst = nullptr;
        }

        static void destroy() {
            SPL_ASSERT(m_pInst, "No instance exists when calling Singleton::destroy");
            delete m_pInst;
        }

        static Base_Type& get() {
            return *getp();
        }

        static Base_Type* getp() {
            SPL_ASSERT(m_pInst, "No instance exists when calling Singleton::getp");
            return m_pInst;
        }

        static bool exists() {
            return m_pInst != nullptr;
        }

    protected:
        Singleton() = default;

    private:
        static Base_Type* m_pInst;
    };
}

template <typename Base_Type>
Base_Type* patterns::Singleton<Base_Type>::m_pInst = nullptr;

#endif // _SINGLETON_H_
