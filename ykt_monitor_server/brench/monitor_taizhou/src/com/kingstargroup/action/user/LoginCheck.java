package com.kingstargroup.action.user;

/**
 * 
 *
 * <p>
 * <a href="ErrorCode.java.html"><i>View Source</i></a>
 * </p>
 *
 * @author <a href="mailto:linqing.he@kingstargroup.com">heliniqng</a>
 */

import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapUserTable;
import org.hibernate.*; 

/**
 * @author Administrator
 *
 */
public class LoginCheck {
	

	 /**
	  * 判断用户名密码是否正确
	  * @param username String
	  * @param password String
	  * @return returnStr String
	  */
	public static String logindbCheck(String userName,String password){		
        Session session = HibernateSessionFactory.currentSession(); 
        String returnStr = "";
        Query query = session.createQuery("from MapUserTable as user where user.username=:userName");
        if(userName==null){
        	query.setString("userName","");
        }else{
        	query.setString("userName",userName);
        }    
        if(query.iterate().hasNext()){
        	MapUserTable user =	(MapUserTable)query.iterate().next();
        	String pwd = user.getPassword();
        	if(password.equals(pwd)){
        		//登入成功的返回用户角色码！
        		if(ErrorCode.USER_STATUS_OK.equals(user.getUserstatus().toString())){
        			returnStr = user.getUserrole().toString();
        		}else{
        			returnStr = ErrorCode.USER_STOPED;
        		}        		
        	}else{
        		returnStr = ErrorCode.PWD_ERROR;
        	}
        }else{
        	returnStr = ErrorCode.NO_USER;
        }
        HibernateSessionFactory.closeSession(); 
		return returnStr ;
	}
	

}
