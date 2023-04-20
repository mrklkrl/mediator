#pragma once

#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "mediator_message.h"
#include "threadsafe_queue.h"

class colleague;

////////////////////////////////////////////////////////////////

class message_mediator 
{
public:
    void add_colleague(colleague* colleague);
    void post_message(mediator_message* message);
    void distribute_messages();

private:
    std::mutex mediator_mutex;
    std::condition_variable cv;
    
    std::vector<colleague*> colleagues;
    threadsafe_queue<mediator_message> message_queue;
};
