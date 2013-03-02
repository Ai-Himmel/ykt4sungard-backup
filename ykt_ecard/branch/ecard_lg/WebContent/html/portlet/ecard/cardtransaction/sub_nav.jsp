<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>
    
    <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td></td>
      </tr>
    </table>
    <table width="242"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td width="193" height="31" align="right" valign="top">
		
		<table width="191"  border="0" cellspacing="0" cellpadding="0" >
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        
		<c:if test="<%= !PermissionUtil.hasCardTransactionAdmin(request)%>">
		
		<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/view" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.querydetail" />
			</a></td>
          </tr>
        </table>
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
		
		<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/gatehisview" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.querygatedetail" />
			</a></td>
          </tr>
        </table>
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        
        <table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/viewcardinfo" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.cardlost" />
			</a></td>
          </tr>
        </table>
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        
        <!-- 
    	<c:if test="<%= PermissionUtil.hasDelayProcess(request)%>">
    	<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/postpone_view" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.carddelay" />
			</a></td>
          </tr>
        </table>
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        
     <table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/view_picdelay" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.picdelay" />
			</a></td>
          </tr>
        </table>
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        </c:if>
        -->
    </c:if>
    
		<c:if test="<%= PermissionUtil.hasCardTransactionAdmin(request)%>">

		<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/postpone_admin" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.processcarddelay" />
			</a></td>
          </tr>
        </table>
        
        <table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        
        <table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/admin_picdelay" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.processpicdelay" />
			</a></td>
          </tr>
        </table>
        
		</c:if>
		        
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>				</td>
        <td align="right">
        <c:if test="<%= PermissionUtil.hasCardTransactionAdmin(request)%>">
	        <img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_kk.jpg" width="46" height="60">
        </c:if>
        <c:if test="<%= !PermissionUtil.hasCardTransactionAdmin(request)%>">
        	<c:choose>
	  	        <c:when test="<%= !PermissionUtil.hasDelayProcess(request)%>">
			        <img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_kk.jpg" width="46" height="60">
		        </c:when>
		        <c:otherwise>
		        	<img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_kk.jpg" width="46" height="120">
		        </c:otherwise>
			</c:choose>
        </c:if>
        </td>
      </tr>
    </table>
	            <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td></td>
      </tr>
    </table>
    <table width="243" height="100"  border="1" cellpadding="0" cellspacing="0" bordercolor="#F5F9FF" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_bg.jpg">
      <tr>
      	<c:choose>
      		<c:when test="<%= !PermissionUtil.hasCardTransactionAdmin(request)%>">
      			<c:if test="<%= PermissionUtil.hasDelayProcess(request)%>">
      				<td height="217" bordercolor="#cfcece">&nbsp;</td>
      			</c:if>
				<c:if test="<%= !PermissionUtil.hasDelayProcess(request)%>">
      				<td height="277" bordercolor="#cfcece">&nbsp;</td>
      			</c:if>
      		</c:when>
      		<c:otherwise>
      			<td height="305" bordercolor="#cfcece">&nbsp;</td>
      		</c:otherwise>
      	</c:choose>
      </tr>
  </table>