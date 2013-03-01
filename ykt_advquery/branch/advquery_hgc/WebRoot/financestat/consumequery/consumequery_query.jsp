<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ page import="com.kingstargroup.advquery.cuttype.TCifCuttypefee" %>
<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.CutTypeUtil" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<%@ include file="permission.jsp" %>
<script src="<c:url value="/js/option.js"/>" type="text/javascript"></script>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<%String bdate70 = session.getAttribute("bdate70").toString();%>
<%String edate70 = session.getAttribute("edate70").toString();%>
<%String operCode = session.getAttribute("username").toString();%>
<%String classNo = "";
	if (null!=session.getAttribute("classNo")){ 
		classNo = session.getAttribute("classNo").toString();
	}
%>
<%String bStuempNo = "";
	if (null!=session.getAttribute("bStuempNo")){ 
		bStuempNo = session.getAttribute("bStuempNo").toString();
	}
%>
<%String eStuempNo = "";
	if (null!=session.getAttribute("eStuempNo")){ 
		eStuempNo = session.getAttribute("eStuempNo").toString();
	}
%>
<%String bconsumeRange = "0";
	if (null!=session.getAttribute("bqconsumeRange")){ 
		bconsumeRange = session.getAttribute("bqconsumeRange").toString();
	}
%>
<%String econsumeRange = "0";
	if (null!=session.getAttribute("eqconsumeRange")){ 
		econsumeRange = session.getAttribute("eqconsumeRange").toString();
	}
%>

<%String sex = "0";
	if (null!=session.getAttribute("sex")){ 
		sex = session.getAttribute("sex").toString();
	}
%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/consumequeryquery/result.do" name=consumeQueryform method=post >

	<td>
	
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="spec.bDate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=bdate70%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><div align="right"><bean:message key="spec.eDate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=edate70%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
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
		
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.deptNo"/></td>
				<td nowrap="nowrap">
        			<select name="deptNo" style="width=155">
        			<OPTION value="">-</OPTION>
					<%
						List deptList = new GetQueryConListDAO().getDeptTreeList();
						String deptCode = "";
						if (null!=session.getAttribute("deptNo")){
							deptCode = session.getAttribute("deptNo").toString();
						}
						Iterator iter = deptList.iterator();
						while (iter.hasNext()){
							Object[] row = (Object[])iter.next();
							String deptName= "";
							deptName = row[2].toString().replaceAll(" ","&nbsp;");
							if (deptCode.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=deptName%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=deptName%></option>
					<%}}%>
				</select>
				</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.specNo"/></td>
				<td nowrap="nowrap">
        			<select name="specNo" style="width=155" >
        			<OPTION value="">-</OPTION>
					<%
						List specList = new GetQueryConListDAO().getSpecialityList();
						String specNo = "";
						if (null!=session.getAttribute("specNo")){
							specNo = session.getAttribute("specNo").toString();
						}
						Iterator iter1 = specList.iterator();
						while (iter1.hasNext()){
							Object[] row = (Object[])iter1.next();
							if (specNo.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				</select>
				</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.class"/></td>
				<td nowrap="nowrap"><input type="text" name="classNo" value="<%=classNo%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.custType"/></td>
				<td nowrap="nowrap"><select name="custType" style="width=155">
		        <OPTION value="0">-</OPTION>
		        <%
		        	List cuttype = CutTypeUtil.getCutType();
		        	String typeid = "";
		        	if (null!=session.getAttribute("custType")){ 
		        		typeid = session.getAttribute("custType").toString();
		        	}
		        	Iterator cutiter = cuttype.iterator();
		        	while (cutiter.hasNext()){
		        		TCifCuttypefee cut = (TCifCuttypefee)cutiter.next();
		        		if (typeid.equals(cut.getCutType().toString())){
		        %>
					<option value="<%=cut.getCutType()%>" selected="selected"><%=cut.getTypeName()%></option>
					<%}else{%>
					<option value="<%=cut.getCutType()%>"><%=cut.getTypeName()%></option>
					<%}}%>
		        </select>
				</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="analyse.cardtype"/></td>
				<td nowrap="nowrap"><select name="cardType" style="width=155">
        			<OPTION value="0">-</OPTION>
					<%
						List cardTypeList = new GetQueryConListDAO().getCardTypeList();
						String cardType = "";
						if (null!=session.getAttribute("cardType")){
							cardType = session.getAttribute("cardType").toString();
						}
						Iterator iter2 = cardTypeList.iterator();
						while (iter2.hasNext()){
							Object[] row = (Object[])iter2.next();
							if (cardType.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				</select>

				</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="analyse.serialtype"/></td>
				<td nowrap="nowrap"><select name="serialType" style="width=155">
				<OPTION value="">-</OPTION>
					<%
						List serialTypeList = new GetQueryConListDAO().getSerialTypeList();
						String serialType = "";
						if (null!=session.getAttribute("qserialType")){
							serialType = session.getAttribute("qserialType").toString();
						}
						Iterator iter3 = serialTypeList.iterator();
						while (iter3.hasNext()){
							Object[] row = (Object[])iter3.next();
							if (serialType.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else if ("930031".equals(row[0])){%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				
		        </select>
				
				</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="ana.busi"/></td>
				<td nowrap="nowrap">
				<select name="shopid" style="width = 155">
				<OPTION value="0">-</OPTION>
				<%List result = new GetQueryConListDAO().getShopTreeList(operCode);//getShopList(operCode);
					int shopId = 0;
					if (null!=session.getAttribute("shopid")){
						shopId = Integer.parseInt(session.getAttribute("shopid").toString());
					}
					Iterator iter4 = result.iterator();
					while (iter4.hasNext()){
						Object[] row = (Object[])iter4.next();
						String shopName = "";
						shopName = row[1].toString().replaceAll(" ","&nbsp;");
						if (shopId==Integer.parseInt(row[0].toString())){
				%>
					<option value="<%=row[0]%>" selected="selected"><%=shopName%></option>
					
				<%}else{%>
					<option value="<%=row[0]%>"><%=shopName%></option>
				<%}}%>
				</select>
				</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="analyse.consumeRange"/></td>
				<td nowrap="nowrap">
				<input style="width=67" type="text" name="bconsumeRange" onkeypress="return checkNumber(event);" value="<%=bconsumeRange%>">
				->
				<input style="width=66" type="text" name="econsumeRange" onkeypress="return checkNumber1(event);" value="<%=econsumeRange%>">
				</td>				
				<td nowrap="nowrap">&nbsp;</td>				
			</tr>
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.stuemprange"/></td>
				<td nowrap="nowrap">
				<input style="width=71" type="text" name="bStuempNo" value="<%=bStuempNo%>">
				-
				<input style="width=71" type="text" name="eStuempNo" value="<%=eStuempNo%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
				
				<td height="25" align="right" nowrap="nowrap"><bean:message key="query.sex"/></td>
				<td nowrap="nowrap">
				<select name="sex" style="width = 155">
				<OPTION value="0">-</OPTION>
				<%if ("1".equals(sex)){%>
					<option value="1" selected="selected"><bean:message key="spec.man"/></option>
				<%}else{%>
					<option value="1"><bean:message key="spec.man"/></option>
				<%}
					if ("2".equals(sex)){
				%>
					<option value="2" selected="selected"><bean:message key="spec.women"/></option>
				<%}else{%>
					<option value="2"><bean:message key="spec.women"/></option>
				<%}%>
				</select>
				</td>
				
			</tr>
			
		</table>
		</td>
	</tr>
</table>

<%String stuempNo="";%>
<input type=hidden name=stuempNo value='<%=stuempNo%>'>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="100%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="28%" class="red_text"><bean:message key="system.note" /></td>
				<td width="60%" align="center">				
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				&nbsp;&nbsp;
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</form>
</tr></table>
<script type="text/javascript">  
function checkNumber(e) {
	var key = window.event ? e.keyCode : e.which;
	var keychar = String.fromCharCode(key);
	var el = document.getElementById('bconsumeRange');
	//var msg = document.getElementById('msg');
	reg = /^\d*(\.\d*)?$/;
	var result = reg.test(keychar);
 	if(!result){
 		return false;
	}else{
		return true;
	}
}
function checkNumber1(e) {
	var key = window.event ? e.keyCode : e.which;
	var keychar = String.fromCharCode(key);
	var el = document.getElementById('econsumeRange');
	//var msg = document.getElementById('msg');
	reg = /^\d*(\.\d*)?$/;
	var result = reg.test(keychar);
 	if(!result){
 		return false;
	}else{
		return true;
	}
}

</script> 
