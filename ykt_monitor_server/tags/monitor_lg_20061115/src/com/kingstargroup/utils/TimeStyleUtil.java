package com.kingstargroup.utils;

import org.apache.log4j.Logger;

import java.io.*;
import java.util.*;
import javax.mail.MessagingException;
import javax.mail.internet.MimeUtility;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class TimeStyleUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(TimeStyleUtil.class);

	public static String ChangeOrderBy(String oldsql, String orderkey) {
		orderkey = " order by " + orderkey;
		oldsql = oldsql.toLowerCase();
		int x = oldsql.indexOf("order by ");
		if (x > 0)
			oldsql = oldsql.substring(0, x);
		return oldsql + orderkey;
	}

	public static String ChangeWhere(String oldsql, String newwhere) {
		int start = oldsql.indexOf("where");
		if (start > 0) {
			if (oldsql.indexOf("1=1") > 0)
				start = oldsql.indexOf("1=1");
			else
				newwhere = " where " + newwhere;
		} else {
			newwhere = " where " + newwhere;
		}
		String newsql = oldsql;
		if (start > 0) {
			newsql = oldsql.substring(0, start);
		} else if (oldsql.indexOf("order by") > 0) {
			newsql = oldsql.substring(0, oldsql.indexOf("order by"));
		}
		newsql += newwhere;
		return newsql;
	}

	/**
	 * @param p
	 *            0,1,...,7,8,9,10,11
	 * @return 当前时间的字符串，格式由参数p指定。
	 * @see pattern java.text.SimpleDateFormat
	 * 
	 * ECDT p pattern return string ------- -------
	 * -------------------------------------- 
	 * 0000 0 "yyyy年MM月dd日 HH时mm分ss秒"
	 * 0001 1 "HH:mm" "20:16" 
	 * 0010 2 "yyyy-MM-dd" "2002-11-28" 
	 * 0011 3 "yyyy-MM-dd HH:mm" "2002-11-28 20:16" 
	 * 0101 4 "HH时mm分" "20时49分" 
	 * 0110 5 "yyyy年MM月dd日" "2002年11月28日" 
	 * 0111 6 "yyyy年MM月dd日 HH时mm分" "2002年11月28日 20时49分" 
	 * 1000 7 "yyyy-MM-dd HH:mm:ss" "2002-11-28 20:16:01" 
	 * 1001 8 "yyyyMMddHHmmss" 
	 * 1010 9 "yyyyMMddHHmm" 
	 * 1011 10 "yyyyMMdd" 
	 * 1100 11 "yyyyMMddHH" 
	 * 1101 12 "yyyy-MM-dd HH" "2002-11-28 20" 
	 * 1110 13 "yyyy年MM月dd日HH时" "2002年11月28日 20时" 
	 * 1111 14 " HH-mm-ss" 说明： E 扩展，C 中文，D 日期，T 时间。
	 */
	public static String getNow(int p) {
		if (logger.isDebugEnabled()) {
			logger.debug("getNow(int) - start"); //$NON-NLS-1$
		}

		String returnString = getDateString(new java.util.Date(), p);
		if (logger.isDebugEnabled()) {
			logger.debug("getNow(int) - end"); //$NON-NLS-1$
		}
		return returnString;
	}

	public static String getNow(String pattern) {
		return (new java.text.SimpleDateFormat(pattern))
				.format(new java.util.Date());
	}

	public static String getDateString(Date thisdate, int p) {
		if (logger.isDebugEnabled()) {
			logger.debug("getDateString(Date, int) - start"); //$NON-NLS-1$
		}

		final String[] pattern = { "yyyy年MM月dd日 HH时mm分ss秒", "HH:mm",
				"yyyy-MM-dd", "yyyy-MM-dd HH:mm", "HH时mm分", "yyyy年MM月dd日",
				"yyyy年MM月dd日 HH时mm分", "yyyy-MM-dd HH:mm:ss", "yyyyMMddHHmmss",
				"yyyyMMddHHmm", "yyyyMMdd", "yyyyMMddHH", "yyyy-MM-dd HH",
				"yyyy年MM月dd日 HH时", " HH-mm-ss" };
		java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
				pattern[p]);
		String str = sdf.format(thisdate);

		if (logger.isDebugEnabled()) {
			logger.debug("getDateString(Date, int) - end"); //$NON-NLS-1$
		}
		return str;
	}

	public static Date getStringDate(String thisdate, int p)
			throws java.text.ParseException {
		final String[] pattern = { "yyyy年MM月dd日 HH时mm分ss秒", "HH:mm",
				"yyyy-MM-dd", "yyyy-MM-dd HH:mm", "HH时mm分", "yyyy年MM月dd日",
				"yyyy年MM月dd日 HH时mm分", "yyyy-MM-dd HH:mm:ss", "yyyyMMddHHmmss",
				"yyyyMMddHHmm", "yyyyMMdd", "yyyyMMddHH", "yyyy-MM-dd HH",
				"yyyy年MM月dd日 HH时", " HH-mm-ss" };
		java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(
				pattern[p]);
		return sdf.parse(thisdate);
	}

	public static String getWeek(Date thisdate, int p) {
		Calendar c = Calendar.getInstance();
		c.setTime(thisdate);
		String temp = "";
		int x = c.get(c.DAY_OF_WEEK);
		switch (x) {
		case 1:
			if (p == 0)
				temp = "星期日";
			else if (p == 1)
				temp = "Sunday";
			break;
		case 2:
			if (p == 0)
				temp = "星期一";
			else if (p == 1)
				temp = "Monday";
			break;
		case 3:
			if (p == 0)
				temp = "星期二";
			else if (p == 1)
				temp = "Tuesday";
			break;
		case 4:
			if (p == 0)
				temp = "星期三";
			else if (p == 1)
				temp = "Wednesday";
			break;
		case 5:
			if (p == 0)
				temp = "星期四";
			else if (p == 1)
				temp = "Thursday";
			break;
		case 6:
			if (p == 0)
				temp = "星期五";
			else if (p == 1)
				temp = "Friday";
			break;
		case 7:
			if (p == 0)
				temp = "星期六";
			else if (p == 1)
				temp = "Saturday";
			break;
		default:
			break;
		}
		return temp;
	}

	// 返回 s (描述数字)的汉字形式
	// 例如：String str = getNativeNumber("123456")
	// 得到的结果是 str = "一十二万三千四百五十六";
	// 得到的结果是 str = "壹拾贰万叁仟肆佰伍拾陆";
	public static String getNativeMoneyStr(String str) {
		String[] strD = { "零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖" };
		StringBuffer result = new StringBuffer("");

		// 处理异常情况
		if (str == null || str.trim().equals(""))
			return "零圆";

		// 获取整数和分数
		int intDot = str.indexOf('.');
		boolean blnFloat = intDot == -1;
		String str1 = blnFloat ? str : str.substring(0, str.indexOf('.'));
		String str2 = blnFloat ? "" : str.substring(str.indexOf('.') + 1);

		{ // 处理整数
			String[] strN = { "", "拾", "佰", "仟" };
			String[] strN4 = { "", "万" };
			String[] strN8 = { "", "亿" };

			String[] r = { "", "", "", "" };
			str1 = "0000000000000000".substring(str1.length()) + str1;

			for (int i = 0; i < 4; i++) {
				String string = str1.substring(i * 4, (i + 1) * 4);
				for (int j = 0; j < string.length(); j++) {
					int t = string.charAt(3 - j) - '0';
					if (t != 0)
						r[i] = strD[t] + strN[j] + r[i];
				}
			}
			if (!r[0].equals(""))
				result.append(r[0]).append("万");
			if (!r[0].equals("") || !r[1].equals(""))
				result.append(r[1]).append("亿");
			if (!r[2].equals(""))
				result.append(r[2]).append("万");
			if (!r[2].equals("") || !r[3].equals(""))
				result.append(r[3]).append("");
			if (!result.toString().equals(""))
				result.append("圆");

		}

		{ // 处理小数
			str2 = str2 + "00";
			String[] strN = { "角", "分", "厘" };
			for (int i = 0; i < 2; i++) {
				int t = str2.charAt(i) - '0';
				if (t != 0)
					result.append(strD[t] + strN[i]);
			}
		}

		//
		String strTemp = result.toString();
		if (strTemp.equals(""))
			strTemp = "零圆";
		return strTemp;
	}

	public static Vector SortUp2(Enumeration e) {
		Vector tempint = new Vector();
		while (e.hasMoreElements()) {
			tempint.addElement(e.nextElement().toString());
		}
		return SortUp1(tempint);
	}

	public static Vector SortDown2(Enumeration e) {
		Vector tempint = new Vector();
		while (e.hasMoreElements()) {
			tempint.addElement(e.nextElement().toString());
		}
		return SortDown1(tempint);
	}

	public static Vector SortUp1(Vector tempVect) {
		int y = tempVect.size();
		String[] sortStrs = new String[y];
		String[] tempsort = new String[y];
		if (y > 1) {
			for (int x = 0; x < y; x++) {
				sortStrs[x] = tempVect.elementAt(x).toString();
			}
			int pass, i;
			String temp;
			for (pass = 1; pass < y; pass++) {
				temp = sortStrs[pass];
				for (i = pass - 1; i >= 0; i--) {
					if (sortStrs[i].compareTo(temp) <= 0) {
						break;
					} else {
						sortStrs[i + 1] = sortStrs[i];
					}
				}
				sortStrs[i + 1] = temp;
				for (i = 0; i < sortStrs.length; i++) {
					tempsort[i] = sortStrs[i];
				}
			}
			tempVect = new Vector();
			for (int q = 0; q < y; q++) {
				tempVect.addElement(tempsort[q]);
			}
		}
		return tempVect;
	}

	public static Vector SortDown1(Vector tempVect) {
		int y = tempVect.size();
		String[] sortStrs = new String[y];
		String[] tempsort = new String[y];
		if (y > 1) {
			for (int x = 0; x < y; x++) {
				sortStrs[x] = tempVect.elementAt(x).toString();
			}
			int pass, i;
			String temp;
			for (pass = 1; pass < y; pass++) {
				temp = sortStrs[pass];
				for (i = pass - 1; i >= 0; i--) {
					if (sortStrs[i].compareTo(temp) >= 0) {
						break;
					} else {
						sortStrs[i + 1] = sortStrs[i];
					}
				}
				sortStrs[i + 1] = temp;
				for (i = 0; i < sortStrs.length; i++) {
					tempsort[i] = sortStrs[i];
				}
			}
			tempVect = new Vector();
			for (int q = 0; q < y; q++) {
				tempVect.addElement(tempsort[q]);
			}
		}
		return tempVect;
	}

	public static Vector SortUpNum(Vector tempVect) {
		int y = tempVect.size();
		int[] sortStrs = new int[y];
		int[] tempsort = new int[y];
		if (y > 1) {
			for (int x = 0; x < y; x++) {
				sortStrs[x] = Integer
						.parseInt(tempVect.elementAt(x).toString());
			}
			int pass, i;
			int temp;
			for (pass = 1; pass < y; pass++) {
				temp = sortStrs[pass];
				for (i = pass - 1; i >= 0; i--) {
					if (sortStrs[i] < temp) {
						break;
					} else {
						sortStrs[i + 1] = sortStrs[i];
					}
				}
				sortStrs[i + 1] = temp;
				for (i = 0; i < sortStrs.length; i++) {
					tempsort[i] = sortStrs[i];
				}
			}
			tempVect = new Vector();
			for (int q = 0; q < y; q++) {
				tempVect.addElement(String.valueOf(tempsort[q]));
			}
		}
		return tempVect;
	}

	public static void digestFile(String filename, String algorithm) {
		byte[] b = new byte[65536];
		int count = 0;
		int read = 0;
		FileInputStream fis = null;
		FileOutputStream fos = null;
		try {
			MessageDigest md = MessageDigest.getInstance(algorithm);
			fis = new FileInputStream(filename);
			while (fis.available() > 0) {
				read = fis.read(b);
				md.update(b, 0, read);
				count += read;
			}
			byte[] digest = md.digest();
			StringBuffer fileNameBuffer = new StringBuffer(128)
					.append(filename).append(".").append(algorithm);
			fos = new FileOutputStream(fileNameBuffer.toString());
			OutputStream encodedStream = MimeUtility.encode(fos, "base64");
			encodedStream.write(digest);
			fos.flush();
		} catch (Exception e) {
			System.out.println("Error computing Digest: " + e);
		} finally {
			try {
				fis.close();
				fos.close();
			} catch (Exception ignored) {
			}
		}
	}

	public static String digestString(String pass, String algorithm)
			throws NoSuchAlgorithmException {

		MessageDigest md;
		ByteArrayOutputStream bos;

		try {
			md = MessageDigest.getInstance(algorithm);
			byte[] digest = md.digest(pass.getBytes("iso-8859-1"));
			bos = new ByteArrayOutputStream();
			OutputStream encodedStream = MimeUtility.encode(bos, "base64");
			encodedStream.write(digest);
			return bos.toString("iso-8859-1");
		} catch (IOException ioe) {
			throw new RuntimeException("Fatal error: " + ioe);
		} catch (MessagingException me) {
			throw new RuntimeException("Fatal error: " + me);
		}
	}

	//处理中文问题
	public String getStr(String str) {
		try {
			String temp_p = str;
			byte[] temp_t = temp_p.getBytes("GBK");
			String temp = new String(temp_t, "ISO8859_1");
			return temp;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return "null";
	}

	//处理文字内容
	//该函数能够将字符串str中的'\n'、'\r'转换为<br>；
	//也能够将字符串str中的''转换为&nbsp;;
	public static String returnToBr(String str) {
		//如果str为null或者str为空值；
		//则该函数会返回不发生变化的str;
		if (str == null || str.equals("")) {
			return str;
		}
		//定义StringBuffer型的变量sTmp
		StringBuffer sTmp = new StringBuffer();
		int i = 0;
		while (i <= str.length() - 1) {
			//将字符串str中的'\n'、'\r'转换为<br>
			if (str.charAt(i) == '\n' || str.charAt(i) == '\r') {
				sTmp = sTmp.append("<br>");
			} else if (str.charAt(i) == ' ') {
				//将字符串str中的''转换为&nbsp;
				sTmp = sTmp.append("&nbsp;");
			} else {
				sTmp = sTmp.append(str.substring(i, i + 1));
			}
			i++;
		}
		String S;
		S = sTmp.toString();
		return S;
	}

	//该函数能够将字符串中str中的'<'转换为'&lt;'
	//也能够将字符串str中的'>'转换为'&gt;'
	public static String returnToHTML(String str) {
		//如果str为null或者str为空值；
		//则该函数会返回不发生变化的str;
		if (str == null || str.equals("")) {
			return str;
		}
		//定义StringBuffer型的变量sTmp
		StringBuffer sTmp = new StringBuffer();
		int i = 0;
		while (i <= str.length() - 1) {
			//该函数能够将字符str中的'<'转换为'&lt;'
			if (str.charAt(i) == '<') {
				sTmp = sTmp.append("&lt;");
			} else if (str.charAt(i) == '>') {
				sTmp = sTmp.append("&gt;");
			} else {
				sTmp = sTmp.append(str.substring(i, i + 1));
			}
			i++;
		}
		String S;
		S = sTmp.toString();
		return S;
	}

	public final static String[] scopeTimes = { "8：00", "8：30", "9：00", "9：30",
			"10：00", "10：30", "11：00", "11：30", "12：00", "12：30", "13：00",
			"13：30", "14：00", "14：30", "15：00", "15：30", "16：00", "16：30",
			"17：00", "17：30", "18：00" };
	
	public final static String[] scopeTimes2 = { "00:00","00:30","01:00","01:30",
			"02:00","02:30","03:00","03:30","04:00","04:30","05:00","05:30","06:00",
			"06:30","07:00","07:30","08:00","08:30","09:00","09:30","10:00","10:30",
			"11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00",
			"15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30",
			"20:00","20:30","21:00","21:30","22:00","22:30","23:00","23:30"};

	/*
	 * public static void main(String[] args) {
	 * 
	 * System.out.print(ChangeWhere("select * from xxx where u>y and xx>4 and
	 * bbb=ccc order by x","iii==y")); }
	 */
}