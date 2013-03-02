<%@ include file="/html/commons/init.jsp" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TGroup" %>
<%@ page import="com.kingstargroup.conference.common.StringUtil" %>
<%@ page import="java.util.HashMap" %>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/option.js"></script>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<%	List result = (List) request.getAttribute("result");
	String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");

%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form name="AttendeeGroupForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeegroup.do" method=post >
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<%String groupedlist="";%>
	<input type=hidden name=cmd value="query">
	<input type=hidden name=groupedlist value='<%=groupedlist%>'>
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;
      	<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message key="attendee.group.title"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="left" valign="top" ><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custno"/></td>
            <td width="35%" align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=custno class="input_box"  maxlength=50 style="width:150"></td>
            <td width="15%" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custname"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=custname class="input_box"  maxlength=50 style="width:150"></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.duty"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=duty class="input_box"  maxlength=50 style="width:150"></td>
            <td align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.dept"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=dept class="select01" style="width:150" >
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
      <td height="35" align="right" valign="middle" >
      	<input name="Submit" type="button" class="button_nor" 
      		value="<bean:message key="button.query"/>" 
      		onclick="javascript:setCmdValue('query');">
      </td>
    </tr>
    <tr> 
      <td align="left" valign="top" class="tdborder02" >&nbsp;</td>
    </tr>
    <tr> 
		<td align="center" valign="top">
			<table width="800" border="0" cellspacing="0" cellpadding="0">
          <tr align="center" valign="top"> 
            <td width="45%"><font color="#FF0000"> 
              <select name="scrlist" size="10" style="width:350" multiple ondblclick="transferOption(this.form.scrlist, this.form.destlist,false)" >
              <%
              	if (null!=result){
              	Iterator iter3 = result.iterator();
              	while (iter3.hasNext()){
              		HashMap row = (HashMap)iter3.next();
              %>
                <option value="<%=row.get("cutId")%>"><%= row.get("cutName")%>&nbsp;&nbsp;
                <%= StringUtil.nullConvertToString(row.get("dutyName"))%>&nbsp;&nbsp;
                <%= StringUtil.nullConvertToString(row.get("deptName"))%>&nbsp;&nbsp;
                <%= StringUtil.nullConvertToString(row.get("duty"))%></option>
              <%}}%>
              </select>
              </font>
            </td>
            <td width="10%" valign="middle"><p> 
                <input name="Submit22" type="button" class="button_nor" value="<bean:message key="button.add"/>" 
                	onclick="transferOption(this.form.scrlist, this.form.destlist,false)">
              </p>
              <p> 
                <input name="Submit23" type="button" class="button_nor" value="<bean:message key="button.move"/>" 
                	onclick="returnOption(this.form.destlist, this.form.scrlist,false)">
              </p></td>
            <td width="45%"><font color="#FF0000"> 
              <select name="destlist" size="10" style="width:350" multiple ondblclick="returnOption(this.form.destlist, this.form.scrlist,false)" >
              </select>
              </font>
            </td>
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
      <td align="left" valign="middle"><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.groupname"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"> <select name=groupname class="select01" onChange="changeCounty()" style="width:150" >
				<%
					List groupList = new GetDictionary().getGroupNameList(username);
					Iterator iter4 = groupList.iterator();
					while (iter4.hasNext()){
						TGroup row = (TGroup)iter4.next();
				%>
				<option value="<%=row.getGroupId()%>"><%=row.getGroupName()%></option>
				<%}%>
              </select>
            </td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td height="40" align="right" valign="middle"> <input name="Submit" type="button" class="button_nor" value="<bean:message key="button.group"/>" onclick="javascript:setCmdValue('group');">
        &nbsp;&nbsp;&nbsp; </td>
    </tr>
	</table>
</form>
<script>
  	function setCmdValue(cmd) {      		
		var groupedlist="";
  		document.AttendeeGroupForm.cmd.value = cmd;
		for (i=0;i<document.AttendeeGroupForm.destlist.options.length;i++){
			groupedlist=groupedlist+document.AttendeeGroupForm.destlist.options[i].value+",";
		}
		document.AttendeeGroupForm.groupedlist.value = groupedlist;
  		document.AttendeeGroupForm.submit();
  	}   
	function sort(e1){ 
		var ar=new Array();
		for (var i=0;i<e1.length;i++){
			ar[ar.length] = new Array(e1.options[i].text,e1.options[i].value);
		}
		ar.sort(cmd);
		e1.length=0;
		for (var j=0;j<ar.length;j++){
			e1.options[j]=new Option(ar[j][0],ar[j][1]);
		}
	}
	
	function startSort(){
		var a=document.getElementById('s').value;
		a=a.split(',')
		a.sort(function(a,b){return a.localeCompare(b)});
		document.getElementById('r2').value=a;
	}
	function cmd(A,B){ 
		execScript('c1=(ASC(\"'+A+'\"))','vbscript'); 
		execScript('c2=(ASC(\"'+B+'\"))','vbscript'); 
		if (((c1>0)&&(c2>0))||((c1<0)&&(c2<0))) return (c1-c2);
		else {return c1>c2?-1:1;}
	}
  	   	
</script>
</body>
