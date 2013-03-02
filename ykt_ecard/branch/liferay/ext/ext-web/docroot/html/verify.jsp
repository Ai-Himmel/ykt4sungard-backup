<%@ page pageEncoding="UTF-8" %>
<%@ page import="org.apache.commons.lang.StringUtils" %>
<%@ page import="com.kingstargroup.ecard.util.SimpleEncoding" %>
<%@ page import="com.liferay.portal.model.User" %>
<%@ page import="com.liferay.portal.service.UserLocalServiceUtil" %>
<%@ page import="com.liferay.portal.security.pwd.PwdEncryptor" %>
<%@ page import="java.util.HashMap" %>
<%@ page import="com.liferay.portal.security.auth.Authenticator" %>
<%@ page import="com.liferay.portal.util.PortalUtil" %>
<%@ page import="com.liferay.portal.model.Company" %>
<%@ page import="com.liferay.portal.service.UserServiceUtil" %>
<%
	boolean isValid = false;
	String userid = request.getParameter("userid");
	String password = request.getParameter("password");
	String token = request.getParameter("token");
	String key = "kingstar";
	try{
		if(StringUtils.isBlank(userid) || StringUtils.isBlank(userid) || StringUtils.isBlank(userid)){
		} else {
			Company company = PortalUtil.getCompany(request);
			//解密过程
			String decodedToken = new String(SimpleEncoding.decode(SimpleEncoding.hex2byte(token),key.getBytes()));
			String decodedUserid = new String(SimpleEncoding.decode(SimpleEncoding.hex2byte(userid),decodedToken.getBytes()));
			String decodedPassword = new String(SimpleEncoding.decode(SimpleEncoding.hex2byte(password),decodedToken.getBytes()));
			
			User user = UserLocalServiceUtil.getUserByScreenName(company.getCompanyId(),decodedUserid);
			if(user!=null){
				if(user.getPassword().equals(PwdEncryptor.encrypt(decodedPassword))){
					isValid = true;	
				}
			}
		}		
	} catch(Exception e){
		System.out.println(e.getMessage());	
	}
%>
<%=isValid%>