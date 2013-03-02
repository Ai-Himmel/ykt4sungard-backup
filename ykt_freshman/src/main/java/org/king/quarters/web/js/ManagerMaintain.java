/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    QuartersMaintain.java
 * �������ڣ� 2007-6-12 16:17:43
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-12 16:17:43     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.quarters.web.js;

import java.util.Map;

import org.directwebremoting.WebContext;
import org.directwebremoting.WebContextFactory;
import org.directwebremoting.proxy.dwr.Util;


public class ManagerMaintain {

	
	public void setPersonInfo(String no){
		
		WebContext context = WebContextFactory.get();
		Util util = new Util(context.getScriptSession());
		if (no == null || no.trim().equals("")){
			util.setValue("message","ѧ�Ų���Ϊ�գ�");
			return ;
		}
		//
		LdapService  service = new LdapService();
		Map info = service.getPersonInfo(no);
		String userName = (String)info.get("userName");
		if (userName == null) {
			util.setValue("message","�û�������!");
		}
		else{
			util.setValue("userName",userName);
			util.setValue("sex",(String)info.get("userSex"));
		}
	}
	
	
}
