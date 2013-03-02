/**
 * 
 */
package org.king.utils;

import org.apache.commons.configuration.ConfigurationException;
import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.configuration.reloading.FileChangedReloadingStrategy;


/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: GetPropertiesUtil.java<br>
 * Description: <br>
 * Modify History（或Change Log）:  <br>
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述<br>
 * 创建  				 2005-11-7  何林青    <br>
 * 修改					2006-03-14  何林青	 
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
public class GetPropertiesUtil {
	private static PropertiesConfiguration instance = null;
	private static FileChangedReloadingStrategy fcrs = new FileChangedReloadingStrategy();
	private static Object mutex = new Object();

	/**
	 * 
	 */
	private GetPropertiesUtil() {
		super();
		// TODO Auto-generated constructor stub
	}
	public static PropertiesConfiguration getInstance(){
		synchronized (mutex) {
			if(null==instance){
				try {
					instance= new PropertiesConfiguration("/main/resources/dictionary.properties");
					instance.setReloadingStrategy(fcrs);
				} catch (ConfigurationException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}				
		}
		instance.reload();
		return instance;
	} 
	
	public static boolean fileChanged(){
		if(fcrs.reloadingRequired()){
			return true;
		}
		return false;
	}
	
}
