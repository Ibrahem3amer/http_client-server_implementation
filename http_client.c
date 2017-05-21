#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<unistd.h>

// Function to convert network addresses. 
#include<arpa/inet.h>

int main(int argc, char *argv[]){
	
	// Graping server address from the command line arguments. 
	char *address;
	address = argv[1];

	// Creating a clien socket.
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Connect to address. 
	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(80);
	// New function from arpa.inet.h, takes a string address and convert it to format for sockaddr
	// Second argument is the place we will save our converted address in. 
	inet_aton(address, remote_address.sin_addr.s_addr);

	connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));

	// Holding the request. Recieving the response.
	char request[] = "GET / HTTP/1.1\r\n\r\n";
	char response[4096];

	// Sending the request. 
	send(client_socket, request, sizeof(request), 0);
	
	// Recieving the response.
	recv(client_socket, &response, sizeof(response), 0);

	printf("Response: %s\n", response);
	close(client_socket); 
	
	return 0;
}
