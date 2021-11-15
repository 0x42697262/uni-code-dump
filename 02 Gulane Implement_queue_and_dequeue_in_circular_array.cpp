// Requirement 2. Implement queue and Dequeue in Circular arrays using C++. 
// Deadline: November 15

/*
   A simple Queue and Dequeue for Fast Modular Exponentiation using Circular Array
   The program takes multiple inputs of numbers which are added one by one to the list.

   TO DO:
        > Create a function for calculating FME
        > Create a class for the node that will store the data

*/

#include <iostream>
#include <string>


/*
    Code algorithm derived from https://www.youtube.com/watch?v=3Bh7ztqBpmw
*/
int fme(long long base, unsigned int power, int modulo){
    int r = 1;

    while(power > 0){
        if( power & 1 )
            r = (r*base) % modulo;
        base = (base*base) % modulo;
        power = power >> 1;
    }
    
    return r;
}


/*
    This class holds the data for each nodes in the list. It requires the base, power, and modulo.
    The mathematical expression of this would be: base^power % module 
                                       or simply: b^p % m

    I initialize the values with -1 because the result of the modular expressions 
    can never go below 1.
*/

class QDataNode{
public:
    long long base;
    unsigned int power;
    int modulo;

    QDataNode(){
        this->base = -1;
        this->power = -1;
        this->modulo = -1;
    }

    QDataNode(long long base, unsigned int power, int modulo){
        this->base = base;
        this->power = power;
        this->modulo = modulo;
    }
};


/*
    In this Queue, we initialize the front and the back, and we also initialize the queue size
        and queue capacity.

    `qsize` is the queue size or the total amount of data in the queue
    `capacity` is the maximum amount of data that the circular array can hold
    `array` is the circular array where we store the data nodes as pointers which is initialized
        from the constructor

    This class contains isEmpty(), isFull(), Enqueue(), Dequeue(), printQueue(), ProcessHelper(),
    Process(), and ProcessAll(), functions.

    isEmpty():
        - is a boolean type function
        - is used for checking if the list is empty
        - returns TRUE if front and rear are empty otherwise FALSE
    isFull():
        - is a boolean type function
        - is used for checking if the list is full
        - returns TRUE if full otherwise FALSE
    Enqueue():
        - is a void function
        - a function for entering new data node into the rear of the list
        - takes 3 parameters: long long base, unsigned int power, int modulo
        - if list is full, we do not add the new data node
        - queue size increases as new data is entered
    Dequeue():
        - is a void function
        - a function for removing the front data node of the list
        - queue size decreases as the front data is removed
    printQueue():
        - a void function that prints the queue list
    ProcessHelper():
        - avoid function that mainly processes the modular expressions and prints them
        - is used by Process() and ProcessAll()
    Process():
        - an void function that prints the calculated expression
        - start calculating the modular expression and dequeues the node
    ProcessAll():
        - the same function as above but iterates the entire nodes
*/
class Queue{
public:
    int qsize;
    int capacity;
    int front;
    int rear;

    QDataNode* array;

    Queue(int size){
        this->qsize = 0;
        this->front = -1;
        this->rear = -1;
        this->capacity = std::max(1, size);
        this->array = new QDataNode[this->capacity];
    }

    bool isEmpty(){
        if(this->front == -1 && this->rear == -1) return true;
        return false;
    }

    bool isFull(){
        if(this->qsize == this->capacity) return true;
        return false;
    }

    void Enqueue(long long base, unsigned int power, int modulo){
        if(isFull())
            return;

        if(this->front == -1) 
            this->front = 0;

        this->rear = (this->rear + 1) % this->capacity;
        this->array[this->rear] = QDataNode(base, power, modulo);
        this->qsize++;
    }

    void Dequeue(){
        if(this->isEmpty())
            return;

        if(this->front == this->rear){
            this->front = -1;
            this->rear = -1;
            this->qsize--;
            return; 
        }
        
        this->front = (this->front + 1) % this->capacity;
        this->qsize--;
    }

    void printQueue(){
        if(this->isEmpty()){
            std::cout << "Queue is Empty." << std::endl;
            return;
        }
        
        std::cout << "Queue Size: " << this->qsize << std::endl << std::endl;
        if(this->front <= this->rear){
            for(int i = this->front; i <= this->rear; i++){
                std::cout << "Base: " << this->array[i].base << std::endl;
                std::cout << "Power: " << this->array[i].power << std::endl;
                std::cout << "Modulo: " << this->array[i].modulo << std::endl << std::endl;
            }
        } else{
            int i = this->front;
            while(i < this->capacity){
                std::cout << "Base: " << this->array[i].base << std::endl;
                std::cout << "Power: " << this->array[i].power << std::endl;
                std::cout << "Modulo: " << this->array[i].modulo << std::endl << std::endl;
                i++;
            }
            i = 0;
            while(i <= this->rear){
                std::cout << "Base: " << this->array[i].base << std::endl;
                std::cout << "Power: " << this->array[i].power << std::endl;
                std::cout << "Modulo: " << this->array[i].modulo << std::endl << std::endl;
                i++;
            }
        }
    }

    void ProcessHelper(int i){
        std::cout << this->array[i].base << "^" << this->array[i].power << " % " << 
        this->array[i].modulo << " = " << fme(this->array[i].base, this->array[i].power, 
                                                this->array[i].modulo) << std::endl;
    }
    void Process(){
        if(this->isEmpty())
            return;
        
        ProcessHelper(this->front);
        this->Dequeue();
    }
    
    void ProcessAll(){
        if(this->isEmpty())
            return;

        if(this->front <= this->rear){
            for(int i = this->front; i <= this->rear; i++){
                ProcessHelper(i);
                this->Dequeue();
            }
        } else{
            int i = this->front;
            while(i < this->capacity){
                ProcessHelper(i);
                this->Dequeue();
                i++;
            }
            i = 0;
            while(i <= this->rear){
                ProcessHelper(i);
                this->Dequeue();
                i++;
            }
        }
    }
};

/*
    DEQueue class is exactly the same as Queue class but with more functions that supports
    adding and removing nodes at both ends of the nodes

    Has new functions: EnqueueRear(), DequeueRear(), and ProcessRear()

    EnqueueRear():
        - the same function as Enqueue from the Queue class but the small change is for
            adding the new data node to the left side of the node
    DequeueRear():
        - although it is the same as Dequeue() from the Queue class, this one has few minor
            changes in the code
        - this specifically removes the rear (right side) of the node
    ProcessRear():
        - the same function as Process() Queue class but this starts processing the rear node
*/

class DEQueue: public Queue{
public:

    DEQueue(int size): Queue{size}{}

    void EnqueueRear(long long base, unsigned int power, int modulo){
        if(isFull())
            return;

        if(this->rear == -1){
            this->rear = 0;
            this->front = 1;
        }

        this->front = (this->front-1>=0)*(this->front-1) + (this->front-1<0)*(this->capacity+(this->front-1));
        this->array[this->front] = QDataNode(base, power, modulo);
        this->qsize++;

    }

    void DequeueRear(){
        if(this->isEmpty())
            return;

        if(this->front == this->rear){
            this->front = -1;
            this->rear = -1;
            this->qsize--;
            return; 
        }
        
        //this->rear = (this->rear - 1) % this->capacity;
        this->rear = (this->rear-1>=0)*(this->rear-1) + (this->rear-1<0)*(this->capacity+(this->rear-1));
        this->qsize--;
    }

    void ProcessRear(){
        if(this->isEmpty())
            return;
        
        ProcessHelper(this->rear);
        this->DequeueRear();
    }
};

/*
    Anything related to using the Queue and Dequeue goes down here. Like menus and user inputs.
*/
void QTypeOne(int size){
    Queue Q(size);
    int choice = -1;

    long long base;
    unsigned int power;
    int modulo;

    system("cls");
    do{
        std::cout << "(1) Input Modular Expression (Enqueue)" << std::endl;
        std::cout << "(2) Remove Modular Expression (Dequeue)" << std::endl;
        std::cout << "(3) Print Modular Expression" << std::endl;
        std::cout << "(4) Process Modular Expression" << std::endl;
        std::cout << "(5) Process All Modular Expression" << std::endl;
        std::cout << "(0) Quit" << std::endl;

        std::cout << ">> ";
        std::cin >> choice;
        
        switch(choice){
            case 0:
                exit(0);
                break;

            case 1:
                std::cout << "Input BASE POWER MODULO: ";
                std::cin >> base >> power >> modulo;
                Q.Enqueue(base, power, modulo);
                break;
            
            case 2:
                Q.Dequeue();
                std::cout << "Dequeue'd the front index." << std::endl;
                break;

            case 3:
                Q.printQueue();
                break;
            
            case 4:
                Q.Process();
                break;

            case 5:
                Q.ProcessAll();
                break;

            default:
                break;
        }
    }while(choice != 0);
}

void QTypeTwo(int size){
    DEQueue Q(size);
    int choice = -1;

    long long base;
    unsigned int power;
    int modulo;

    system("cls");
    do{
        std::cout << "(1) Input Modular Expression (Enqueue)" << std::endl;
        std::cout << "(2) Remove Modular Expression (Dequeue)" << std::endl;
        std::cout << "(3) Print Modular Expression" << std::endl;
        std::cout << "(4) Process Modular Expression" << std::endl;
        std::cout << "(5) Process All Modular Expression" << std::endl;
        std::cout << "(6) Input Modular Expression (Enqueue Rear)" << std::endl;
        std::cout << "(7) Remove Modular Expression (Dequeue Rear)" << std::endl;
        std::cout << "(8) Process Modular Expression (Rear)" << std::endl;
        std::cout << "(0) Quit" << std::endl;

        std::cout << ">> ";
        std::cin >> choice;

        switch(choice){
            case 0:
                exit(0);
                break;
            
            case 1:
                std::cout << "Input BASE POWER MODULO: ";
                std::cin >> base >> power >> modulo;
                Q.Enqueue(base, power, modulo);
                break;


            case 2:
                Q.Dequeue();
                std::cout << "Dequeue'd the front index." << std::endl;
                break;

            case 3:
                Q.printQueue();
                break;

            case 4:
                Q.Process();
                break;
            
            case 5:
                Q.ProcessAll();
                break;
            
            case 6:
                std::cout << "Input BASE POWER MODULO: ";
                std::cin >> base >> power >> modulo;
                Q.EnqueueRear(base, power, modulo);
                break;

            case 7:
                Q.DequeueRear();
                std::cout << "Dequeue'd the rear index." << std::endl;
                break;

            case 8:
                Q.ProcessRear();
                break;


            default:
                break;
        }

    }while(choice != 0);
}

int main(){

    int s, choice;

    std::cout << "Enter SIZE of array: ";

    std::cout << ">>";
    std::cin >> s;

    std::cout << "(1) Use Queue Circular Array" << std::endl;
    std::cout << "(2) Use DEQueue Circular Array" << std::endl;

    std::cout << ">>";
    std::cin >> choice;

    if(choice == 1){
        QTypeOne(s);
        
    }
    if(choice == 2){
        QTypeTwo(s);
        
    }

    return 0;
}
