<script language="JavaScript" src="/html/extjs/tree_nobox.js"></script>
<%@page import="com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil"%>
<%@ page import="java.util.List"%>
<%
	List shopList = ShopServiceUtil.createShopJSList("0");
%>
<table>
	<tr>
		<td width=2%>
			&nbsp;
		</td>
		<td>
			<table border="0" cellspacing="0" cellpadding="0">

				<tr>
					<td>
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
							// id | parentId | ls | path | name | img | href
						
							var dlArray = new Array();
						
							//dlArray[0] = "1||0||<bean:message key="eadvquery.funclist" />|0|#";
							
							<%for (int i = 0; i < shopList.size(); i++) {%>
							dlArray[<%=i%>] = "<%=(String) shopList.get(i)%>";
							<%}%>
						</script>

						<div>
						<script language="JavaScript">							
							var dlTree = new Tree("dlTree", dlArray, dlIcons, "topmenu_link_12", "");
							dlTree.create("dlTree");
						</script>
						</div>
				</tr>
			</table>
		</td>
	</tr>
</table>
