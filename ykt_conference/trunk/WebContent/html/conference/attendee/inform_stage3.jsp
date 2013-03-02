<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.common.ParamUtil" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TCifDeptfull" %>
<%@ page import="com.kingstargroup.conference.common.StringUtil" %>
<%@ page import="java.util.HashMap" %>
<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/option.js"></script>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<html:base/>
</head>
<%List result = (List) request.getAttribute("result");%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<script>
    ajaxAnywhere.formName = "AttendeeInformForm";
</script>
<form name="AttendeeInformForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeeinform.do" method=post >
	<%String queryliststring=ParamUtil.getString(request,"queryliststring");%>
	<input type=hidden name=cmd value="stage3">
	<input type=hidden name=confid value='<%=ParamUtil.getString(request,"confid")%>'>
	<input type=hidden name=ifquery value='<%= ParamUtil.getString(request, "ifquery")%>'>
	<input type=hidden name=gselect value='<%= ParamUtil.getString(request, "gselect")%>'>
	<input type=hidden name=groupliststring value='<%=ParamUtil.getString(request,"groupliststring")%>'>
	<input type=hidden name=queryliststring value='<%=queryliststring%>'>
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;
      	<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message key="attendee.allot.stage2"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="left" valign="top" ><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custno"/></td>
            <td width="35%" align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=custno class="input_box" maxlength=50 style="width:150"></td>
            <td width="15%" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custname"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=custname class="input_box" maxlength=50 style="width:150"></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.duty"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=duty class="input_box" maxlength=50 style="width:150"></td>
            <td align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.dept"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=dept class="select01" style="width:150">
				<option >-</option>
				<%
					List deptList = new GetDictionary().getDeptList();
					Iterator iter2 = deptList.iterator();
					while (iter2.hasNext()){
						HashMap row = (HashMap)iter2.next();
				%>
				<option value="<%=row.get("deptCode")%>"><%=row.get("deptName")%></option>
				<%}%>
              </select></td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td height="35" align="right" valign="middle" ><input name="Submit" type="button" class="button_nor" 
      		value="<bean:message key="button.query"/>" onclick="ajaxAnywhere.submitAJAX();"></td>
    </tr>
    <tr> 
      <td align="left" valign="top" class="tdborder02" >&nbsp;</td>
    </tr>
    <tr> 
		<td align="center" valign="top">
			<table width="800" border="0" cellspacing="0" cellpadding="0">
          <tr align="center" valign="top"> 
            <td width="45%"><font color="#FF0000"> 
            <aa:zone name="hjwquerylist">            
              <select name="querysrclist" size="10" style="width:350" multiple 
              	ondblclick="transferOption(this.form.querysrclist, this.form.querydestlist,false)" >
              <%
              	if (null!=result){
              	Iterator iter3 = result.iterator();
              	while (iter3.hasNext()){
              		HashMap row = (HashMap)iter3.next();
              %>
                <option value="<%=row.get("cutId")%>">
                <%= row.get("cutName")%>&nbsp;&nbsp;
                <%= row.get("deptName")%>&nbsp;&nbsp;
                 <%= StringUtil.nullConvertToString(row.get("duty"))%></option>
              <%}}%>
              </select>
            </aa:zone>
              </font>
            </td>
            <td width="10%" valign="middle">
              <p> 
                <input name="Submit22" type="button" class="button_nor" value="<bean:message key="button.add"/>" 
                onclick="transferOption(this.form.querysrclist, this.form.querydestlist,false)">
              </p>
              <p> 
                <input name="Submit23" type="button" class="button_nor" value="<bean:message key="button.move"/>" 
                onclick="returnOption(this.form.querydestlist, this.form.querysrclist,false)">
              </p>
              <p> 
                <input name="Submit22" type="button" class="button_nor" value="<bean:message key="button.addall"/>" 
                onclick="transferOption(this.form.querysrclist, this.form.querydestlist,true)">
              </p>
              <p> 
                <input name="Submit23" type="button" class="button_nor" value="<bean:message key="button.moveall"/>" 
                onclick="returnOption(this.form.querydestlist, this.form.querysrclist,true)">
              </p>
            </td>
            <td width="45%"><font color="#FF0000"> 
              <select name="querydestlist" size="10" style="width:350" multiple 
              	ondblclick="returnOption(this.form.querydestlist, this.form.querysrclist,false)">
              </select>
              </font></td>
          </tr>			
			</table>
		</td>
    </tr>
    <tr> 
      <td align="center" valign="top">&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" class="tdborder02">&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle">
      	<input name="Submit24" type="button" class="button_nor" value="<bean:message key="button.back"/>" 
      		onClick="javascript:setCmdValue('back');" >&nbsp;&nbsp; 
      	<input name="Submit252" type="button" class="button_nor" value="<bean:message key="button.next"/>" 
      		onClick="javascript:setCmdValue('next');" >&nbsp;&nbsp; 
      	<input name="Submit2522" type="button" class="button_nor" value="<bean:message key="button.cancle"/>" 
      		onClick="javascript:renderCancelPage();" > 
      </td>
    </tr>
	</table>
</form>
<script>
  	function setCmdValue(cmd) {      		
		var querylist="";
		if (cmd == 'next') {
			cmd = 'stage4';
		}else if (cmd=='back'){
			cmd = 'stage2'
		}
  		document.AttendeeInformForm.cmd.value = cmd;
		for (i=0;i<document.AttendeeInformForm.querydestlist.options.length;i++){
			querylist=querylist+document.AttendeeInformForm.querydestlist.options[i].value+",";
		}
		document.AttendeeInformForm.queryliststring.value = querylist;
  		document.AttendeeInformForm.submit();
  	}   
  	   	
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/informconflist.do';
	}
</script>
</body>
