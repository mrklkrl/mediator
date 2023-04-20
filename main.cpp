#include <iostream>
#include <thread>
#include <chrono>

#include "message_mediator.h"
#include "colleague_a.h"
#include "colleague_b.h"

bool a_finished = false;
bool b_finished = false;

////////////////////////////////////////////////////////////////

void thread_a(colleague_a* colleague_a) 
{
    int data_a = 0;
    
    while(true)
    {
        colleague_a->process_messages();
        
        if(data_a < 100)
        {
            data_a = data_a + 1.0;
            colleague_a->send_message(ID_COLLEAGUE_B, data_a);
        }
        else
        {
            a_finished = true;
            
            if(a_finished && b_finished)
                std::terminate();
        }
    }
}

////////////////////////////////////////////////////////////////

void thread_b(colleague_b* colleague_b) 
{
    int data_b = 0;
    
    while(true)
    {
        colleague_b->process_messages();

        if(data_b < 100)
        {
            data_b = data_b + 1.0;
            colleague_b->send_message(ID_COLLEAGUE_A, data_b);
        }
        else
        {
            b_finished = true;
            
            if(a_finished && b_finished)
                std::terminate();
        }
    }
}

////////////////////////////////////////////////////////////////

void thread_m(message_mediator* mediator) 
{
    mediator->distribute_messages();
}

////////////////////////////////////////////////////////////////

int main() 
{
    message_mediator mediator;

    colleague_a colleague_A(&mediator, ID_COLLEAGUE_A);
    colleague_b colleague_B(&mediator, ID_COLLEAGUE_B);

    mediator.add_colleague(&colleague_A);
    mediator.add_colleague(&colleague_B);
    
    std::thread t0(thread_m, &mediator);
    std::thread t1(thread_a, &colleague_A);
    std::thread t2(thread_b, &colleague_B);
    
    t0.join();
    t1.join();
    t2.join();

    std::cout << "colleague_a data: " << colleague_A.get_data() << std::endl;
    std::cout << "colleague_b data: " << colleague_B.get_data() << std::endl;

    return 0;
}
