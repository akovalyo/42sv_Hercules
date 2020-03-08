#!/bin/bash

if [[ $EUID -ne 0 ]]; then
	echo "This script must be run as root"
	exit 1
fi

apt-get install openssh-server

echo "1. Make backup"
cp /etc/ssh/sshd_config /etc/ssh/sshd_config.BACKUP

echo "2. Edit ssh config..."
sed -i 's/#Port 22/Port 4221/g' /etc/ssh/sshd_config

echo "New SSH Port number: 4221"

echo "3. Restart SSH"

/etc/init.d/ssh restart sshd restart
