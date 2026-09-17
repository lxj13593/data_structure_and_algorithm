#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool priority(char v, char v_top)
{
    if ((v == '/' || v == '*') && (v_top == '+' || v_top == '-'))
    {
        return true;
    }
    if (v_top == '(' && v != ')')
    {
        return true;
    }
    return false;
}

string middle_to_end_expr(string expr)
{
    stack<char> s;
    string result;
    for (char v : expr)
    {
        if (v >= '0' && v <= '9')
        {
            result.push_back(v);
        }
        else
        {
            for (;;)
            {
                if (s.empty() || v == '(')
                {
                    s.push(v);
                    break;
                }
                char v_top = s.top();
                if (priority(v, v_top))
                {
                    s.push(v);
                    break;
                }
                else
                {
                    s.pop();
                    if (v_top == '(')
                    {
                        break;
                    }
                    result.push_back(v_top);
                }
            }
        }
    }
    while (s.empty() != 1)
    {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}

int main()
{
    cout << middle_to_end_expr("(1+2)*(3+4)") << endl;
    cout << middle_to_end_expr("2+(4+6)/2+6/3") << endl;
    return 0;
}