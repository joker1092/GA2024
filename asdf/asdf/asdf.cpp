#include <iostream>
#include <stack>
#include <string>

void Enter(int input, char from, char stop, char to) {
    std::cout << "Enter" << input << "-" << from << "-" << stop << "-" << to << std::endl;
}

void Leave(int input, char from, char stop, char to) {

    std::cout << "Leave" << input << "-" << from << "-" << stop << "-" << to << std::endl;
}

bool move(std::stack<int>& from, std::stack<int>& over, std::stack<int>& to) {
    while (!from.empty()) {
        int ring = from.top();
        if (to.empty()) {
            to.push(ring);
            from.pop();
            std::cout << ring << "to move" << std::endl;
        }
        else if (ring < to.top())
        {
            to.push(ring);
            from.pop();
            std::cout << ring << "to move" << std::endl;
        }
        else if(over.empty()) {
            over.push(ring);
            from.pop();
            std::cout << ring << "to move" << std::endl;
        }
        else if (ring < over.top())
        {
            over.push(ring);
            from.pop();
            std::cout << ring << "to move" << std::endl;
        }
        else {
            std::cout << ring << "to move fail" << std::endl;
            break;
        }
        
    }
    return false;
}

void printtower(std::stack<int>* tower) {
    if (tower[0].empty()) {
        std::cout << "A is empty()" << std::endl;
    }
    else {
        std::cout << "A is top()"<< tower[0].top() << std::endl;
    }
    if (tower[1].empty()) {
        std::cout << "b is empty()" << std::endl;
    }
    else {
        std::cout << "b is top()" << tower[1].top() << std::endl;
    }
    if (tower[2].empty()) {
        std::cout << "c is empty()" << std::endl;
    }
    else {
        std::cout << "c is top()" << tower[2].top() << std::endl;
    }
}

void Hanoi(int input, std::stack<int>* tower) {
    int a = 0;
    int b = 1;
    int c = 2;
    while (true) {
        
        
        if (!tower[0].empty() && !tower[1].empty() && !tower[2].empty())
        {
            move(tower[b], tower[c], tower[a]);
            /*a++; b++; c++;
            a = a > 2 ? 0 : a;
            b = b > 2 ? 0 : b;
            c = c > 2 ? 0 : c;*/
            a--; b--; c--;
            a = a < 0 ? 2 : a;
            b = b < 0 ? 2 : b;
            c = c < 0 ? 2 : c;
            
        }
        else if(tower[0].empty()) {
            move(tower[a], tower[b], tower[c]);
           /* a++; b++; c++;
            a = a > 2 ? 0 : a;
            b = b > 2 ? 0 : b;
            c = c > 2 ? 0 : c;*/
            a--; b--; c--;
            a = a < 0 ? 2 : a;
            b = b < 0 ? 2 : b;
            c = c < 0 ? 2 : c;
        }
        else {
            move(tower[a], tower[b], tower[c]);
            a++; b++; c++;
            a = a > 2 ? 0 : a;
            b = b > 2 ? 0 : b;
            c = c > 2 ? 0 : c;
        }
        if (!tower[2].empty() && tower[2].size() == input) {
            break;
        }
        
        
    }
  /*  move(tower[0], tower[1],tower[2]);
    if (!tower[0].empty()&& !tower[1].empty()&& !tower[2].empty())
    {
        move(tower[2],tower[0],tower[1]);
        move(tower[0],tower[1],tower[2]);
    }
    if (tower[0].empty()) {
        move(tower[1], tower[2], tower[0]);
        move(tower[0], tower[1], tower[2]);
    }*/
    
    printtower(tower);
}

int main()
{
    std::stack<int> tower[3];
    std::string input;

    std::cout << "원판의 개수를 입력하세요(1~5) : ";
    std::getline(std::cin, input);
    int ring = stoi(input);
    for (size_t i = ring; 0 < i; i--)
    {
        tower[0].push(i);
    }

    Hanoi(ring, tower);

    return 0;
}


//void Hanoi(int input, char from, char stop, char to) {
//
//    if (input == 0) { return; }
//    //Enter(input, from, stop, to);
//    Hanoi(input - 1, from, to, stop);
//    std::cout << "원판" << input << "을" << from << "에서" << to << "로 이동" << std::endl;
//    Hanoi(input - 1, stop, from, to);
//    //Leave(input, from, stop, to);
//}
//
//int main()
//{
//    std::string input;
//
//    std::cout << "원판의 개수를 입력하세요(1~5) : ";
//    std::getline(std::cin, input);
//
//    Hanoi(stoi(input), 'A', 'B', 'C');
//
//    return 0;
//}