#include <ESP8266WiFi.h>  //ESP8266 Wifi modülü kütüphanesi

int role = 2;
int anahtar = 0;
int x = 0;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("Modemadi", "Modemsifresi");  //bağlanılacak ağ adı ve şifresi
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

  Serial.print("Connected, IP address: ");  //IP adresi öğrenme
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

  if (request.indexOf("/LED-ACIK") != -1) {  //ledi yak butanuna basıldığında ya da uygulamadan /LED-ACIK bilgisi geldiğinde röleyi aç
    digitalWrite(role, HIGH);
  }
  if (request.indexOf("/LED-KAPALI") != -1) {  //ledi sondur butanuna basıldığında ya da uygulamadan /LED-KAPALI bilgisi geldiğinde röleyi kapat
    digitalWrite(role, LOW);
  }

  //html kodları
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
