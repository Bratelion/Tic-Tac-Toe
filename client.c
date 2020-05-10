
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#define MAX 80
#define IP  "161.53.171.106" 
#define PORT 50555 
#define SA struct sockaddr

char* game[3][3];
int counter;
int coords[2];
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff));
        
        while(1){
            printf("Enter the coordinate value to place X or \"exit\" the game: "); 
            n = 0; 
            while ((buff[n++] = getchar()) != '\n') 
                ; 
            // String to Int Coordinates
            coords[0] = atoi(&buff[0]);
            coords[1] = atoi(&buff[2]);
            
            // If Client typed "exit", leave while loop
            if((strncmp(buff, "exit", 4)) == 0){
                break;
            }
            else if(game[coords[0]][coords[1]] == " " &&                                 // If there is space available
                coords[0] < 3 && coords[0] > -1 && coords[1] < 3 && coords[1] > -1){ // If it's not out of range
                
                // Send to Server and write into Game array
                write(sockfd, buff, sizeof(buff));
                game[coords[0]][coords[1]] = "X";
                counter++;
                break;
            }
            else 
                printf("You can't place there!\n");
            }
        // If Client typed "exit", leave game    
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        }

        // Print Game array
        printf("Placed X on (%d, %d)\n", coords[0], coords[1]);
        printf("\n\n");
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
        
        // Clear Buffer and get Server response
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff));

        // String to Int Coordinates
        coords[0] = atoi(&buff[0]);
        coords[1] = atoi(&buff[2]);
        game[coords[0]][coords[1]] = "O";
        counter++;

        // Print Game array
        printf("Server placed O on (%d, %d)\n", coords[0], coords[1]);
        printf("\n\n");
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
 
    } 
} 
  
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

    // Count to full array
    counter = 0;

    int sockfd, connfd; 
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
    servaddr.sin_addr.s_addr = inet_addr(IP); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 
