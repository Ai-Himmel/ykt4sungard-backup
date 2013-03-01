<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ include file="/commons/init.jsp"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
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
		title='<%= GetProperty.getProperties("shopreport.title",getServletContext())+dateRange%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="10" locale="zh_CN"
		>

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="deptname" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("shopreport.shopname",getServletContext())%>' />
		<ec:column property="shopname" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("shopreport.childshop",getServletContext())%>' />
		<ec:column property="period" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("shopreport.tradedate",getServletContext())%>' />
		<ec:column property="tradenum"  headerStyle="text-align:center"
			filterable="false" 
			style="text-align:left"
			sortable="false" 
			title='<%= GetProperty.getProperties("shopreport.tradenum",getServletContext())%>' />	
		<ec:column property="tradeamt"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopreport.tradeamt",getServletContext())%>' />	
	</ec:row>

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
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/shopreportcont.do';
		}
</script>

