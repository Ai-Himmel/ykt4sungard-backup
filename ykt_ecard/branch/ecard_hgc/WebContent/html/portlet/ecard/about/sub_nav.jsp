<%@ include file="/html/portlet/ecard/about/init.jsp" %>	 
    
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
		<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardabout/view" /></portlet:renderURL>" >
			<bean:message key="ecard.about.view" />
			</a></td>
          </tr>
        </table>                
		<table width="191"  border="0" cellspacing="0" cellpadding="0" >
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        
		<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardabout/edit" /></portlet:renderURL>" >
			<bean:message key="ecard.management" />
			</a></td>
          </tr>
        </table>        
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
		      
		</td>
        <td align="right">       
	        <img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left_kk.jpg" width="46" height="60">
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
		  	<td height="305" bordercolor="#cfcece">&nbsp;</td>
      </tr>
  </table>