<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp" %>
<%@ include file="permission.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<%request.setCharacterEncoding("GBK"); %>
<head>
    <title><bean:message key="system.name"/></title>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css"/>
</head>
 <%
  String stuempno="";
   if (null!=session.getAttribute("stuempno")){
  	stuempno = session.getAttribute("stuempno").toString();
  }
  String tradedept="";
   if (null!=session.getAttribute("tradedept")){
  	tradedept = session.getAttribute("tradedept").toString();
  }
  String lunchtype="";
   if (null!=session.getAttribute("lunchtype")){
  	lunchtype = session.getAttribute("lunchtype").toString();
  }
%>
 <html:form action="/financestat/lunchperson_queryresult.do"
            method="post">
<table width="100%" border="0" align="center" cellpadding="0"
       cellspacing="0">
    <tr>
            <td>
                <table width="98%" border="0" align="center" cellpadding="0"
                       cellspacing="0">
                    <tr>
                        <td height="40">
                            <table width="96%" border="0" align="center" cellpadding="0"
                                   cellspacing="0">
                                <tr>
                                    <td height="25" align="right" nowrap="nowrap"><bean:message
                                            key="lunch.query.stuempno"/>&nbsp;</td>
                                    <td nowrap="nowrap">
                                    <input name="stuempno" value="<%=stuempno%>" />
                                    </td>
                                    <td></td>
                                    <td height="25" align="right" nowrap="nowrap"><bean:message
                                            key="lunch.query.dept"/></td>
                                    <td nowrap="nowrap">
                                    <input name="tradedept" value="<%=tradedept %>"/>
                                  
                                    </td>
                                  </tr>
                                    
                                  <tr>
                                  
                                    <td height="25" align="right" nowrap="nowrap"><bean:message    key="lunch.query.type"/></td>
                                    <td nowrap="nowrap">
                                       <select name="lunchtype">
                                        <option value="">--------</option>
                                        <option value="1" <%if("1".equals(lunchtype)) out.print("selected"); %>><bean:message    key="lunch.query.type1"/></option>
                                        <option value="2" <%if("2".equals(lunchtype)) out.print("selected"); %>><bean:message    key="lunch.query.type2"/></option>
                                        <option value="3" <%if("3".equals(lunchtype)) out.print("selected"); %>><bean:message    key="lunch.query.type3"/></option>
                                       </select>
                                    </td>
                                    <td></td>
                                     <td height="25" align="right" nowrap="nowrap">&nbsp;</td>
                                    <td nowrap="nowrap">&nbsp;
                                    </td>
                                </tr>
                            </table>
                        </td>
                    </tr>
                </table>
                <table width="98%" border="0" align="center" cellpadding="0"
                       cellspacing="0" bgcolor="#f8f8f8">
                    <tr>
                        <td height="30">
                            <table width="96%" border="0" align="center" cellpadding="0"
                                   cellspacing="0">
                                <tr>
                                    <td width="66%" class="red_text"><bean:message key="system.note"/></td>
                                    <td width="34%" align="center">
                                        <button onclick="document.forms[0].submit();"><bean:message key="btn.query"/></button>
                                        <button onclick="document.forms[0].reset();"><bean:message key="btn.clear"/></button>
                                    </td>
                                </tr>
                            </table>
                        </td>
                    </tr>
                </table>
            </td>
    </tr>
</table>
</html:form>