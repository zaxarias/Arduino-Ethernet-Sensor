# Arduino-Ethernet-Sensor

## Arduino Weather Station

**First, lets create the Database in the Local Web Server**

**Database Name is: sensor**

**Table Name is: mydata**

**The structure of mydata Table in the Database is as Follows:**

| # | Name    | Type          | Extra        |
|---|---------|---------------|--------------|
|1  |id       |int(11)        |AUTO_INCREMENT|
|2  |time     |timestamp      |              |
|3  |hum      |varchar(10)    |              |
|4  |temp     |varchar(10)    |              |


**The Ethernet module used is ENC28J60**

*The  ENC28J60  is  a  stand-alone  Ethernet  controller
with  an  industry  standard  Serial  Peripheral  Interface
(SPI).  It  is  designed  to  serve  as  an  Ethernet  network
interface for any controller equipped with SPI.*

**Connect ENC28J60 to an Arduino Uno Board**

*Below we can see the wiring between an Arduino Uno R3 and the Ethernet module ENC28J60.*

*ETHERNET WIRING :
Arduino Uno pins: 10 = CS, 11 = MOSI, 12 = MISO, 13 = SCK*

![alt tag](screenshots/wiringEthernet.png "Sensor Wiring")

[Wiring Designed Using Fritzing Software: http://fritzing.org/home/](http://fritzing.org/home/)


**Connect the DHT11 Sensor to an Arduino Uno Board**

*Complete Wiring. Arduino Uno R3 & Ethernet Module ENC28J60 & DHT11 Sensor.*

![alt tag](screenshots/wiringSensor.png "Sensor Wiring")

[Wiring Designed Using Fritzing Software: http://fritzing.org/home/](http://fritzing.org/home/)

**Libraries :**

*The Library for the Ethernet Module is :*

*UIPEthernet Library :* [Arduino Ethernet library for ENC28J60 shields and breakout boards](https://github.com/ntruchsess/arduino_uip/)

*The Library for the DHT11 sensor is :*

*DHT Library :* [Adafruit DHT Humidity & Temperature Unified Sensor Library](https://github.com/adafruit/DHT-sensor-library)

**Arduino Serial Monitor :**

![alt tag](screenshots/serial_Monitor.png "Sensor Monitor")

**Arduino HTML Data Table :**

![alt tag](screenshots/dataTable.png "Data Table")

*In the table above we see the data sent to our database. More specifically, there is a humidity-temperature sensor connected to our Arduino and periodically via a network connection using the Ethernet Module ENC28J60 these data are recorded in a database. All the recordings are shown in detail in the list above.*
