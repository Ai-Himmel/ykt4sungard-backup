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
	 * 取得唯一句柄
	 * @return - 创建成功返回句柄，失败返回 null
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
	 * 从 InputStream 中加载配置
	 * @param is - 输入流
	 * @throws IOException - 读取输入流失败，则抛出 IOException
	 */
	protected void loadResource(InputStream is)
		throws IOException{
		properties = new Properties();
		properties.load(is);
	}
	/**
	 * 获取参数值
	 * @param propName - 参数名
	 * @param defaultValue - 默认值
	 * @return - 返回参数值
	 */
	public String getProperty(String propName,String defaultValue){
		String v = properties.getProperty(propName);
		if(null == v){
			return defaultValue;
		}
		return v;
	}
	/**
	 * 获取参数值，默认值为 ""
	 * @param propName - 参数名
	 * @return - 返回参数值
	 */
	public String getProperty(String propName){
		//
		return getProperty(propName,"");
	}
	/**
	 * 读取整型参数值
	 * @param propName - 参数名
	 * @param defaultValue - 参数默认值
	 * @return - 返回参数值
	 */
	public int getPropertyAsInt(String propName,int defaultValue){
		String v = getProperty(propName);
		if(null == v || "".equals(v)){
			return defaultValue;
		}
		return Integer.parseInt(v);
	}
	/**
	 * 读取整型参数值,默认返回 0
	 * @param propName - 参数名
	 * @return - 返回参数值
	 */
	public int getPropertyAsInt(String propName){
		return getPropertyAsInt(propName,0);
	}
	/**
	 * 读取布尔型参数值
	 * @param propName - 参数名
	 * @param defaultValue - 默认值
	 * @return - 返回参数值
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
	 * 读取布尔型参数值，默认返回 false
	 * @param propName - 参数名
	 * @return - 返回参数值
	 */
	public boolean getPropertyAsBool(String propName){
		return getPropertyAsBool(propName,false);
	}
	
	public Enumeration getParameterNames(){
		return properties.propertyNames();
	}
}
