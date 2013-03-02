<%@ page import="java.util.List" %>
<%@ page import="com.kingstargroup.advquery.util.WebKeys" %>
<script language="JavaScript" src="/advquery/js/tree.js"></script>
<%
List moduleJSList = (List) getServletContext().getAttribute(WebKeys.MODULE_JS_TREE);%>
<script language="JavaScript">
	var dlIcons	= new Array();

	// Basic icons

	dlIcons[0] = "/advquery/images/trees/root.gif";
	dlIcons[1] = "/advquery/images/trees/spacer.gif";
	dlIcons[2] = "/advquery/images/trees/line.gif";
	dlIcons[3] = "/advquery/images/trees/join.gif";
	dlIcons[4] = "/advquery/images/trees/join_bottom.gif";
	dlIcons[5] = "/advquery/images/trees/minus.gif";
	dlIcons[6] = "/advquery/images/trees/minus_bottom.gif";
	dlIcons[7] = "/advquery/images/trees/plus.gif";
	dlIcons[8] = "/advquery/images/trees/plus_bottom.gif";
	dlIcons[9] = "/advquery/images/trees/folder.gif";
	dlIcons[10] = "/advquery/images/trees/folder_open.gif";
	dlIcons[11] = "/advquery/images/trees/page.gif";

	// More icons
	dlIcons[12] = "/advquery/images/trees/checked.gif";
	dlIcons[13] = "/advquery/images/trees/unchecked.gif";
	// id | parentId | ls | path | name | img | href

	var dlArray = new Array();

	dlArray[0] = "1||0||<bean:message key="eadvquery.funclist" />|0|0";
	
	<%for (int i = 0; i < moduleJSList.size(); i++) {%>
	dlArray[<%= i + 1%>] = "<%= (String) moduleJSList.get(i)%>";
	<%}%>
</script>

<div>
	<script language="JavaScript">
		var dlTree = new Tree("dlTree", dlArray, dlIcons, "topmenu_link_12", "<%= userLimitString%>");
		dlTree.create("dlTree");		
	</script>
</div>
	