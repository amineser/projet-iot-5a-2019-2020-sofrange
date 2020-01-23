# Configuration Passerelle - Cloud

Concernant le cloud, Si on a un Raspberry Pi, Beaglebone ou un autre appareil basé sur Linux, et on souhaite interagir avec Ubidots, voici un descreptif qui montre comment on a créé notre cloud sous Ubidots et comment on a pu le tester avec les avantages de ce dernier. Pour notre cas on a travaillé avec un Beaglebone.

On a commencé par créer un compte upidots sur https://industrial.ubidots.com, avec ce compte on a une version de test gratuite pendant 30 jours où on peut utiliser toutes les fonctionnalitées d'Ubidots mais parfois avec des limitaions qu'on verra plus tard dans ce descreptif.

On a créé par la suite un device qu'on a appelé "Beaglebone-data" sur lequel on a ajouté les variables qu'on souhaite avoir sur le cloud comme données depuis le beaglebone, les variables sont les suivantes : Lumonisité, Remplissage et NBdéchets, chacune de ces variables a une "API label" qu'on utilisera plus tard dans notre script qui permet d'envoyer les données.

Ensuite je me suis penché sur le script python qui va me permettre d'envoyer les données, dans un premier temps j'ai commencé par envoyer des données random afin de tester mon script et dans un deuxième temps faire la connexion entre les données reçu dans le beaglebone et le cloud.

Il faut tout d'abord s'assurer qu'on a bien python installer sur notre machine linux ainsi que certaines bibliothèques, si ce n'est pas le cas il faut commencé par installer la bibliothéque requests qui est une bibliothèque Python populaire qui simplifie les requêtes HTTP à partir de n'importe quel script python qui peut être exécuté dans le terminal de votre ordinateur ou tout périphérique Linux intégré. Si vous ne disposez pas de Python configuré sur votre ordinateur ou appareil, référez-vous à la documentation Python officielle pour commencer en cliquant sur le lien suivant : https://www.python.org/downloads/.

Avec votre ordinateur correctement configuré avec Python, exécutez le package pip dans le terminal de votre ordinateur ou périphérique pour installer la bibliothèque appropriée.

     $ pip demandes d'installation

Avec Python correctement installé, nous pourrons maintenant créer un script Python qui permet d'envoyer les données sur ubidots et qu'on peut visualiser sur l'interface graphique d'Ubidots en cliquant sur notre device. On peut remarquer les valeurs de nos variables qui change avec les données reçues. Vous pouvez trouver le fichier du script python dans ce répertoire.

Sur ubidots nous avons déjà notre device mise en place et parametré à recevoir les valeurs concernant ses capteurs qui sont  Lumonisité, Remplissage et NBdéchets. Pour chacun de ses capteurs on peut voir un graphe de toutes les valeurs reçu dans le temps depuis la mise en place du device. Ensuite pour permettre à tout utilsateur de visualiser les données envoyés par notre device (poubelle connectée) de façon simplifiée nous avons mis en place un dashboard regroupant toute les données affichées à l'aide de widget et de graphique des derniers résultats et celles des derniers 24h.

Ensuite nous avons mis en place des alertes sur les differentes variables avec des règles d'astreinte comme par exemple si le remplissage, la luminosité ou le NBdéchets dépasse un certain seuil on envoie un message sur telegram (la semaine de 00:00-23h49), un mail (la semaine de 08:00-18:00), un sms (le week-end de 00:00-23h59), (cette fonctionnalité dans notre compte d'essai est limitée à 10 sms sur les 30 jours), ou encore un appel téléphonique au service d'astreinte (cette fonctionnalité dans notre compte d'essai est limitée à 1 appel sur les 30 jours). Nous avons aussi mis en place un envoie de rapport quotidien nous résumant ce qu'il s'est passé la veille pour analyser les résultats chaque matin afin de voir s'il s'est passé une anomalie dans le système au cas ou on reçoit pas d'alerte.

