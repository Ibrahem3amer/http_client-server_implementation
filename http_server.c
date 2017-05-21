#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<unistd.h>

int main() {

	// Open a file to serve to request.
	FILE *html_data;
	html_data = fopen("index.html", "r");

	// Creating a response body that will get the contet of opend file.
	char response_data[1024];
	fgets(response_data, 1024, html_data);

	// Creating a HTTP header with 2048 size because we will catinuate the response body with it.
	char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
	strcat(http_header, response_data);

	// Creating a server socket to accept the request.
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Define the address for this socket. 
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// Binding the socket. 
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// Listening for a request. 
	listen(server_socket, 5);

	// Accept a connection.
	// An infinte loop because we want our server to always listen. 
	int client_socket;
	while(1){
		client_socket = accept(server_socket, NULL, NULL);
		send(client_socket, http_header, sizeof(http_header), 0);
		close(client_socket);
	}


	return 0;
}
