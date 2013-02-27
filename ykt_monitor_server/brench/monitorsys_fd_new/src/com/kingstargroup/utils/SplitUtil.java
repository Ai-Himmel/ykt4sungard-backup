package com.kingstargroup.utils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

public class SplitUtil {
	
	public static String[] split(String s, String delimiter) {
		if (s == null || delimiter == null) {
			return new String[0];
		}

		s = s.trim();

		if (!s.endsWith(delimiter)) {
			s += delimiter;
		}

		if (s.equals(delimiter)) {
			return new String[0];
		}

		List nodeValues = new ArrayList();

		if (delimiter.equals("\n") || delimiter.equals("\r")) {
			try {
				BufferedReader br = new BufferedReader(new StringReader(s));

				String line = null;

				while ((line = br.readLine()) != null) {
					nodeValues.add(line);
				}

				br.close();
			}
			catch (IOException ioe) {
				ioe.printStackTrace();
			}
		}
		else {
			int offset = 0;
			int pos = s.indexOf(delimiter, offset);

			while (pos != -1) {
				nodeValues.add(s.substring(offset, pos));

				offset = pos + delimiter.length();
				pos = s.indexOf(delimiter, offset);
			}
		}

		return (String[])nodeValues.toArray(new String[0]);
	}
	
	public static String firstSplit(String s, String delimiter) {	
		String Str = null;
		String[] a = SplitUtil.split(s,delimiter);
		Str = a[0];
		return Str;
	}
	
	public static String secondSplit(String s, String delimiter, String delimiter2) {	
		String Str = null;
		String[] a = SplitUtil.split(s,delimiter);
		String[] b = SplitUtil.split(a[1],delimiter2);
		Str = b[0];
		return Str;
	}

}
