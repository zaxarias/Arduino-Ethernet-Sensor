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

![alt tag](screenshots/wiringEthernet.png "ENC28J60 Wiring")
