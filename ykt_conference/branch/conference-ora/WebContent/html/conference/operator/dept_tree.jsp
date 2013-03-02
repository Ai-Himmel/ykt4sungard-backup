<script language="JavaScript" src="/conference/html/commons/js/tree.js"></script>
<%@ page import="java.util.List"%>
<%@ page import="com.kingstargroup.conference.common.WebKeys"%>
<%
			List deptList = (List) getServletContext().getAttribute(
			WebKeys.DEPT_JS_TREE);//OperatorUtil.createDeptJSList("NA");
%>
<script language="JavaScript">
	var dlIcons	= new Array();

	// Basic icons

	dlIcons[0] = "/conference/html/commons/images/trees/root.gif";
	dlIcons[1] = "/conference/html/commons/images/trees/spacer.gif";
	dlIcons[2] = "/conference/html/commons/images/trees/line.gif";
	dlIcons[3] = "/conference/html/commons/images/trees/join.gif";
	dlIcons[4] = "/conference/html/commons/images/trees/join_bottom.gif";
	dlIcons[5] = "/conference/html/commons/images/trees/minus.gif";
	dlIcons[6] = "/conference/html/commons/images/trees/minus_bottom.gif";
	dlIcons[7] = "/conference/html/commons/images/trees/plus.gif";
	dlIcons[8] = "/conference/html/commons/images/trees/plus_bottom.gif";
	dlIcons[9] = "/conference/html/commons/images/trees/folder.gif";
	dlIcons[10] = "/conference/html/commons/images/trees/folder_open.gif";
	dlIcons[11] = "/conference/html/commons/images/trees/page.gif";

	// More icons
	dlIcons[12] = "/conference/html/commons/images/trees/checked.gif";
	dlIcons[13] = "/conference/html/commons/images/trees/unchecked.gif";
	// id | parentId | ls | path | name | img | href

	var dlArray = new Array();

	
	<%for (int i = 0; i < deptList.size(); i++) {%>
	dlArray[<%=i%>] = "<%=(String) deptList.get(i)%>";
	<%}%>
</script>

