int xstart =0;
int ystart =0;
void page2(){
  lcd.fillRect(0,200,540,700,0xFFFFFFu);
  //lcd.setColor(0xFF0000U);
  lcd.setTextColor(16);
    lcd.setTextSize(5);
  //lcd.drawLine(300,300,250,200,16);
  //lcd.drawCircle ( 300, 300, 60    );
  mqttClient.beginMessage(topic);
    mqttClient.print("hello ");
    mqttClient.print("na mal schauen ob das wirklich klappt");
    mqttClient.endMessage();
    M5.TP.update();
      Serial.print(M5.TP.isFingerUp());
      webSocket.sendTXT("get:/nodes/-1");
 
  /*
  Serial.println("page2");
  canvas.createCanvas(300, 300);
  Serial.println("create Canvas");
  canvas.setTextSize(5);
  Serial.println("textsize");
  //canvas.drawPngFile(SD, "/icon/plug100.png");
  Serial.println("SD geladen");
  */
  
  /*
  canvas.pushCanvas(1, 170, UPDATE_MODE_A2);
  canvas.pushCanvas(240, 170, UPDATE_MODE_A2);
  canvas.pushCanvas(1, 470, UPDATE_MODE_A2);
  canvas.pushCanvas(240, 470, UPDATE_MODE_A2);
  canvas.pushCanvas(1, 560, UPDATE_MODE_A2);
  canvas.pushCanvas(240, 560, UPDATE_MODE_A2);
  Serial.println("push durchgeführt");
  canvas.deleteCanvas();
  Serial.println("Canvas gelöscht");
  */
  seite = 2;
  y = 200;
   xstart =0;
  ystart =0;
  }

void chart(uint16_t x){
  lcd.setTextColor(16);
    lcd.setTextSize(8);
  //if (seite == 2){
    Serial.println(x);
 lcd.drawLine(xstart,700-ystart,xstart+5,700-(x/10), 16);
 lcd.drawLine(xstart+1,700-ystart+1,xstart+5+1,700-(x/10)+1, 16);
 xstart = xstart+5;
 ystart = (x/10);
  if ( xstart >530){
    lcd.fillRect(0,200,540,700,0xFFFFFFu);
    xstart = 0;
 // }
  }
 }
