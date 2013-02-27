/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.util.LdapFromSunDS.java
 * �������ڣ� 2006-6-9 17:40:41
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-9 17:40:41      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.util;

import org.apache.log4j.Logger;

import java.io.IOException;
import java.io.InputStream;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.Properties;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;


/**
 * <p> LdapFromSunDS.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="LdapFromSunDS.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-9
 * 
 *
 */
public class LdapFromSunDS {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LdapFromSunDS.class);

	
	private Properties properties = new Properties();
	
	public  HashMap getPersonInfo(HttpServletRequest request,String id){
		init("");
		
		HashMap personInfo = new HashMap();
		
	     //String is_config=request.getRealPath("/client.properties");
		String is_config = getPreference("constant.ldap.path")+"/client.properties";
	     try {
	     Cookie all_cookies[] = request.getCookies();
	     Cookie myCookie;
					String decodedCookieValue = null;
					if (all_cookies != null) {
						for (int i = 0; i < all_cookies.length; i++) {
							myCookie = all_cookies[i];
							if (myCookie.getName().equals("iPlanetDirectoryPro")) {
								decodedCookieValue = URLDecoder.decode(myCookie
										.getValue(), "GB2312");
							}
						}
					}


	                
		
	     }catch (Exception e) {
	    	
	     }
		
		
		return personInfo;
		
	}
	
	
	public void init(String preferencesLocation) {
        try {
            properties.load(this.getClass().getResourceAsStream("/oneks.properties"));
            if (StringUtils.isNotBlank(preferencesLocation)) {
                InputStream input = this.getClass().getResourceAsStream(preferencesLocation);
                if (input != null) {
                    properties.load(input);
                }
            }
        } catch (IOException e) {
           logger.error("Could not load properties.", e);
        }
    }
	
	
    public String getPreference(String name) {
        return (String) properties.get(name);
    }
	
}
