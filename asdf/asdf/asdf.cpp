#include <iostream>
#include <string>

void Enter(int input, char from, char stop, char to) {
    std::cout << "Enter" << input << "-" << from << "-" << stop << "-" << to << std::endl;
}

void Leave(int input, char from, char stop, char to) {

    std::cout << "Leave" << input << "-" << from << "-" << stop << "-" << to << std::endl;
}


void Hanoi(int input, char from, char stop, char to) {

    if (input == 0) { return; }
    //Enter(input, from, stop, to);
    Hanoi(input - 1, from, to, stop);
    std::cout << "원판" << input << "을" << from << "에서" << to << "로 이동" << std::endl;
    Hanoi(input - 1, stop, from, to);
    //Leave(input, from, stop, to);
}

int main()
{
    std::string input;

    std::cout << "원판의 개수를 입력하세요(1~5) : ";
    std::getline(std::cin, input);

    Hanoi(stoi(input), 'A', 'B', 'C');

    return 0;
}





// bool move(std::stack<int>& from, std::stack<int>& over, std::stack<int>& to) {
//    while (!from.empty()) {
//        int ring = from.top();
//        int count = from.size();
//        std::cout << "ring : " << ring << " size count : "<<count << std::endl;
//        if (count != 1) {
//            if (to.empty()) {
//                to.push(ring);
//                from.pop();
//                std::cout << ring << "to move" << std::endl;
//            }
//            else if (ring < to.top())
//            {
//                to.push(ring);
//                from.pop();
//                std::cout << ring << "to move" << std::endl;
//            }
//            else if (over.empty()) {
//                over.push(ring);
//                from.pop();
//                std::cout << ring << "to move over" << std::endl;
//            }
//            else if (ring < over.top())
//            {
//                over.push(ring);
//                from.pop();
//                std::cout << ring << "to move over" << std::endl;
//            }
//            else 
//            {
//                std::cout << ring << "to move fail" << std::endl;
//                break;
//            }
//        }
//        else {
//            if (to.empty()) {
//                to.push(ring);
//                from.pop();
//                std::cout << ring << "to move" << std::endl;
//            }
//            else if (ring < to.top())
//            {
//                to.push(ring);
//                from.pop();
//                std::cout << ring << "to move" << std::endl;
//            }
//            else {
//                if (over.empty())
//                {
//                    over.push(to.top());
//                    std::cout << to.top() << "to move  over" << std::endl;
//                    to.pop();
//                }
//                else if (to.top() < over.top())
//                {
//                    over.push(to.top());
//                    std::cout << to.top() << "to move  over" << std::endl;
//                    to.pop();
//                }
//                else {
//                    std::cout << ring << "to move fail" << std::endl;
//                    break;
//                }
//            }
//        }
//                
//    }
//    return false;
//}
//
//
//void Hanoi(int input, std::stack<int>* tower) {
//    
//    while (true) {
//        std::cout << "A" << "B" << "C" << std::endl;
//        move(tower[0], tower[1], tower[2]);
//        if (!tower[2].empty() && tower[2].size() == input) {
//            break;
//        }
//        std::cout << "B" << "A" << "C" << std::endl;
//        move(tower[1], tower[0], tower[2]);
//        if (!tower[2].empty() && tower[2].size() == input) {
//            break;
//        }
//    }
//  
//    
//}
//
//int main()
//{
//    std::stack<int> tower[3];
//    std::string input;
//
//    std::cout << "원판의 개수를 입력하세요(1~5) : ";
//    std::getline(std::cin, input);
//    int ring = stoi(input);
//    for (size_t i = ring; 0 < i; i--)
//    {
//        tower[0].push(i);
//    }
//
//    Hanoi(ring, tower);
//
//    return 0;
//}