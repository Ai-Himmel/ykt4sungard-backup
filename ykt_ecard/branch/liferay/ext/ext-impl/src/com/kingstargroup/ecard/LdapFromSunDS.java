/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.util.LdapFromSunDS.java
 * 创建日期： 2006-6-9 17:40:41
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-9 17:40:41      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package com.kingstargroup.ecard;

import java.io.IOException;
import java.io.InputStream;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.Properties;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;

/**
 * <p> LdapFromSunDS.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="LdapFromSunDS.java.html"><i>查看源代码</i></a></p>  
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
	                
	                //姓名
	                personInfo.put("userName",userName);
	                
	                //性别
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
		                //人员类别
		                personInfo.put("userType",type);
	                }
	                //一级单位代码
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
            properties.load(this.getClass().getResourceAsStream("/oneks-ext.properties"));
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
