
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
  <html:form  action="/feeQueryResult.do">
   
       <table width="94%" border="0" align="center" cellpadding="0"  cellspacing="0">
          <tr><td>&nbsp;</td></tr>
	      <tr>
		      <td nowrap="nowrap" ><bean:message key="spec.stuempNo"/>
		         <html:text property="stuempNo" size="13" maxlength="20"  value="${register.stuempNo}"/>
			     
		      </td>
		       <td nowrap="nowrap" ><bean:message key="special.name"/>
		         <html:text property="name" size="17" maxlength="20"  value="${register.name}"/>
			     
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
		          <html:text property="classroom" size="13" maxlength="20"  value="${register.classroom}" />
		      </td>
		      
		      <td ><bean:message key="spec.dept"/>
		        <html:select property="dept" value="${register.dept}" style="width:140px;"> 
		         <option value=""/></option>
		         <html:optionsCollection name="deptList" value="id" label="name"/> 
		        </html:select>
		     
		       
		      </td>
		      <td nowrap="nowrap"><bean:message key="spec.feeType"/>
			     <html:select property="feeType"  style="width:140px;" value="${register.feeType}"> 
			      <option value=""/></option>
			       <html:optionsCollection  name="Feetype" value="type" label="name"/>
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
	    <table width="94%" border="0" align="center" cellpadding="0"  cellspacing="0">
	       <tr>
	       	<td width="15%" nowrap="nowrap"  align="left">
			  <bean:message key="fee.state" />
		       <html:select property="feeState" value="${register.feeState}"   style="width:85px;">
		         <option value=""/></option>
                  <html:optionsCollection name="FeeState" value="flag"  label="info"/>
		      </html:select>  
		      </td>
		<td width="5%" align="left" nowrap="nowrap"><bean:message key="spec.bDate" /></td>
        <td width="8%" nowrap="nowrap"  align="left"><input type="text" name="begindate" value="${register.begindate}" size="9"  readonly="readonly"/></td>
        <td width="5%" nowrap="nowrap"  align="left"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
        <td width="7%" nowrap="nowrap"  align="left"><bean:message key="spec.eDate" /></td>
        <td width="10%" nowrap="nowrap"  align="left"><input type="text" name="enddate"  value="${register.enddate}" size="9"  readonly="readonly"/></td>
        <td width="25%" nowrap="nowrap"  align="left"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
		
	
		    <script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers	   :	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
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
