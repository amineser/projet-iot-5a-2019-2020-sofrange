# Configuration BeagleBone Black (BBB)

![alt Beaglebone](../images/bbb.jpg)

#Nous allons dans un premier temps formater la carte SD et  télécharger la dernière version de l’image: "Debian 9.9 2019-08-03 4GB SD LXQT" 

#Veiller à démarrer la machine virtuel en activant les cartes eth0 eth1 eth2, le BBB déjà connecté. une fois allumé, le BBB remonte et fait office de DHCP en accordant une addresse IP: 192.168.7.2 à la carte eth2(pour notre cas). 

#Dans  gtkterm,ou minicom  s'assurer de la bonne configuration du terminal série  afin  de  communiquer  avec  la  carte.On devrait avoir un nouveau port nommé «/dev/ttyACM0», et la  vitesse  de  transmission  à  «115200».

#Se mettant dans le meme réseau, on peut alors se connecter via : ssh debian@192.168.7.2 pour y faire les différentes configurations. le mdp est : temppwd

#Il faut impérativement dans un premier temps, désactiver "connman" qui est une gestionnaire de connexion internet pour les périphériques car cela pourrait induire l'actualisation fréquente d'une mauvaise route par défaut et empêcherait le bon fonctionnement de notre configuration.

#Commande de désactivation connman : sudo systemctl disable connman.service  puis sudo /etc/init.d/connman stop

#Modifier le fichier /etc/resolv.conf pour la configuration DNS. rajouter la ligne "nameserver @serverDNS"

#dans  /etc/network/interfaces il faut configurer l'interface eth0 qui permettra le partage de connexion. 

auto eth0
iface eth0 inet static
    address 192.168.11.2
    netmask 255.255.255.252
    network 192.168.11.0
    gateway 192.168.11.1
    
 Redémarrer le service réseau pour valider toutes ces modifications. "/etc/init.d/networking restart"

#La table de routage du BBB devrait ressembler à ceci:
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         192.168.11.1    0.0.0.0         UG    0      0        0 eth0
192.168.7.0     0.0.0.0         255.255.255.252 U     0      0        0 usb0
192.168.11.0    0.0.0.0         255.255.255.252 U     0      0        0 eth0

#Configurer ensuite l'interface eth1 de la machine virtuelle qui est connecté en accès par pont sur VM0 en lui assignant l'adresse 192.168.11.1 qui correspond à la gateway dans eth0 du beaglebone. La carte eth0 de la Machine virtuelle est configurée en NAT et a accès à Internet. C'est ce qui nous permettrait d'accéder à Internet. 

#Pour que la machine virtuelle puisse rediriger les paquets du BBB vers internet il faut y activer le forwarding et configurer des règles IPTABLES.
 
 la commande sysctl -w net.ipv4.ip_forward=1 permet d'activer le forwading. (on peut vérifier avec sysctl -a | grep forward)
 
 #Régles IPTABLES : 
 
  iptables -- table nat -- append POSTROUTING -o eth0 -j MASQUERADE  (pour l'output)
  
  iptables -- append FORWARD -i eth1 -j ACCEPT (pour l'input)






