#include "WProgram.h"
#include "SSI.h"

SSI::SSI(){
    DDRC |= (1 << PINC4);
    _scale=1.0;
    _direction=0;
}

int SSI::getPosition() {
    int i;
    for(i=0; i < 26; i++)
    {
        _binaryArray[i] = 0;
    }

    delayMicroseconds(40);

    for(i = 12; i >=0; i--)
    {
        PORTC = (0<<PINC4);
        delayMicroseconds(3);
        _binaryArray[i] = PINC;  //delayMicroseconds(3) fits a 10us tictac
        PORTC = (1<<PINC4);
        delayMicroseconds(3);
    }
    delayMicroseconds(100);
return 0;
}

int SSI::setScale(char *scale)
{
   _scale=atof(scale);
  // _scale=1.0;
   return 0;
}

int SSI::setdirection(int dir){
    if (dir != 0) _direction=1;
    else _direction=0;
    return 0;
}
int SSI::condensePosition()
{int i, j;

    for(j=0;j<4;j++)
      _binaryCondense[j] = 0;

    for(j=0; j<3;j++) {
      for(i = 0;i < 8; i++) {
        if((_binaryArray[i+j*8] & (1<<PINC3)) > 0) {
  	    _binaryCondense[j] |= 1 << i;
         }
       }
    }
/*    for(i = 0; i < 2; i++) {
      	if((_binaryArray[i+24] & (1<<PINC3))>0) {
	     _binaryCondense[3] |= 1 << i;
         }
      }
*/

    position = _binaryCondense[1]*256+_binaryCondense[0]-4096;
    if (_direction)
    position = (4096-position) & 4095;

   // position /= _scale;
    return 0;
}

