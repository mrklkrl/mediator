#include "colleague_b.h"

////////////////////////////////////////////////////////////////

colleague_b::colleague_b(message_mediator* mediator_, colleague_ids id_)
{
    data = 0;
    id = id_;
    msg_mediator = mediator_;
}

// ////////////////////////////////////////////////////////////////

// void colleague_b::send_message(int receiver_id, float data) 
// {
//     colleague::send_message(receiver_id, data);
// }

// ////////////////////////////////////////////////////////////////

// void colleague_b::receive_message(mediator_message* message) 
// {
//     colleague::receive_message(message);
// }

// ////////////////////////////////////////////////////////////////

// void colleague_b::process_messages() 
// {
//     colleague::process_messages();
// }

////////////////////////////////////////////////////////////////

float colleague_b::get_data() const 
{
    return data;
}