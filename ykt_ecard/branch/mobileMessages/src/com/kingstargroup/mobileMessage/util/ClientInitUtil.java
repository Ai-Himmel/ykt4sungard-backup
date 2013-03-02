
//建立到移动代理服务器的连接，分配所属资源
package com.kingstargroup.mobileMessage.util;


import org.apache.log4j.Logger;

import com.jasson.im.api.APIClient;

public class ClientInitUtil {
	
	private static final String  imIP=KSConfiguration.getInstance().getProperty("imIP");
	private static final String  loginName=KSConfiguration.getInstance().getProperty("loginName");
	private static final String  loginPWD=KSConfiguration.getInstance().getProperty("loginPWD");
	private static final String  apiCode=KSConfiguration.getInstance().getProperty("apiCode");
	private static final String  dbName=KSConfiguration.getInstance().getProperty("dbName");
	
	
   public   int  init(){
	   APIClient client = new APIClient();
	   int connectRe = client.init(imIP,loginName,loginPWD,apiCode, dbName);
	                 
	       if(connectRe == APIClient.IMAPI_SUCC)
		   log.info("---初始化成功---");
		   else if(connectRe == APIClient.IMAPI_CONN_ERR)
		   log.error("---连接失败---");
		   else if(connectRe == APIClient.IMAPI_API_ERR)
		   log.info("---apiID不存在---");
	   return connectRe;
	}
   private  Logger log = Logger.getLogger(ClientInitUtil.class);
}
