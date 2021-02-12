/*BY SteffenTM
 * 
 * 
 */
void setup_NVS() {

  //Daten aus NVS bei Neustart laden und in Variablen schreiben
  preferences.begin (NAME, false);

  homeeIP_string = preferences.getString ("homeeIP");     //homee IP

  token_string = preferences.getString ("token");         //homee Token

  name1_string = preferences.getString ("name1");         //Name Gerät 1
  id1_string = preferences.getString ("id1");             //ID Gerät 1
  attr1_string = preferences.getString ("attr1");         //Attribut Gerät 1
  hg1_string = preferences.getString ("hg1");             // HG1

  name2_string = preferences.getString ("name2");         //Name Gerät 2
  id2_string = preferences.getString ("id2");             //ID Gerät 2
  attr2_string = preferences.getString ("attr2");         //Attribut Gerät 2
  hg1_string = preferences.getString ("hg2");

  name3_string = preferences.getString ("name3");         //Name Gerät 3
  id3_string = preferences.getString ("id3");             //ID Gerät 3
  attr3_string = preferences.getString ("attr3");         //Attribut Gerät 3
  hg1_string = preferences.getString ("hg3");

  name4_string = preferences.getString ("name4");         //Name Gerät 4
  id4_string = preferences.getString ("id4");             //ID Gerät 4
  attr4_string = preferences.getString ("attr4");         //Attribut Gerät 4
  hg1_string = preferences.getString ("hg4");

  name5_string = preferences.getString ("name5");         //Name Gerät 5
  id5_string = preferences.getString ("id5");             //ID Gerät 5
  attr5_string = preferences.getString ("attr5");         //Attribut Gerät 5
  hg1_string = preferences.getString ("hg5");

  name6_string = preferences.getString ("name6");         //Name Gerät 6
  id6_string = preferences.getString ("id6");             //ID Gerät 6
  attr6_string = preferences.getString ("attr6");         //Attribut Gerät 6
  hg1_string = preferences.getString ("hg6");

  TempOut = preferences.getString ("TempOut");            // Temp Outdoor

  varbutton = preferences.getString("varbutton");         // Buttonanzahl
  Serial.println(varbutton);
  preferences.end();
}
