<!--
<div id="layout-outer-side-decoration">
	<div id="layout-inner-side-decoration">
		<div id="layout-top-decoration">
			<div id="layout-corner-ul"></div>
			<div id="layout-corner-ur"></div>
		</div>
		<div id="layout-box">
-->
			 <!-- <table width="1000" border="0" cellspacing="0" cellpadding="0">
			  <tr>
			    <td height="59" valign="bottom" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/company_logo.jpg">
				   <table width="<%= themeDisplay.getResTotal() %>" border="0" cellspacing="0" cellpadding="0">
				      <tr>
				        <td width="600" height="20">&nbsp;</td>       
					    <td width="568" height="20" class="text_blue_12" align=right><%= user.getGreeting() %>&nbsp;&nbsp
					    <bean:message key="ecard.bottom.visitwords" 
					    arg0="<%= com.kingstargroup.ecard.util.WebCountUtil.getCount(request)%>" />	</td>
				        <td width="213" height="20" class="text_brown" align=center>
				        
				        <c:if test="<%= !themeDisplay.isSignedIn() %>">
				        <a href="<%= themeDisplay.getURLSignIn() %>" class="brown_link"><bean:message key="sign-in" /></a>
				        </c:if>
				        <c:if test="<%= themeDisplay.isSignedIn() %>">
				        	<c:if test="<%= com.kingstargroup.ecard.util.PermissionUtil.hasAdmin(request)%>">
				        	<a href="<%= themeDisplay.getURLMyAccount() %>" class="brown_link"><bean:message key="ecard.editpassword" /></a>
				        	&nbsp;&nbsp;|&nbsp;&nbsp;
				        	</c:if>				        
				        <a href="<%= themeDisplay.getURLSignOut() %>" class="brown_link"><bean:message key="sign-out" /></a>
				        </c:if>
				        </td>
				        
				      </tr>
				    </table> 
			    </td>
			  </tr>
			</table>-->
			<!-- <table width="1000" height="2" border="0" cellpadding="0" cellspacing="0">
			  <tr>
			    <td bgcolor="#3B639E"></td>
			  </tr>
			</table>-->