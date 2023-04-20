#include "colleague_a.h"

////////////////////////////////////////////////////////////////

colleague_a::colleague_a(message_mediator* mediator_, colleague_ids id_)
{
    data = 0;
    id = id_;
    msg_mediator = mediator_;
}

// ////////////////////////////////////////////////////////////////

// void colleague_a::send_message(int receiver_id, float data) 
// {
//     colleague::send_message(receiver_id, data);
// }

// ////////////////////////////////////////////////////////////////

// void colleague_a::receive_message(mediator_message* message) 
// {
//     colleague::receive_message(message);
// }

// ////////////////////////////////////////////////////////////////

// void colleague_a::process_messages() 
// {
//     colleague::process_messages();
// }

////////////////////////////////////////////////////////////////

float colleague_a::get_data() const 
{
    return data;
}