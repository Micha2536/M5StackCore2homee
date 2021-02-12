/*BY Micha homee Community
 * 
 * 
 */

void buttonstate1() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[1] == 1 ) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 50);
      } else
        M5.Lcd.fillRect(10, 50, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);
    }
    else if (varbutton == "1") {
      if (bnstate[1] == 1 ) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 105);
      } else
        M5.Lcd.fillRect(10, 105, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);
    }
    else if (varbutton == "2") {
      if (bnstate[1] == 1 ) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 105);
      } else
        M5.Lcd.fillRect(10, 105, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);
    }
    else if (varbutton == "4") {
      if (bnstate[1] == 1 ) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 65);
      } else
        M5.Lcd.fillRect(10, 65, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 65);
    }
  }
}
void buttonstate2() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[2] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 105);
      } else
        M5.Lcd.fillRect(10, 105, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);
    }
    else if (varbutton == "2") {
      if (bnstate[2] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 105);
      } else
        M5.Lcd.fillRect(170, 105, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);
    }
    else if (varbutton == "4") {
      if (bnstate[2] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 145);
      } else
        M5.Lcd.fillRect(10, 145, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 145);
    }
  }
}
void buttonstate3() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[3] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 160);
      } else
        M5.Lcd.fillRect(10, 160, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 160);
    }
    else if (varbutton == "4") {
      if (bnstate[3] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 65);
      } else
        M5.Lcd.fillRect(170, 65, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 65);
    }
  }
}

void buttonstate4() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[4] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 50);
      } else
        M5.Lcd.fillRect(170, 50, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 50);
    }
    else if (varbutton == "4") {
      if (bnstate[4] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 145);
      } else
        M5.Lcd.fillRect(170, 145, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 145);
    }
  }
}
void buttonstate5() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[5] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 105);
      } else
        M5.Lcd.fillRect(170, 105, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);
    }
  }
}
void buttonstate6() {
  if (seite == 1) {
    if (varbutton == "6") {
      if (bnstate[6] == 1) {
        M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 160);
      } else
        M5.Lcd.fillRect(170, 160, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 160);
    }
  }
}

