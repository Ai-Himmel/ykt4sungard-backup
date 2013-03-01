
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>

<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <html:base/>
    
    <title><%= GetProperty.getProperties("fee.reserver",getServletContext())%></title>
    
    <meta http-equiv="pragma" content="no-cache">
    <meta http-equiv="cache-control" content="no-cache">
    <meta http-equiv="expires" content="0">
    <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
    <meta http-equiv="description" content="This is my page">
    
    <!--
    <link rel="stylesheet" type="text/css" href="styles.css">
    -->
  </head>
  
  <body  >
    <% // Map result = (Map)request.getAttribute("result");
    %>
      
     <html:form  action="/updateReserver.do?cmd=update">
     <table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#f8f8f8">
     <tr><td>
       <c:out value="${result.cutName}"/>  : <c:out value="${result.registerInfo}"/> 
       <input type="hidden" name="stuempNo" value="${result.stuempNo}"/>
       <input type="hidden" name="optDate" value="${result.optDate}">
       <input type="hidden" name="optTime" value="${result.optTime}">
       <html:textarea   property="comments"   cols="40" rows="10" value="${result.comments}" ></html:textarea>
      </td></tr>    
     </table>  
       
     <table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#f8f8f8">
        <tr >
          <td align="center"> 
             <html:submit property="sub"><bean:message key="btn.save" /></html:submit> 
             <html:button property="clo"  onclick="window.close()"><bean:message key="btn.close" /> </html:button>
          </td>
        </tr>
         
     </table>
     </html:form>
  </body>
</html>
<%
  String  success="";
  Boolean flag = (Boolean)request.getAttribute("flag");
  if(flag!=null){
   if(flag.booleanValue()==true){
     success="true";
   }else{
     success="false";
   }
  }
%>
<script language="javascript">
 <%if("true".equals(success)){%>
   alert("<%= GetProperty.getProperties("save.success",getServletContext())%>");
 <%}%>
  <%if("false".equals(success)){%>
   alert("<%= GetProperty.getProperties("save.false",getServletContext())%>");
 <%}%>
</script>