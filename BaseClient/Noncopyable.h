#ifndef _BASECLIENT_NONCOPYABLE_H 
#define _BASECLIENT_NONCOPYABLE_H 

namespace BaseClient
{

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}

private:
    Noncopyable(const Noncopyable&) {}
    Noncopyable &operator=(const Noncopyable &) { return *this; }
};

}

#endif
