//
// Created by kostia on 11/25/24.
//

#include "Store.h"

bool Store::addCard(const RFID_CARD& card)
{
    for (const auto& existing_card : cards)
    {
        if (existing_card.uid == card.uid)
        {
            return false;
        }
    }
    cards.push_back(card);
    return true;
}

RFID_CARD* Store::findCardByUID(const UID& uid)
{
    for (auto& card : cards)
    {
        if (card.uid == uid)
        {
            return &card;
        }
    }
    return nullptr;
}

void Store::clear()
{
    cards.clear();
}
