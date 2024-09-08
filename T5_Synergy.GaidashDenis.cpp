#include <iostream>

struct Node 
{
    int data;        
    Node* next;      

    Node(int value) : data(value), next(nullptr) {}
};


class SinglyLinkedList 
{
public:
    Node* head;  

    SinglyLinkedList() : head(nullptr) {}

    // добавления элемента в начало списка
    void Push(int value) 
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // вывод элементов списка
    void PrintList() 
    {
        Node* temp = head;
        while (temp != nullptr) 
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "конец списка" << std::endl;
    }

    // сортировка вставками
    void InsertionSort() 
    {
        if (!head || !head->next) return;  

        Node* sorted = nullptr;  
        Node* current = head;

        
        while (current != nullptr) 
        {
            Node* next = current->next;  
            sorted = sortedInsert(sorted, current); 
            current = next;  
        }

        head = sorted;  
    }

private:
    
    Node* sortedInsert(Node* sorted, Node* newNode) 
    {        
        if (!sorted || sorted->data >= newNode->data) 
        {
            newNode->next = sorted;
            return newNode;
        }

        // поиск места
        Node* current = sorted;
        while (current->next != nullptr && current->next->data < newNode->data) 
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;

        return sorted;
    }
};

int main() 
{
    setlocale(LC_ALL, "Rus");

    SinglyLinkedList list;
    
    list.Push(5);
    list.Push(3);
    list.Push(6);
    list.Push(8);
    list.Push(1);
    list.Push(2);
    list.Push(4);
    list.Push(7);
    list.Push(9);

    std::cout << "Исходный список:" << std::endl;
    list.PrintList();
    
    list.InsertionSort();

    std::cout << "Отсортированный список:" << std::endl;
    list.PrintList();

    return 0;
}
