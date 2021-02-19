void page1() {

  seite = 1;
  lcd.fillRect(0, 170, 540, 730, 0xFFFFFFu);
  bulb(45, 200, name1_string);
  delay(200);
  bulb(45, 430, name2_string);
  delay(200);
  bulb(45, 660, name3_string);
  delay(200);
  bulb(295, 200, name4_string);
  delay(200);
  bulb(295, 430, name5_string);
  delay(200);
  dimmablebulb(295, 660, name6_string);// button mitte y700-800 x 300-500 , unten x300-400 ,y820-860, x 400-500
  buttonstate1();
  delay(200);
  buttonstate2();
  delay(200);
  buttonstate3();
  delay(200);
  buttonstate4();
  delay(200);
  buttonstate5();
  delay(200);
  buttonstate6();
  delay(200);

  /* canvas.createCanvas(200, 200);
    canvas.setTextSize(6);
    canvas.drawRoundRect(0, 0, 200, 200, 20, G15);
    canvas.drawRoundRect(1, 1, 198, 198, 20, G15);
    canvas.pushCanvas(300, 200, UPDATE_MODE_DU);
    canvas.deleteCanvas();

    canvas.createCanvas(100, 100);
    canvas.setTextSize(5);
    canvas.drawPngFile(SD, "/icon/bulb100off.png");
    canvas.pushCanvas(350, 250, UPDATE_MODE_DU);
    canvas.deleteCanvas();
  */
}
