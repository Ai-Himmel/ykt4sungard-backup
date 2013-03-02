package com.kingstargroup.advquery.common;

import org.apache.commons.configuration.PropertiesConfiguration;
import com.kingstargroup.advquery.util.GetPropertiesUtil;
import org.apache.log4j.Logger;

import com.kingstar.bcc.bccclt;

public class BccctlInit {
	
	
	
	
	private static bccclt bcc = null;
	//private static String DRTP_IP = "10.14.164.193";
	
	private static int DRTP_PORT = 4000;
	public static int drtpno = -1;
	//public static String CPACKFILE = "/opt/cpack.dat";
	//public static String CPACKFILE = "c:\\cpack.dat";
	public static int FUNCNO = 847308;
	public static int MAINFUNC = 9600;
	private BccctlInit(){
		
	}
	public static  String  getCpack(){
		 PropertiesConfiguration configs = GetPropertiesUtil.getInstance();
		 String cpack =configs.getString("cpackfile");
		 return cpack;
	}
	public static String getDrtp(){
		PropertiesConfiguration configs = GetPropertiesUtil.getInstance();
		String drtp = configs.getString("drtp");
	    return drtp;
	}
	public static bccclt getBccctlInstance(){
		
		//System.out.println(System.getProperty("java.library.path"));
		
		if(null==bcc){
			bcc = new bccclt();
		//	_log.info("-------------bcc--------------");
			bcc.BCCCLTInit(1);			
		//	_log.info("-------------BCCCLTInit(1)--------------");
			bcc.XPackInit(1);		
		//	_log.info("-------------XPackInit(1)--------------");
			drtpno = bcc.AddDrtpNode(getDrtp().getBytes(), DRTP_PORT);
		//	_log.info("-------------drtpno--------------");
			return bcc;
		}else{
			return bcc;
		}
	}
	private static final Logger _log = Logger.getLogger(BccctlInit.class);

}
