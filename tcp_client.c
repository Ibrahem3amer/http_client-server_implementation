#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<unistd.h>
#include<netinet/in.h>

int main(){
	// Create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// Calling connect function
	// connect() --> returns an int value. 0 is ok, -1 is error on connection
	// connect(socket_isntance, server_address that will be called to connect, size of server address)
	int conn_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	
	// Assuring that everthing is Ok
	if(conn_status == -1){
		printf("there was an error \n\n");
	}

	// Calling the recv function that recieves data from server
	char server_response[256]; // The variable that will hold the data coming from the server
	recv(network_socket, &server_response, sizeof(server_response), 0);

	// Print the data we get back.
	printf("The server sent the data: %s\n", server_response);

	// Closing the socket.
	close(network_socket);
	return 0;
}
