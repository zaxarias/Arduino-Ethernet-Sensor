#include <dht.h> //DHT11 LIBRARY
#include <UIPEthernet.h> //UIPE ETHERNT LIBRARY FOR THE ETHERNET MODULE ENC28J60
#define DHT11_PIN 9 // DHT11 IS CONNECTED TO PIN NUMBER 9 (ARDUINO UNO BOARD), OR SPECIFY ANY OTHER PIN
#define DEBUG // TURN DEBUGGING ON OR OFF, TO TURN IT OFF JUST COMMENT THIS LINE
dht DHT; // DEFINE A "dht" OBJECT INSTANCE WITH THE NAME "DHT"
/* ETHERNET SETTINGS
ARDUINO UNO PINS USED FOR THE ENC28J60 MODULE: 10=CS, 11=MOSI, 12=MISO, 13=SCK
THE ETHERNET MAC ADDRESS MUST BE UNIQUE IN THE PRIVATE LOCAL NETWORK
REMEMBER THAT THE MAC ADDRESS IS IN HEXADECIMAL FORMAT
IN THIS EXAMPLE WE USE THE FOLLOWING MAC ADDRESS : OE:96:03:38:94:92 */
byte mac[] = { 0x0E, 0x96, 0x03, 0x38, 0x94, 0x92 };
EthernetClient client; // CREATES A CLIENT WHICH CAN CONNECT TO A SPECIFIED INTERNET IP ADDRESS AND PORT
char server[] = "192.168.1.4"; /// IP ADDRESS OF THE LOCAL SERVER WE CONNECT AND SEND DATA TO
int  interval = 5000; // DELAY INTERVAL TO SAVE THE DATA IN THE DATABSE
long myinterval = 6000; //3 Minutes-> 180000ms INTERVAL BETWEEN DATA READINGS, I SET IT IN 6 SECONDS FOR TESTING PURPOSES
long previousMillis = 0;
int status = -2; // INITIALIZE THE CONNECTION STATUS VARIABLE
void setup() {
  Serial.begin(9600); // OPEN SERIAL COMMUNICATIONS AND WAIT FOR A PORT TO OPEN
  Ethernet.begin(mac); // INITIALIZES THE ETHERNET LIBRARY AND NETWORK SETTINGS
  /* ETHERNET SERIAL PRINTS
  INFORMATION ABOUT CLIENTS IP ADDRESS, THE SUBNET MASK OF THE NETWORK, THE GATEWAYS
  IP ADDRESS AND FINALLY THE DNS SERVER IP ADDRESS WHICH IS THE SAME AS THE GATEWAYS IP
  THESE INFORMATION WILL ONLY BE VISIBLE WHEN DEBUGGING IS ON */
#ifdef DEBUG
  Serial.println("Temperature Logger");
  Serial.println("*********************");
  Serial.print("IP Address   : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask  : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP     : ");
  Serial.println(Ethernet.dnsServerIP());
#endif
}

void loop() {
  unsigned long currentMillis = millis();
  // RESET ENC28J60 IN CASE OF FAILURE TO CONNECT WITH THE LOCAL SERVER
  if (!client.connect(server, 80)) {
#ifdef DEBUG
    Serial.println("Connection Failure: Resetting ENC28j60!");
#endif
    Enc28J60.init(mac); //RESET AND INITIALIZE THE ENC28J60 AND STARTS PACKET TRANSMISSION-RECEPTION
  } else {
    client.stop();
  }
  /* CONNECT TO THE SPECIFIED IP ADDRESS AND PORT
   IF A CONNECTION IS ESTABLISHED START SENDING DATA EVERY 3 MINUTES
   DATA WILL BE SENT AFTER THE FIRST 3 MINUTES
   ALSO WE CHECK THE STATUS OF THE SERVER
   THE FUNCTION CONNECT() RETURNS AN INT INDICATING CONNECTION STATUTS:
   SUCCESS (1)
   TIMED_OUT (-1)
   INVALID SERVER (-2)
   TRUNCATED (-3)
   INVALID RESPONSE (-4)*/
  status = client.connect(server, 80);
  if (status == 1) {
#ifdef DEBUG
    Serial.println("\nConnection Success");
#endif
    if (currentMillis - previousMillis > myinterval) {
      previousMillis = currentMillis;
      //READ DATA FROM THE DHT11 SENSOR
      int chk = DHT.read11(DHT11_PIN);
      /* THE READ11() FUNCTION RETURNS:
      DHTLIB_OK (0): THE SENSOR SAMPLE AND ITS CHECKSUM ARE OK
      DHTLIB_ERROR_CHECKSUM (-1): THE CHECKSUM TEST FAILED. THIS MEANS THE DATA WAS RECEIVED BUT MAY NOT BE CORRECT
      DHTLIB_ERROR_TIMEOUT (-2): A TIME OUT OCCURRED AND COMMUNICATION HAS FAILED
      BELOW WE CHECK THE STATUS OF THE SENSOR */
#ifdef DEBUG
      switch (chk) {
        case 0:
          Serial.print("Sensor OK");
          break;
        case -1:
          Serial.print("Checksum Test Failed");
          break;
        case -2:
          Serial.print("Time out Occurred, Communication Failed");
          break;
        default:
          Serial.print("Unknown Error");
          break;
      }
#endif
      // PRINT THE HUMIDITY AND TEMPERATURE VALUES IN THE SERIAL MONITOR
#ifdef DEBUG
      Serial.print("\nValues: ");
      Serial.print(DHT.humidity, 1);
      Serial.print(",\t");
      Serial.println(DHT.temperature, 1);
      Serial.println("Connected...sendingData");
#endif
      // MAKE A HTTP REQUEST
      // SPECIFY THE PHP FILE LOCATION IN THE SERVER
      //PRINT DATA TO THE SERVER THE CLIENT IS CONNECTED TO
      //STRUCTURE: "GET /filepath/yourfile.php?"
      client.print( "GET /arduEth/write_data.php?");
      client.print("hum="); //DATABASE VARIABLE IS USED
      client.print(DHT.humidity, 1); //THE VALUE TO WRITE IN THE DATABSE FOR HUMIDITY
      client.print("&&");
      client.print("temp=");
      client.print(DHT.temperature, 1); //THE VALUE TO WRITE IN THE DATABSE FOR TEMPERATURE
      client.println( " HTTP/1.1");
      client.print( "Host: " );
      client.println(server);
      client.println( "Connection: close" );
      client.println();
      client.println();
      client.stop(); // DISCONNECT FROM THE SERVER
      delay(interval); //SOME INTERVAL FOR THE DATA TO BE WRITTEN IN THE DATABASE
    }
  }
  // IN CASE OF A TIME_OUT
  else if (status == -1) {
#ifdef DEBUG
    Serial.println("Connection Timed Out !");
#endif
  }
  // IN CASE OF AN INVALID SERVER
  else if (status == -2) {
#ifdef DEBUG
    Serial.println("Invalid Server !");
#endif
  }
  // IN CASE OF TRUNCATION
  else if (status == -3) {
#ifdef DEBUG
    Serial.println("Truncated !");
#endif
  }
  // IN CASE OF AN INVALID RESPONCE
  else if (status == -4) {
#ifdef DEBUG
    Serial.println("Invalid Response !");
#endif
  }
  // IN CASE OF AN UNKNOWN ERROR
  else {
#ifdef DEBUG
    Serial.println("Unknown Error !");
#endif
  }
}
