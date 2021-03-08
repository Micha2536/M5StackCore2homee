
void array_to_string(uint8_t array[], unsigned int len, char buffer[])
{
  for (unsigned int i = 0; i < len; i++)
  {
    byte nib1 = (array[i] >> 4) & 0x0F;
    byte nib2 = (array[i] >> 0) & 0x0F;
    buffer[i * 2 + 0] = nib1  < 0xA ? '0' + nib1  : 'a' + nib1  - 0xA;
    buffer[i * 2 + 1] = nib2  < 0xA ? '0' + nib2  : 'a' + nib2  - 0xA;
  }
  buffer[len * 2] = '\0';
}

void hashPassword(char* password, size_t size, char* hash) {
  uint8_t value[HASH_SIZE];
  sha512.reset();
  sha512.update(password, size);
  sha512.finalize(value, sizeof(value));
  array_to_string(value, HASH_SIZE , hash);
}

void homee(String user, String pass, String ip) {
  String username = user;
  char buffer_user[username.length() + 1];
  username.toCharArray(buffer_user, username.length() + 1);
  char username2[username.length()];
  for (int i = 0; i < username.length() + 1; i++) {
    username2[i] = buffer_user[i];
  };
  String password = pass;
  char buffer_pass[password.length() + 1];
  password.toCharArray(buffer_pass, password.length() + 1);
  char password2[password.length()];
  for (int i = 0; i < password.length() + 1; i++) {
    password2[i] = buffer_pass[i];
  };

  //char username[user.length()+1] = user;
  //char password[pass.length() +1] = pass;
  char hash[HASH_SIZE * 2 + 1];

  hashPassword(password2, strlen(password2), hash);
  char authBuffer[strlen(username2) + strlen(hash) + 1 ] = {'\0'};
  sprintf(authBuffer, "%s:%s", username2, hash);
  String authString = "Basic " + base64::encode(authBuffer);
  HTTPClient http;
  String Url = "http://" + ip + ":7681/access_token";
  http.begin(Url);
  http.addHeader("Authorization", authString);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST("device_name=esp32_1&device_hardware_id=esp32_1&device_os=5&device_type=4&device_app=1}");
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    response.replace("&", " ");
    char buffer[200];
    char * anfang = buffer;
    strcpy(buffer, response.c_str());
    char * zeiger = strstr(buffer, "access_token=");
    zeiger += 13;
    char * ende = strstr(zeiger, " user_id");
    buffer[ende - anfang] = 0;
    Serial.println(zeiger);
     preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("token", String(zeiger));
      preferences.end();
  } else {

    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);

  }
}
