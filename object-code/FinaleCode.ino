/**************************************************************************/
/*!
    @creator ALEXANDRE PEREIRA
*/
/**************************************************************************/

#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <Wire.h>
#include "Adafruit_VL6180X.h"


/**************************************************************************/
/*!
    CC3000 CLICK : Initialisation des PINs selon l'arduino et le SLOT

*  POUR ARDUINO UNO avec un Shield

*  SLOT 1
       #define ADAFRUIT_CC3000_IRQ     2
       #define ADAFRUIT_CC3000_VBAT    14
       #define ADAFRUIT_CC3000_CS      10

 * SLOT 2
      #define ADAFRUIT_CC3000_IRQ      3
      #define ADAFRUIT_CC3000_VBAT     15
      #define ADAFRUIT_CC3000_CS       9


*  POUR ARDUINO MEGA avec Click Shield

   ATTENTION : SLOT 1 Inutilisable car le pin 5 (PE3/PWM) n'est pas utilisable en interruption

*  SLOT 2
      #define ADAFRUIT_CC3000_IRQ       2
      #define ADAFRUIT_CC3000_VBAT      48
      #define ADAFRUIT_CC3000_CS        46

*  SLOT 3
      #define ADAFRUIT_CC3000_IRQ       3
      #define ADAFRUIT_CC3000_VBAT      47
      #define ADAFRUIT_CC3000_CS        45

*/


#define ADAFRUIT_CC3000_IRQ   3  
#define ADAFRUIT_CC3000_VBAT  47
#define ADAFRUIT_CC3000_CS    45
/**************************************************************************/




/**************************************************************************/
/*!
    CC3000 CLICK : Initialisation des variables
*/

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIVIDER); // création de l'objet

#define WLAN_SSID       "APwifi"           // SSID < 32 caractères!
#define WLAN_PASS       ""
#define WLAN_SECURITY   WLAN_SEC_WPA2  // choix possible : WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Valeur du TIME OUT sans réponse

uint32_t ip;

/**************************************************************************/



/**************************************************************************/
/*! LIGHT RANGER CLICK : Initialisation des variables*/


Adafruit_VL6180X capteur = Adafruit_VL6180X(); // création de l'objet capteur proximité

float lumiere; int proximite; int etat;


/**************************************************************************/


/**************************************************************************/
/*
    MOTION CLICK : Initialisation des variables et de la pin selon le slot


   POUR ARDUINO MEGA avec Click Shield
   SLOT 1
   int motionPin = 10
   SLOT 2
   int motionPin = 11
   SLOT 3
   int motionPin = 12
*/

int motionPin = 10; 
int motionCp = 0;

/**************************************************************************/


//Variable de transformation uniquement. Utilisé pour l'envoi via TCP.
String Lum; String Prox; String Nb; 


void setup(void)
{
  Serial.begin(115200); //Initialisation de l'affichage Serial

  /**************************************************************************/
  /*! LIGHT RANGER + MOTION CLICK*/

  pinMode(LED_BUILTIN, OUTPUT); // initialisation pin LED_BUILTIN comme output.
  pinMode(motionPin, INPUT); // initialisation pin motion comme intput.

  Wire.begin(); // initialisation de la liaison I2C
  capteur.begin(); // initialisation de capteur

  /**************************************************************************/


  /**************************************************************************/
  /*! LIGHT RANGER + MOTION CLICK*/

  /* Initialise le module */
  Serial.println(F("\nInitializing CC3000..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while (1);
  }

  /* Connection au réseau */
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while (1);
  }

  Serial.println(F("Connected!"));

  /* Requette DHCP */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }

  /* Appercu des informations réseau obtenues */
  while (! displayConnectionDetails()) {
    delay(1000);
  }
  
  /* Definition de l'ip du serveur TCP*/
  ip = cc3000.IP2U32(192, 168, 4, 1); //Définition ip static

  /**************************************************************************/
  
}

void loop(void)
{
  if (digitalRead(motionPin)) //Si un mouvement a été detecter par le capteur
  {
    motion();//Incrémentation du compteur
    ligthRanger();//Récupération des données du capteur
    toString();//Transformation des variables en String

    /**************************************************************************/
    /*!
        Connection au serveur + envoi des données 
    */
        
        // Connection au serveur en utilisant l'adresse ip + port
        Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 9000); 
        
        if (www.connected()) {
          www.print(Lum);
          www.print("\r");
          delay(10);
          www.print(Prox);
          www.print("\r");
          delay(10);
          www.print(Nb);
          www.print("\r");    
        }
        else {
          Serial.println(F("Connection failed"));
          return;
        }
        www.close(); // ATTENTION bien fermer la connection après chaque envoi !!
    /**************************************************************************/

  }

  delay(1000);
}

/**************************************************************************/
/*!
    @brief  Incrémentation du compteur de bouteille + affichage
*/
/**************************************************************************/
void motion() {

  motionCp++; //incrementation du compteur

  Serial.print("Motion n° ");
  Serial.print(motionCp);
  Serial.println(" detected !!!"); // affichage du message`

  delay(4000); //delay de 4 secondes = temps du capteur pour s'eteindre
}

/**************************************************************************/
/*!
    @brief  Aqcuisitiond des données du capteur + allumage LED
*/
/**************************************************************************/
void ligthRanger() {

  // Acquisition des grandeurs
  lumiere = capteur.readLux(VL6180X_ALS_GAIN_5);
  proximite = capteur.readRange();
  etat = capteur.readRangeStatus();

  // Affichage de la luminosité
  Serial.print("Eclairement=");
  Serial.print(lumiere);
  Serial.println(" Lux");

  if (etat == VL6180X_ERROR_RAWOFLOW) //le capteur ne recois pas le signal de retour
  {
    Serial.println("Erreur Capteur");
    digitalWrite(LED_BUILTIN, HIGH);   // LED on
  }
  else if (proximite >= 200)
  {
    Serial.println("Niveau Ok");
    digitalWrite(LED_BUILTIN, LOW); // LED off
  }
  else if (proximite <= 50)
  {
    Serial.println("Niveau Critique");
    digitalWrite(LED_BUILTIN, HIGH);   // LED on
  }
  else
  {
    Serial.print("Proximite="); Serial.print(proximite); Serial.println(" mm");
    digitalWrite(LED_BUILTIN, LOW); //  off
  }

  delay(500);
}

/**************************************************************************/
/*!
    @brief  Translation des variables en STRING + formatage selon besoin
*/   
/**************************************************************************/
void toString() {
  Lum  = "L="  + String(lumiere);
  Prox = "P="  + String(proximite);
  Nb   = "Nb=" + String(motionCp);

}

/**************************************************************************/
/*!
    @brief  Lectures des informations réseaux
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if (!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
