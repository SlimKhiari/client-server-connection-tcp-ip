#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct User
{
		int nbr_paquet;
}User;

int main(void)
{
		int socketClient = socket(AF_INET, SOCK_STREAM, 0); //On crée notre socket client
		struct sockaddr_in addrClient;
		addrClient.sin_addr.s_addr=inet_addr("127.0.0.1"); // On met notre adresse serveur
		addrClient.sin_family=AF_INET;
		addrClient.sin_port=htons(30000); 
		connect(socketClient,(const struct sockaddr *)&addrClient, sizeof(addrClient)); //On connecte le client à l adresse qu'on a à l'adresse sockaddr_in avec la taille
		printf("Connecté\n");
		
		User user;
		char msg[33];
		char msgbis[1000];
		char msgbisbis[1000];
	
		recv(socketClient, msgbisbis, 999, 0);
		recv(socketClient, msgbis, 999, 0);
		recv(socketClient, msg, 32, 0);
		
		printf("%s\n",msg);
		scanf("%d",&user.nbr_paquet);
		send(socketClient, &user, sizeof(user), 0);
		if(user.nbr_paquet < 0)
		{
			sleep(2);
			printf("%s\n",msgbisbis);
		}
		else if(user.nbr_paquet > 0)
		{
			sleep(2);
			printf("Paquets envoyés\n\n");
		}
		
		while(user.nbr_paquet != 0)
		{
			recv(socketClient, msg, 32, 0);
			printf("%s\n",msg);
			scanf("%d",&user.nbr_paquet);
			send(socketClient, &user, sizeof(user), 0);
			if(user.nbr_paquet < 0)
			{
				sleep(2);
				printf("%s\n",msgbisbis);
			}
			if(user.nbr_paquet > 0)
			{
				sleep(2);
				printf("Paquets envoyés\n\n");
			}
			
		}
		printf("%s\n",msgbis);
		sleep(30);
		close(socketClient);

		return 0;
}
