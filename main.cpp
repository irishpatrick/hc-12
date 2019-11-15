#include <Arduino.h>
#include "hc12.hpp"

HC12 veh;
HC12 gnd;

int do_send = 0;

char buffer[1024];
char* bufp = buffer;

void setup()
{
    Serial.begin(9600);
    delay(1000);

    veh.attach(2, 3, 4);
    gnd.attach(8, 9, 10);

    veh.setMode(HC12_MODE_COMMAND);
    gnd.setMode(HC12_MODE_COMMAND);

    Serial.println("ready");
}

void loop() 
{
    while (Serial.available() && !do_send)
    {
        *bufp = Serial.read();
        if (*bufp == '\n')
        {
            do_send = 1;
        }
        bufp++;
        *bufp = '\0';
    }

    if (do_send)
    {
        do_send = 0;
        Serial.write(buffer, bufp - buffer);

        veh.write(buffer, bufp - buffer);
        gnd.write(buffer, bufp - buffer);

        bufp = buffer;
        *bufp = '\0';
    }

    gnd.listen();
    veh.listen();
}