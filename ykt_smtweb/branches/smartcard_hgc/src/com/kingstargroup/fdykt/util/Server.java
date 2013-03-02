package com.kingstargroup.fdykt.util;

import java.net.*;
import java.io.*;

public class Server {
	ServerSocket server;

	DataOutputStream output;

	Socket socket;

	public Server() {
		try {
			// create a server on port 5000
			server = new ServerSocket(2000);
			// display interactive informaion
			System.out.println("Server   created.");
			System.out.println("waiting   for   client   to   connect   on...");
			// waiting for client to connect on...
			int i=0;
			while(true){
			socket = server.accept();
			
			// client connected
			System.out.println("server:client   connected."+i+++"\n");
			output = new DataOutputStream(socket.getOutputStream());
			output.writeBytes("100670100000000000000000012345678901234567890120002200072710260320070727123456111111111110012345678901234567890123456789012345678901234567890123456820,876,876,964,876,964,820,964,327,327,327,327,327,327,327,327,327,327,327,876,876,876,820,820,876,876                           ");
			}
//			output = new DataOutputStream(socket.getOutputStream());
//			output.writeUTF("Welcome   to   Server.Bye!");
//			output.close();
//			server.close();
		} catch (SocketException e) {
			System.out.println(e.toString());
			e.printStackTrace();
			System.exit(1);
		} catch (IOException e) {
			System.out.println(e.toString());
			e.printStackTrace();
			System.exit(1);
		}
	}

	public static void main(String args[]) {
		Server game = new Server();
	}
}
