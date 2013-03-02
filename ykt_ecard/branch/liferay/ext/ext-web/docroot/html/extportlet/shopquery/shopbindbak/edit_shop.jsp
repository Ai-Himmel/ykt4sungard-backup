<%@ include file="/html/extportlet/shopquery/init.jsp"%>
<%@page import="com.liferay.portal.kernel.util.ParamUtil"%>
<html>
	<head>
		<title><bean:message key="ecard.shop.bind" />
		</title>
		<script language="JavaScript" src="/html/extjs/util.js"></script>
	</head>
	<table width="100%" height="5" border="0" cellpadding="0"
		cellspacing="0">
		<tr>
			<td></td>
		</tr>
	</table>

	<%
		String userid = (String)request.getAttribute("userid");

		String storeLimitString = (String)request.getAttribute("storeLimitString");
	%>
	<table>
		<tr>
			<td width=2%>
				&nbsp;
			</td>
			<td>
				<table width="598" height="27" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td width="14">
							&nbsp;
						</td>
						<td width="584">

						</td>
					</tr>
				</table>
				<html:form action="/ext/shop_admin_save_shop" method="POST"
					onsubmit="submitPortletForm(this); return false;">

					<input type=hidden name="userid" value='<%=userid%>'>
					<input type="hidden" name="storeLimitString">

					<table border="0" cellspacing="0" cellpadding="0">

						<tr>
							<td>
								<%@ include
									file="/html/extportlet/shopquery/shopbind/shop_tree.jsp"%></td>
						</tr>
					</table>
					<table width="100%" height="1" border="0" cellpadding="0"
						cellspacing="0">
						<tr>
							<td bgcolor="#e1e1e2">
								&nbsp;
							</td>
						</tr>
					</table>
					<table width="100%" height="5" border="0" cellpadding="0"
						cellspacing="0">
						<tr>
							<td>
								&nbsp;
							</td>
						</tr>
					</table>
					<table width="99%" height="35" border="0" cellpadding="0"
						cellspacing="0">
						<tr>
							<td align="center">
								<html:submit styleClass="button_blank" property="save"
									value='<%=LanguageUtil.get(pageContext, "ecard.save")%>'
									onclick="javascript:setCmdValue();" />
								<html:button property="add" styleClass="button_blank"
									value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>'
									onclick="javascript:renderCancelPage();" />
							</td>
						</tr>
					</table>
			</td>
		</tr>
	</table>
	</html:form>
	<script>
      	function setCmdValue() {      		
      		var childs = document.all;
      		var storelimit = '';
      		for (var i = 0; i < childs.length; i++) {
      			var element = childs.item(i);      			

      			if (element.type == 'checkbox' &&       				
      				element.id.indexOf('box') == 0 &&
      				element.checked) {      				
      				storelimit = storelimit + element.value + ',';
      				alert(storelimit);
				}
      		}
      		if (storelimit.length != 0) {
      			storelimit = storelimit.substring(0, storelimit.length -1);
      		}
      		document.all.storeLimitString.value = storelimit;
      		document.all.submit();
      	}
      	function renderCancelPage() {
      		self.location = '/ext/extshopbindusersview';
      	}
      	//inital tree select status
      	
      </script>