package com.kingstar.console;

import java.io.*;
import java.util.*;

//读取INT,BOOLEAN,LONG 类型时用相应的方法

public class properFile extends Properties {

	private static final long serialVersionUID = 1L;

	private Hashtable randomAccessFiles = new Hashtable(); //#1
	
	private String fileName = null;

	//use property class construct
	public properFile(Properties props) {
		Enumeration fullList = props.propertyNames();

		String propertyName;

		while (fullList.hasMoreElements()) {
			propertyName = (String) fullList.nextElement();
			this.setProperty(propertyName, props.getProperty(propertyName));
		}
	}

	public properFile() {
		super();
	}

	//file name to construct
	public properFile(String fileName) {
		this();
		this.fileName = fileName;
	}

	public void load(String fileName) throws IOException {
		load(new FileInputStream(fileName));
		this.fileName = fileName;
	}

	public void load() throws IOException {
		load(this.fileName);
	}

	public void saveAs(String fileName) //#1
			throws IOException {
		StringWriter sw = new StringWriter();
		PrintWriter out = new PrintWriter(sw);
		out.print("#");
		list(out);
		String content = sw.toString();
		out.close();//#2
		RandomAccessFile raf = null;

		synchronized (randomAccessFiles) {
			raf = (RandomAccessFile) randomAccessFiles.get(fileName);
			if (raf == null) {
				raf = new RandomAccessFile(fileName, "rw");
				randomAccessFiles.put(fileName, raf);
			}
		}
		synchronized (raf) {
			raf.setLength(0);//#3
			raf.writeBytes(content);
		}
	}

	public void save(String fileName) throws IOException {
		saveAs(fileName);
		this.fileName = fileName;
	}

	public void save() throws IOException {
		save(fileName);
	}

	public void setPropertyBool(String propName, boolean value) {
		if (value)
			put(propName, "YES");
		else
			put(propName, "NO");
	}

	public boolean getPropertyBool(String propName, boolean def) {
		String temp = getProperty(propName);

		if (temp != null) {
			temp = temp.toLowerCase().trim();

			if (temp.equals("y") || temp.equals("yes") || temp.equals("true"))
				return true;

			if (temp.equals("n") || temp.equals("no") || temp.equals("false"))
				return false;
		}

		return def;
	}

	public boolean getPropertyBool(String propName) {
		return getPropertyBool(propName, false);
	}

	public void setPropertyL(String key, long value) {
		put(key, String.valueOf(value));
	}

	public long getPropertyL(String key, long defaultValue) {
		String value = getProperty(key);
		try {
			return (value == null) ? defaultValue : Long
					.parseLong(value.trim());
		} catch (NumberFormatException e) {
			throw new NumberFormatException("The value of " + key
					+ " is not numeric. " + e);
		}
	}

	public int getPropertyI(String key) {
		try {
			return Integer.valueOf(getProperty(key).trim()).intValue();
		} catch (NullPointerException npe) {
			throw new NullPointerException(key + " does not exist in setup. "
					+ npe);
		} catch (NumberFormatException nfe) {
			throw new NumberFormatException("The value of " + key
					+ " is not numeric in setup. " + nfe);
		}
	}

	public int getPropertyI(String key, int defaultValue) {
		String value = getProperty(key);
		try {
			return (value == null) ? defaultValue : Integer.parseInt(value
					.trim());
		} catch (NullPointerException npe) {
			throw new NullPointerException(key + " does not exist in setup. "
					+ npe);
		} catch (NumberFormatException nfe) {
			throw new NumberFormatException("The value of " + key
					+ " is not numeric in setup. " + nfe);
		}
	}

	public Object put(String key, int value) {
		return put(key, String.valueOf(value));
	}

	public static void main(String args[]) throws Exception {

		properFile p = new properFile("console.ini");
		p.load();
		System.out.println(p.getProperty("LOGFILENAME"));

	}

}