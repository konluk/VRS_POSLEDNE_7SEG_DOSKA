

#include "vypocty.h"

float ziskajNadVysku(float tlak){

 	return tlak/6.3;

 }

float ziskajAzimut(void){
	float mag[3];
	lis3mdl_get_mag(mag, (mag+1), (mag+2));
	float vyp = atan(mag[0])*atan(mag[1]);

	return vyp*10000;
}

float ziskajTeplotu(void){
	////po 5 hodinách sme to vzdali...   tmp = getTmpFromSenzor();
	float tmp = -130;

	if(tmp>99.9)tmp=99.9;
	if(tmp<-99.9)tmp=-99.9;

	return tmp;

}
