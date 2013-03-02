<%@ include file="/html/extportlet/ecard/rule/init.jsp" %>
<liferay:box top="/html/extcommon/themes/inner_top.jsp"
		bottom="/html/extcommon/themes/inner_bottom.jsp">
		<liferay:param name="box_title"
			value='<%= LanguageUtil.get(pageContext, "ecard.search") %>' />

<html:form action="/ext/ecardrulesearch_result" method="POST"
	onsubmit="javascript:submitPortletForm(this); return false;">
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
	<tr>
		<td align="center">
			<table border="0" cellpadding="4" cellspacing="2">			
			<tr>
				<td>&nbsp;</td>
						<td align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="search_title" /></font><br>
						<font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="content" /></font></td>
			</tr>
			<tr>
				<td>
					<font class="portlet-font" style="font-size: x-small;"><b>
					<bean:message key="ecard.title" />
					</b></font>
				</td>
				<td>
					<html:text property="search_title" styleClass="form-text" size="20" />
				</td>
			</tr>
			<tr>
				<td>
					<font class="portlet-font" style="font-size: x-small;"><b>
					<bean:message key="ecard.content" />
					</b></font>
				</td>
				<td>
					<html:text property="search_content" styleClass="form-text" size="20" />
				</td>
			</tr>
			<tr>
				<td></td>
				<td>
					<html:submit styleClass="portlet-form-button" property="search" value='<%= LanguageUtil.get(pageContext, "ecardrule.button.search") %>' /> 
				</td>
			</tr>
			<tr>
				<td colspan="2">
					<br>
				</td>
			</tr>			
			</table>
		</td>
	</tr>
	</table>
</html:form>
</liferay:box>