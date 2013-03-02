<%@ page pageEncoding="GBK"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TGroup"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TPifDictionary"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="com.kingstargroup.conference.common.StringUtil"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TDelegate"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa"%>
<script language="JavaScript"
	src="<%=ContextUtil.getCtxPath(request)%>/html/commons/js/option.js"></script>
<head>
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css" />
</head>

<%
	String oneattend = (String) request.getAttribute("oneattend");
	String username = GetterUtil.get((String) request.getSession()
			.getAttribute("username"), "");
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<form name="AttendeeAllotForm"
		action="<%=ContextUtil.getCtxPath(request)%>/attendeeallot.do"
		method="post">
		<input type="hidden" name="cmd" value="stage1">
		<input type="hidden" name="oneattend" value='<%=oneattend%>'>
		<input type="hidden" name="confid"
			value='<%=ParamUtil.getString(request, "confid")%>'>
		<input type="hidden" name="bindCust">
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="25" align="left" valign="middle"
					background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
					&nbsp;&nbsp;&nbsp;
					<span class="mediumwhite"><strong><bean:message
								key="attendee.allot.stage1" /> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="left" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td width="22%" align="center" valign="top">
					<table width="800" border="0" cellspacing="0" cellpadding="0">
						<tr align="center" valign="top">
							<td align="left">
								<font color="#FF0000"> <select name="groupsrclist"
										size="20" style="width: 190"
										onChange="javascript:ajaxsetvalue();">
										<%
											List groupList = GetDictionary.getGroupNameList(username);
											Iterator iter4 = groupList.iterator();
											while (iter4.hasNext()) {
												TGroup row = (TGroup) iter4.next();
										%>
										<option value="<%=row.getGroupId()%>">
											<%=row.getGroupName()%>
										</option>
										<%
										}
										%>
									</select> </font>
							</td>
							<td width="35%">
								<font color="#FF0000"> <aa:zone name="countriesList">
										<select name="custdestlist" size="20" style="width: 250"
											multiple
											ondblclick="transferOption(this.form.custdestlist, this.form.groupdestlist,this.form.delegray.value,this.form.custtype.value,false)">
											<%
													if (null != request.getAttribute("refreshlist")) {
													List test = (List) request.getAttribute("refreshlist");
													Iterator itertest = test.iterator();
													while (itertest.hasNext()) {
														HashMap rowtest = (HashMap) itertest.next();
											%>
											<option value="<%=rowtest.get("cutId")%>">
												<%=rowtest.get("cutName")%>
												&nbsp;&nbsp;
												<%=StringUtil.nullConvertToString(rowtest
									.get("duty"))%>
												&nbsp;&nbsp;
												<%=StringUtil.nullConvertToString(rowtest
									.get("deptName"))%>
											</option>
											<%
												}
												}
											%>

										</select>
									</aa:zone> </font>
							</td>
							<td width="8%" valign="middle">
								<p>
									<input name="Submit22" type="button" class="button_nor"
										value="<bean:message key="button.add"/>"
										onclick="transferOption(this.form.custdestlist, this.form.groupdestlist,this.form.delegray.value,this.form.custtype.value,false)">
								</p>
								<p>
									<input name="Submit23" type="button" class="button_nor"
										value="<bean:message key="button.move"/>"
										onclick="returnOption(this.form.custdestlist, this.form.groupdestlist,false)">
								</p>
								<p>
									<input name="Submit22" type="button" class="button_nor"
										value="<bean:message key="button.addall"/>"
										onclick="transferOption(this.form.custdestlist, this.form.groupdestlist,this.form.delegray.value,this.form.custtype.value,true)">
								</p>
								<p>
									<input name="Submit23" type="button" class="button_nor"
										value="<bean:message key="button.moveall"/>"
										onclick="returnOption(this.form.custdestlist, this.form.groupdestlist,true)">
								</p>
							</td>
							<td width="35%">
								<font color="#FF0000"> <select name="groupdestlist"
										size="20" style="width: 250" multiple
										ondblclick="returnOption(this.form.custdestlist, this.form.groupdestlist,false)">
										<%
												if (null != request.getAttribute("attendedList")) {
												List test = (List) request.getAttribute("attendedList");
												Iterator itertest = test.iterator();
												while (itertest.hasNext()) {
													HashMap rowtest = (HashMap) itertest.next();
										%>
										<option value="<%=rowtest.get("cutId")%>">
											<%=rowtest.get("cutName")%><%="-"%>
											<%=StringUtil.nullConvertToString(rowtest
									.get("duty"))%><%="-"%>
											<%=StringUtil.nullConvertToString(rowtest
									.get("deptName"))%>
										</option>
										<%
											}
											}
										%>
									</select> </font>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="800" border="0" cellspacing="0" cellpadding="0">
						<tr align="center" valign="top">
							<td>
								&nbsp;
							</td>
						</tr>
						<tr align="center" valign="top">
							<td align="left" valign="middle">
								<bean:message key="attendee.allot.delegray" />
								<select name="delegray" class="select01" style="width:100"
									onchange="javascript:dochange(this.form.groupdestlist,this.value);">
									<OPTION value="0">
									</OPTION>
									<%
										Iterator iter3 = GetDictionary.getDlgtList(username).iterator();
										while (iter3.hasNext()) {
											TDelegate dlgt = (TDelegate) iter3.next();
									%>
									<option value="<%=dlgt.getDlgtId()%>">
										<%=dlgt.getDlgtName()%>
									</option>
									<%
									}
									%>
								</select>
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<bean:message key="attendee.allot.custtype" />
								<select name="custtype" class="select01" style="width:100">
									<%
										Iterator iter2 = GetDictionary.getCustTypeList().iterator();
										while (iter2.hasNext()) {
											TPifDictionary custtype = (TPifDictionary) iter2.next();
									%>
									<option value="<%=custtype.getId().getDictValue()%>">
										<%=custtype.getDictCaption()%>
									</option>
									<%
									}
									%>
								</select>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top" class="tdborder02">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="right" valign="middle">
					<input name="Submit24" type="button" class="button_nor"
						value="<bean:message key="button.next"/>"
						onClick="javascript:setCmdValue();">
					&nbsp;&nbsp;
					<input name="Submit25" type="button" class="button_nor"
						value="<bean:message key="button.cancle"/>"
						onClick="javascript:renderCancelPage();">
				</td>
			</tr>
		</table>
	</form>
	<script language="javascript">
	function setCmdValue() {
		document.AttendeeAllotForm.cmd.value = 'stage2';
		document.all.bindCust.value=bindCust;
		document.AttendeeAllotForm.submit();
	}
	function renderCancelPage() {
		self.location = '<%=ContextUtil.getCtxPath(request)%>/conf/attendeeconflist.do';
	}
	
	function ajaxsetvalue(){
		document.all.bindCust.value=CustIds;
		ajaxAnywhere.submitAJAX();
		
	}	
	</script>

	<script language="javascript">
	var bindCustcount;
		bindCustcount = 0;
		bindCust = new Array(); 
		CustIds = new Array();
	<%	
		int m = 0;
		List attendedList = (List) request.getAttribute("attendedList");
		if(null!=attendedList){
		Iterator iteratt = attendedList.iterator();
		while (iteratt.hasNext()) {
			HashMap rowatt = (HashMap) iteratt.next();		
			String cutId=StringUtil.nullConvertToString(rowatt.get("cutId"));
			String cutName=StringUtil.nullConvertToString(rowatt.get("cutName"));
			String stuempNo=StringUtil.nullConvertToString(rowatt.get("stuempNo"));
			String duty=StringUtil.nullConvertToString(rowatt.get("duty"));
			String deptName=StringUtil.nullConvertToString(rowatt.get("deptName"));
			String delegray=StringUtil.nullConvertToString(rowatt.get("delegray"));
			String dlgtName=StringUtil.nullConvertToString(rowatt.get("dlgtName"));
			String attendeeType = StringUtil.nullConvertToString(rowatt.get("attendeeType"));
			String dictCaption = StringUtil.nullConvertToString(rowatt.get("dictCaption"));
	%>
		bindCust[<%=m%>]= new Array("<%=cutId%>","<%=cutName%>-<%=duty%>-<%=deptName%>","<%=delegray%>","<%=attendeeType%>"); 
		CustIds[<%=m%>]= new Array("<%=cutId%>"); 
	<%	
		m++;
		}
		}
	%>

	bindCustcount=<%=null==attendedList?0:attendedList.size()%> 
</script>

<script language="javascript">
function returnOption(e1,e2,all){
  	var src = e2.options;
  	var tgt = e1.options;
  	var items;
  	var index;
  	for (var i = src.length - 1; i >= 0; --i) {
    	if (all || src[i].selected) { 
			clone = uiCommon_cloneSelectOption(src[i]);
  			tgt.add(clone);
  			uiOptionReturn_putArrayItem(src[i].value);
  			src[i] = null;
  		}
  	}
}

function transferOption(e1,e2,dlgtId,custType,all){
  	var src = e1.options;
  	var tgt = e2.options;
  	var dlgt_id = dlgtId;
  	var cust_type = custType
  	for (var i = src.length - 1; i >= 0; --i) {
    	if (all || src[i].selected) { 
			clone = uiCommon_cloneSelectOption(src[i]);
  			tgt.add(clone);
  			uiOptionTransfer_putArrayItem(src[i].value,src[i].text,dlgt_id,cust_type);
  			src[i] = null;
  		}
  	}
}

function uiOptionReturn_putArrayItem(custId){
	var cust_id = custId;
	var i;
	for(i=0;i<bindCust.length;i++){	
	 	if(bindCust[i][0]==cust_id){	 	
	 		bindCust[i][0]="";
	 		bindCust[i][1]="";
	 		bindCust[i][2]="";
	 		bindCust[i][3]="";
	 		CustIds[i]="";
	 	}	 	
 }
}

//add classId to unbinddormitory's record   
//and add this record to binddormitory
//and delete this record from unbinddormitory
function uiOptionTransfer_putArrayItem(custId, content,dlgtId,attendeeType){
	var cust_id = custId;
	var all_content = content;
	var dlgt_id = dlgtId;
	var attendee_type = attendeeType;
	bindCust[bindCustcount] = new Array(cust_id,all_content,dlgt_id,attendee_type);
	CustIds[bindCustcount] = new Array(cust_id);
	bindCustcount++;
	
 }
// Returns the location (index) of opt in list. If not found, -1 is returned.
function uiCommon_findSelectOption(list, opt) {
  for(var i = 0; i < list.length; ++i) {
    if(list[i].value == opt.value &&
       list[i].text == opt.text) {
      return i;
    }
  }
  return -1;
}



function uiCommon_cloneSelectOption(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}

function dochange(e1,dlgtId){
	var tgt =e1.options;
	var dlgt_id=dlgtId;	
	for (var i = tgt.length - 1; i >= 0; --i) {
  			tgt[i] = null;
  	}
  	if(dlgt_id==0){
	  	for(var j=0;j<bindCust.length;j++){
	  		document.all.groupdestlist.options[document.all.groupdestlist.length]= new Option(bindCust[j][1],bindCust[j][0]);
	  	}
  	}else{
  		for(var k=0;k<bindCust.length;k++){
  			if(bindCust[k][2]==dlgt_id){
	  			document.all.groupdestlist.options[document.all.groupdestlist.length]= new Option(bindCust[k][1],bindCust[k][0]);
	  		}
	  	}
  	}
}
</script>


</body>

