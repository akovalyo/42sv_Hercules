# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/20 11:20:56 by akovalyo          #+#    #+#              #
#    Updated: 2020/03/20 11:20:56 by akovalyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys, requests, os, json

if len(sys.argv) != 2:
	print("usage: python script.py file")
	sys.exit(1)

userfile = sys.argv[1]

def get_api(env):
	print("Register", env + ":")
	os.environ[env] = input("")

# check UID and SECRET tokens if not prompt user for correct credentials
if not os.environ.get('MY_UID'):
	get_api('MY_UID')
if not os.environ.get('MY_SECRET'):
	get_api('MY_SECRET')

UID = os.environ['MY_UID']
SECRET = os.environ['MY_SECRET']
ACCESS_URL = 'https://api.intra.42.fr/oauth/token'

response = requests.post(ACCESS_URL, data = { 'grant_type': 'client_credentials',
						'client_id': UID,
						'client_secret': SECRET})
access_token = json.loads(response.text)['access_token']

# open file with usernames and check if user is available and show location
with open(userfile, 'r') as uf:
	users = uf.readlines()
	for user in users:
		user = user.rstrip('\n')
		api = "users/{}/locations".format(user)
		url = "https://api.intra.42.fr/v2/{}?access_token={}".format(api, access_token)
		response = requests.get(url)
		num = response.status_code	
		while num == 500:
			response = requests.get(url)
			num = response.status_code	
			print("API not responding...")
		if num != 200 and num != 404:
			print("Connection faild")
			sys.exit(1)
			
		if num == 404:
			print("Invalid intra name:", user)
		else:
			user_data = json.loads(response.text)
			
			if user_data[0]['end_at'] != None:
				print(user, "is not available now.")
			else:
				if user_data[0]['host'] == None:
					print(user, "is not available now.")
				else:
					print(user, "is available at", user_data[0]['host'])
