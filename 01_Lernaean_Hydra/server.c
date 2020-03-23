/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:32:57 by akovalyo          #+#    #+#             */
/*   Updated: 2020/03/12 20:32:57 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "connection.h"
int		response(int socket)
{
	int		n;
	char	buffer[BUFF_SIZE];

	bzero(buffer, BUFF_SIZE);
	n = read(socket, buffer, BUFF_SIZE - 1);
	if (n < 0 || strcmp(buffer, "exit\n") == 0) 
	{	
		fprintf(stderr, "Connection closed\n");
		exit(1);
	}
	n = write(socket, "pong pong\n", 10);
	if (n < 0)
	{	
		fprintf(stderr, "ERROR writing to socket");
		exit(1);
	}
	return (0);
}


int		main(int argc, char **argv)
{
	int		sockfd;
	int 	newsockfd;
	int 	portno;
	int 	clilen;
	struct	sockaddr_in serv_addr;
	struct	sockaddr_in	cli_addr;
	
	portno = PORT;
	if (argv[1])
		portno = atoi(argv[1]);
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		fprintf(stderr, "ERROR opening socket");
		exit(-1);
	}
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		fprintf(stderr, "ERROR on binding");
		exit(1);
	}
	printf("Waiting for connection...\n");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
	if (newsockfd < 0)
	{
		fprintf(stderr, "ERROR on accept");
		exit(1);
	}
	printf("Connection established with <%i> on port <%i>\n", cli_addr.sin_addr.s_addr, portno);
	while (1)
	{
		if (response(newsockfd) == -1)
			{
				printf("Connection closed\n");
				close(newsockfd);
				exit(1);
			}
	}
	return (0);
}
