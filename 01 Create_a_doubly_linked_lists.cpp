// Requirement 1: 
// Create a doubly linked list in C++. Include the following functions:  
// 1. insert a node,  
// 2. delete a node  
// 3. check if the node is empty

#include <iostream>

class Node{
public:
    int data;
    Node *next;
    Node *prev;
};


void insertNodeNext(Node *selected_node, int data){
    if(selected_node == NULL){
        std::cout << selected_node << " node is NULL.";
        return;
    }

    Node *new_node = new Node();

    new_node->data = data;
    // For the new_node, we get the next and prev
    // There are two things to initialized: next and prev
    new_node->next = selected_node->next; // Sel --> Next == [New] --> Next
    new_node->prev = selected_node; // Sel <-- Next == Sel <-- [New]

    // For the next node, we change the previous node to new_node
    // There is one thing to change: prev node
    selected_node->next->prev = new_node; // Sel <-- Next, Sel <-- New <-- [Next]

    // For the selected node, we change the next to new_node
    // There is one thing to change: next node
    selected_node->next = new_node; // [Sel] --> New
}

void insertNodePrevious(Node *selected_node, int data){
    if(selected_node == NULL){
        std::cout << selected_node << " node is NULL.";
        return;
    }

    Node *new_node = new Node();

    new_node->data = data;
    // For the new_node, we get the prev and next
    // There are two things to initialized: next and prev
    new_node->next = selected_node; // Prev --> Sel == [New] --> Sel
    new_node->prev = selected_node->prev; // Prev <-- Sel == Prev <-- [New]

    // For the prev node, we change the next node to new_node
    // There is one thing to change: next node
    selected_node->prev->next = new_node; // Prev --> Sel, [Prev] --> New --> Sel

    // For the selected node, we change the prev to new_node
    // There is one thing to change: prev node
    selected_node->prev = new_node; // New <-- [Sel] 
}

void push(Node **head, int data){
    Node *Index = new Node();

    Index->data = data;
    Index->next = *head; 
    Index->prev = *head;

    *head = Index;
}

void append(Node **head_ref, int data){
    Node *new_node = new Node();
    Node *last_node = *head_ref;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = last_node;

    if(*head_ref == NULL){
        *head_ref = new_node;
        return;
    }

    while(last_node->next != NULL)  last_node = last_node->next;

    last_node->next = new_node;
}

void printList(Node *N){
    while(N != NULL){
        if(N->prev != NULL)
            std::cout << "Previous: " << N->prev->data << std::endl;
        std::cout << "Data: " << N->data << std::endl;
        if(N->next != NULL)
            std::cout << "Next: " << N->next->data << std::endl;

        std::cout << std::endl;
        N = N->next;
    }
}

void test(){
    Node *head = NULL;
    Node *second = NULL;
    Node *tail = NULL;

    head = new Node();
    second = new Node();
    tail = new Node();

    head->data = 1;
    head->next = second;
    head->prev = NULL;

    second->data = 3;
    second->next = tail;
    second->prev = head;

    tail->data = 5;
    tail->next = NULL;
    tail->prev = second;

    insertNodeNext(head, 2);
    insertNodePrevious(tail, 4);

    printList(head);


}

int main(){
    Node *head = NULL;
    Node *second = NULL;
    Node *tail = NULL;

    head = new Node();
    second = new Node();
    tail = new Node();

    head->data = 727;
    head->next = second;
    head->prev = NULL;

    second->data = 2016;
    second->next = tail;
    second->prev = head;

    tail->data = 20210827;
    tail->next = NULL;
    tail->prev = second;

    push(&head, 420);
    append(&head, 69);
    insertNodeNext(head->next, 42);
    insertNodePrevious(second, 929);

    printList(head);

    test();
    return 0;
}
