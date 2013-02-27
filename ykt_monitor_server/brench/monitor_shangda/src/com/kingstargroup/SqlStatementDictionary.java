package com.kingstargroup;
/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: SqlStatementDictionary.java<br>
 * Description: <br>
 * 系统中参数的形式分两种
 * 1：数值标示参数对 sql中的参数描写为{0}...
 * 2:值标识参数对 sql中的参数描述为:abc
 * 在调用时注意配置文件中的参数形式 
 * Modify History（或Change Log）:  <br>
 * 操作类型（创建、修改等）   操作日期       操作者    操作内容简述<br>
 * 创建  				 Feb 27, 2006  何林青    <br>
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.regex.PatternSyntaxException;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;


public class SqlStatementDictionary {

	private static HashMap sqlDictionary = new HashMap();

	// 缓存用户当前设置的sql
//	private static HashMap sqlCacheDictionary = new HashMap();
	private static String xmlfile="sql_db2.xml";

	static private SqlStatementDictionary instance = null;

	static private Object mutex = new Object();

	private SqlStatementDictionary() {
		load(xmlfile);
	}
	

	static public SqlStatementDictionary getIntance() {
		synchronized (mutex) {
			if (null == instance) {
				instance = new SqlStatementDictionary();
			}
		}
		return instance;
	}
	
	private boolean load(String file){
		// 读取sql配置文件,解析成可查找模式 hashmap中
		SAXBuilder sax = new SAXBuilder();
		try {
			InputStream in = this.getClass().getClassLoader().getResourceAsStream(xmlfile);
			Document doc = sax.build(in);
			Element element = doc.getRootElement();
		//	element.getChild("sql").getChild("sql-name").getText();
			List list = element.getChildren();
			for(int i=0; i<list.size();i++){
				Element sqlelement = (Element)list.get(i);
				sqlDictionary.put(sqlelement.getChild("sql-name").getText(),sqlelement.getChild("sql-statement").getText());
			}
		} catch (JDOMException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return true;
	}
	//
	/**
	 * 根据key返回需要的sql语句
	 * @param key 唯一的sql标识
	 * @return sql语句
	 */
	public static String getSQL(String key) {
		String temp = "";
		if (sqlDictionary.containsKey(key)) {
			temp = sqlDictionary.get(key).toString();
		}
		return temp;
	}

	/**
	 * 参数化原始sql 返回完整的sql
	 * @param key 唯一的sql标识 
	 * @param params 参数的map表 参数标识值对 如 abc、bcd、cde 代表abc参数、bcd参数、cde参数
	 * @return sql语句
	 */
	public static String getNamedParamSQL(String key, Map params) {
		String temp = "";
		try {
			if (sqlDictionary.containsKey(key)) {
				temp = sqlDictionary.get(key).toString();
				Iterator iter = params.keySet().iterator();
				String keyset = "";
				while (iter.hasNext()) {
					keyset = iter.next().toString();
					temp = getIntance().autoMakeUpSQLForNamed(temp, keyset,
							sqlDictionary.get(keyset).toString());
				}
			}
			return temp;
		} catch (Exception e) {
			e.printStackTrace();
			return temp;
		}

	}
	/**
	 * 参数化原始sql 返回完整的sql
	 * @param key 唯一的sql标识 
	 * @param params 参数的map表 数值标识值对 如 1、2、3 代表第一个参数、第二个参数、第三个参数
	 * @return sql语句
	 */
	public static String getSequenceParamSQL(String key, Map params) {
		String temp = "";
		try {
			if (sqlDictionary.containsKey(key)) {
				temp = sqlDictionary.get(key).toString();
				Iterator iter = params.keySet().iterator();
				String keyset = "";
				while (iter.hasNext()) {
					keyset = iter.next().toString();
					temp = getIntance().autoMakeUpSQLForSequence(temp, keyset,
							sqlDictionary.get(keyset).toString());
				}
			}
			return temp;
		} catch (Exception e) {
			e.printStackTrace();
			return temp;
		}

	}
	
	/**
	 * 用正确的值替代sql中的参数值
	 * @param sql
	 * @param key
	 * @param param
	 * @return
	 */
	private String autoMakeUpSQLForNamed(String sql, String key, String param) {
		try {
			sql.replaceFirst(":" + key, param);
			return sql;
		} catch (PatternSyntaxException e) {
			e.printStackTrace();
			return sql;
		}catch(NullPointerException e){
			e.printStackTrace();
			return sql;
		}

	}
	
	/**
	 * 用正确的值替代sql中的参数值
	 * @param sql
	 * @param key
	 * @param param
	 * @return
	 */
	private String autoMakeUpSQLForSequence(String sql, String key, String param) {
		try {
			sql.replaceFirst("{" + key +"}", param);
			return sql;
		} catch (PatternSyntaxException e) {
			e.printStackTrace();
			return sql;
		}catch(NullPointerException e){
			e.printStackTrace();
			return sql;
		}

	}
	
	

}