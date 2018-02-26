// Boxguardian v0.1

#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>

// initialize lcd library
const int rs = 7, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int relayPin = 6;  // Pin of Relay Module


// Definition adresse mac
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

// Initialize the Ethernet client library
EthernetClient client;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Boxgardian");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("* Initialisation");

  // initialisation de la sortie relais
  pinMode(relayPin, OUTPUT);  // Set Pin connected to Relay as an OUTPUT
  digitalWrite(relayPin, HIGH);  // Set Pin to LOW to turn Relay OFF

  // Open serial communications: (pour test)
  Serial.begin(9600);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  // print your local IP address:
  printIPAddress();
}

void loop() {
  
  switch (Ethernet.maintain())
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");

      //print your local IP address:
      printIPAddress();
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");

      //print your local IP address:
      printIPAddress();
      break;

    default:
      //nothing happened
      break;

  }
}

void printIPAddress()
{
  //lcd.begin(16, 2);
  lcd.clear();
  //lcd.setCursor(0, 0);
  //lcd.print("");
  lcd.print("Adresse IP: ");
  lcd.setCursor(0, 1);
  Serial.print("My IP address: ");
  
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
    //lcd.setCursor(0, 1);
    //lcd.print("TEST");
    lcd.print(Ethernet.localIP()[thisByte], DEC);
    lcd.print(".");
  }

  Serial.println();
}
