#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket, sys
from pathlib import Path

# port to listen on (standard finger port is 79)
PORT = 79

# timeout (in seconds) before an open connection is closed
TIMEOUT = 15

# max number of simultaneous connections allowed
MAX_CONNECTS = 10

# local fingerspace directory to query
FINGERSPACE = "/fingerspace"

def get_plan(username, verbose):

	filename = f"{FINGERSPACE}/{username}"

	if Path(filename).is_file():
		planfile = open(filename, "r")
		plan = planfile.read()
		planfile.close()
		print(f"Returned the contents of: {filename}")
		return plan;
	else:
		return "Bogus user specified."

if __name__ == "__main__":

	try:
		addr = ("", PORT)
		if socket.has_dualstack_ipv6():
			s = socket.create_server(addr, family=socket.AF_INET6, dualstack_ipv6=True)
		else:
			s = socket.create_server(addr, backlog=MAX_CONNECTS)
	except OSError as msg:
		print(msg, file=sys.stderr)
		sys.exit(1)

	print(f"Now listening on port: {PORT}\nConnection timeout: {TIMEOUT} seconds\nMax simultaneous connections: {MAX_CONNECTS}")

	while True:
		try:
			conn, addr = s.accept()
			with conn:
				conn.settimeout(TIMEOUT)
				print(f"Connected by: {addr[0]}:{addr[1]}")
				while True:
					command = conn.recv(128)
					if not command: break
					print(f"Finger command: {repr(command)}")
					cmd = command.decode("ascii").strip()
					if cmd[:3].casefold() == "/W ".casefold():
						username = cmd[3:]
						verbose = True
					else:
						username = cmd
						verbose = False
					plan = get_plan(username, verbose)
					conn.sendall(f"{plan}\n\n".encode("ascii"))
					conn.shutdown(socket.SHUT_RDWR)
					conn.close()
					break
		except KeyboardInterrupt:
			print("Shutting down")
			break

	s.shutdown(socket.SHUT_RDWR)
	s.close()
