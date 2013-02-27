package com.kingstargroup;
/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: SqlStatementDictionary.java<br>
 * Description: <br>
 * ϵͳ�в�������ʽ������
 * 1����ֵ��ʾ������ sql�еĲ�����дΪ{0}...
 * 2:ֵ��ʶ������ sql�еĲ�������Ϊ:abc
 * �ڵ���ʱע�������ļ��еĲ�����ʽ 
 * Modify History����Change Log��:  <br>
 * �������ͣ��������޸ĵȣ�   ��������       ������    �������ݼ���<br>
 * ����  				 Feb 27, 2006  ������    <br>
 * <p>
 *
 * @author      ������
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

	// �����û���ǰ���õ�sql
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
		// ��ȡsql�����ļ�,�����ɿɲ���ģʽ hashmap��
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
	 * ����key������Ҫ��sql���
	 * @param key Ψһ��sql��ʶ
	 * @return sql���
	 */
	public static String getSQL(String key) {
		String temp = "";
		if (sqlDictionary.containsKey(key)) {
			temp = sqlDictionary.get(key).toString();
		}
		return temp;
	}

	/**
	 * ������ԭʼsql ����������sql
	 * @param key Ψһ��sql��ʶ 
	 * @param params ������map�� ������ʶֵ�� �� abc��bcd��cde ����abc������bcd������cde����
	 * @return sql���
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
	 * ������ԭʼsql ����������sql
	 * @param key Ψһ��sql��ʶ 
	 * @param params ������map�� ��ֵ��ʶֵ�� �� 1��2��3 �����һ���������ڶ�������������������
	 * @return sql���
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
	 * ����ȷ��ֵ���sql�еĲ���ֵ
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
	 * ����ȷ��ֵ���sql�еĲ���ֵ
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