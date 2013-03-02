package com.kingstargroup.ecard.hibernate.util;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TimerTask;

import javax.mail.AuthenticationFailedException;

import org.apache.commons.mail.HtmlEmail;
import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.common.EcardTransactionManager;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.web.WebDictionary;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.util.HibernateUtil;
import com.liferay.util.InstancePool;

public class SendEmailReportUtil   extends TimerTask{
	
	
	public void run() {
		
		
		sendEmail();

	}

	private void sendEmail() {

		try {

			List list = WebDictionaryUtil.getDictionaryByDicNo("008");
			WebDictionary webservice = WebDictionaryUtil.getDictionary("003",
					"01");
			String service = "";
			if (webservice != null) {
				service = webservice.getDicCaption();
			}

			WebDictionary websendEmail = WebDictionaryUtil.getDictionary("004",
					"01");
			String sendEmail = "";
			if (websendEmail != null) {
				sendEmail = websendEmail.getDicCaption();
			}

			WebDictionary webusername = WebDictionaryUtil.getDictionary("005",
					"01");
			String username = "";
			if (webusername != null) {
				username = webusername.getDicCaption();
			}

			WebDictionary webpassword = WebDictionaryUtil.getDictionary("006",
					"01");
			String password = "";
			if (webpassword != null) {
				password = webpassword.getDicCaption();
			}

			/*
			 * WebDictionary webtitle =
			 * WebDictionaryUtil.getDictionary("007","01"); String title ="";
			 * if(webtitle!=null){ title=webtitle.getDicCaption(); }
			 */
			String title = EcardConstants.REPORTTITLE;
			if (list != null) {
				for (int i = 0; i < list.size(); i++) {
					WebDictionary dic = (WebDictionary) list.get(i);
					if (dic.getDicCaption() != null
							&& !dic.getDicCaption().equals("")) {
						//SimpleEmail email = new SimpleEmail();
						HtmlEmail email = new HtmlEmail();
						email.setHostName(service);// �ʼ�������
						email.setFrom(sendEmail, EcardConstants.MAINTAIN);// ������
						email.addTo(dic.getDicCaption());// ������
						email.setAuthentication(username, password);// smtp��֤���û���������
						email.setSubject(title);// ����
						email.setCharset("gb2312");// �����ʽ
						email.setMsg(getReport());// ����
						email.send();// ����
					}
				}
			}
		} catch (AuthenticationFailedException e) {
			System.out.println("�����ʼ�ʧ��");
			e.printStackTrace();
		} catch (DBSystemException e) {
			e.printStackTrace();
		} catch (Exception mex) {
			mex.printStackTrace();
		} finally {
			closeSession();
		}
	}

	private String getReport() {
		try {
			WebDictionary webbegindate = WebDictionaryUtil.getDictionary("011",
					"0");
			String beginDate = "";
			if (webbegindate != null) {
				beginDate = webbegindate.getDicCaption();
			}

			SimpleDateFormat fm = new SimpleDateFormat("yyyy/MM/dd");
			
			String endDate = fm.format(new Date());
			
			List list = MaintainUtil.adminTotal(beginDate, endDate);
			
			int 	 alltype=0;
		    int      allsum=0 ;
			Iterator it = list.iterator();
			StringBuffer  sb = new StringBuffer("");
			sb.append("<html><table><tr>" +
					           " <td>  ��������("+beginDate+"--"+endDate+") </td>" +
					           " <td>  ��������  </td>" +
					           "</tr><br>");
					          
			while(it.hasNext()){
			  Map  tempMap =	(Map)it.next();
			  if(!"0".equals(tempMap.get("dicValue"))&& !"1".equals(tempMap.get("dicValue"))){
					 alltype=alltype+Integer.parseInt((String)tempMap.get("total"));
		             sb.append("<tr> <td> "+tempMap.get("dicCaption")+" </td> <td>"+tempMap.get("total")+" </td></tr> ");
			  }
			  if("0".equals(tempMap.get("dicValue"))){
            	     allsum= allsum+Integer.parseInt((String)tempMap.get("total"));
            	     sb.append("<tr> <td> "+tempMap.get("dicCaption")+" </td> <td>"+tempMap.get("total")+" </td></tr>");
			  }
			  if("1".equals(tempMap.get("dicValue"))){
            	     allsum= allsum+Integer.parseInt((String)tempMap.get("total"));
            	     sb.append("<tr> <td> "+tempMap.get("dicCaption")+" </td> <td>"+tempMap.get("total")+" </td></tr>");
			  }

			}
			sb.append("<tr><td> ά�����ͺϼ� </td><td>"+alltype+" </td></tr>");
			sb.append("<tr><td> ���޼����ϼ�</td><td>"+allsum+" </td></tr>");
			sb.append("</table></html>");
			return sb.toString();
		} catch (Exception e) {
			return null;
		}
	}
	
	protected static EcardTransactionManager getTxManager() {		
		return new EcardTransactionManager();
		
	}
	
	protected static Object getPersistence(String className) {		
		return InstancePool.get(className);
	}
	
	protected static void closeSession() {
		HibernateUtil.closeSession();
	}
	
	protected static Transaction beginTransaction() {
		return HibernateUtil.openLocalSession().beginTransaction();
	}


}
