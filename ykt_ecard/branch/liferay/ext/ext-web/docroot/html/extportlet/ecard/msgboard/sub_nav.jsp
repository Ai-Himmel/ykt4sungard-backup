<%@ include file="/html/extportlet/ecard/msgboard/init.jsp" %>

	<table width="243" height="107"  border="1" cellpadding="0" cellspacing="0" bordercolor="#F5F9FF" background="/html/extthemes/classic/images/ecard/left_bg.jpg">
	  <tr>
	    <td valign="top" bordercolor="#cfcece"><table width="100%" height="7"  border="0" cellpadding="0" cellspacing="0">
	      <tr>
	        <td width="239" height="36" valign="bottom" background="/html/extthemes/classic/images/ecard/search.jpg">
	        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
	          <tr>
	            <td width="17%">&nbsp;</td>
	            <td width="83%" class="text_w_12"><bean:message key="ecardmsgboard.tab.search" /></td>
	          </tr>
	        </table></td>
	      </tr>
	    </table>
        
        <html:form action="/ecardmsgboard/search_result" method="POST"
						onsubmit="javascript:setKeyword(this);return false;">
		<html:hidden property="search_title" />
		<html:hidden property="search_content" />
		<input type=hidden name=page value=0>
	<table width="239" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td bordercolor="#F5F9FF"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td width="69%"><table width="97%"  border="0" cellspacing="0" cellpadding="0">
                      <tr>
                        <td width="70%" height="25" align="right">
                        <input name="virtual_content" type="text" style="height:21px" value='<bean:message key="ecard.pleaseinputthekeyword" />' size="20" 
                        	onfocus="javascript:this.value='';"></td>
                      </tr>
                      <tr>
                        <td height="25" align="right">
                        <select id="keywordSelect">
                          <option value="0"><bean:message key="ecard.title" /></option>
                          <option value="1"><bean:message key="ecard.content" /></option>
                          </select></td>
                      </tr>
                  </table></td>
                  <td width="31%" align="center">
                  <input type="image" src="/html/extthemes/classic/images/ecard/go_button.jpg" width="66" height="52" border="0"></td>
                </tr>
            </table>
            <script>
            	document.InfoSearchForm.virtual_content.focus();
            	function setKeyword(form) {
            		var select = document.getElementById("keywordSelect");
					var selectValue = select.options[select.selectedIndex].value;
					if (selectValue == '0') {
						document.InfoSearchForm.search_title.value = document.InfoSearchForm.virtual_content.value;
						document.InfoSearchForm.search_content.value = '';
					} else {
						document.InfoSearchForm.search_content.value = document.InfoSearchForm.virtual_content.value;
						document.InfoSearchForm.search_title.value = '';
					}
					validateSearchForm(form,'<bean:message key="ecard.error.keywordmaxlength" />');					
            	}
            </script>
            </html:form>
            </td>
          </tr>
        </table></td>
      </tr>
    </table>
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
            <td><img src="/html/extthemes/classic/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
		<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="/html/extthemes/classic/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardmsgboard/view" /></portlet:renderURL>" >
			<bean:message key="ecardmsgboard.tab.view" />
			</a></td>
          </tr>
        </table>
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="/html/extthemes/classic/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
		<table width="100%"  border="0" cellspacing="0" cellpadding="0" background="/html/extthemes/classic/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardmsgboard/add" /></portlet:renderURL>" >
			<bean:message key="ecardmsgboard.tab.add" />
			</a></td>
          </tr>
        </table>
        
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="/html/extthemes/classic/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        
        <c:if test="<%= PermissionUtil.hasMsgboardAdmin(request)%>">
        <table width="100%"  border="0" cellspacing="0" cellpadding="0" background="/html/extthemes/classic/images/ecard/bbs_1_new.jpg">
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardmsgboard/admin" /></portlet:renderURL>" >
			<bean:message key="ecardmsgboard.tab.delete" />
			</a></td>
          </tr>
        </table>
		<table width="191"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td><img src="/html/extthemes/classic/images/ecard/left_line.jpg" width="191" height="1"></td>
          </tr>
        </table>
        </c:if>				</td>
        <td align="right">
        <c:choose>
	        <c:when test="<%= PermissionUtil.hasMsgboardAdmin(request)%>">
	        <img src="/html/extthemes/classic/images/ecard/left_kk.jpg" width="46" height="90">
	        </c:when>
	        <c:otherwise>		
	        <img src="/html/extthemes/classic/images/ecard/left_kk.jpg" width="46" height="60">
	        </c:otherwise>
        </c:choose></td>
      </tr>
    </table>
	            <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td></td>
      </tr>
    </table>
    <table width="243" height="100"  border="1" cellpadding="0" cellspacing="0" bordercolor="#F5F9FF" background="/html/extthemes/classic/images/ecard/left_bg.jpg">
      <tr>
      	    		<td height="168" bordercolor="#cfcece">&nbsp;</td>
      	       
      </tr>
  </table>