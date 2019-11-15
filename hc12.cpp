#include "hc12.hpp"
#include <Arduino.h>

HC12::HC12() :
    rx(0),
    tx(0),
    set(0),
    mode(0),
    pipe(nullptr)
{

}

HC12::~HC12()
{
    if (pipe != nullptr)
    {
        delete pipe;
        pipe = nullptr;
    }
}

void HC12::attach(int a, int b, int c)
{
    rx = a;
    tx = b;
    set = c;

    pinMode(set, OUTPUT);
    
    pipe = new SoftwareSerial(rx, tx);
    pipe->begin(9600);
    int i;
    for (i = 0; i < 10; i++)
    {
        if (pipe)
        {
            break;
        }
        delay(100);
    }
    if (i == 10)
    {
        Serial.println("init failed");
    }
}

void HC12::setMode(int m)
{
    mode = m;
    digitalWrite(set, mode);
}

void HC12::write(const char* buf, size_t len)
{
    pipe->write(buf, len);
}

void HC12::listen()
{
    while (pipe->available())
    {
        Serial.write(pipe->read());
    }
}

int HC12::getMode()
{
    return mode;
}