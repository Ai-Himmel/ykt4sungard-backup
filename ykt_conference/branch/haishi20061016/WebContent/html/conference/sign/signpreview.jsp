<%@ page import="java.util.Iterator" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="java.util.List" %>
<%@ page import="com.kingstargroup.conference.common.DateUtilExtend" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference" %>
<%@ page import="com.kingstargroup.conference.common.StringUtil" %>
<%@ page import="java.util.HashMap" %>
<%@ include file="/html/commons/init.jsp" %>

<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
<META http-equiv=REFRESH 
content=10;URL=<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&attendeesign=prev&selecttype=totle >
</head>
<body  bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<%
	TConference conference = (TConference)request.getAttribute("conference");
	int totleattendee = Integer.parseInt(request.getAttribute("totleattendee").toString());
	int signednum = Integer.parseInt(request.getAttribute("signednum").toString());
	int leavenum = Integer.parseInt(request.getAttribute("leavenum").toString());
	List leavelist = (List)request.getAttribute("leavelist");
	int replacenum = Integer.parseInt(request.getAttribute("replacenum").toString());
	List replacelist = (List)request.getAttribute("replacelist");
	int csignednum = Integer.parseInt(request.getAttribute("csignednum").toString());
	List csignedlist = (List)request.getAttribute("csignedlist");
	int unsignnum = Integer.parseInt(request.getAttribute("unsignnum").toString());
	List unsignlist = (List)request.getAttribute("unsignlist");
	float signRate = 0;
	if (totleattendee>0){
		signRate = signednum*10000/totleattendee/100.00f;
	}
	
%>
<table width="850" border="0" align="center" cellpadding="0" cellspacing="0">
<form id="SignPreview" name="SignPreview" action='<%=ContextUtil.getCtxPath(request)%>/preview.do' method=post >
  <tr> 
    <td height="42" align="center" valign="middle"><table width="100%" height="42" border="0" cellpadding="0" cellspacing="0">
        <tr align="center" valign="middle"> 
          <td width="35%" class="medium"><font color="#9B772B"><strong><%=conference.getConName()%></strong></font></td>
          <td align="left" class="medium">
          	<bean:message key="conference.confdate"/>&nbsp;:&nbsp;<%=conference.getConEnddate()%>-<%=DateUtilExtend.reFormatTime(conference.getConBegintime().toString()+"00")%>&nbsp; &nbsp;
          	<bean:message key="conference.assembly"/>&nbsp;:&nbsp;<%=GetDictionary.getAssemblyNameById(conference.getRoomId())%>&nbsp;&nbsp;
          </td>
          <td align="center" valign="middle" class="medium" style="color: red;font: bold">
          <a><bean:message key="analyse.attendper"/>[<%=signRate%>%]</a></td>
          
        </tr>
      </table></td>
  </tr>
  <tr> 
    <td align="center" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td>&nbsp;</td>
          <td width="300" height="25" align="center" valign="middle" class="medium">
          <a href='<%= ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=totle&attendeesign=sign'>
          <bean:message key="sign.signed"/>[<%=csignednum%>]</a></td>
          <td align="center" valign="middle">&nbsp;</td>
          <td width="300" align="center" valign="middle" class="medium">
          <a href='<%= ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=totle&attendeesign=unsign'>
          <bean:message key="sign.nosign"/>[<%=unsignnum%>]</a></td>
          <td align="center" valign="middle">&nbsp;</td>
          <td height="25" align="center" valign="middle" class="medium"><bean:message key="sign.preview"/></td>
          
        </tr>
        <tr> 
          <td width="7">&nbsp;</td>
          <td align="center" valign="top"><table width="100%" height="100%" border="0" cellpadding="0" cellspacing="0">
              <tr> 
                <td align="left" valign="top" bgcolor="#DEF2FD"> <table width="100%" border="0" cellpadding="0" cellspacing="0">
                    <tr> 
                      <td width="14"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop1.gif" width="14" height="14"></td>
                      <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop2.gif">
                      	<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop2.gif" width="5" height="14"></td>
                      <td width="14"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop3.gif" width="14" height="14"></td>
                    </tr>
                  </table></td>
              </tr>
              <tr> 
                <td align="left" valign="top"><table width="100%" height="100" border="0" cellpadding="0" cellspacing="0">
                    <tr> 
                      <td width="1" bgcolor="#8CD4FA"><img src="leftline.gif" width="1" height="3"></td>
                      <td height="398" align="center" valign="top" bgcolor="#DEF2FD">
                      <table width="90%" border="0" cellspacing="0" cellpadding="0">
                          <tr align="center" valign="middle"> 
                            <td class="medium"><bean:message key="attendee.custname"/></td>
                            <td class="medium"><bean:message key="attendee.dept"/></td>
                            <td class="medium"><bean:message key="sign.signtime"/></td>
                          </tr>
                          <%Iterator iter = csignedlist.iterator();
                            int i = 0;
                          	while (iter.hasNext()){
	                          	HashMap row = (HashMap)iter.next();
	                          	i++;
	                          	if (i>18){
	                          		break;
	                          	}
                          %>
                          <tr align="center" valign="middle"> 
                            <td class="medium"><%=row.get("cutName")%></td>
                            <td class="medium"><%=StringUtil.nullConvertToString(row.get("deptName")) %></td>
                            <td class="medium"><%=DateUtilExtend.reFormatTime(row.get("attendTime").toString())%></td>
                          </tr>
                          <%}%>
                        </table>
                        </td>
                      <td width="1" bgcolor="#8CD4FA"><img src="leftline.gif" width="1" height="3"></td>
                    </tr>
                  </table></td>
              </tr>
              <tr> 
                <td align="left" valign="top"><table width="100%" border="0" cellpadding="0" cellspacing="0">
                    <tr> 
                      <td width="14"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom1.gif" width="14" height="14"></td>
                      <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom2.gif">
                      	<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom2.gif" width="6" height="14"></td>
                      <td width="14"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom3.gif" width="14" height="14"></td>
                    </tr>
                  </table></td>
              </tr>
            </table></td>
          <td width="10" align="center" valign="middle">&nbsp;</td>
          <td height="387" align="center" valign="top" class="tdborder03"> 
            <table width="98%" border="0" cellspacing="0" cellpadding="0">
              <tr align="center" valign="middle"> 
                <td >&nbsp;</td>
                <td >&nbsp;</td>
                <td >&nbsp;</td>
              </tr>
              <tr align="center" valign="middle"> 
                <td class="medium"><bean:message key="attendee.custname"/></td>
                <td class="medium"><bean:message key="attendee.dept"/></td>
              </tr>
              <%Iterator iter2 = unsignlist.iterator();
                int i2 = 0;
              	while (iter2.hasNext()){
	              	HashMap row2 = (HashMap)iter2.next();
	              	i2++;
	              	if (i2>18){
	              	  break;
	              	}
              %>
              <tr align="center" valign="middle"> 
                <td class="medium"><%=row2.get("cutName")%></td>
                <td class="medium"><%=StringUtil.nullConvertToString(row2.get("deptName"))%></td>
              </tr>
              <%}%>
            </table>
          </td>
          <td width="10" align="center" valign="middle">&nbsp;</td>
          <td width="240" align="center" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr> 
                <td align="center" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellpadding="0" cellspacing="0">
                          <tr> 
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop1.gif" width="13" height="13"></td>
                            <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif">
                            <img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif" width="7" height="13"></td>
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop3.gif" width="13" height="13"></td>
                          </tr>
                        </table></td>
                    </tr>
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                          <tr> 
                            <td width="1" bgcolor="#BCE2F5"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif" width="1" height="2"></td>
                            <td align="center" valign="top" bgcolor="#F2F2F2"> 
                              <table width="98%" border="0" cellspacing="0" cellpadding="0">
                                <tr align="center" valign="middle"> 
                                  <td width="56%" class="medium"><bean:message key="sign.totle"/></td>
                                  <td align="left" class="medium" style="color: red;font: bold"><%=totleattendee%></td>
                                </tr>
                                <tr align="center" valign="middle"> 
                                  <td class="medium"><bean:message key="sign.fact"/></td>
                                  <td align="left" class="medium" style="color: red;font: bold"><%=signednum%></td>
                                </tr>
                                <tr align="center" valign="middle"> 
                                  <td class="medium"><bean:message key="sign.leave"/></td>
                                  <td align="left" class="medium" style="color: red;font: bold"><%=leavenum%></td>
                                </tr>
                                <tr align="center" valign="middle"> 
                                  <td class="medium"><bean:message key="sign.replace"/></td>
                                  <td align="left" class="medium" style="color: red;font: bold"><%=replacenum%></td>
                                </tr>
                                <tr align="center" valign="middle"> 
                                  <td class="medium"><bean:message key="sign.nosign"/></td>
                                  <td align="left" class="medium" style="color: red;font: bold"><%=unsignnum%></td>
                                </tr>
                              </table></td>
                            <td width="1" bgcolor="#BCE2F5"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif" width="1" height="2"><img src="rightline.gif" width="1" height="2"></td>
                          </tr>
                        </table></td>
                    </tr>
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellpadding="0" cellspacing="0">
                          <tr> 
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom1.gif" width="13" height="14"></td>
                            <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif">
                            <img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif" width="6" height="14"></td>
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom3.gif" width="13" height="14"></td>
                          </tr>
                        </table></td>
                    </tr>
                  </table></td>
              </tr>
              
              <tr>
	          <td align="center" valign="middle" class="medium">
	          <a href='<%= ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=totle&attendeesign=leave'>
	          <bean:message key="sign.leave"/>[<%=leavenum%>]</a></td>
	          </tr>
              
              <tr> 
                <td align="left"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellpadding="0" cellspacing="0">
                          <tr> 
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop1.gif" width="13" height="13"></td>
                            <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif">
                            <img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif" width="7" height="13"></td>
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop3.gif" width="13" height="13"></td>
                          </tr>
                        </table></td>
                    </tr>
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                          <tr> 
                            <td width="1" bgcolor="#BCE2F5"><img src="rightline.gif" width="1" height="2"></td>
                            <td height="95" align="center" valign="top" bgcolor="#F2F2F2"> 
                              <table width="98%" border="0" cellspacing="0" cellpadding="0">
                                <tr align="center" valign="middle"> 
                                  <td class="medium"><bean:message key="attendee.custname"/></td>
                                  <td class="medium"><bean:message key="attendee.dept"/></td>
                                </tr>
		                          <%Iterator iter3 = leavelist.iterator();
		                            int i3 = 0;
		                          	while (iter3.hasNext()){
			                          	HashMap row3 = (HashMap)iter3.next();
			                          	i3++;
			                          	if (i3>3){
			                          	  break;
			                          	}
		                          %>
		                          <tr align="center" valign="middle"> 
		                            <td class="medium"><%=row3.get("cutName")%></td>
		                            <td class="medium"><%=StringUtil.nullConvertToString(row3.get("deptName"))%></td>
		                          </tr>
		                          <%}%>
                              </table></td>
                            <td width="1" bgcolor="#BCE2F5"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif" width="1" height="2"><img src="rightline.gif" width="1" height="2"></td>
                          </tr>
                        </table></td>
                    </tr>
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellpadding="0" cellspacing="0">
                          <tr> 
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom1.gif" width="13" height="14"></td>
                            <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif">
                            <img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif" width="6" height="14"></td>
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom3.gif" width="13" height="14"></td>
                          </tr>
                        </table></td>
                    </tr>
                  </table></td>
              </tr>
              <tr> 
                <td height="25" align="center" class="medium"> 
                <a href='<%= ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=totle&attendeesign=replace'>
                <bean:message key="sign.replace"/>[<%=replacenum%>]</a></td>
              </tr>
              <tr>
                <td align="center" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellpadding="0" cellspacing="0">
                          <tr> 
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop1.gif" width="13" height="13"></td>
                            <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif">
                            <img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif" width="7" height="13"></td>
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop3.gif" width="13" height="13"></td>
                          </tr>
                        </table></td>
                    </tr>
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                          <tr> 
                            <td width="1" bgcolor="#BCE2F5"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif" width="1" height="2"></td>
                            <td height="95" align="center" valign="top" bgcolor="#F2F2F2"> 
                              <table width="98%" border="0" cellspacing="0" cellpadding="0">
                                <tr align="center" valign="middle"> 
                                  <td class="medium"><bean:message key="rep.name"/></td>
                                  <td class="medium"><bean:message key="attendee.dept"/></td>
                                  <td class="medium"><bean:message key="reped.name"/></td>
                                </tr>
		                          <%Iterator iter4 = replacelist.iterator();
		                            int i4 = 0;
		                         
		                          	while (iter4.hasNext()){
			                          	HashMap row4 = (HashMap)iter4.next();
			                          	i4++;
			                          	if (i4>3){
			                          	  break;
			                          	}
		                          %>
		                          <tr align="center" valign="middle"> 
		                            <td class="medium"><%=row4.get("repName")%></td>
		                            <td class="medium"><%=StringUtil.nullConvertToString(row4.get("deptName"))%></td>
		                            <td class="medium"><%=row4.get("cutName")%></td>		                            
		                          </tr>
		                          <%}%>
                              </table></td>
                            <td width="1" bgcolor="#BCE2F5"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif" width="1" height="2"><img src="rightline.gif" width="1" height="2"></td>
                          </tr>
                        </table></td>
                    </tr>
                    <tr> 
                      <td align="left" valign="top"><table width="100%" border="0" cellpadding="0" cellspacing="0">
                          <tr> 
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom1.gif" width="13" height="14"></td>
                            <td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif">
                            <img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif" width="6" height="14"></td>
                            <td width="13"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom3.gif" width="13" height="14"></td>
                          </tr>
                        </table></td>
                    </tr>
                  </table></td>
              </tr>
            </table></td>
        </tr>
      </table></td>
  </tr>
  </form>
</table>

</body>
