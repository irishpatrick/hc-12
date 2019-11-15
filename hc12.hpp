#ifndef HC12_HPP
#define HC12_HPP

#include <SoftwareSerial.h>

#define HC12_MODE_TRANSPARENT 1
#define HC12_MODE_COMMAND 0

class HC12
{
public:
    HC12();
    ~HC12();

    void attach(int, int, int);
    void setMode(int);
    void write(const char*, size_t);
    void listen();

    int getMode();

private:
    int rx;
    int tx;
    int set;
    int mode;
    SoftwareSerial* pipe;
};

#endif /* HC12_HPP */