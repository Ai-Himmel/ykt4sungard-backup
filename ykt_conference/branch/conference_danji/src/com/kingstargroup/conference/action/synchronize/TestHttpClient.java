package com.kingstargroup.conference.action.synchronize;

import java.io.IOException;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpException;
import org.apache.commons.httpclient.HttpStatus;
import org.apache.commons.httpclient.methods.GetMethod;

public class TestHttpClient {

	/**
	 * File name: TestHttpClient.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      何林青    2007-1-24  <br>
	 * @author   何林青
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
		HttpClient client = new HttpClient();
		GetMethod method = new GetMethod("http://www.ecardapp.fudan.edu.cn/conference/");
		int state;
		
			state = client.executeMethod(method);
		
		String config = "";
		if(HttpStatus.SC_OK==state){
			config = method.getResponseBodyAsString();
		}
		
		} catch (HttpException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
