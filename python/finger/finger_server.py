#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket, sys

PORT=79
TIMEOUT=15
MAX_CONNECTS=10

def get_plan(username, verbose):
	return f"username={username} verbose={verbose}"

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
