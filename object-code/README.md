# Configuration Arduino

Configuration d'un arduino MEGA 2560 avec un Click SHIELD.

## Prés-requis

### 1. Installation Arduino IDE

Rendez-vous sur le site officiel d'Arduino : https://www.arduino.cc/en/Main/Software est installer la dernière version de l'IDE disponible.
Il est aussi possible d'utiliser le Web Editor pour configurer l'Arduino

### 2. Ajout des librairies Adafruit

Pour configurer l'Arduino comme convenu, il faut se rendre dans l'onglet "Croquis" puis "Inclure une bibliothèque" et "Gerer les bibliothèques" comme ci-dessous :

![Arduino1](/images/arduino1.png)

Ensuite, ajouter les **deux** librairies suivantes

Adafruit_CC3000 | Adafruit_VL6180X
------------ | -------------
![Arduino2](/images/arduino2.png) | ![Arduino3](/images/arduino3.png)

**NOTE :** les librairies utilisés durant le projet sont disponibles dans ce repertoire

**ATTENTION :** Ne pas oublier d'inclure les librairies en allant dans l'onglet "Croquis" puis "Inclure une bibliothèque" et cliquant sur les deux librairies. (le redémarrage de Arduino IDE peut être nécessaire)

## Configuration matériel

### Utilisation du click shield pour Arduino

Pour ce projet nous utilisons l'Arduino MEGA accompagné par un click Shield comme ci-dessous :

![ArduinoMega](/images/arduinoMega.png)

### Click utilisés pour le projet

Les clicks associés sont les suivants :

* SLOT 1 : MOTION CLICK 
* SLOT 2 : LIGHT RANGER CLICK
* SLOT 3 : CC3000 CLICK 

![ArduinoCLICK](/images/ClickPosition.png)

**NOTE :** Il est possible d'interchanger les clicks Light Ranger et Motion ainsi que le CC3000 et le Light Ranger en ajustant les pins de configuration.

**ATTENTION :** Il est impossible de placer le CC3000 sur le slot 1 du SHIELD, car le pin d'interruption associée au slot 1 (PE3/PWM) correspondant au pin 5 de l'arduino est inutilisable en interruption selon la doc officielle d'Arduino : https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

 



