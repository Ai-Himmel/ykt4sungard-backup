package com.kingstar;

//iplabel.java
import java.net.*;
import java.awt.*;
import javax.swing.*;

public class iplabel {
	JFrame frame;
	JLabel label1, label2;
	JPanel panel;
	String ip, address;

	public void getip() {
		try {
			InetAddress addr = InetAddress.getLocalHost();
			ip = addr.getHostAddress();// 获得本机IP
			address = addr.getHostName();// 获得本机名称

			// System.out.println("addr=:"+String.valueOf(addr));
		} catch (Exception e) {
			System.out.println("Bad IP Address!" + e);
		}
	}

	public void showframe() {
		frame = new JFrame("my ip");
		label1 = new JLabel("this my ip");
		label1.setText(ip);
		label2 = new JLabel("this my address");
		label2.setText(address);
		panel = new JPanel();
		panel.add(label1);
		panel.add(label2);
		frame.getContentPane().add(panel);

		frame.setSize(400, 300);
		frame.setVisible(true);
	}

	public static void main(String agrs[]) {
		iplabel myip = new iplabel();
		myip.getip();
		myip.showframe();

	}
}
