#ifndef __MOVETAB_H
#define __MOVETAB_H

Acrobatics m000;
Acupressure m001;
Aeroblast m002;
Agility m003;
AirSlash m004;
Amnesia m005;
AncientPower m006;
AquaJet m007;
AquaRing m008;
AquaTail m009;
Aromatherapy m010;

m000 = Acrobatics();
m001 = Acupressure();
m002 = Aeroblast();
m003 = Agility();
m004 = AirSlash();
m005 = Amnesia();
m006 = AncientPower();
m007 = AquaJet();
m008 = AquaRing();
m009 = AquaTail();
m010 = Aromatherapy();

Move* mtab[10];
mtab[0] = &m000;
mtab[1] = &m001;
mtab[2] = &m002;
mtab[3] = &m003;
mtab[4] = &m004;
mtab[5] = &m005;
mtab[6] = &m006;
mtab[7] = &m007;
mtab[8] = &m008;
mtab[9] = &m009;

#endif