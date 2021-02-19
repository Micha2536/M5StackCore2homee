/*BY Micha homee Community


*/

//Clock left top
void ntp() {

  if (lasttime != timeClient.getMinutes()) {
    String timepaper;
    int h = timeClient.getHours();
    int  m = timeClient.getMinutes();
    String h_str;
    String m_str;
    if ( h  < 10 ) {
      h_str = "0" + String(h);
    } else h_str = String(h);
    if ( m  < 10) {
      m_str = "0" + String(m);
    } else m_str = String(m);
    timepaper = h_str + ":" + m_str;
    lasttime = timeClient.getMinutes();
    canvasntp.createCanvas(130, 40);
    canvasntp.setTextSize(3);
    canvasntp.drawString(timepaper, 0, 0);
    canvasntp.pushCanvas(5, 10, UPDATE_MODE_DU);
  }
  //if (timeClient.getSeconds() == 20 ){page1();}
  //if (timeClient.getSeconds() == 50 ){page2();}

}
