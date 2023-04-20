#pragma once

#include "message_mediator.h"
#include "mediator_message.h"
#include "threadsafe_queue.h"

#include <mutex>

class message_mediator;
class mediator_message;

////////////////////////////////////////////////////////////////

enum colleague_ids
{
    ID_COLLEAGUE_A = 0,
    ID_COLLEAGUE_B
};

////////////////////////////////////////////////////////////////

static std::mutex colleague_mutex;

///////////////////////////////////////////////////////////////

class colleague 
{
public:
    // colleague(message_mediator* mediator_, colleague_ids id_);
    virtual ~colleague() = default;
    void send_message(int receiver_id, float data);
    void receive_message(mediator_message* message);
    void process_messages();
    
    mediator_message* current_message() { return &message_instance;}
    const int get_id() const { return id; }
    const float get_data() const {return data; }
    
    void print_msg(int sender_id, float data);

protected:
    message_mediator* msg_mediator;
    float data;
    int id;
    mediator_message message_instance;
    
    threadsafe_queue<mediator_message> inbox;
    threadsafe_queue<mediator_message> outbox;
};