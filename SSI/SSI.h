#ifndef SSI_h
#define SSI_h
#include "WProgram.h"

class SSI
{
 public: 
         SSI();
         int getPosition();
         int condensePosition();
         int setScale(char *scale);
         int setdirection(int dir);
         float _scale;
         unsigned long position;

 private:
         unsigned long _position;
         int _clock_pin;
         int _data_pin;
         int _direction;
         byte _binaryArray[26];
         unsigned  _binaryCondense[4];
};


#endif
