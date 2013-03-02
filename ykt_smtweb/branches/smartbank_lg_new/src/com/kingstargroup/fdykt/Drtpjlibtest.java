package com.kingstargroup.fdykt;

import com.cn.kingstar.drtp.drtpjlib;

public class Drtpjlibtest {

	/**
	 * File name: Drtpjlibtest.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      何林青    2007-4-9  <br>
	 * @author   何林青
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		{
			// TODO: Add initialization code here
			drtpjlib obj=new drtpjlib();
			int errcode[]={1};
			byte errmsg[]=new byte[300];
			byte ip[]=new byte[300];
			byte message[]=new byte[8000];
			byte drtphandle[]=new byte[64];
			int port=4000;
			int handle;
			boolean ret;
			int len[]={1};
			int func=0;
			
			String sip="10.49.188.243";
			ip=sip.getBytes();
				
			ret=obj.DrtpInit(errcode,errmsg);
			System.out.println("init="+ret);
			handle=obj.DrtpConnect(ip,port,errcode,errmsg);
			if (handle < 0)
			{
					String s=new String(errmsg,0,300);
					System.out.println("connect:errcode="+errcode[0]+"msg="+s);
					
			}
			else
			{
				for (int i=0; i<3; i++)
				{
					byte[] version = new byte[10];
					obj.DrtpGetVersion(version);
					String s1=new String(version,0,10);
					System.out.println(s1);
					String hello="hello world";
					message=hello.getBytes();
					ret=obj.DrtpPostMessage(3,0,847315,message,hello.length(),errcode,errmsg,handle);
					if (ret == false)
					{
						String s=new String(errmsg,0,300);
						System.out.println(s);
					}
					ret=obj.DrtpReadMessage(message,7000,len,handle,drtphandle,errcode,errmsg);
					if (ret == false)
					{
						String s=new String(errmsg,0,300);
						System.out.println(s);
					}
					else
					{
						String s=new String(message,0,len[0]);
						System.out.println(s);
					}
				}
			}
		    obj.DrtpClose();
			obj.DrtpExit();
		}
	}

}
