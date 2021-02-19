int  lastmilli = 0;
void laufzeit(){
  if (millis() > lastmilli+60000){
    lastmilli = millis();
     canvas.createCanvas(100, 40);
  canvas.setTextSize(3);
int h = millis()/3600000;
int m = ((h - (h,0) *60),0);
  String newstr = String((millis()/3600000),0)+":"+m;
  canvas.drawString(newstr, 0, 0);
  canvas.pushCanvas(450, 920, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  }
}

