<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ page import="com.kingstargroup.advquery.register.dto.*" %>
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
  <html:form  action="/registerReportResult.do">
   
       <table width="94%" border="0" align="center" cellpadding="0"  cellspacing="0">
          <tr><td>&nbsp;</td></tr>
	         
	        <tr>
	            
	            <td nowrap="nowrap"><bean:message key="term"/>
			     <html:select property="term" value="${register.term}" style="width:140px;"> 
			      <option value=""/></option>
			      <html:optionsCollection name="TermList" value="code"  label="name"/>
		          </html:select>
			      
		       </td>
	        
	            
	            <td ><bean:message key="spec.dept"/>
		        <html:select property="dept" value="${register.dept}"    style="width:130px;" > 
		         <option value=""/></option>
		         <html:optionsCollection name="deptList" value="id" label="name"/>
		       </html:select>
		     
		       
		      <td nowrap="nowrap"><bean:message key="spec.class"/>&nbsp;&nbsp;&nbsp;
		          <html:text property="classroom" size="16" maxlength="20"/>
		      </td>
		      
	        </tr>
	   </table>
	   <!--     
	    <table width="94%" border="0" align="center" cellpadding="0"  cellspacing="0">
	       <tr>
		<td width="5%" align="left" nowrap="nowrap"><bean:message key="spec.bDate" /></td>
        <td width="20%" nowrap="nowrap"  align="right"><input type="text" name="begindate"  size="16" value="${register.begindate}"  readonly="readonly"/></td>
        <td width="25%" nowrap="nowrap"  align="left"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
        <td width="10%" nowrap="nowrap"  align="left"><bean:message key="spec.eDate" /></td>
        <td width="18%" nowrap="nowrap"  align="left"><input type="text" name="enddate"  size="16" value="${register.enddate}"  readonly="readonly"/></td>
        <td width="22%" nowrap="nowrap"  align="left"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
		    <script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					</script>
	        </tr>
        </table>
        -->
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
</html:html>
