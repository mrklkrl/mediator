#include <iostream>
#include <mutex>
#include "colleague.h"
#include "mediator_message.h"

////////////////////////////////////////////////////////////////

void message_mediator::add_colleague(colleague* colleague)
{
    colleagues.push_back(colleague);
}

////////////////////////////////////////////////////////////////

void message_mediator::post_message(mediator_message* message) 
{
    message_queue.push(*message);
}

////////////////////////////////////////////////////////////////

void message_mediator::distribute_messages() 
{
    while (true) 
    { 
        if(!message_queue.empty())
        {
            mediator_message message = message_queue.front();
            
            for (colleague* colleague : colleagues) 
            {
                if (colleague->get_id() == message.receiver_id) 
                {
                    colleague->receive_message(&message);
                }
            }
            
            message_queue.pop();
        }
    }
}
