/*BY Micha homee Community


*/

void buttonstate1() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[1] == 1 ) {
        bulbon(45, 200);
      } else if  (bnstate[1] == 0 ) {
        bulboff(45, 200);
      }
    }
  }
}
void buttonstate2() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[2] == 1 ) {
        bulbon(45, 430);
      } else if  (bnstate[2] == 0 ) {
        bulboff(45, 430);
      }
    }
  }
}
void buttonstate3() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[3] == 1 ) {
        bulbon(45, 660);
      } else if (bnstate[3] == 0 ) {
        bulboff(45, 660);
      }
    }
  }
}

void buttonstate4() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[4] == 1 ) {
        bulbon(295, 200);
      } else if (bnstate[4] == 0 ) {
        bulboff(295, 200);
      }
    }
  }
}
void buttonstate5() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[5] == 1 ) {
        bulbon(295, 430);
      } else if (bnstate[5] == 0 ) {
        bulboff(295, 430);
      }
    }
  }
}
void buttonstate6() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[6] == 0 ) {
        bulboff(295, 660);
      }
      else if (bnstate[6] >0 && bnstate[6] <20){
      dimmablebulb10(295,660);
      }
      else if (bnstate[6] >20 && bnstate[6] <40){
      dimmablebulb30(295,660);
      }
      else if (bnstate[6] >40 && bnstate[6] <55){
      dimmablebulb50(295,660);
      }
      else if (bnstate[6] >55 && bnstate[6] <70){
      dimmablebulb60(295,660);
      }
      else if (bnstate[6] >70 && bnstate[6] <88){
      dimmablebulb80(295,660);
      }
      else if (bnstate[6] >88 && bnstate[6] <95){
      dimmablebulb90(295,660);
      }
      else if (bnstate[6] >95 && bnstate[6] <101){
      bulbon(295,660);
      }
      
      
    }
  }
}
