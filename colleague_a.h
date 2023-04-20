#pragma once

#include "colleague.h"

////////////////////////////////////////////////////////////////

class colleague_a : public colleague 
{
public:

    colleague_a(message_mediator* mediator_, colleague_ids id_);
    
    // void send_message(int receiver_id, float data) override;
    // void receive_message(mediator_message* message) override;
    // void process_messages() override;

    float get_data() const;
};