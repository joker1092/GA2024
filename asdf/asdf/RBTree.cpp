//### Rule

//1. ��� ���� �� �Ǵ� �����̴�.
//2. ��Ʈ ���� ���̴�.
//3. ��� ����(Null) ���� ���̴�.
//4. ��� ���� ��忡�� ��Ʈ ������ ��ο� ���Ե� �� ����� ������ ����.
//5. ���� ��尡 ���ӵ� ��δ� ����. (���� ���� �Ұ�)

#include <iostream>
#include <queue>
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


    //- ���� ȸ��
    //- ���� ����� ������ �ڽ��� ���� Ʈ���� ���ο� ��Ʈ�� �����.
    //- ���� ��Ʈ�� ���ο� ��Ʈ�� ���� �ڽ����� �����.
    void RotateLeft(Node* node) {
        Node* prevRoot = node;
        Node* parent = node->parent;
        Node* newRoot = node->right;

        //-���� ����� ������ �ڽ��� ���� Ʈ���� ���ο� ��Ʈ�� �����.
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
        //-���� ��Ʈ�� ���ο� ��Ʈ�� ���� �ڽ����� �����.
        newRoot->left = prevRoot;
        prevRoot->parent = newRoot;

        if (newRoot->left != nullptr && newRoot->right != nullptr) {
            newRoot->color = BLACK;
            newRoot->left->color = RED;
            newRoot->right->color = RED;
        }
    }
    //- ������ ȸ��
    //- ���� ����� ���� �ڽ��� ���� Ʈ���� ���ο� ��Ʈ�� �����.
    // - ���� ��Ʈ�� ���ο� ��Ʈ�� ������ �ڽ����� �����.
    void RotateRight(Node* node) {
        Node* prevRoot = node;
        Node* parent = node->parent;
        Node* newRoot = node->left;

        //-���� ����� ���� �ڽ��� ���� Ʈ���� ���ο� ��Ʈ�� �����.
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
        //-���� ��Ʈ�� ���ο� ��Ʈ�� ������ �ڽ����� �����.
        newRoot->right = prevRoot;
        prevRoot->parent = newRoot;

        if (newRoot->left != nullptr && newRoot->right != nullptr) {
            newRoot->color = BLACK;
            newRoot->left->color = RED;
            newRoot->right->color = RED;
        }
    }


    void Insert(int data) {
        //[Step 1] ���� Ž�� Ʈ�� ��Ģ�� ���� �����ϰ� ���� ���ԵǴ� ���[N]�� ����� �����մϴ�
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
        //- [Step 2] ���� ���ԵǴ� ���, [N]�� ��Ʈ���? 2�� ��Ģ�� ���� ������ �����ϰ� ����
        if (parent == nullptr) {
            root = newNode;
        }
        else if (parent->data > newNode->data) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        //[Step 3] [N]�� �θ�[P]�� ������ ���, 
         // Restructuring && Recoloring
        while (newNode != root && newNode->parent->color == RED) {
            //[N]�� �θ�[P]�� ������ ���, ���θ�[G]�� ���Դϴ�.
            Node* parent = newNode->parent;
            Node* grandParent = parent->parent;
            // �θ��� ���� ���[U]�� Ȯ��
            Node* uncle = nullptr;
            if (parent == grandParent->left)
            {
                uncle = grandParent->right;
                //�θ��� ���� ��尡 ������ ������ ���ų� ���� ���̰� ���θ� ���Դϴ�.
                // ��, 4�� ��Ģ�� ���� �ϱ� ���� �θ��� ���� ���� �θ��� ���� ������ �ٲٰ� ���θ� ����� �ٲߴϴ�.

                if (uncle != nullptr && uncle->color == RED)
                {
                    //- [U] �� �����̸� Recoloring!
                    //     -[U] ��[P]�� ������ ���θ�[G]�� ����� ����.
                    //    - [G] �� ��Ʈ��� ������ ����  �� 2�� ��Ģ
                    //    - [G] �� ���� ���尡 �߻��ϸ�[G]�� �������� ���� ���� �ذ� �ݺ�

                        //-[U] ��[P]�� ������ ���θ�[G]�� ����� ����.
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandParent->color = RED;
                    //    - [G] �� ���� ���尡 �߻��ϸ�[G]�� �������� ���� ���� �ذ� �ݺ�
                    // -->newNode�� grandParent�ְ� while������ parent�� �������� Ȯ���Ͽ� �����尡 ������ ���������� �ݺ�
                    newNode = grandParent;
                }
                //�θ��� ���� ��尡 ���ų� ���̶�� 4�� ��Ģ�� �����ϱ� ���� 
                // ���ο� ��带 �θ�[��]�� �ϰ� ���, ���θ�� �θ� �ڽ�[����]�� �մϴ�.
                else {
                    //[P] ��[N] �� �θ� - �ڽ� ���踦 �ٲ۴�.

                    if (newNode == parent->right)
                    {
                        // [N]��[P] �� ������ �ڽ��̹Ƿ� ���� ȸ��
                        RotateLeft(parent);
                    }
                    //else {
                    //    // [N]��[P] �� ���� �ڽ��̹Ƿ� ������ ȸ��
                    //    RotateRight(parent);
                    //}
                    //[N]�� [G]�� �θ�-�ڽ� ���踦 �ٲ۴�.

                    //[N]��[G]��  ���� �ڽ��̹Ƿ� ������ ȸ��.
                    RotateRight(grandParent);
                }
            }
            else {
                uncle = grandParent->left;
                //�θ��� ���� ��尡 ������ ������ ���ų� ���� ���̰� ���θ� ���Դϴ�.
                // ��, 4�� ��Ģ�� ���� �ϱ� ���� �θ��� ���� ���� �θ��� ���� ������ �ٲٰ� ���θ� ����� �ٲߴ�z��.
                if (uncle != nullptr && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandParent->color = RED;
                    newNode = grandParent;
                }
                //�θ��� ���� ��尡 ���ų� ���̶�� 4�� ��Ģ�� �����ϱ� ���� 
                // ���ο� ��带 �θ�[��]�� �ϰ� ���, ���θ�� �θ� �ڽ�[����]�� �մϴ�.
                else {
                    //[P] ��[N] �� �θ� - �ڽ� ���踦 �ٲ۴�.

                    if (newNode == parent->left)
                    {
                        // [N]��[P] �� ���� �ڽ��̹Ƿ� ������ ȸ��
                        RotateRight(parent);
                    }
                    //else {
                    //    // [N]��[P] �� ������ �ڽ��̹Ƿ� ���� ȸ��
                    //    RotateLeft(parent);
                    //}
                    //[N]�� [G]�� �θ�-�ڽ� ���踦 �ٲ۴�.

                    //[N]��[G]��  ������ �ڽ��̹Ƿ� ���� ȸ��.
                    RotateLeft(grandParent);
                }
            }
        }
        //    - [G] �� ��Ʈ��� ������ ����  �� 2�� ��Ģ
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


    void printDsf()
    {
        Node* node = root;
        queue<Node*> v;
        v.push(node);

        while (v.size() != 0)
        {
            Node* node = v.front();
            v.pop();
            if (node == nullptr) {
                cout << "null" << endl;
            }
            else {
                cout << "data: " << node->data << " level: " << GetLevel(node) << endl;
                v.push(node->left);
                v.push(node->right);
            }

        }
    }

    void Print() {


    }
};


int main()
{
    RBTree tree;
    tree.Insert(10);
    tree.printDsf();
    cout << "----------------" << endl;
    tree.Insert(20);
    tree.printDsf();
    cout << "----------------" << endl;
    tree.Insert(30);
    tree.printDsf();
    cout << "----------------" << endl;
    tree.Insert(15);
    tree.printDsf();
    cout << "----------------" << endl;
    tree.Insert(25);
    tree.printDsf();
    cout << "----------------" << endl;
    tree.Insert(35);
    tree.printDsf();
    cout << "----------------" << endl;



}
