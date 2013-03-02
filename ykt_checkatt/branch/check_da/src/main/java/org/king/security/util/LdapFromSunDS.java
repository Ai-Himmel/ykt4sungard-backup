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

import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;

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

					IdentityFactory factory = IdentityFactory
							.createFactory(is_config);
					IdentityManager im = factory.getIdentityManager();
	                String userName = im.getUserNameByID(id);
	                
	                //����
	                personInfo.put("userName",userName);
	                
	                //�Ա�
	                String sex = "";
	                String [] sexs = im.getUserAttribute(id,"eduPersonSex");
	                if(sexs!=null&&sexs.length>0){
	                	sex = sexs[0];
	                	personInfo.put("userSex",sex);
	                }
	                
	                String dn = "";
	                String[] dns = im.getUserAttribute(id,"DN");
	                if(dns!=null&&dns.length>0){
		                dn = dns[0];
		                String type = "";
		                String [] result = dn.split(",");
		                
		                type = result[1].substring(3);
		                //��Ա���
		                personInfo.put("userType",type);
	                }
	                //һ����λ����
	                String org = "";
	                String [] orgs = im.getUserAttribute(id,"eduPersonOrgDN");
	                if(orgs!=null&&orgs.length>0){
	                	org = orgs[0];
	                }
	                personInfo.put("userOrg",org);
	                
	                
		
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
