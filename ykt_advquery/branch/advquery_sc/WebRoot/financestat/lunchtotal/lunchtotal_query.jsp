<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp" %>
<%@ include file="permission.jsp" %>
<%@ page import ="com.kingstargroup.advquery.hibernate.util.LunchUtil"  %>
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
    <title><bean:message key="system.name"/></title>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css"/>
</head>
    <%String beginDate = session.getAttribute("enddate42d").toString();%>
    <%String endDate = session.getAttribute("enddate42d").toString();%>
    <%if(request.getAttribute("beginDate")!=null){
    		beginDate = request.getAttribute("beginDate").toString();
    	}
      if(request.getAttribute("endDate")!=null){
      	endDate = request.getAttribute("endDate").toString();
      }
     %>
    <%
 
  String tradedept="";
   if (null!=session.getAttribute("tradedept")){
  	tradedept = session.getAttribute("tradedept").toString();
  }
 
   String lunchtype="";
   if (null!=session.getAttribute("lunchtype")){
  	lunchtype = session.getAttribute("lunchtype").toString();
  }
%>
<table width="100%" border="0" align="center" cellpadding="0"
       cellspacing="0">
    <tr>
        <form action="<%= ContextUtil.getCtxPath(request)%>/financestat/lunchtotal_queryresult.do"
              name="lunchDetailForm" method="post">
            <td>
                <table width="98%" border="0" align="center" cellpadding="0"
                       cellspacing="0">
                    <tr>
                        <td height="40">
                            <table width="96%" border="0" align="center" cellpadding="0"
                                   cellspacing="0">
                                <tr>
                                   <td height="25" align="right" nowrap="nowrap"><bean:message
                                            key="lunch.query.dept"/></td>
                                    <td nowrap="nowrap"><input type="text" name="tradedept" value="<%=tradedept%>" /></td>
                                    <td></td>                        
                                     <td height="25" align="right" nowrap="nowrap"><bean:message    key="lunch.query.type"/></td>
                                    <td nowrap="nowrap">
                                       <select name="lunchtype" >
                                        <option value="">--------</option>
                                        <option value="1" <%if("1".equals(lunchtype)) out.print("selected"); %>><bean:message    key="lunch.query.type1"/></option>
                                        <option value="2" <%if("2".equals(lunchtype)) out.print("selected"); %>><bean:message    key="lunch.query.type2"/></option>
                                        <option value="3" <%if("3".equals(lunchtype)) out.print("selected"); %>><bean:message    key="lunch.query.type3"/></option>
                                       </select>
                                       
                                    </td>
                                </tr>
                                <tr>
                                    <td width="8%" align="right" nowrap="nowrap"><bean:message
                                            key="query.begindate"/></td>
                                    <td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate%>"/></td>
                                    <td width="20%" nowrap="nowrap"><a href="#"><img
                                            src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate"/></a></td>
                                    <td width="8%" nowrap="nowrap"><bean:message key="query.enddate"/></td>
                                    <td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate%>"/></td>
                                    <td width="20%" nowrap="nowrap"><a href="#"><img
                                            src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate"/></a></td>
                                    <script language="JavaScript">

                                        Calendar.setup({
                                            inputField     :    "begindate",     // id of the input field
                                            weekNumbers       :    <%=GetProperty.getProperties("format.byweek",getServletContext())%>,
                                            button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
                                            ifFormat       :    "<%=GetProperty.getProperties("format.date",getServletContext())%>",
                                            align          :    "Tr",           // alignment (defaults to "Bl")
                                            singleClick    :    true
                                        });

                                        Calendar.setup({
                                            inputField     :    "enddate",     // id of the input field
                                            weekNumbers        :    <%=GetProperty.getProperties("format.byweek",getServletContext())%>,
                                            button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
                                            ifFormat       :    "<%=GetProperty.getProperties("format.date",getServletContext())%>",
                                            align          :    "Tr",           // alignment (defaults to "Bl")
                                            singleClick    :    true
                                        });
                                    </script>

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
        </form>
    </tr>
</table>
