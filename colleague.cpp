
#include "colleague.h"
#include <iostream>
#include <thread>

////////////////////////////////////////////////////////////////

void colleague::send_message(int receiver_id, float data) 
{
    mediator_message* msg = current_message();

    msg->read = false;
    msg->sender_id = id;
    msg->receiver_id = receiver_id;
    msg->data = data;
    
    outbox.push(*msg);
}

////////////////////////////////////////////////////////////////

void colleague::receive_message(mediator_message* message) 
{
    inbox.push(*message);
}

////////////////////////////////////////////////////////////////

void colleague::print_msg(int sender_id, float data)
{
    const std::scoped_lock lock{colleague_mutex};
    
    std::cout << "colleague " << id << " processed message from : " << sender_id << ", data : " << data << std::endl;
}

////////////////////////////////////////////////////////////////

void colleague::process_messages()
{
    // read incoming messages
    while(!inbox.empty())
    {
        // retrieve incoming message
        auto message = inbox.front();
        
        // copy data
        data = message.data;
       
        // do some work
        print_msg(message.sender_id, data);
        message.read = true;
       
        // remove from inbox
        inbox.pop();
    }
    
    // send outgoing messages
    while(!outbox.empty())
    {
        // retrieve outgoing message
        auto message = outbox.front();
        
        // forward it to the mediator
        msg_mediator->post_message(&message);
        
        // remove from outbox
        outbox.pop();
    }
    
    // give other colleagues a chance to access the mediator. should we devise a built in scheduling mechanism?
    std::this_thread::sleep_for(std::chrono::microseconds(50));
}
