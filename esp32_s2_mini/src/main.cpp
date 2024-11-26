//
// Created by kostia on 11/25/24.
//

#include <Arduino.h>
#include "Store.h"

Store store;

void setup()
{
    Serial.begin(115200);
    Serial.printf("Welcome home Sir. Jarvis is here\n");


    // Example UID
    uint8_t uid1[] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t uid2[] = {0x01, 0x02, 0x03, 0x04};

    // Adding the testing cards
    store.addCard(RFID_CARD(UID(uid1, 4), OWNER("Alice"), true));
    store.addCard(RFID_CARD(UID(uid2, 4), OWNER("Bob"), false));

    Serial.println("Testing cards has been added.");
}

void loop()
{
    // Example search for card
    uint8_t testUID[] = {0xDE, 0xAD, 0xBE, 0xEF};
    UID searchUID(testUID, 4);

    RFID_CARD* card = store.findCardByUID(searchUID);

    if (card)
    {
        Serial.print("Card was found: UID=");
        for (int i = 0; i < card->uid.length; i++)
        {
            Serial.print(card->uid.bytes[i], HEX);
            if (i < card->uid.length - 1) Serial.print(":");
        }
        Serial.print(", Owner=");
        Serial.print(card->owner.name);
        Serial.print(", IsValid=");
        Serial.println(card->isValid ? "Yes" : "Nope");
    }
    else
    {
        Serial.println("Card was not found.");
    }

    delay(3000); // Delay for testing
}
