<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ include file="/commons/init.jsp"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<%@ page import="java.net.URLEncoder" %>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%List result = (List) request.getAttribute("result");%>
<%String dateRange = request.getAttribute("daterange").toString();%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr>
<td>
<ec:table items="result" 
		title='<%= GetProperty.getProperties("lunch.title",getServletContext())+dateRange%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="10" locale="zh_CN"
		>

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="feeName" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("lunchtable.feename",getServletContext())%>' />
		<ec:column property="stuempNo" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("lunchtable.stuempno",getServletContext())%>' />
		<ec:column property="custName" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("lunchtable.custname",getServletContext())%>' />
		<ec:column property="meal"  headerStyle="text-align:center"
			filterable="false" 
			style="text-align:left"
			sortable="false" 
			title='<%= GetProperty.getProperties("lunchtable.num",getServletContext())%>' />	
		<ec:column property="amount"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("lunchtable.amount",getServletContext())%>' />	
		<ec:column property="period" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("lunchtable.time",getServletContext())%>' />
	</ec:row>
	<ec:parameter name="custname" value='<%=request.getAttribute("custname")==null?"":URLEncoder.encode((String)request.getAttribute("custname"))%>'></ec:parameter>
</ec:table>
</td></tr></table>


<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="85%" class="red_text"></td>
				<td width="15%" align="center">
				<button onclick="javascript:renderCancelPage();"><bean:message key="btn.return" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</tr></table>
<script>

      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/lunchdetail.do';
		}
</script>

