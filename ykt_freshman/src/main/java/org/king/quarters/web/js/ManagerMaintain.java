/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QuartersMaintain.java
 * 创建日期： 2007-6-12 16:17:43
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-12 16:17:43     王胜        创建文件，实现基本功能
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
			util.setValue("message","学号不能为空！");
			return ;
		}
		//
		LdapService  service = new LdapService();
		Map info = service.getPersonInfo(no);
		String userName = (String)info.get("userName");
		if (userName == null) {
			util.setValue("message","用户不存在!");
		}
		else{
			util.setValue("userName",userName);
			util.setValue("sex",(String)info.get("userSex"));
		}
	}
	
	
}
