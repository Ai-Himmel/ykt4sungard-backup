<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
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
<html>
  <head>
  
    <html:base/>
    <title><bean:message key="system.name" /></title>

  </head>
  <body>
  <html:form  action="/registercomeQuery.do">
   
       <table width="94%" border="0" align="center" cellpadding="0"  cellspacing="0">
          <tr><td>&nbsp;</td></tr>
	      <tr>
		      <td nowrap="nowrap" ><bean:message key="spec.stuempNo"/>
		         <html:text property="stuempNo"  value="${register.stuempNo}" size="13" maxlength="20"/>
			     
		      </td>
		       <td nowrap="nowrap" ><bean:message key="special.name"/>
		         <html:text property="name" size="17" maxlength="20" value="${register.name}" />
			     
		      </td>
		     
		       <td nowrap="nowrap"><bean:message key="spec.degree"/>
			     <html:select property="degree" value="${register.degree}" style="width:140px;" > 
			       <option value=""/></option>
			       <html:optionsCollection  name="Cuttype" value="degree" label="name"/>
			      
		        </html:select>
		      </td>
		      
		       <td nowrap="nowrap"><bean:message key="spec.scode"/>
			      <html:select property="scode" value="${register.scode}" style="width:140px;"> 
			       <option value=""/></option>
			       <html:optionsCollection name="Speciality" value="code" label="name" />
		          </html:select>
		      </td>
	       </tr>
	       <tr>
		      <td nowrap="nowrap"><bean:message key="spec.class"/>
		          <html:text property="classroom"  size="13" value="${register.classroom}" maxlength="20"/>
		      </td>
		      
		      <td ><bean:message key="spec.dept"/>
		        <html:select property="dept" value="${register.dept}" style="width:140px;"> 
		         <option value=""/></option>
		         <html:optionsCollection name="deptList" value="id" label="name"/> 
		       </html:select>
		     
		       
		      </td>
		      	<td width="15%" nowrap="nowrap"  align="left">
	    
			  <bean:message key="register.isregister" />
		       <html:select property="isCome"  style="width:85px;">
		         <option value=""/></option>
		         <html:optionsCollection name="isregisterList" value="code"  label="name"/>
		       </html:select>  
		      </td>
		      
		       <td nowrap="nowrap"><bean:message key="term"/>
			     <html:select property="term" value="${register.term}" style="width:140px;"> 
			      <option value=""/></option>
			      <html:optionsCollection name="TermList" value="code"  label="name"/>
		          </html:select>
			     
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
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();" ><bean:message key="btn.clear" /></button>
				</td>
        </tr>
       </table>
 
    
    </html:form>
  </body>
</html>
