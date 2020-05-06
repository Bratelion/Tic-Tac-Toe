#include <stdio.h>
#include <time.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#define MAX 80 
#define IP  "161.53.171.106"
#define PORT 50555 
#define SA struct sockaddr

char* game[3][3];
int counter;
int coords[2];

// Function designed for game between client and server. 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n;
	// Infinite loop for game 
	for (;;) {
		// Clean Buffer 
		bzero(buff, MAX); 

		// Read the message from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff)); 
		// Get Client coorindates
        coords[0] = atoi(&buff[0]);
        coords[1] = atoi(&buff[2]);
        game[coords[0]][coords[1]] = "X";
		counter++;

        printf("Client placed X on (%d, %d)\n", coords[0], coords[1]);
          
        printf("\t\t--- --- ---\n");
        printf("\t\t %s | %s | %s \n", game[0][0], game[0][1], game[0][2]);
        printf("\t\t--- --- ---\n");
        printf("\t\t %s | %s | %s \n", game[1][0], game[1][1], game[1][2]);
        printf("\t\t--- --- ---\n");
        printf("\t\t %s | %s | %s \n\n", game[2][0], game[2][1], game[2][2]);

		 // End game Winner Check!
		if((game[0][0] == "X" && game[0][1] == "X" && game[0][2] == "X") || 	// hor
			(game[1][0] == "X" && game[1][1] == "X" && game[1][2] == "X") ||
			(game[2][0] == "X" && game[2][1] == "X" && game[2][2] == "X") ||
			(game[0][0] == "X" && game[1][0] == "X" && game[2][0] == "X") ||	// ver
			(game[0][1] == "X" && game[1][1] == "X" && game[2][1] == "X") ||
			(game[0][2] == "X" && game[1][2] == "X" && game[2][2] == "X") ||
			(game[0][0] == "X" && game[1][1] == "X" && game[2][2] == "X") ||	// diagonal
			(game[0][2] == "X" && game[1][1] == "X" && game[2][0] == "X")){

				printf("Winner is Client!\n");
				break;
		}
		else if((game[0][0] == "O" && game[0][1] == "O" && game[0][2] == "O") || 	// hor
			(game[1][0] == "O" && game[1][1] == "O" && game[1][2] == "O") ||
			(game[2][0] == "O" && game[2][1] == "O" && game[2][2] == "O") ||
			(game[0][0] == "O" && game[1][0] == "O" && game[2][0] == "O") ||	// ver
			(game[0][1] == "O" && game[1][1] == "O" && game[2][1] == "O") ||
			(game[0][2] == "O" && game[1][2] == "O" && game[2][2] == "O") ||
			(game[0][0] == "O" && game[1][1] == "O" && game[2][2] == "O") ||	// diagonal
			(game[0][2] == "O" && game[1][1] == "O" && game[2][0] == "O")){

				printf("Winner is Server!\n");
				break;
		}
		else if(counter == 9){
			printf("It's a Draw!\n");
			break;
		}

		// Clear Buffer
		bzero(buff, MAX); 
		n = 0;
        while(1){
			// Server picks random coordinates and writes them in Game array
            coords[0] = rand() % 3;
            coords[1] = rand() % 3;
            if(game[coords[0]][coords[1]] == " "){
                buff[0] = coords[0] + 48;
                buff[1] = " ";
                buff[2] = coords[1] + 48;
                write(sockfd, buff, sizeof(buff));
                game[coords[0]][coords[1]] = "O";
				counter++;

                printf("Placed O on (%d, %d)\n", coords[0], coords[1]);
          
                printf("\t\t--- --- ---\n");
                printf("\t\t %s | %s | %s \n", game[0][0], game[0][1], game[0][2]);
                printf("\t\t--- --- ---\n");
                printf("\t\t %s | %s | %s \n", game[1][0], game[1][1], game[1][2]);
                printf("\t\t--- --- ---\n");
                printf("\t\t %s | %s | %s \n\n", game[2][0], game[2][1], game[2][2]);
				break;
            }
        }
        
	} 
}

// Driver function 
int main() 
{
    // Nothing else works!
    game[0][0] = " ";
    game[0][1] = " ";
    game[0][2] = " ";
    game[1][0] = " ";
    game[1][1] = " ";
    game[1][2] = " ";
    game[2][0] = " ";
    game[2][1] = " ";
    game[2][2] = " ";

	counter = 0;
    srand(time(NULL));

	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
} 
