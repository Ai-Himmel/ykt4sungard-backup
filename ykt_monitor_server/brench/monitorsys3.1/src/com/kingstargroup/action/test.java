package com.kingstargroup.action;

import java.util.ArrayList;
import java.util.List;

import com.kingstargroup.form.UnusualDeviceResult;

public class test {

	/**
	 * Method name: main<br>
	 * Description: <br>
	 * Return: void<br>
	 * Args: @param args
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      何林青    Aug 5, 2008  <br>
	 * @author   何林青
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		System.out.print("".indexOf("abc"));
		List list = new ArrayList();
		UnusualDeviceResult tmp1 = new UnusualDeviceResult(1,"AAAAAAAA","","","",1);
		UnusualDeviceResult tmp2 = new UnusualDeviceResult(1,"BBBBBBBB","","","",1);
		UnusualDeviceResult tmp3 = new UnusualDeviceResult(1,"AAAAAAAA","","","",1);
		UnusualDeviceResult tmp4 = new UnusualDeviceResult(1,"CCCCCCCC","","","",1);
		UnusualDeviceResult tmp5 = new UnusualDeviceResult(1,"BBBBBBBB","","","",1);
		UnusualDeviceResult tmp6 = new UnusualDeviceResult(1,"AAAAAAAA","","","",1);
		list.add(tmp1);
		list.add(tmp2);
		list.add(tmp3);
		list.add(tmp4);
		list.add(tmp5);
		list.add(tmp6);
		
		
		String devphyids = "";
		for(int i=0;i<list.size();i++){
			UnusualDeviceResult unusualDR = (UnusualDeviceResult)list.get(i);
			if(devphyids.indexOf(unusualDR.getDevphy999Id())!=-1){
				list.remove(i);
				i--;
			}else{
				devphyids= devphyids+unusualDR.getDevphy999Id()+",";
			}
		}
	}

}
