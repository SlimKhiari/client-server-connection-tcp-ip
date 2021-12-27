Le projet consiste à simuler un échange des paquets de bout en bout entre un client et un serveur.
Le client ouvre la connexion, le serveur le renvoie le nombre demandé de paquets par le client, ce
dernier fermera la connexion dès réception des paquets.

pour compiler :
le serveu.c : gcc serveur.c -o serveur -lpthread , et pour 
le client.c : gcc client.c -o client

* schema explicatif :
![schema_explicatif](https://user-images.githubusercontent.com/73532355/147503297-4a0690a6-7fb6-4a2f-81df-aede87d60e4e.png)
