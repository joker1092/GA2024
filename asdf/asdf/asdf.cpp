//### Rule

//1. 모든 노드는 블랙 또는 레드이다.
//2. 루트 노드는 블랙이다.
//3. 모든 리프(Null) 노드는 블랙이다.
//4. 모든 리프 노드에서 루트 노드까지 경로에 포함된 블랙 노드의 개수는 같다.
//5. 레드 노드가 연속된 경로는 없다. (더블 레드 불가)

#include <iostream>

using namespace std;

enum Color
{
    RED,
    BLACK
};


struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int index;
    Color color;		//0: red, 1: black
};

struct RBTree {

    Node* root = nullptr;

      
    //- 왼쪽 회전
    //- 기준 노드의 오른쪽 자식을 서브 트리의 새로운 루트로 만든다.
    //- 이전 루트를 새로운 루트의 왼쪽 자식으로 만든다.
    void RotateLeft(Node* node) {
        Node* prevRoot = node;
        Node* parent = node->parent;
        Node* newRoot = node->right;

        //-기준 노드의 오른쪽 자식을 서브 트리의 새로운 루트로 만든다.
        if (parent == nullptr)
        {
            root = newRoot;
        }
        else if (parent->left == prevRoot) {
            parent->left = newRoot;
        }
        else {
            parent->right = newRoot;
        }
        newRoot->parent = parent;
        prevRoot->right = nullptr;
        //-이전 루트를 새로운 루트의 왼쪽 자식으로 만든다.
        newRoot->left = prevRoot;
        prevRoot->parent = newRoot;

    }
    //- 오른쪽 회전
    //- 기준 노드의 왼쪽 자식을 서브 트리의 새로운 루트로 만든다.
    // - 이전 루트를 새로운 루트의 오른쪽 자식으로 만든다.
    void RotateRight(Node* node) {
        Node* prevRoot = node;
        Node* parent = node->parent;
        Node* newRoot = node->left;

        //-기준 노드의 왼쪽 자식을 서브 트리의 새로운 루트로 만든다.
        if (parent == nullptr)
        {
            root = newRoot;
        }
        else if (parent->left == prevRoot) {
            parent->left = newRoot;
        }
        else {
            parent->right = newRoot;
        }
        newRoot->parent = parent;
        prevRoot->left = nullptr;
        //-이전 루트를 새로운 루트의 오른쪽 자식으로 만든다.
        newRoot->right = prevRoot;
        prevRoot->parent = newRoot;

        
    }


    void Insert(int data) {
        //[Step 1] 이진 탐색 트리 규칙에 따라 삽입하고 새로 삽입되는 노드[N]는 레드로 설정합니다
        Node* newNode = new Node;
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = nullptr;
        newNode->color = RED;

        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (current->data > newNode->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        newNode->parent = parent;
        //- [Step 2] 새로 삽입되는 노드, [N]이 루트라면? 2번 규칙에 의해 블랙으로 설정하고 리턴
        if (parent == nullptr) {
            root = newNode;
        }
        else if (parent->data > newNode->data){
            parent->left = newNode;
        }else{
            parent->right = newNode;
        }

        //[Step 3] [N]의 부모[P]가 레드인 경우, 
         // Restructuring && Recoloring
        while (newNode != root && newNode->parent->color == RED) {
            //[N]의 부모[P]가 레드인 경우, 조부모[G]는 블랙입니다.
            Node* parent = newNode->parent;
            Node* grandParent = parent->parent;
            // 부모의 형제 노드[U]를 확인
            Node* uncle = nullptr;
            if (parent == grandParent->left)
            {
                uncle = grandParent->right;
                //부모의 형제 노드가 레드라면 사촌은 없거나 블랙일 것이고 조부모도 블랙입니다.
                // 즉, 4번 규칙을 유지 하기 위해 부모의 형제 노드와 부모의 색을 블랙으로 바꾸고 조부모를 레드로 바꿉니다.
                
                if (uncle != nullptr && uncle->color==RED )
                {
                //- [U] 가 레드이면 Recoloring!
                //     -[U] 와[P]를 블랙으로 조부모[G]를 레드로 변경.
                //    - [G] 가 루트라면 블랙으로 변경  → 2번 규칙
                //    - [G] 가 더블 레드가 발생하면[G]를 기준으로 더블 레드 해결 반복
               
                    //-[U] 와[P]를 블랙으로 조부모[G]를 레드로 변경.
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandParent->color = RED;
                    //    - [G] 가 더블 레드가 발생하면[G]를 기준으로 더블 레드 해결 반복
                    // -->newNode에 grandParent넣고 while문에서 parent가 레드인지 확인하여 더블레드가 나오지 않을때까지 반복
                    newNode = grandParent;
                }
                //부모의 형제 노드가 없거나 블랙이라면 4번 규칙을 유지하기 위해 
                // 새로운 노드를 부모[블랙]로 하고 대신, 조부모와 부모를 자식[레드]로 합니다.
                else {
                    //[P] 와[N] 이 부모 - 자식 관계를 바꾼다.

                    if (newNode == parent->right)
                    {
                        // [N]이[P] 의 오른쪽 자식이므로 왼쪽 회전
                        RotateLeft(parent);
                    }
                    else {
                       // [N]이[P] 의 왼쪽 자식이므로 오른쪽 회전
                        RotateRight(parent);
                    }
                    //[N]과 [G]의 부모-자식 관계를 바꾼다.

                    //[N]이[G]의  왼쪽 자식이므로 오른쪽 회전.
                    RotateRight(grandParent);
                }
            }
            else {
                uncle = grandParent->left;
                //부모의 형제 노드가 레드라면 사촌은 없거나 블랙일 것이고 조부모도 블랙입니다.
                // 즉, 4번 규칙을 유지 하기 위해 부모의 형제 노드와 부모의 색을 블랙으로 바꾸고 조부모를 레드로 바꿉니z다.
                if (uncle != nullptr && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandParent->color = RED;
                    newNode = grandParent;
                }
                //부모의 형제 노드가 없거나 블랙이라면 4번 규칙을 유지하기 위해 
                // 새로운 노드를 부모[블랙]로 하고 대신, 조부모와 부모를 자식[레드]로 합니다.
                else {
                    //[P] 와[N] 이 부모 - 자식 관계를 바꾼다.

                    if (newNode == parent->right)
                    {
                        // [N]이[P] 의 오른쪽 자식이므로 왼쪽 회전
                        RotateLeft(parent);
                    }
                    else {
                        // [N]이[P] 의 왼쪽 자식이므로 오른쪽 회전
                        RotateRight(parent);
                    }
                    //[N]과 [G]의 부모-자식 관계를 바꾼다.

                    //[N]이[G]의  오른쪽 자식이므로 왼쪽 회전.
                    RotateLeft(grandParent);
                }
            }
        }
        //    - [G] 가 루트라면 블랙으로 변경  → 2번 규칙
        root->color = BLACK;
    }

    void Remove(int data) {

    }


    int GetLevel(Node* node)
    {
        int level = 0;
        while (node != root)
        {
            node = node->parent;
            level++;
        }
        return level;
    }


    void Print(Node* node) {
        Node* temp = node;

        if (temp == nullptr) return;
        char color = temp->color == RED ? 'R' : 'B';

        
        char isPanent = temp->parent != nullptr ? temp->parent->left == temp ? 'L' : 'R' : 'N';
        cout << temp->data << color << GetLevel(temp) << isPanent << endl;
        Print(temp->left);
        Print(temp->right);
    }
};


int main()
{
    RBTree tree;
    tree.Insert(10);
    tree.Print(tree.root);
    cout << "----------------" << endl;
    tree.Insert(20);
    tree.Print(tree.root);
    cout << "----------------" << endl;
    tree.Insert(30);
    tree.Print(tree.root);
    cout << "----------------" << endl;
    tree.Insert(15);
    tree.Print(tree.root);
    cout << "----------------" << endl;
    tree.Insert(25);
    tree.Print(tree.root);
    cout << "----------------" << endl;
    tree.Insert(35);
    tree.Print(tree.root);
    cout << "----------------" << endl;


    
}
