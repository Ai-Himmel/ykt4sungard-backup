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
<%String sheet = "sheet1";
	if (null!=session.getAttribute("sheet")){ 
		sheet = session.getAttribute("sheet").toString();
	}
%>
<%String bconsumeRange = "0";
	if (null!=session.getAttribute("bconsumeRange")){ 
		bconsumeRange = session.getAttribute("bconsumeRange").toString();
	}
%>
<%String econsumeRange = "0";
	if (null!=session.getAttribute("econsumeRange")){ 
		econsumeRange = session.getAttribute("econsumeRange").toString();
	}
%>

<%String sgroupedlist = "";
	if (null!=session.getAttribute("groupedlist")){ 
		sgroupedlist = session.getAttribute("groupedlist").toString();
	}
%>



<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/consumeanalysequery/result.do" name=consumeAnalyseform method=post >

	<td>
	
---------------------------------------------------------<bean:message key="analyse.querycontext"/>---------------------------------------------------------
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
						if (null!=session.getAttribute("serialType")){
							serialType = session.getAttribute("serialType").toString();
						}
						Iterator iter3 = serialTypeList.iterator();
						while (iter3.hasNext()){
							Object[] row = (Object[])iter3.next();
							if (serialType.equals(row[0])){
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
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.bStuempNo"/></td>
				<td nowrap="nowrap"><input type="text" name="bStuempNo" value="<%=bStuempNo%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="spec.eStuempNo"/></td>
				<td nowrap="nowrap"><input type="text" name="eStuempNo" value="<%=eStuempNo%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
		</table>
		</td>
	</tr>
</table>

---------------------------------------------------------<bean:message key="analyse.analysecontext"/>---------------------------------------------------------
<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
	<tr>	
		<td  width="30%" nowrap="nowrap" align="right">
		<select name="srclist" size="5" style="width:155" multiple ondblclick="transferOption(document.consumeAnalyseform.srclist, document.consumeAnalyseform.destlist,false)">
			<OPTION value="tradetype"><bean:message key="ana.tradetype"/></OPTION>
			<OPTION value="custtype"><bean:message key="ana.custtype"/></OPTION>
			<OPTION value="cardtype"><bean:message key="ana.cardtype"/></OPTION>
			<OPTION value="busi"><bean:message key="ana.busi"/></OPTION>
			<OPTION value="device"><bean:message key="ana.device"/></OPTION>
			<OPTION value="dept"><bean:message key="ana.dept"/></OPTION>
			<OPTION value="spec"><bean:message key="ana.spec"/></OPTION>
			<OPTION value="class"><bean:message key="ana.class"/></OPTION>
		</select> 		
		</td>
		
		<td    width="27%" nowrap="nowrap" align="center">
			<p>
				<input name="Submit22" type="button" class="button_nor" value="<bean:message key="btn.add" />" onclick="transferOption(document.consumeAnalyseform.srclist, document.consumeAnalyseform.destlist,false);">
			</p>
			<p>
				<input name="Submit23" type="button" class="button_nor" value="<bean:message key="btn.del" />" onclick="returnOption(document.consumeAnalyseform.destlist, document.consumeAnalyseform.srclist,false);">
			</p>
		</td>
		
		<TD  width="43%" nowrap="nowrap" align="left">
			<select name="destlist" size="5" style="width:155" multiple ondblclick="returnOption(document.consumeAnalyseform.destlist, document.consumeAnalyseform.srclist,false);">
			<%	String[] grpList = sgroupedlist.split(",");
				int grpSize = grpList.length;
				String currGrp = "";
				for (int i=0;i<grpSize;i++){
				currGrp = grpList[i].toString();
					if ("dept".equals(currGrp)){
			%>
			<OPTION value="dept"><bean:message key="ana.dept"/></OPTION>
			<%}else if ("spec".equals(currGrp)){ %>
			<OPTION value="spec"><bean:message key="ana.spec"/></OPTION>
			<%}else if ("class".equals(currGrp)){ %>
			<OPTION value="class"><bean:message key="ana.class"/></OPTION>
			<%}else if ("custtype".equals(currGrp)){ %>
			<OPTION value="custtype"><bean:message key="ana.custtype"/></OPTION>
			<%}else if ("cardtype".equals(currGrp)){%>
			<OPTION value="cardtype"><bean:message key="ana.cardtype"/></OPTION>
			<%}else if ("tradetype".equals(currGrp)){%>
			<OPTION value="tradetype"><bean:message key="ana.tradetype"/></OPTION>
			<%}else if ("busi".equals(currGrp)){%>
			<OPTION value="busi"><bean:message key="ana.busi"/></OPTION>
			<%}else if ("device".equals(currGrp)){%>
			<OPTION value="device"><bean:message key="ana.device"/></OPTION>
			<%}}%>
			</select>
		</TD>
	</tr>
</table>

------------------------------------------------------------------------------------------------------------------------------
<%String groupedlist="";%>
<input type=hidden name=groupedlist value='<%=groupedlist%>'>
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
				<button onclick="getSelectList();"><bean:message key="btn.analyse" /></button>
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

function getSelectList(){
	var groupedlist="";
	for (i=0;i<consumeAnalyseform.destlist.options.length;i++){
		groupedlist=groupedlist+consumeAnalyseform.destlist.options[i].value+",";
	}
	document.consumeAnalyseform.groupedlist.value = groupedlist;
	document.consumeAnalyseform.submit();
}

</script> 
