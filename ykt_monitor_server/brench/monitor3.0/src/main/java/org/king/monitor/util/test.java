package org.king.monitor.util;


public class test {
	
	private void mytestfun(boolean flag){
		if(flag){
			return;
		}
		System.out.print("shit");
	}

	/**
	 * Description: 
	 * @param @param args
	 * @return void
	 * Modify History: 2010-8-6 Linqing.He create
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		test test = new test();
		test.mytestfun(false);
		System.out.println("----------------");
		test.mytestfun(true);
	

	}

}
