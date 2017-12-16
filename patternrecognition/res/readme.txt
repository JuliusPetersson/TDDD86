/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150		46		21
    200		107		47
    300		325		77
    400		749		112
    800		5811		400
   1600		46630		1591
   3200				6461
   6400				27301
  12800				116673


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
Har tidkomplexitet n ^4 . Det syns i att den har tid en n + n ^4 vilket säger att det är ordo(n ^4). Det kan enkelt ses på funktionens for-loopar.
Sortering:
Har tidskomlplexitet ordo(n ^2) syns på de tv for-looparna
