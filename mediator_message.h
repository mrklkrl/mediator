#pragma once

struct mediator_message
{
    bool read = true;
    int sender_id;
    int receiver_id;
    float data;
};