/**
 * 
 */
package org.king.support.util;

import org.apache.commons.configuration.ConfigurationException;
import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.configuration.reloading.FileChangedReloadingStrategy;

/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: GetApplicationResources.java<br>
 * Description: <br>
 * Modify History（或Change Log）:  <br>
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述<br>
 * 创建  				 2005-11-9  何林青    <br>
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
public class GetApplicationResources {
	private static PropertiesConfiguration instance = null;
	private static Object mutex = new Object();

	/**
	 * 
	 */
	public static PropertiesConfiguration getInstance(){
		synchronized (mutex) {
			if(null==instance){
				try {
					instance= new PropertiesConfiguration("ApplicationResources.properties");
				} catch (ConfigurationException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		return instance;
	}

}
