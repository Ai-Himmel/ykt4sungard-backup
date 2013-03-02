package com.kingstargroup.fdykt.util;

import java.net.*;
import java.io.*;

public class Server {
	ServerSocket server;

	DataOutputStream output;
	
	DataInputStream input;

	Socket socket;

	public Server() {
		try {
			// create a server on port 5000
			server = new ServerSocket(2000);
			// display interactive informaion
			System.out.println("Server   created.");
			System.out.println("waiting   for   client   to   connect   on...");
			// waiting for client to connect on...
			byte[] rcvmsg = new byte[330];
			int i=0;
			while(true){
			socket = server.accept();
			
			// client connected
			System.out.println("server:client   connected."+i+++"\n");
			input = new DataInputStream(socket.getInputStream());
			input.read(rcvmsg);
//			input.read(rcvmsg, 0, 327);
			int j = 0;
			for (j = 0; j < rcvmsg.length; j++) {
				if (0 == rcvmsg[j]) {
					break;
				}
			}
			String msg = new String(rcvmsg, 0, j);
			//System.out.println(msg);
			output = new DataOutputStream(socket.getOutputStream());
			output.writeBytes("1006701000000000000000000123456789012345678901200050000802173557200708021234561111111111102123456789012345678901234567890123456820,876,876,964,876,1630,876,820,327,820,1338,929,321,2572,327,327,327,327,327,327,327,327,327,327,327,876,876,876,321,876,876,876                                                                      ");
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
