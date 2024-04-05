#include <iostream>

using namespace std;


template<typename T> struct Que {
    
private:    
    const int MAX_QUE = 10;
    T array[10];
    int front_index = 0;
    int rear_index = 0;
public:
    bool isEmpty() {
        return front_index == rear_index;
    }

    bool isFull() {
        return (rear_index + 1) % MAX_QUE == front_index;
    }

    void Enqueue(T data) {
        if (isFull()) {
            cout << "Que is full Enqueue fail" << endl;
            return;
        }
        array[rear_index] = data;
        rear_index++;
        rear_index = rear_index % MAX_QUE;
    }

    T Front() {
        return array[front_index];
    }

    void Dequeue() {
        if (isEmpty()) {
            cout << "Que is Empty Dequeue fail" << endl;
            return;
        }
        array[front_index] = NULL;
        front_index++;
        front_index = front_index % MAX_QUE;
    }

    int Size() {
        if (front_index > rear_index)
            return MAX_QUE + (rear_index - front_index);
        else
            return rear_index - front_index;
    }

    void PacthAll() {
        while (!isEmpty())
        {
            cout << Front() << endl;
            Dequeue();
        }
    }
};




int main()
{
    Que<char> MyQue;
    
    while (true) {
        char a;
        cout << "문자 입력 0:정지 후 일괄 출력 1:출력" << endl;
        cin >> a;
        if (a == '0')
        {
            break;
        }
        if (a == '1') {
            cout << MyQue.Front() << endl;
            MyQue.Dequeue();
        }
        else {
            MyQue.Enqueue(a);
        }
    }

    MyQue.PacthAll();
    

    /*cout << "empty++" << "size " << MyQue.Size() << endl;
    cout << MyQue.Front() << endl;
    MyQue.Dequeue();*/
    

    return 0;
}

