# Configuration Arduino

Configuration d'un arduino MEGA 2560 avec un Click SHIELD.

## Prés-requis

### 1. Installation Arduino IDE

Rendez-vous sur le site officiel d'Arduino : https://www.arduino.cc/en/Main/Software est intaller la dernière version de l'IDE disponible.
Il est aussi possible d'utiliser le Web Editor pour configurer l'Arduino

### 2. Ajout des librairies Adafruit

Pour configurer l'Arduino comme convenue, il faut se rendre dans l'onglet "Croquis" puis "Inclure une bibliothèque" et "Gerer les bibliothèques" comme ci-dessous :

![Arduino1](/images/arduino1.png)

Ensuite ajouter les **deux** librairies suivantes

Adafruit_CC3000 | Adafruit_VL6180X
------------ | -------------
![Arduino2](/images/arduino2.png) | ![Arduino3](/images/arduino3.png)

**ATTENTION :** Ne pas oublier d'inclure les librairies en allant dans l'onglet "Croquis" puis "Inclure une bibliothèque" et cliquant sur les deux librairies. (le redémarrage de Arduino IDE peut être nécessaire)

## Configuration matériel

### Utilisation du click shield pour Arduino

Pour ce projet nous utilisons l'Arduino MEGA accompagné par un click Shield comme ci-dessous :

![ArduinoMega](/images/arduinoMega.png)

### Click utilisés pour le projet

Les clicks associé sont les suivants :

Adafruit_CC3000 | Adafruit_VL6180X
------------ | -------------
* SLOT 1 : MOTION CLICK 
* SLOT 2 : LIGHT RANGER CLICK
* SLOT 3 : CC3000 CLICK | TEST




