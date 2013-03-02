<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ page import="com.kingstargroup.advquery.cuttype.TCifCuttypefee" %>
<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.CutTypeUtil" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<%String remark = configs.getString("specialcont"); %>
<%String beginDate27d = session.getAttribute("begindate27d").toString();%>
<%String endDate27d = session.getAttribute("enddate27d").toString();%>
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
<%String per = "20";
	if (null!=session.getAttribute("per")){ 
		per = session.getAttribute("per").toString();
	}
%>
<%String meal = "";
	if (null!=session.getAttribute("meal")){ 
		meal = session.getAttribute("meal").toString();
	}
%>
<%String bavgRange = "0";
	if (null!=session.getAttribute("bavgRange")){ 
		bavgRange = session.getAttribute("bavgRange").toString();
	}
%>
<%String eavgRange = "0";
	if (null!=session.getAttribute("eavgRange")){ 
		eavgRange = session.getAttribute("eavgRange").toString();
	}
%>
<%String selPer = "";
	if (null!=session.getAttribute("selPer")){ 
		selPer = session.getAttribute("selPer").toString();
	}
%>
<%String perRange = "0";
	if (null!=session.getAttribute("perRange")){ 
		perRange = session.getAttribute("perRange").toString();
	}
%>

<form action="<%= ContextUtil.getCtxPath(request)%>/yktcarduser/speciallist/speciallist_queryresult.do"
	name=oneaccountform method=post >
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>

	<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="spec.bDate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate27d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><div align="right"><bean:message key="spec.eDate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate27d%>" /></td>
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
						List deptList = new GetQueryConListDAO().getDeptList();
						String deptCode = "";
						if (null!=session.getAttribute("deptNo")){
							deptCode = session.getAttribute("deptNo").toString();
						}
						Iterator iter = deptList.iterator();
						while (iter.hasNext()){
							Object[] row = (Object[])iter.next();
							if (deptCode.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				</select>
				</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.specNo"/></td>
				<td nowrap="nowrap">
        			<select name="specNo" style="width=155">
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
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.feeType"/></td>
				<td nowrap="nowrap"><select name="feeType" style="width=155">
        			<OPTION value="0">-</OPTION>
					<%
						List feeList = new GetQueryConListDAO().getFeeTypeList(); 
						String feeType = "";
						if (null!=session.getAttribute("feeType")){ 
							feeType = session.getAttribute("feeType").toString();
						}
						Iterator iter2 = feeList.iterator();
						while (iter2.hasNext()){
							Object[] row = (Object[])iter2.next();
							if (feeType.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				</select>

				</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.meal"/></td>
				<td nowrap="nowrap"><select name="meal" style="width=155">
				<OPTION value=""><bean:message key="spec.all"/></OPTION>
				<%if ("bk".equals(meal)){%>
		        <OPTION value="bk" selected="selected"><bean:message key="spec.bk"/></OPTION>
		        <%}else{%>
		        <OPTION value="bk"><bean:message key="spec.bk"/></OPTION>
		        <%}%>
		        <%if ("lun".equals(meal)){%>
		        <OPTION value="lun" selected="selected"><bean:message key="spec.lun"/></OPTION>
		        <%}else{%>
		        <OPTION value="lun"><bean:message key="spec.lun"/></OPTION>
		        <%}%>
		        <%if ("sup".equals(meal)){%>
		        <OPTION value="sup" selected="selected"><bean:message key="spec.sup"/></OPTION>
		        <%}else{%>
		        <OPTION value="sup"><bean:message key="spec.sup"/></OPTION>
		        <%}%>
		        </select>
				
				</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.bStuempNo"/></td>
				<td nowrap="nowrap"><input type="text" name="bStuempNo" value="<%=bStuempNo%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.eStuempNo"/></td>
				<td nowrap="nowrap"><input type="text" name="eStuempNo" value="<%=eStuempNo%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.per"/></td>
				<td nowrap="nowrap"><input type="text" name="per" onkeypress="return checkNumber(event);" value="<%=per%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
				
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.avgRange"/></td>
				<td nowrap="nowrap">
				<input style="width=65" type="text" name="bavgRange"  value="<%=bavgRange%>">
				-->
				<input style="width=65" type="text" name="eavgRange"  value="<%=eavgRange%>">
				</td>
			</tr>
			
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.perRange"/></td>
				<td nowrap="nowrap">
				<select name="selPer" style="width=85">
				<OPTION value=""><bean:message key="spec.nullAvg"/></OPTION>
				<%if ("up".equals(selPer)){%>
		        <OPTION value="up" selected="selected"><bean:message key="spec.upAvg"/></OPTION>
		        <%}else{%>
		        <OPTION value="up"><bean:message key="spec.upAvg"/></OPTION>
		        <%}%>
		        <%if ("down".equals(selPer)){%>
		        <OPTION value="down" selected="selected"><bean:message key="spec.downAvg"/></OPTION>
		        <%}else{%>
		        <OPTION value="down"><bean:message key="spec.downAvg"/></OPTION>
		        <%}%>
		        </select>				
				<input style="width=65" type="text" name="perRange" onkeypress="return checkNumber(event);" value="<%=perRange%>">
				%
				</td>
				<td nowrap="nowrap">&nbsp;</td>
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
				<td width="66%" ><bean:message key="system.note" /><%=remark %></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>

</tr></table>
</form>
<script type="text/javascript">  
function checkNumber(e) {     
	var key = window.event ? e.keyCode : e.which;     
	var keychar = String.fromCharCode(key);     
	var el = document.getElementById('per');     
	//var msg = document.getElementById('msg');     
	reg = /\d/;     
	var result = reg.test(keychar);     
 	if(!result){         
 		return false;
	}else{
		return true;
	}
}
</script> 
