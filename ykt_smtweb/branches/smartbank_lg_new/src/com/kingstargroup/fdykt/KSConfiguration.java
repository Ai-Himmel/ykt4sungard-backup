package com.kingstargroup.fdykt;

import java.io.IOException;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.Properties;

public class KSConfiguration {
	static private KSConfiguration instance = null;
	static private Object mutex = new Object();
	
	private Properties properties;
	
	private KSConfiguration(){
		// empty
	} 
	/**
	 * ȡ��Ψһ���
	 * @return - �����ɹ����ؾ����ʧ�ܷ��� null
	 */
	public static KSConfiguration getInstance(){
		synchronized (mutex) {
			if(null == instance){
				instance = new KSConfiguration();
				InputStream in = instance.getClass().getClassLoader()
				.getResourceAsStream(KSConstant.CONFIG_FILE);
				try {
					instance.loadResource(in);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					return null;
				}
			}
		}
		return instance;
	}
	
	/**
	 * �� InputStream �м�������
	 * @param is - ������
	 * @throws IOException - ��ȡ������ʧ�ܣ����׳� IOException
	 */
	protected void loadResource(InputStream is)
		throws IOException{
		properties = new Properties();
		properties.load(is);
	}
	/**
	 * ��ȡ����ֵ
	 * @param propName - ������
	 * @param defaultValue - Ĭ��ֵ
	 * @return - ���ز���ֵ
	 */
	public String getProperty(String propName,String defaultValue){
		String v = properties.getProperty(propName);
		if(null == v){
			return defaultValue;
		}
		return v;
	}
	/**
	 * ��ȡ����ֵ��Ĭ��ֵΪ ""
	 * @param propName - ������
	 * @return - ���ز���ֵ
	 */
	public String getProperty(String propName){
		//
		return getProperty(propName,"");
	}
	/**
	 * ��ȡ���Ͳ���ֵ
	 * @param propName - ������
	 * @param defaultValue - ����Ĭ��ֵ
	 * @return - ���ز���ֵ
	 */
	public int getPropertyAsInt(String propName,int defaultValue){
		String v = getProperty(propName);
		if(null == v || "".equals(v)){
			return defaultValue;
		}
		return Integer.parseInt(v);
	}
	/**
	 * ��ȡ���Ͳ���ֵ,Ĭ�Ϸ��� 0
	 * @param propName - ������
	 * @return - ���ز���ֵ
	 */
	public int getPropertyAsInt(String propName){
		return getPropertyAsInt(propName,0);
	}
	/**
	 * ��ȡ�����Ͳ���ֵ
	 * @param propName - ������
	 * @param defaultValue - Ĭ��ֵ
	 * @return - ���ز���ֵ
	 */
	public boolean getPropertyAsBool(String propName,boolean defaultValue){
		String v = getProperty(propName);
		if(null == v || "".equals(v)){
			return defaultValue;
		}
		Boolean ret = Boolean.valueOf(defaultValue);
		if(Boolean.TRUE == ret){
			return true;
		}
		return false;
	}
	/**
	 * ��ȡ�����Ͳ���ֵ��Ĭ�Ϸ��� false
	 * @param propName - ������
	 * @return - ���ز���ֵ
	 */
	public boolean getPropertyAsBool(String propName){
		return getPropertyAsBool(propName,false);
	}
	
	public Enumeration getParameterNames(){
		return properties.propertyNames();
	}
}
