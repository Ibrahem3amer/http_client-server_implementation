#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<unistd.h>

int main(){
	
	char server_message[256] = "You have reached the server";
	
	// Creating socket.
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Define address structure.
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	// INADDR_ANY will grap any IP on our machine.
	server_address.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to our IP and port.
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// Calling listen function.
	listen(server_socket, 5);

	// Define the cardenalties of client socket that sent us a connection.
	// Accept function retuns the address of client socket.
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// Sending the message to client socket after connecting.
	send(client_socket, server_message, sizeof(server_message), 0);

	// closing the socket. 
	close(server_socket);
	
	return 0;
}
