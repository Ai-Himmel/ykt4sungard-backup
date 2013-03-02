package com.kingstar.log;

import com.kingstar.files.Parameters;


public class DebugFactory {

	private static Debug instance = null;
	
	public static synchronized Debug getInstance() throws Exception {

		if (instance == null) {
			
			//从console parameter 取出相关debug参数
			instance = new Debug();
			
			//从console parameter 取出相关debug参数
		 	Parameters p=new Parameters();
	    	p.load("console.ini");
			instance.setDebug(p.getPropertyBool("DEBUG"));
	
		}
		return instance;

	}
	public static void main(String args[]) throws Exception{
		
		Debug d=DebugFactory.getInstance();
		
		d.debug("title", "12345678901234567890123456789");
		d.debug("title", "12345678901234567890123456789");
		d.debug("title", "12345678901234567890123456789");
		d.debug("title", "12345678901234567890123456789");
		
	
	
	}
}

