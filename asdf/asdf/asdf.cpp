//> ```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <stack>

bool CheckValidParentheses(const std::string& s)
{
    std::stack<char> Parent;
    
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            Parent.push(s[i]);
        }
        if (s[i] == ')' || s[i] == '}' || s[i] == ']')
        {
            if (!Parent.empty())
            {
                if (s[i] == ')')
                {
                    if ( Parent.top() == '(')
                    {
                        Parent.pop();
                    }
                    else
                    {
                        return false;
                    }
                    
                }else if (s[i] == '}')
                {
                    if (Parent.top() == '{')
                    {
                        Parent.pop();
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (s[i] == ']')
                {
                    if (Parent.top() == '[')
                    {
                        Parent.pop();
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else {
                return false;
            }
        }
    }
    
    if (Parent.empty())
    {
        return true;
    }

    // 괄호의 짝이 맞는지 확인하세요.
    // 예) "()" => true, "()[]{}" => true, "(]" => false, "([)]" => false, "{[]}" => true
    // Hint: 스택을 사용하세요.
    // 일단, 시도 하세. 다음 시간에 함께 풀어 봅시다.
    return false;
}

int main()
{
    std::string input;

    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

        // Valid Parentheses
    std::cout << "Valid Parentheses: " << CheckValidParentheses(input) << std::endl;

    return 0;
}