// AVL_tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#ifndef TYPES_H
#define TYPES_H
#include <string>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <time.h>

using namespace std;

typedef struct node
{
    int inf;
    node* left, * right;
} TNode;
#endif // TYPES_H

void initTree(TNode*& root, int cntEl);
void insTree(TNode*& root, TNode* elem);
void findInTree(int key, TNode* root, TNode*& findNode);
void getMaxMin(TNode* root, int& max, int& min);
void delTree(TNode*& root);
void showTree(TNode* root);
void PBDSP(TNode* root);

void task6(TNode*& root);
void task7(TNode*& root);

void initTree(TNode*& root, int cntEl)
{
    TNode* pNew;
    root = NULL;
    srand(time(NULL) | clock());
    for (int i = 0; i < cntEl; i++)
    {
        pNew = new TNode;
        pNew->inf = rand() % 100 - 50;
        pNew->left = NULL;
        pNew->right = NULL;
        insTree(root, pNew);
    }
}
void insTree(TNode*& root, TNode* elem)
{
    if (root == NULL)
    {
        root = elem;
    }
    else
        if (elem->inf < root->inf)
        {
            insTree(root->left, elem);
        }
        else
        {
            insTree(root->right, elem);
        }
}
void findInTree(int key, TNode* root, TNode*& findNode)
{
    if (root == NULL)
    {
        findNode = NULL;
        return;
    }
    if (root->inf > key)
    {
        findInTree(key, root->left, findNode);
    }
    else
        if (root->inf < key)
        {
            findInTree(key, root->right, findNode);
        }
        else
        {
            findNode = root;
            return;
        }
}

void getMaxMin(TNode* root, int& max, int& min)
{
    if (root == NULL)
    {
        return;
    }
    if (root->inf > max)
    {
        max = root->inf;
    }
    if (root->inf < min)
    {
        min = root->inf;
    }
    getMaxMin(root->left, max, min);
    getMaxMin(root->right, max, min);
}

void delTree(TNode*& root)
{
    if (root == NULL)
        return;
    if (root->left != NULL)
        delTree(root->left);
    if (root->right != NULL)
        delTree(root->right);
    if (root->left == NULL && root->right == NULL)
    {
        TNode* del = root;
        delete del;
        root = NULL;
    }
}

void showTree(TNode* root)
{
    static int tab = 0;
    if (!root)
    {
        cout << "NULL" << endl;
        return;
    }
    cout << root->inf << endl;
    tab++;
    for (int i = 0; i < tab; i++)
    {
        cout << "\t";
    }
    cout << "лв:";
    showTree(root->left);
    for (int i = 0; i < tab; i++)
    {
        cout << "\t";
    }
    cout << "пр:";
    showTree(root->right);
    tab--;
}

void PBDSP(TNode* root)
{
    if (root != NULL)
    {
        PBDSP(root->left); //прохід в симетричному порядку лівого піддерева
        cout << root->inf << endl; //роздруківка вмісту
        PBDSP(root->right); //прохід в симетричному порядку правого піддерева
    }
}

void task6(TNode*& root)
{
    if (root == NULL)
    {
        return;
    }
    // если элемент отрицательный
    if (root->inf < 0)
    {
        root->inf = 0; // заменяем на 0
    }
    // рекурсивно вызываем функцию для левого и правого поддерева
    task6(root->left);
    task6(root->right);
}

void task7(TNode*& root)
{
    if (root == NULL)
    {
        return;
    }

    int s = (root->left ? root->left->inf : 0) + (root->right ? root->right->inf : 0);
    if (s % 2 == 0)
    {
        cout << root->inf << " (Sum = " << s << ")" << endl;
    }

    task7(root->left);
    task7(root->right);
}


TNode* root;
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    root = NULL;
    char ch;
    do {
        system("cls");
        cout << "Choose option:\n";
        cout << "---------------------------------\n";
        cout << "1.Form binary tree\n";
        cout << endl;
        cout << "2.Display lowest and highest values of the element\n";
        cout << endl;
        cout << "3.Display the tree\n";
        cout << endl;
        cout << "4.Delete the tree\n";
        cout << endl;
        cout << "5.Symmetrical bypass \n";
        cout << endl;
        cout << "6.Change all negative roots to zero\n";
        cout << endl;
        cout << "7.Display roots with paired descendants sum\n";
        cout << "---------------------------------\n";
        cout << endl;
        cout << "Choose option: ";
        cin >> ch;
        switch (ch) {
        case '1':
        {
            int cnt;
            cout << "\nType in the number of elements: ";
            cin >> cnt;
            initTree(root, cnt);
            cout << "\nA tree has been formed\n";
        }
        break;
        case '2':
        {
            int max = INT_MIN, min = INT_MAX;
            getMaxMin(root, max, min);
            cout << "\nHighest value: " << max << "\n";
            cout << "\nLowest value: " << min << "\n";
        }
        break;
        case '3':
        {
            cout << "\n";
            showTree(root);
            cout << "\n";
        }
        break;
        case '4':
        {
            delTree(root);
            cout << "\nThe tree was deleted!\n";
        }
        break;
        case '5':
        {
            cout << "\n";
            PBDSP(root);
            cout << "\n";
        }
        break;
        case '6':
        {
            cout << "\nTo changes\n";
            showTree(root);
            cout << "\n";
            task6(root);
            cout << "\nAfter:\n";
            showTree(root);
            cout << "\n";
        }
        break;
        case '7':
        {
            cout << "\n";
            task7(root);
            cout << "\n";
        }
        break;
        }
        system("pause");
    } while (true);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
