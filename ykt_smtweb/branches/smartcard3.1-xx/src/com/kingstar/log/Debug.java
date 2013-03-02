package com.kingstar.log;

import java.io.*;
import java.util.*;

public class Debug {
	public static boolean debug = true;
	private static FileWriter f = null;
	

	public static void init(Properties parameters) {
		debug = (parameters.getProperty("DEBUG", "N").equalsIgnoreCase("Y"));
	}


	public static void debug(String title, String content) {
		if (!debug)
			return;
    {
        	System.out.println("title: "+title+"|"+"content :"+content+"|");
        	
        }
		try {
			if (f == null)
				f = new FileWriter("debug.txt");

			f.write(title);
			f.write("\r\n");
			f.write(content);
			f.write("\r\n");
			f.write("\r\n");
			f.flush();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void debug(String content) {
		if (!debug)
			return;
		{
	       System.out.println("content :"+content+"|");
	        	
	        }
		try {
			if (f == null)
				f = new FileWriter("debug.txt");

			f.write(content);
			f.write("\r\n");
			f.write("\r\n");
			f.flush();


		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void debugObject(String title, Object content) {
		if (debug)
			debug(title, content.toString());
	}

	
	public static void debugObjectBin(String title, Object content) {
		if (debug)
			debugBinary(title, content.toString());
	}

	public static void debugBinary(String title, String content) {
		if (!debug)
			return;

		try {
			if (f == null)
				f = new FileWriter("debug.txt");

			f.write(title);
			f.write("\r\n");

			int last = content.length() - 1;
			String x = null;
			for (int i = 0; i <= last; i++) {
				x = Integer.toHexString(content.charAt(i));
				if (x.length() < 2)
					f.write("0");
				f.write(x);
				f.write(" ");
				if ((i % 20) == 19)
					writeString(" ", content, i - 19, i, "\r\n");
			}
			if ((last % 20) < 19) {
				for (int i = 0; i < (19 - (last % 20)); i++)
					f.write("   ");
				writeString(" ", content, last - (last % 20), last, "\r\n");
			}
			f.write("\r\n");
			f.flush();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private static void writeString(String before, String content,
			int beginIndex, int endIndex, String after) throws Exception {
		f.write(before);
		for (int j = beginIndex; j <= endIndex; j++) {
			char c = content.charAt(j);
			f.write(((c > '\u0001') && (c < ' ')) ? '.' : c);
		}
		f.write(after);
	}

	public static void main(String[] argv) throws Exception {

		debug = true;
		debug("title", "12345678901234567890123456789");
		debug("tidtle", "12345678901234567890123456789");
		debug("title", "12345678901234567890123456789");
		debug("tidtle", "12345678901234567890123456789");
	}

	public static boolean isDebug() {
		return debug;
	}

	public static void setDebug(boolean debug) {
		Debug.debug = debug;
	}
}