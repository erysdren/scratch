#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket, sys

def get_plan(username, verbose):
	return f"username={username} verbose={verbose}"

if __name__ == "__main__":

	try:
		addr = ("", 79)
		if socket.has_dualstack_ipv6():
			s = socket.create_server(addr, family=socket.AF_INET6, dualstack_ipv6=True)
		else:
			s = socket.create_server(addr)
	except OSError as msg:
		print(msg, file=sys.stderr)
		sys.exit(1)

	print(f"Listening on {repr(addr)}")

	while True:
		try:
			conn, addr = s.accept()
			with conn:
				print(f"Connected by {repr(addr)}")
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
