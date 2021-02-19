String icon;
void bulb(uint16_t x , uint16_t y , String name) {
  canvas.createCanvas(200, 200);
  canvas.setTextSize(6);
  canvas.drawRoundRect(0, 0, 200, 200, 20, G15);
  canvas.drawRoundRect(1, 1, 198, 198, 20, G15);
  canvas.drawRoundRect(2, 2, 196, 196, 20, G15);
  canvas.drawRoundRect(3, 3, 194, 194, 20, G15);
  canvas.drawFastHLine(0, 150, 200, 4, G15);
  canvas.drawFastVLine(98, 150, 50, 4, G15);
  canvas.setTextSize(3);
  canvas.drawString(name, 20, 124);
  canvas.setTextSize(4);
  canvas.drawString("ON", 30, 160);
  canvas.drawString("OFF", 115, 160);
  canvas.pushCanvas(x, y, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100off.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();

}

void bulbon(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100on.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void bulboff(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100off.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void dimmablebulb(uint16_t x , uint16_t y , String name) {
  canvas.createCanvas(200, 200);
  canvas.setTextSize(6);
  canvas.drawRoundRect(0, 0, 200, 200, 20, G15);
  canvas.drawRoundRect(1, 1, 198, 198, 20, G15);
  canvas.drawRoundRect(2, 2, 196, 196, 20, G15);
  canvas.drawRoundRect(3, 3, 194, 194, 20, G15);
  canvas.drawFastHLine(0, 150, 200, 4, G15);
  canvas.drawFastVLine(98, 150, 50, 4, G15);
  canvas.setTextSize(3);
  canvas.drawString(name, 20, 124);
  canvas.setTextSize(3);
  canvas.drawString("+10%", 18, 160);
  canvas.drawString("-10%", 107, 160);
  canvas.pushCanvas(x, y, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100off.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();

}

void dimmablebulb50(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100_50.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void dimmablebulb30(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100_30.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void dimmablebulb10(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100_10.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void dimmablebulb60(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100_60.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void dimmablebulb80(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100_80.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}
void dimmablebulb90(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/bulb100_90.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}
void fan(uint16_t x , uint16_t y , String name) {
  
  /*switch (type){
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
  */
  //size_t Size = strlen(name);
  canvas.createCanvas(200, 200);
  canvas.setTextSize(6);
  canvas.drawRoundRect(0, 0, 200, 200, 20, G15);
  canvas.drawRoundRect(1, 1, 198, 198, 20, G15);
  canvas.drawRoundRect(2, 2, 196, 196, 20, G15);
  canvas.drawRoundRect(3, 3, 194, 194, 20, G15);
  canvas.drawFastHLine(0, 150, 200, 4, G15);
  canvas.drawFastVLine(98, 150, 50, 4, G15);
  canvas.setTextSize(3);
  canvas.drawString(name, 20, 125);
  canvas.setTextSize(4);
  canvas.drawString("ON", 30, 160);
  canvas.drawString("OFF", 115, 160);
  canvas.pushCanvas(x, y, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/fan100off.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();

}

void fanon(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/fan100.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void fanoff(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/fan100off.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void plug(uint16_t x , uint16_t y , String name) {
  
  /*switch (type){
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
  */
  //size_t Size = strlen(name);
  canvas.createCanvas(200, 200);
  canvas.setTextSize(6);
  canvas.drawRoundRect(0, 0, 200, 200, 20, G15);
  canvas.drawRoundRect(1, 1, 198, 198, 20, G15);
  canvas.drawRoundRect(2, 2, 196, 196, 20, G15);
  canvas.drawRoundRect(3, 3, 194, 194, 20, G15);
  canvas.drawFastHLine(0, 150, 200, 4, G15);
  canvas.drawFastVLine(98, 150, 50, 4, G15);
  canvas.setTextSize(3);
  canvas.drawString(name, 20, 125);
  canvas.setTextSize(4);
  canvas.drawString("ON", 30, 160);
  canvas.drawString("OFF", 115, 160);
  canvas.pushCanvas(x, y, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/plug100.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();

}

void plugon(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/plug100.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void plugoff(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/plug100.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void wallbulb(uint16_t x , uint16_t y , String name) {
  
  /*switch (type){
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
  */
  //size_t Size = strlen(name);
  canvas.createCanvas(200, 200);
  canvas.setTextSize(6);
  canvas.drawRoundRect(0, 0, 200, 200, 20, G15);
  canvas.drawRoundRect(1, 1, 198, 198, 20, G15);
  canvas.drawRoundRect(2, 2, 196, 196, 20, G15);
  canvas.drawRoundRect(3, 3, 194, 194, 20, G15);
  canvas.drawFastHLine(0, 150, 200, 4, G15);
  canvas.drawFastVLine(98, 150, 50, 4, G15);
  canvas.setTextSize(3);
  canvas.drawString(name, 20, 125);
  canvas.setTextSize(4);
  canvas.drawString("ON", 30, 160);
  canvas.drawString("OFF", 115, 160);
  canvas.pushCanvas(x, y, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/wall-bulb100off.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();

}

void wallbulbon(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/wall-bulb100on.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void wallbulboff(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/wall-bulb100off.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void tumbledryer(uint16_t x , uint16_t y , String name) {
  
  /*switch (type){
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
    case "bulb" : icon ="/icon/"+type+"100off.png";
    break;
  */
  //size_t Size = strlen(name);
  canvas.createCanvas(200, 200);
  canvas.setTextSize(6);
  canvas.drawRoundRect(0, 0, 200, 200, 20, G15);
  canvas.drawRoundRect(1, 1, 198, 198, 20, G15);
  canvas.drawRoundRect(2, 2, 196, 196, 20, G15);
  canvas.drawRoundRect(3, 3, 194, 194, 20, G15);
  canvas.drawFastHLine(0, 150, 200, 4, G15);
  canvas.drawFastVLine(98, 150, 50, 4, G15);
  canvas.setTextSize(3);
  canvas.drawString(name, 20, 125);
  canvas.setTextSize(4);
  canvas.drawString("ON", 30, 160);
  canvas.drawString("OFF", 115, 160);
  canvas.pushCanvas(x, y, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/tumble-dryer100off.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();

}

void tumbledryeron(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/tumble-dryer100on.png");
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void tumbledryeroff(uint16_t x,uint16_t y) {
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/tumble-dryer100off.png" );
  canvas.pushCanvas(x+50, y+20, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void device (uint16_t x , uint16_t y){
  if ( (x > 295 && x < 495) && (y > 660 && y < 860)){
    Serial.println("device 6 berührt");
    if ( (x > 295 && x < 395) && (y > 830 && y < 860)){
      Serial.println("device 6 linker Button");
      int value = bnstate[6] + 10;
      String str  = String("PUT:/nodes/") + id6_string + String("/attributes/") + attr6_string + String("?target_value=")+String(value);
                Serial.println(str);
                webSocket.sendTXT(str);
    }
    
    if ( (x > 395 && x < 495) && (y > 830 && y < 860)){
      Serial.println("device 6 rechter  Button");
      int value = bnstate[6] - 10;
      String str  = String("PUT:/nodes/") + id6_string + String("/attributes/") + attr6_string + String("?target_value=")+String(value);
                Serial.println(str);
                webSocket.sendTXT(str);
    }
    
    if ( (x > 295 && x < 495) && (y > 660 && y < 830)){
      Serial.println("device 6 mittlerer Button");
    }
  }
}

