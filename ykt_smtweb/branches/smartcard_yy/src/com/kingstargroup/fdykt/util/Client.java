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
			DataOutputStream output;
			String connectto = "10.49.188.50";
			Socket connection;
			// connect to server
			if (connectto.equals("localhost")) {
				connection = new Socket(InetAddress.getLocalHost(), 3000);

			} else {
				connection = new Socket(InetAddress.getByName(connectto), 3000);
			}
			output = new DataOutputStream(connection.getOutputStream());
			output.writeBytes("0014100010000000000000000123                 16000001              000010008201414262007082000000000000000000100000000000000000000000000000000");
			
			BufferedReader input=new BufferedReader(new InputStreamReader(connection.getInputStream()));


			connection.setSoTimeout(6000);
			char[] cbuf = new char[142];
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
