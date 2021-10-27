#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h> 
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct User
{
		int nbr_paquet;
}User;

void *function(void *arg)
{
		int socket = *(int*)arg;
		const char msg[]="Nombre de paquets: ";
		const char msgbis[]="Fermeture en cours ... ";
		const char msgbisbis[]="Paquets erronés !\n";
		User user;
		send (socket,msgbisbis, strlen(msgbis)+1,0);
		send (socket,msgbis, strlen(msgbis)+1,0);
		send (socket,msg, strlen(msg)+1,0);
		recv(socket, &user, sizeof(user), 0);
		
		if (user.nbr_paquet < 0)
		{
			sleep(1);
			printf("PAQUET ERRONES ! \n");
		}
		else if (user.nbr_paquet > 0)
		{
			sleep(1);
			printf("NOMBRE DE PAQUETS DEMANDE PAR LE CLIENT :%d \n",user.nbr_paquet);
		}
		else 
		{
				printf("FERMETURE DE LA CONNEXION AVEC LE CLIENT \n");
		}
		
	
		while(user.nbr_paquet != 0){ //pour fermer la  connexion le client entrer 0 pour la variable age
		send (socket,msg, strlen(msg)+1,0);
		recv(socket, &user, sizeof(user), 0);
		if (user.nbr_paquet < 0)
		{
			sleep(1);
			printf("PAQUET ERRONES ! \n");
		}
		else if (user.nbr_paquet > 0)
		{
			sleep(1);
			printf("NOMBRE DE PAQUETS DEMANDE PAR LE CLIENT :%d \n",user.nbr_paquet);
		}
		else 
		{
				printf("FERMETURE DE LA CONNEXION AVEC LE CLIENT \n");
		}}
		sleep(30);
		close(socket);
		free(arg);
		pthread_exit(NULL);
}

int main(void)
{
		int socketServer = socket(AF_INET, SOCK_STREAM, 0); //AF_INET pour les adresse ipv4, SOCK_STREAM=type de socket pour le protocle TCP 
		struct sockaddr_in addrServer; //Configurer l adresse de mon serveur par le type sockaddr_in
		addrServer.sin_addr.s_addr=inet_addr("127.0.0.1"); //inet_addr pour convertir l adresse au type qui corespond
		addrServer.sin_family=AF_INET;
		addrServer.sin_port=htons(30000); //mon numero de port
		
		bind(socketServer,(const struct sockaddr *)&addrServer, sizeof(addrServer)); //connecter mon serveur
		printf("liaison: %d\n", socketServer);

		listen(socketServer, 5); // attendre que les clients se connectent
		printf("écoute\n");
		
		pthread_t threads[3];
		
		for(int i=0; i<3;i++){
			struct sockaddr_in addrClient;
			socklen_t csize = sizeof(addrClient);
			int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize); //accepter au niveau du socket serveur une adresse de type sockaddr
			printf("accepté\n");
			printf("client: %d\n", socketClient);

			int *arg=malloc(sizeof(int));
			*arg = socketClient;
			
			pthread_create(&threads[i], NULL, function, arg);
		}
	
		for(int i=0;i<3;i++)
		{
			pthread_join(threads[i],NULL);
		}
		
		close(socketServer);
		printf("fermé\n");
			
		return 0;
}
