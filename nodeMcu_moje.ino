#include <ESP8266WiFi.h>

const char* ssid     = "router";                              //nazwa sieci
const char* password = "haslo123";                            //haslo do sieci
WiFiServer server(80);
int startNum = 7;                                             //numer pierwszego znaku do pobrania
int quaChar = 2;                                              //ilosc znakow ktore sa nazwa obiektu


//fukcje wykonywane raz
void setup() {
  pinMode(16, OUTPUT);                                        //ustawienie pinu jako wyjscia
  pinMode(5, OUTPUT);                                         //ustawienie pinu jako wyjscia
  pinMode(4, OUTPUT);                                         //ustawienie pinu jako wyjscia
  
  Serial.begin(115200);                                       //rozpoczęcie komunikacja na porcie szeregowym z predkoscia 115200
  delay(10);                                                  //odczekaj 10mills

  Serial.println();
  Serial.println();
  Serial.print("łączę do: ");                                 //wysylanie na serial port
  Serial.println(ssid);
                             
  WiFi.begin(ssid, password);                                  //rozpocznij połączenie do sieci WiFi
  
  while (WiFi.status() != WL_CONNECTED) {                      //kiedy nie jest poloczone do WiFi wypisuj kropki
    delay(500);
    Serial.print(".");
  }
  
  server.begin();                                             //rozpoczecie serwera
  
  Serial.println("");                       
  Serial.println("łączę do WiFi");  
  Serial.println("adres ip: ");
  Serial.println(WiFi.localIP());                             //wyslij na serial port IP
}


//fukcje wykonywane w petli
 void loop() {
 String nameVal = "";                                         //String przekazywany do wlaczenie
  
 WiFiClient client = server.available();                      //utworzenie klienta WiFi
  if (!client) {
    return;
  }
  
  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');                  //czytaj stringa do momentu gdy bedzie zakonczenie linii
  Serial.println(req);                                        //wyswietl odczytana wartosc
  

  //dodawanie kolejnych charow do stringa
  for(int i = startNum; i < startNum + quaChar; i++){
    nameVal = nameVal + String(req[i]);   
  }
  
//  if(nameVal.equals("pod")){
//    getPinOuts(16, String(req[startNum + quaChar + 1]));
//  }


  getPinOuts(nameVal.toInt(), String(req[startNum + quaChar + 1]));

  client.flush();                                           //wyczysc klienta
  client.print("koniec");
  client.stop();                                             //zatrzymaj klienta
  delay(1);
}

void getPinOuts(int pin, String state){
 
  digitalWrite(pin, state.toInt());                         //pin o numerze ustaw stan
}

