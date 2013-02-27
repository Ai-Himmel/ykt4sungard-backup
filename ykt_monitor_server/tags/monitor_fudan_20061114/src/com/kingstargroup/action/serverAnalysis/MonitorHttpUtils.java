package com.kingstargroup.action.serverAnalysis;

import java.io.IOException;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpException;
import org.apache.commons.httpclient.HttpStatus;
import org.apache.commons.httpclient.methods.GetMethod;

public class MonitorHttpUtils {

	public MonitorHttpUtils() {
		super();
		// TODO Auto-generated constructor stub
	}

	public static boolean checkHttpClient(String url){
		boolean chkclint = false;
		HttpClient client = new HttpClient();
		GetMethod method = new GetMethod(url);
		try {
			int code = client.executeMethod(method);
			if(HttpStatus.SC_OK==code){
				chkclint = true;
			}
		} catch (HttpException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			method.releaseConnection();
		  }
		return chkclint;
	}
	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
//		Protocol myhttps = new Protocol("https", new DefaultProtocolSocketFactory(), 443);
		
//		Protocol.registerProtocol("myhttps", 
//				new Protocol("https", new DefaultProtocolSocketFactory(), 443));

		HttpClient client = new HttpClient();
//		client.getHostConfiguration().setHost("www.ecard.fudan.edu.cn", 443, myhttps);		
//		HttpMethod method = new GetMethod("myhttps://www.ecard.fudan.edu.cn");
		GetMethod method = new GetMethod("https://www.ecard.fudan.edu.cn/advbis/");
		try {
			int code = client.executeMethod(method);
			if(HttpStatus.SC_OK==code){
				System.out.println(method.getStatusLine());
				System.out.println(method.getResponseBodyAsString());
			}
		} catch (HttpException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			method.releaseConnection();
		  }

	}

}
