/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <FS.h>

AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "AB";
const char* password = "Vivek@1234";

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";
const char* PARAM_INPUT_4 = "FormatData";

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    C01: <input type="text" name="input1">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    C02: <input type="text" name="input2">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    C03: <input type="text" name="input3">
    <input type="submit" value="Submit">
  </form>
  <form action ="/get">
    Format data : <input type = "bool" name = "FormatData">
                  <input type ="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  SPIFFS.begin();//start SPIFFS
  
  
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on( "/get", HTTP_GET, [] (AsyncWebServerRequest * request)
  {
    String inputMessage_1;
    String inputMessage_2;
    String inputMessage_3;
    String inputParam;

    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1))
    {
      inputMessage_1 = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      String filename = "/sample.txt";
      
      File fp = SPIFFS.open(filename, "w");
      if(!fp)
        Serial.println("Error :Open File ");
      fp.println("IP_1: " + inputMessage_1);
      fp.close();
    }

    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2))
    {
      inputMessage_2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
      File fp = SPIFFS.open("/sample.txt", "a+");
      if(!fp)
        Serial.println("Error :Open File ");
      fp.println("IP_2: " + inputMessage_2);
      fp.close();
    }

    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_3))
    {
      inputMessage_3 = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
      File fp = SPIFFS.open("/sample.txt", "a+");
      if(!fp)
        Serial.println("Error :Open File ");
      fp.println("IP_3: " + inputMessage_3);
      fp.close();
    }
    else if(request->hasParam(PARAM_INPUT_4) )
    {
      inputParam = request->getParam(PARAM_INPUT_4)->value();
      if( inputParam.equals("1") )
        {
          Serial.println("Formatting Data :...!!!");
          Serial.println("It will take some time.");
          SPIFFS.format();  
        }
    }
    else
    {
      
      inputMessage_1 = "No message sent";
      inputParam = "none";
    }

    Serial.println(inputMessage_1);
    Serial.println(inputMessage_2);
    Serial.println(inputMessage_3);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field ("
                  + inputParam + ") with value: " + inputMessage_1 + "<br>" + inputMessage_2 + "<br>" + inputMessage_3 + "<br>" +
                  "<br><a href=\"/\">Return to Home Page</a>");
  });

  server.onNotFound(notFound);
  server.begin();
  Serial.println("Reading From SPIFSS :......!!!");

}

bool flag = true;
void loop() {
   
  File fp = SPIFFS.open("/sample.txt", "r");
  if (!fp )
  {
    if( flag)
       {
        Serial.println("Error : Open File\nFile doesn't have Data....!!! ");
        flag = false;
      }
  }
  else
  {
    
    for (int i = 0; i < fp.size(); i++)
      Serial.print( (char)fp.read() );
    fp.close();
    flag = true;
     Serial.println();
  delay(2000);
  }
  
 
}
