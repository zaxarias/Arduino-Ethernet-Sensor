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

**Connect ENC28J60 to Arduino Uno Board**

*The image below shows how we can wire an Arduino Uno board with the ENC28J60 Module*

![alt tag](screenshots/wiringEthernet.png "ENC28J60 Wiring")


*The sensor used is DHT11. DHT11 is a basic Temperature-Humidity Sensor*

**Technical Details of DHT11**

- Low cost
- 3 to 5V power and I/O
- 2.5mA max current use during conversion (while requesting data)
- Good for 20-80% humidity readings with 5% accuracy
- Good for 0-50°C temperature readings ±2°C accuracy
- No more than 1 Hz sampling rate (once every second)
- Body size 15.5mm x 12mm x 5.5mm
- 4 pins with 0.1" spacing

*The image below shows how we can wire an Arduino Uno board with the DHT11 Sensor*

![alt tag](screenshots/wiringSensor.png "DHT11 Wiring")
