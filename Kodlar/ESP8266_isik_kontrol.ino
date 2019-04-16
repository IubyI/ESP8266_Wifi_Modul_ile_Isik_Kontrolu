#include <ESP8266WiFi.h>

int role = 2;
int anahtar = 0;
int x = 0;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("Modemadi", "Modemsifresi");
  server.begin();
  pinMode(role, OUTPUT);
  pinMode(anahtar, INPUT);
  delay(5000);
 
  Serial.print("Connecting");
  for (int i = 0; i<10; i++)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

}

void loop(){
  
  if( !x && digitalRead(anahtar) == HIGH ){
    digitalWrite(role, HIGH);
    x = 1;
  }
  if( x && digitalRead(anahtar) == LOW ){
    digitalWrite(role, LOW);
    x = 0;
  }  
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/LED-ACIK") != -1) {
    digitalWrite(role, HIGH);
  }
  if (request.indexOf("/LED-KAPALI") != -1) {
    digitalWrite(role, LOW);
  }
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("");
  client.println("<a href=\"/LED-ACIK\"\"><button>ledi yak </button></a>");
  client.println("<a href=\"/LED-KAPALI\"\"><button>ledi sondur </button></a>"); 
  client.println("</html>");
}