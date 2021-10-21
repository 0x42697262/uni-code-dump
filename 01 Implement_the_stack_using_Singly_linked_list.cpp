
#include <iostream>
#include <string>

class Node{
public:
    int ID;
    Node *next;

    Node(){
        this->ID = -1;
        this->next = NULL;
    }
};

class Stack{
public:
    Node *top;

    Stack(){
        this->top = NULL; // initializes the empty stack
    }

    bool nodeExist(Node *node){
        // checks whether a particular ID of a node exists
        Node *temp = this->top;
        while(temp != NULL){
            if(temp->ID == node->ID) return true;
            temp = temp->next;
        }
        return false;
    }

    bool isEmpty(){
        // checks if stack is empty
        if(this->top == NULL) return true;
        else return false;
    }

    int count(){
        // returns the number of nodes in the stack
        int count = 0;
        Node *temp = this->top;

        while(temp != NULL){
            count++;
            temp = temp->next;
        }

        return count;
    }

    Node *peek(){
        // returns the top node
        if(isEmpty()) return NULL;
        return this->top;
    }

    Node *pop(){
        // returns the top node and delete that node
        if(isEmpty()) return NULL;
        Node *temp = this->top;
        top = temp->next;
        
        return temp;
    }

    int push(Node *node){
        // pushes node at the top of the stack
        if(!nodeExist(node)){ // if a node's ID doesn't exist, push it
            if(this->top == NULL){ // if top is null, push it there
                this->top = node;
                

                return 0;
            }
            else{ // otherwise, place it on top
                Node *temp = this->top;
                this->top = node;
                node->next = temp;
                
                return 0;
            }
        }
        else return 1; // returns an error code 1 if node exists

    }

    void display(int type){
        Node *temp = this->top;
        while(temp != NULL){
            if(type == 1)
                std::cout << "ID: " << temp->ID << std::endl;
            if(type == 2)
                std::cout << temp->ID << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    
} NukeCodes;

void printDisplay(bool display){
    if(display){
        std::cout << std::endl << std::endl;
        std::cout << "Favorites: ";
        NukeCodes.display(2);
    }
    std::cout << std::endl;
}

std::string showhide(bool s){
    if(!s) return "Show";
    else return "Hide";
}

void choice2(Node *n){
    std::cout << "Input the new ID: ";
    std::cin >> n->ID;
    
    if(!NukeCodes.push(n))
        std::cout << "Successfully added new ID (node)." << std::endl;
    else
        std::cout << "ID (node) already exist." << std::endl;
    std::cout << std::endl;
}

void choice3(Node *n){
    if(NukeCodes.isEmpty())
        std::cout << "You have no favorites." << std::endl;
    else
        std::cout << "You removed " << NukeCodes.pop()->ID << std::endl;
    std::cout << std::endl;
}

void choice4(Node *n){
    if(NukeCodes.isEmpty())
        std::cout << "You have no favorites." << std::endl;
    else
        std::cout << "You have " << NukeCodes.count() << " favorites listed." << std::endl;
    std::cout << std::endl;
}

void choice5(Node *n){
    if(!NukeCodes.isEmpty())
        std::cout << "Last added favorites: " << NukeCodes.peek()->ID << std::endl;
    else 
        std::cout << "Your favorites is empty." << std::endl;
    std::cout << std::endl;
}

int main(){
    int choice, id;
    bool display = false;

    do{
        Node *menuNode = new Node();

        std::cout << "(1) "<< showhide(display) << " Favorites" << std::endl;      // display()
        std::cout << "(2) Add New Favorites" << std::endl;        // push()
        std::cout << "(3) Delete Newest Favorites" << std::endl;  // pop()
        std::cout << "(4) Check Favorites" << std::endl;          // count(), isEmpty()
        std::cout << "(5) Peek Last Favorite" << std::endl;       // peek()
        std::cout << "(0) Exit" << std::endl << std::endl;

        std::cout << ">> ";
        std::cin >> choice;

        system("cls");
        switch (choice){
        case 0:
            exit(0);
            break;
        case 1:
            display = !display;
            break;
        
        case 2:
            choice2(menuNode);
            break;
        case 3:
            choice3(menuNode);
            break;

        case 4:
            choice4(menuNode);
            break;

        case 5:
            choice5(menuNode);
            break;

        default:
            
            break;
        }
        printDisplay(display);
        
    }while(choice != 0);

    return 0;
}
