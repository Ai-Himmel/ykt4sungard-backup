package com.kingstar.version;

import java.io.*;
import java.util.*;

public final class StringManip {

	public static String replaceString(String oldString, String newString,
			String inputString) {
		String outputString = "";
		int i;
		for (i = 0; i < inputString.length(); i++) {
			if (!(inputString.regionMatches(true, i, oldString, 0, oldString
					.length())))
				outputString += inputString.charAt(i);
			else {
				outputString += newString;
				i += oldString.length() - 1;
			}
		}
		return outputString;
	}

	/**
	 * The following method is used to pattern validate the content of the str .
	 * 
	 * @param pattern This parameter specifies the pattern the subject should adhere to. Use the '*' as a wild-card.
	 * @return true if the subject pattern matches and false if not.
	 */

	public static String getBetween(String str, char startDelim, char endDelim) {
		int startPos;
		int endPos;

		startPos = str.indexOf(startDelim, 0);

		if (startPos == -1)
			return new String("");

		endPos = str.indexOf(endDelim, startPos + 1);

		if (endPos == -1)
			return new String("");

		return str.substring(startPos + 1, endPos);

	}

	public static boolean checkPattern(String str, String pattern) {
		String matchStr = "";
		StringTokenizer token = new StringTokenizer(pattern, "*");
		int len;

		len = pattern.length();
		//相等�?=0        
		if (pattern.compareTo("*") == 0)
			return true;
		else if (pattern.charAt(0) == '*' && pattern.charAt(len - 1) == '*') {
			matchStr = token.nextToken();

			if (str.indexOf(matchStr) != -1)
				return true;
		} else if (pattern.charAt(0) == '*') {
			matchStr = token.nextToken();
			return str.endsWith(matchStr);
		} else if (pattern.charAt(len - 1) == '*') {
			matchStr = token.nextToken();
			return str.startsWith(matchStr);
		} else if (str.compareTo(pattern) == 0)
			return true;

		return false;
	}

	public static String getLines(String str, int from, int lines) {
		BufferedReader br = new BufferedReader(new StringReader(str));
		String line = "";
		int lineCount = 1;
		String result = "";

		try {
			while (((line = br.readLine()) != null) && lineCount++ != from)
				;

			lineCount = 1;

			if (lines == 0)
				result = "";
			else {
				result = line + "\r\n";
				while (((line = br.readLine()) != null) && lineCount++ != lines)
					result = result + line + "\r\n";
			}
			br.close();
		} catch (IOException e) {
			System.out.println(e + "Could not read string");
		}

		return result;

	}

	public static String parseString(String str, String seperator, int from,
			int lines) {
		String result = "";
		StringTokenizer token = new StringTokenizer(str, seperator);
		int tokenCount = 0;

		while (token.hasMoreElements() && tokenCount++ != from)
			result = (String) token.nextElement() + seperator;

		tokenCount = 1;

		if (lines == 0)
			result = "";
		else {
			while (token.hasMoreElements() && tokenCount++ != lines)
				result = result + (String) token.nextElement() + seperator;
		}

		return result;
	}

	//string translate to  byte type's String
	public static String getFixString(String str, int size) {
		byte res[] = new byte[size];
		for (int i = 0; i < size; i++) {
			if (i < str.length())
				res[i] = (byte) str.charAt(i);
			else
				res[i] = (byte) ' ';
		}
		return new String(res);
	}

	public static String getPropertyList(Properties props) {
		Enumeration proNames = props.propertyNames();
		String pName = "";
		String pValue = "";
		String result = "";

		while (proNames.hasMoreElements()) {
			pName = (String) proNames.nextElement();
			pValue = props.getProperty(pName);

			result = result + getFixString(pName, 30) + " = [" + pValue + "]\n";
		}

		return result;
	}

	public static void main(String[] args) {

		System.out.println(getBetween("aaaaaaa[bbb]aaaaaaaaaaa", '[', ']'));

	}
}
