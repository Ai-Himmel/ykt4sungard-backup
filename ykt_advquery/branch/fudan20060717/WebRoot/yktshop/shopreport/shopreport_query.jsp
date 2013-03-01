<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ page import="com.kingstargroup.advquery.util.ParamUtil" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<%@ include file="permission.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/js/util.js"></script>
</head>
<%String queryType = ParamUtil.getString(request, "querytype", "0");%>
<%String storeLimitString = ParamUtil.getString(request, "storeLimitString");%>	
<%String userName = session.getAttribute("username").toString();%>
<%String beginDate35d = session.getAttribute("begindate35d").toString();%>
<%String endDate35d = session.getAttribute("enddate35d").toString();%>
<%String beginDate35m = session.getAttribute("begindate35m").toString();%>
<%String endDate35m = session.getAttribute("enddate35m").toString();%>
<%String level = session.getAttribute("level")==null?"1":session.getAttribute("level").toString();%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktshop/shopreport/shopreport_queryresult.do"
	name=shopreportform method=post >
	<td>
	<input type=hidden name="querytype" value="0">
	<input type=hidden name=storeLimitString value='<%= storeLimitString%>'>
	<input type=hidden name=operCode value='<%= userName%>'>
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td nowrap="nowrap" width="50%"><bean:message key="query.type"/><input
			name="statType" type="radio" value="bydate" 
			<c:if test='<%= queryType.equals("0")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('0')" /><bean:message key="query.bydate" />
		<input type="radio"
			name="statType" value="bymonth"
			<c:if test='<%= queryType.equals("1")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('1')" /><bean:message key="query.bymonth" />
		<input type="radio"
			name="statType" value="byday"
			<c:if test='<%= queryType.equals("2")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('2')" /><bean:message key="query.byday" />
		</td>
		<TD nowrap="nowrap" align="left" width="50%"><bean:message key="query.level" />
			<select id="level" value="<%=level%>" name="level">
				<option value="1">1</option>
				<option value="2">2</option>
				<option value="3">3</option>
				<option value="4">4</option>
				<option value="5">5</option>
			</select>	
		</TD>
	</tr>
</table>
<c:if test='<%= queryType.equals("0")%>'>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="8%" nowrap="nowrap"><bean:message key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate35d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate35d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
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
		</table>
		</td>
	</tr>
</table>

<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
  <tr> 
  	<td>
    	<%@ include file="/user/shop_tree.jsp" %>
    </td>
  </tr>
</table>
<table width="98%" height="1"  border="0" align="center" cellpadding="0" cellspacing="0">
    <tr>
      <td bgcolor="#e1e1e2"></td>
    </tr>
</table>

<table width="98%" height="5"  border="0" align="center" cellpadding="0" cellspacing="0">
   <tr>
     <td></td>
   </tr>
</table>

<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="66%" class="red_text"></td>
				<td width="34%" align="center">
				<button onclick="javascript:setCmdValue('query');"><bean:message key="btn.query" /></button>
				<button onclick="javascript:renderCancelPage();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
<c:if test='<%= queryType.equals("1")%>'>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="8%" nowrap="nowrap"><bean:message key="query.beginmonth" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate35m%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.endmonth" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate"  readonly="readonly" value="<%=endDate35m%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					</script>
					
			</tr>
		</table>
		</td>
	</tr>
</table>
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
  <tr> 
  	<td>
    	<%@ include file="/user/shop_tree.jsp" %>
    </td>
  </tr>
</table>
<table width="98%" height="1"  border="0" align="center" cellpadding="0" cellspacing="0">
    <tr>
      <td bgcolor="#e1e1e2"></td>
    </tr>
</table>

<table width="98%" height="5"  border="0" align="center" cellpadding="0" cellspacing="0">
   <tr>
     <td></td>
   </tr>
</table>

<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="66%" class="red_text"></td>
				<td width="34%" align="center">
				<button onclick="javascript:setCmdValue('query');"><bean:message key="btn.query" /></button>
				<button onclick="javascript:renderCancelPage();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
<c:if test='<%= queryType.equals("2")%>'>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="8%" nowrap="nowrap"><bean:message key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate35d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate35d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
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
		</table>
		</td>
	</tr>
</table>

<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
  <tr> 
  	<td>
    	<%@ include file="/user/shop_tree.jsp" %>
    </td>
  </tr>
</table>
<table width="98%" height="1"  border="0" align="center" cellpadding="0" cellspacing="0">
    <tr>
      <td bgcolor="#e1e1e2"></td>
    </tr>
</table>

<table width="98%" height="5"  border="0" align="center" cellpadding="0" cellspacing="0">
   <tr>
     <td></td>
   </tr>
</table>

<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="66%" class="red_text"></td>
				<td width="34%" align="center">
				<button onclick="javascript:setCmdValue('query');"><bean:message key="btn.query" /></button>
				<button onclick="javascript:renderCancelPage();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
</td>
</form>
</tr></table>
<script>
	function setQueryType(typevalue) {
		document.shopreportform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/yktshop/shopreport/shopreport_query.jsp?querytype=' + typevalue;
	}
</script>
<script>
      	function setCmdValue(cmd) {
          	var level = document.getElementById("level").value;
      		var childs = document.all;
      		var storelimit = '';
      		for (var i = 0; i < childs.length; i++) {
      			var element = childs.item(i);      			

      			if (element.type == 'checkbox' &&       				
      				element.id.indexOf('box') == 0 &&
      				element.checked) {
      				if(getLevel(element)==level){
      					storelimit = storelimit + element.value + ',';	
      				}      				
				}
      		}
      		if (storelimit.length != 0) {
      			storelimit = storelimit.substring(0, storelimit.length -1);
      		}
      		document.forms[0].storeLimitString.value = storelimit;
      		document.forms[0].submit();
      	}
      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/shopreportcont.do';
		}
		function getLevel(element){
			var boxid = element.id.substring(3);
			var node = dlTree.nodes[boxid-1];
			var nodeValues = node.split("|");
			var parentBoxId = nodeValues[1];
			var level = 1;
			//box id of the root node is 1 
			while(parentBoxId!=""){
				node = dlTree.nodes[parentBoxId-1];
				nodeValues = node.split("|");
				parentBoxId = nodeValues[1];
				level = level+1;
			}
			return level;
		}
	//inital tree select status
	
</script>
