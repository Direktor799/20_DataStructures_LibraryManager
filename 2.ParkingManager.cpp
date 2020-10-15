#include<iostream>
using namespace std;
const int MAX_STACK_SIZE = 2;

struct cars
{
    int number;
    int arrive_time;
    int parking_time;
};

struct node
{
    cars car;
    node* next;
    node()
    {
        next = NULL;
    }
};

class parkinglot
{
public:
    cars stack[MAX_STACK_SIZE];
    cars tmp_stack[MAX_STACK_SIZE];
    int stack_top;
    int tmp_top;
    node* queue_start;
    node* queue_end;
    int queue_length;
    parkinglot()
    {
        queue_start = NULL;
        queue_end = NULL;
        stack_top = 0;
        tmp_top = 0;
        queue_start = new node;
        queue_end = queue_start;
        queue_length = 0;
    }

    void arrive(int number, int time)
    {
        if(stack_top >= MAX_STACK_SIZE)
        {
            node* new_node_ptr = new node;
            new_node_ptr->car.number = number;
            new_node_ptr->car.arrive_time = time;
            queue_end->next = new_node_ptr;
            queue_end = new_node_ptr;
            cout << "Arrived in sideway:" << queue_length + 1 << endl;
            queue_length++;
        }
        else
        {
            stack[stack_top].number = number;
            stack[stack_top].arrive_time = time;
            stack[stack_top].parking_time = time;
            cout << "Arrived in parkinglot:" << stack_top + 1 << endl;
            stack_top++;
        }
    }

    void depart(int number, int time)
    {
        int i;
        for(i = 0; i < stack_top; i++)
            if(stack[i].number == number)
                break;
        cout << "Departed,you've stayed for " << time - stack[i].parking_time << endl;
        for(; i < stack_top; i++)
            stack[i] = stack[i+1];
        stack_top--;
        if(queue_length > 0)
        {
            stack[stack_top] = queue_start->next->car;
            stack[stack_top].parking_time = time;
            node* tmp = queue_start;
            queue_start = queue_start->next;
            free(tmp);
            stack_top++;
            queue_length--;
        }
    }
};

int main()
{
    parkinglot p1;
    char operation;
    int number;
    int time;
    while(true)
    {
        cin >> operation >> number >> time;
        if(operation == 'E')
            break;
        if(operation == 'A')
            p1.arrive(number, time);
        if(operation == 'D')
            p1.depart(number, time);
    }
}