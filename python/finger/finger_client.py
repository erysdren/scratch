#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket, sys

def print_help():
	print("python3 finger_client.py username@hostname")
	sys.exit(0)

if __name__ == "__main__":

	if len(sys.argv) != 2:
		print_help()

	args = sys.argv[1].split("@")
	if not args or len(args) != 2:
		print_help()

	username = args[0]
	hostname = args[1]

	try:
		s = socket.create_connection((hostname, 79), 5)
	except OSError as msg:
		print(msg, file=sys.stderr)
		sys.exit(1)

	s.sendall(f"{username}\r\n".encode("ascii"))
	plan = s.recv(8192)
	print(f"[{hostname}]")
	print(plan.decode("ascii"), end="")

	s.shutdown(socket.SHUT_RDWR)
	s.close()
