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
    std::cout << "����" << input << "��" << from << "����" << to << "�� �̵�" << std::endl;
    Hanoi(input - 1, stop, from, to);
    //Leave(input, from, stop, to);
}

int main()
{
    std::string input;

    std::cout << "������ ������ �Է��ϼ���(1~5) : ";
    std::getline(std::cin, input);

    Hanoi(stoi(input), 'A', 'B', 'C');

    return 0;
}