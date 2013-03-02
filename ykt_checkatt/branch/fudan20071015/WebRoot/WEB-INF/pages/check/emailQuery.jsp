
<%@ page language="java" import="java.util.*" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
        <%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
    <title>邮件设置</title>
    
    <meta http-equiv="pragma" content="no-cache">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
    <meta http-equiv="description" content="This is my page">
    
    <!--
    <link rel="stylesheet" type="text/css" href="styles.css">
    -->
  </head>
  <%  String address="";
      String addressvalue="";
      List addressList =(List)request.getAttribute("addressList");
      if(addressList != null && !addressList.isEmpty()){
       Map addressMap =(Map)addressList.get(0);
        address = (String)((Map)addressList.get(0)).get("dic_caption"); 
        addressvalue=(String)((Map)addressList.get(0)).get("dic_value"); 
      }
      
      
      String email="";
      String emailvalue="";
      List emailList =(List)request.getAttribute("emailList");
      if(emailList != null && !emailList.isEmpty()){
       Map emailMap =(Map)emailList.get(0);
        email= (String)((Map)emailList.get(0)).get("dic_caption"); 
        emailvalue=(String)((Map)emailList.get(0)).get("dic_value"); 
      }
      
      String user="";
      String uservalue="";
      List userList =(List)request.getAttribute("userList");
      if(userList != null && !userList.isEmpty()){
        Map userMap =(Map)userList.get(0);
        user= (String)((Map)userList.get(0)).get("dic_caption"); 
        uservalue =(String)((Map)userList.get(0)).get("dic_value"); 
      }
      
      
      
      String pwd ="";
      String pwdvalue="";
      List pwdList =(List)request.getAttribute("pwdList");
      if(pwdList != null && !pwdList.isEmpty()){
       Map pwdMap =(Map)pwdList.get(0);
        pwd= (String)((Map)pwdList.get(0)).get("dic_caption"); 
        pwdvalue =(String)((Map)pwdList.get(0)).get("dic_value"); 
      }
      
      
      String title="";
      String titlevalue="";
      List titList =(List)request.getAttribute("titList");
       if(titList != null && !titList.isEmpty()){
       Map  titMap =(Map)titList.get(0);
        title= (String)((Map)titList.get(0)).get("dic_caption"); 
      //  titlevalue =(String)((Map)titList.get(0)).get("dic_value"); 
      }
      
  %>
  <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 请假申请邮件设置 </font> </strong>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
  
  <html:form action="/editEmail.do?method=editEmail" method="POST"  onsubmit="return validateEditEmailForm(this);">
  <div id="tableDiv">
    <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td bgcolor="#e1e1e2"></td>
            </tr>
          </table>    
          <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td bgcolor="#e1e1e2"></td>
            </tr>
          </table>   
          <br/>     
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="2%" valign="center" class="text_or_12">主机地址: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="address"   styleClass="input_box"  size="30" value="<%=address%>"/>
              </td>
                
            </tr>
          </table>
          <br/>
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="2%" valign="center" class="text_or_12">邮箱地址: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="email"  styleClass="input_box" size="30"  value="<%=email%>"/>
              </td>
               
            </tr>
          </table>
          <br/>
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="2%" valign="center" class="text_or_12">用户名: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="username" styleClass="input_box"  size="30"  value="<%=user%>"/>
              </td>
            </tr>
          </table>
          <br/>
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="2%" valign="center" class="text_or_12">密码: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="password" styleClass="input_box"  size="30" value="<%=pwd%>"/>
              </td>
            </tr>
          </table>
          <br/>
           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="2%" valign="center" class="text_or_12">邮件标题: </td>
              <td width="30%" align="left" class="text_or_12">
                 <html:text  property="title" styleClass="input_box"  size="30"   value="<%=title%>" />
              </td>
              
            </tr>
          </table>
          
         <div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		  <br/>
          <table width="2%" height="1" align="left"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10%" align="center"><input type="submit" value=" 保 存 " class="submitButton" >&nbsp;&nbsp;&nbsp;&nbsp;</td>
          
            <td width="10%" align="center"><input type="reset" value="重 置 " class="submitButton"  ></td>
           </tr>
           </table>
           </div>
          </html:form>
  </body>
</html>
<html:javascript formName="editEmailForm" staticJavascript="true" dynamicJavascript="true"/>
