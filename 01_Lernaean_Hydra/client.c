/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:33:11 by akovalyo          #+#    #+#             */
/*   Updated: 2020/03/12 21:18:38 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connection.h"

int	manual_commun(int sockfd)
{
	char buffer[BUFF_SIZE];
	int n;
	while (1)
	{
		bzero(buffer, BUFF_SIZE);
		printf("Client: ");
		fgets(buffer, BUFF_SIZE - 1, stdin);
		if (strcmp(buffer, "exit\n") == 0)
		{
			printf("\nClosing connection...\n");
			return (1);
		}
		n = write(sockfd, buffer, strlen(buffer));
		if (n < 0)
		{
			fprintf(stderr, "ERROR writing to socket\n");
			exit(1);
		}
		bzero(buffer, BUFF_SIZE);
		n = read(sockfd, buffer, BUFF_SIZE - 1);
		if (n < 0)
		{
			fprintf(stderr, "ERROR reading from socket\n");
			exit(1);
		}
		printf("Server: %s\n", buffer);
	}
	return (0);
}

int 	auto_commun(int sockfd)
{
	int i = 0;
	int n;
	char buffer[BUFF_SIZE];
	
	while (i < 10)
	{
		printf("Client: ping\n");
		n = write(sockfd, "ping", 4);
		if (n < 0)
		{
			fprintf(stderr, "ERROR writing to socket\n");
			exit(1);
		}
		bzero(buffer, BUFF_SIZE);
		n = read(sockfd, buffer, BUFF_SIZE - 1);
		if (n < 0)
		{
			fprintf(stderr, "ERROR reading from socket\n");
			exit(1);
		}
		printf("Server: %s\n", buffer);
		i++;
		sleep(2);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int		sockfd;
	int		portno;
	struct	sockaddr_in serv_addr;
	struct	hostent *server;
	
	portno = PORT;
	if (argc < 2)
	{
		printf("\nusage: %s [hostname] [port] [option]\n\n[hostname] - the name of the host on which the server is running, on single mashine use 'localhost'\n[port] - port number on which the server is listening for connections (by default port is 8080)\n[option]: -d    ping server (by default manual communication)\n", argv[0]);
		exit(0);
	}
	if (argc >= 3 && strcmp(argv[2], "-p") != 0)
		portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		fprintf(stderr, "ERROR opening socket\n");
	    	exit(1);
	}
		server = gethostbyname(argv[1]);
    	if (server == NULL)
    	{
		fprintf(stderr, "ERROR, no such host\n");
		exit (1);
	}
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		fprintf(stderr, "ERROR connecting\n");
		exit(1);
	}
	printf("Connection established with <%i> on port <%i>\n", serv_addr.sin_addr.s_addr, portno);
	
	if ((argc == 4 && strcmp(argv[3], "-p") == 0) || argc == 3 && strcmp(argv[2], "-p") == 0)
		auto_commun(sockfd);
	else
		manual_commun(sockfd);
	printf("Connection closed\n");
	close(sockfd);
	return (0);
}
