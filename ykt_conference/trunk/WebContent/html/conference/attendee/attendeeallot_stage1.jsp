<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="java.util.List" %>
<%@ page import="com.kingstargroup.conference.common.ParamUtil" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TGroup" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TPifDictionary" %>
<%@ page import="java.util.HashMap" %>
<%@ page import="com.kingstargroup.conference.common.StringUtil" %>
<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/option.js"></script>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
</head>
<%List result = (List) request.getAttribute("result");%>
<script>
    ajaxAnywhere.formName = "AttendeeAllotForm";
</script>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form name="AttendeeAllotForm" id="AttendeeAllotForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeeallot.do" method=post >

	<%String groupliststring = ParamUtil.getString(request, "groupliststring");%>
	<input type=hidden name=cmd value="stage1">
	<input type=hidden name=confid value='<%=ParamUtil.getString(request,"confid")%>'>
	<input type=hidden name=devliststring value='<%=ParamUtil.getString(request,"devliststring")%>'>
	<input type=hidden name=queryliststring value='<%=ParamUtil.getString(request,"queryliststring")%>'>
	<input type=hidden name=groupliststring value="<%= groupliststring%>">
  <table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
      <span class="mediumwhite"><strong><bean:message key="attendee.allot.stage1"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td width="22%" align="center" valign="top" ><table width="800" border="0" cellspacing="0" cellpadding="0">
          <tr align="center" valign="top"> 
            <td align="left"><font color="#FF0000"> 
              <select name="groupsrclist" size="10" style="width: 190" 
              	onChange="ajaxAnywhere.submitAJAX();">
				<%
					List groupList = new GetDictionary().getGroupNameList();
					Iterator iter4 = groupList.iterator();
					while (iter4.hasNext()){
						TGroup row = (TGroup)iter4.next();
				%>
				<option value="<%=row.getGroupId()%>"><%=row.getGroupName()%></option>
				<%}%>
              </select>
              </font></td>
            <td width="35%" ><font color="#FF0000"> 
            <aa:zone name="countriesList">            
              <select name="custdestlist" size="10"  style="width: 250" multiple 
              	ondblclick="transferOption(this.form.custdestlist, this.form.groupdestlist,false)" >
				<%
					if (null!=request.getAttribute("refreshlist")){
					List test = (List) request.getAttribute("refreshlist");
					Iterator itertest = test.iterator();
					while (itertest.hasNext()){
						HashMap rowtest = (HashMap)itertest.next();
				%>
       			<option value="<%=rowtest.get("cutId")%>" ><%=rowtest.get("cutName")%>&nbsp;&nbsp;
       				<%=StringUtil.nullConvertToString(rowtest.get("duty"))%>&nbsp;&nbsp;
       				<%=StringUtil.nullConvertToString(rowtest.get("deptName"))%></options>
				<%}}%>            
			  </select>
            </aa:zone>
              </font></td>
            <td width="8%" valign="middle">
              <p> 
                <input name="Submit22" type="button" class="button_nor" value="<bean:message key="button.add"/>" 
                	onclick="transferOption(this.form.custdestlist, this.form.groupdestlist,false)"  >
              </p>
              <p> 
                <input name="Submit23" type="button" class="button_nor" value="<bean:message key="button.move"/>" 
                	onclick="returnOption(this.form.groupdestlist, this.form.custdestlist,false)" >
              </p>
              <p> 
                <input name="Submit22" type="button" class="button_nor" value="<bean:message key="button.addall"/>" 
                	onclick="transferOption(this.form.custdestlist, this.form.groupdestlist,true)">
              </p>
              <p> 
                <input name="Submit23" type="button" class="button_nor" value="<bean:message key="button.moveall"/>" 
                	onclick="returnOption(this.form.groupdestlist, this.form.custdestlist,true)">
              </p>
            </td>
            <td width="35%" ><font color="#FF0000"> 
              <select name="groupdestlist" size="10" style="width: 250" multiple 
              		ondblclick="returnOption(this.form.groupdestlist, this.form.custdestlist,false)" >
              </select>
              </font></td>
          </tr>
        </table></td>
    </tr>
    <tr>
      <td align="center" valign="top" ><table width="800" border="0" cellspacing="0" cellpadding="0">
          <tr align="center" valign="top">
            <td>&nbsp;</td>
          </tr>
          <tr align="center" valign="top">
            <td align="left" valign="middle"><bean:message key="attendee.allot.delegray"/>
              <input name=delegray class="input_box"  maxlength=50>
              	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<bean:message key="attendee.allot.custtype"/> 
              	<select name=custtype class="select01" style="width:100" >
                <%
                	Iterator iter2 = GetDictionary.getCustTypeList().iterator();
                	while (iter2.hasNext()){
                		TPifDictionary custtype = (TPifDictionary)iter2.next();
                %>
                <option value="<%=custtype.getId().getDictValue()%>"><%=custtype.getDictCaption()%></option>
                <%}%>
              </select></td>
          </tr>
          
          <tr align="center" valign="top"> 
            <td align="left" valign="middle">
              <input type="checkbox" name="ifquery" value="checkbox"
		        <c:if test='<%= !ParamUtil.getString(request, "ifquery").equals("")%>'>
		        checked
		        </c:if>
              >
              <bean:message key="attendee.allot.continue"/> </td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td align="center" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="center" valign="top" class="tdborder02" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" >
      <input name="Submit24" type="button" class="button_nor" 
      		value="<bean:message key="button.next"/>" onClick="javascript:setCmdValue('next');" > 
        &nbsp;&nbsp; 
        <input name="Submit25" type="button" class="button_nor" 
        	value="<bean:message key="button.cancle"/>" onClick="javascript:renderCancelPage();" ></td>
    </tr>
</table>
</form>
<script>
	function setCmdValue(cmd) {
		var grouplist="";
		if (cmd == 'next') {
      			if (document.AttendeeAllotForm.ifquery.checked) {
      				cmd = 'stage2';
      			} else {
      				cmd = 'stage3';
      			}
		}
		if (document.AttendeeAllotForm.ifquery.checked) {
			document.AttendeeAllotForm.queryliststring.value = "";
		}
		document.AttendeeAllotForm.cmd.value = cmd;
		for (i=0;i<document.AttendeeAllotForm.groupdestlist.options.length;i++){
			grouplist=grouplist+document.AttendeeAllotForm.groupdestlist.options[i].value+",";
		}
		document.AttendeeAllotForm.groupliststring.value = grouplist;
		document.AttendeeAllotForm.submit();
	}
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/attendeeconflist.do';
	}
	
</script>
</body>

