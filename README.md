The project consists of simulating an end-to-end packet exchange between a client and a server. The client opens the connection, the server sends back the number of packets requested by the client, the latter will close the connection as soon as the packets are received.

to compile:

the server.c: gcc serveur.c -o server -lpthread (for the 1st terminal)

the client.c: gcc client.c -o client (for the 2nd terminal)

Next:

./server (for the 1st terminal)

./client (for the 2nd terminal)

explanatory diagram :
![schema_explicatif](https://user-images.githubusercontent.com/73532355/147503297-4a0690a6-7fb6-4a2f-81df-aede87d60e4e.png)
