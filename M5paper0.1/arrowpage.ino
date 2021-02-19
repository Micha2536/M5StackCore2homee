void arrow(){
  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/arrow-left100.png");
  canvas.pushCanvas(10, 70, UPDATE_MODE_DU);
  canvas.deleteCanvas();

  canvas.createCanvas(100, 100);
  canvas.setTextSize(5);
  canvas.drawPngFile(SD, "/icon/arrow-right100.png");
  canvas.pushCanvas(430, 70, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

