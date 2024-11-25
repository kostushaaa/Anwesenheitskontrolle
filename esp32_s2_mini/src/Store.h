//
// Created by kostia on 11/25/24.
//

#ifndef STORE_H
#define STORE_H

#include <Arduino.h>
#include <vector>

struct UID
{
    uint8_t bytes[10];
    uint8_t length;

    UID(const uint8_t* data = nullptr, uint8_t len = 0) : length(len)
    {
        if (bytes && len > 0 && len <= 10)
        {
            memcpy(bytes, data, len);
        }
        else
        {
            memset(bytes, 0, sizeof(bytes));
        }
    }

    bool operator==(const UID& other) const
    {
        return length == other.length && memcmp(bytes, other.bytes, length) == 0;
    }
};



struct OWNER
{
    String name;

    OWNER(const String& name = "") : name(name)
    {
    }
};

struct RFID_CARD
{
    UID uid;
    OWNER owner;
    bool isValid;

    RFID_CARD(const UID& uid = UID(), const OWNER& owner = OWNER(), bool isValid = false)
        : uid(uid), owner(owner), isValid(isValid)
    {
    }
};

class Store
{
private:
    std::vector<RFID_CARD> cards;

public:
    Store() = default;
    ~Store() = default;

    bool addCard(const RFID_CARD& card);
    RFID_CARD* findCardByUID(const UID& uid);
    void clear();
};


#endif //STORE_H
