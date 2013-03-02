
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>

<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link
	href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css"
	rel="stylesheet" type="text/css" />
<link
	href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css"
	rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
</head>
<html:html>
  <head>
   
    <html:base/>
    <title><bean:message key="system.name" /></title>
  </head>
  <body>

  <html:form  action="/impnoregister.do">
       <table width="70%" border="0" align="center" cellpadding="0"  cellspacing="0">
          <tr><td>&nbsp;</td></tr>
          <tr><td>&nbsp;</td></tr>
	        <tr>
	            <td nowrap="nowrap"><bean:message key="term"/>
			     <html:select property="termName"  style="width:140px;"> 
			      <option value=""/></option>
			      <html:optionsCollection name="TermList" value="code"  label="name"/>
		          </html:select>  <font Color="red"><html:errors property="termName"/></font>
		       </td>	      
		       
	        </tr>
	   </table>
	   
	   <table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#f8f8f8">
          <tr><td>&nbsp;</td></tr>
          <tr>
            <td height="30"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
             <tr>
				<td width="66%" class="red_text"><bean:message key="system.note" /></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.imp" /></button>
				<button onclick="document.forms[0].reset();" ><bean:message key="btn.clear" /></button>
			</td>
        </tr>
       </table>
 
    </html:form>
  </body>
</html:html>
