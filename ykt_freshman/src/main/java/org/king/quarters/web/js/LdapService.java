/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    LdapService.java
 * �������ڣ� 2007-6-18 16:23:12
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-18 16:23:12     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.quarters.web.js;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.king.security.util.LdapFromSunDS;

import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;

public class LdapService {

private static final Logger logger = Logger.getLogger(LdapFromSunDS.class);

	
	private Properties properties = new Properties();
	
	public  HashMap getPersonInfo(String stuNo){
		init("");
		
		HashMap personInfo = new HashMap();
		
	     //String is_config=request.getRealPath("/client.properties");
		String is_config = getPreference("constant.ldap.path")+"/client.properties";
	     try {
	    
					IdentityFactory factory = IdentityFactory
							.createFactory(is_config);
					IdentityManager im = factory.getIdentityManager();
	                String userName = im.getUserNameByID(stuNo);
	                
	                //����
	                personInfo.put("userName",userName);
	                
	                //�Ա�
	                String sex = "";
	                String [] sexs = im.getUserAttribute(stuNo,"eduPersonSex");
	                if(sexs!=null&&sexs.length>0){
	                	sex = sexs[0];
	                	personInfo.put("userSex",sex);
	                }
	                
	                String dn = "";
	                String[] dns = im.getUserAttribute(stuNo,"DN");
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
	                String [] orgs = im.getUserAttribute(stuNo,"eduPersonOrgDN");
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
