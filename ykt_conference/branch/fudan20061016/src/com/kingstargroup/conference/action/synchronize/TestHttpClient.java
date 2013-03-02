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
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ������    2007-1-24  <br>
	 * @author   ������
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
