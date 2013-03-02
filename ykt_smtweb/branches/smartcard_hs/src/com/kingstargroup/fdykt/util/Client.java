package com.kingstargroup.fdykt.util;

import java.io.*;
import java.net.*;

public class Client {
	public static void main(String args[]) {
		try {
//			if (args.length != 1) {
//				System.out.println("USAGE:   java   Client   servername");
//				return;
//			}
			String connectto = "localhost";
			Socket connection;
			// connect to server
			if (connectto.equals("localhost")) {
				connection = new Socket(InetAddress.getLocalHost(), 5000);

			} else {
				connection = new Socket(InetAddress.getByName(connectto), 5000);
			}
			BufferedReader input=new BufferedReader(new InputStreamReader(connection.getInputStream()));


			// read information from server
			String info;
			connection.setSoTimeout(6000);
			char[] cbuf = new char[100];
			int info1 = input.read(cbuf);
			System.out.println(String.valueOf(cbuf));
			connection.close();
		} catch (SecurityException e) {
			System.out
					.println("SecurityException   when   connecting   Server!");
		} catch (IOException e) {
			System.out.println("IOException   when   connecting   Server!");
		}
	}

}
