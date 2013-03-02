<%@ page contentType="text/html; charset=UTF-8" %>
<script language="JavaScript" src="/html/extjs/util.js"></script>
<script language="JavaScript" src="/html/extjs/tree.js"></script>
<%@page import="com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil"%>
<%@ page import="java.util.List" %>
<%
	List shopList = ShopServiceUtil.createShopJSList("0");
%>
<script language="JavaScript">
	var dlIcons	= new Array();

	// Basic icons

	dlIcons[0] = "/html/extimg/trees/root.gif";
	dlIcons[1] = "/html/extimg/trees/spacer.gif";
	dlIcons[2] = "/html/extimg/trees/line.gif";
	dlIcons[3] = "/html/extimg/trees/join.gif";
	dlIcons[4] = "/html/extimg/trees/join_bottom.gif";
	dlIcons[5] = "/html/extimg/trees/minus.gif";
	dlIcons[6] = "/html/extimg/trees/minus_bottom.gif";
	dlIcons[7] = "/html/extimg/trees/plus.gif";
	dlIcons[8] = "/html/extimg/trees/plus_bottom.gif";
	dlIcons[9] = "/html/extimg/trees/folder.gif";
	dlIcons[10] = "/html/extimg/trees/folder_open.gif";
	dlIcons[11] = "/html/extimg/trees/page.gif";

	// More icons
	dlIcons[12] = "/html/extimg/trees/checked.gif";
	dlIcons[13] = "/html/extimg/trees/unchecked.gif";

	var dlArray = new Array();
	
	<%for (int i = 0; i < shopList.size(); i++) {%>
	dlArray[<%= i %>] = "<%= (String) shopList.get(i)%>";
	<%}%>
</script>

<div>
	<script language="JavaScript">
		var dlTree = new Tree("dlTree", dlArray, dlIcons, "topmenu_link_12", "<%=request.getAttribute("storeLimitString")%>");
		dlTree.create("dlTree");
	</script>
</div>
	