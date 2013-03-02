<%@ include file="/commons/init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/js/util.js"></script>
</head>
<body bgcolor="#eff0eb">
<table width="197" border="0" cellspacing="0" cellpadding="0" >
        <tr> 
          <td height="35" bgcolor="#dadbd5"><table width="150" height="22" border="0" align="center" cellpadding="0" cellspacing="0">
              <tr> 
                <td width="1" bgcolor="#000000"></td>
                <td width="148" align="center" valign="bottom" bgcolor="#FFFFFF" class="topmenu_on">
				<bean:message key="menu.shop" />
				</td>
                <td width="1" bgcolor="#000000"></td>
              </tr>
            </table></td>
        </tr>
      </table>
      <table width="100%" height="1" border="0" cellpadding="0" cellspacing="0" bgcolor="#FFFFFF">
        <tr> 
          <td></td>
        </tr>
      </table>
      <table width="100%" height="1" border="0" cellpadding="0" cellspacing="0" bgcolor="#dadbd5">
        <tr> 
          <td></td>
        </tr>
      </table>
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td>&nbsp;</td>
        </tr>
      </table>
      <table width="197" border="0" cellspacing="0" cellpadding="0">
      <tr>
      	<td width="7">&nbsp;</td>
      	<td width=172>
	      <table align=center background="<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg" width="182" height="31" border="0" align=center cellpadding="0" cellspacing="0"  style="cursor:hand" onclick="">
	        <tr> 	          
	          <td width="172" align=center><a href="javascript:showContent('<%= ContextUtil.getCtxPath(request)%>/carduse.do');" class="topmenu_link_12">
				<bean:message key="menu.shop.distribute" />
				</a></td>
	        </tr>
	      </table>
      	</td>
      </tr>
      </table>
      
      <table width="197" border="0" cellspacing="0" cellpadding="0">
      <tr>
      	<td width="7">&nbsp;</td>
      	<td width=172>
	      <table align=center background="<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg" width="182" height="31" border="0" align=center cellpadding="0" cellspacing="0"  style="cursor:hand" onclick="">
	        <tr> 	          
	          <td width="172" align=center><a href="<%= ContextUtil.getCtxPath(request)%>/consumebyposcont.do" target="dataframe"  class="topmenu_link_12">
				<bean:message key="menu.shop.consumebypos" />
				</a></td>
	        </tr>
	      </table>
      	</td>
      </tr>
      </table>
      
      <table width="197" border="0" cellspacing="0" cellpadding="0">
      <tr>
      	<td width="7">&nbsp;</td>
      	<td width=172>
	      <table align=center background="<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg" width="182" height="31" border="0" align=center cellpadding="0" cellspacing="0"  style="cursor:hand" onclick="">
	        <tr> 	          
	          <td width="172" align=center><a href="<%= ContextUtil.getCtxPath(request)%>/allshopaccountcont.do" target="dataframe"  class="topmenu_link_12">
				<bean:message key="menu.shop.allfinance" />
				</a></td>
	        </tr>
	      </table>
      	</td>
      </tr>
      </table>
      
      <table width="197" border="0" cellspacing="0" cellpadding="0">
      <tr>
      	<td width="7">&nbsp;</td>
      	<td width=172>
	      <table align=center background="<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg" width="182" height="31" border="0" align=center cellpadding="0" cellspacing="0"  style="cursor:hand" onclick="">
	        <tr> 	          
	          <td width="172" align=center><a href="<%= ContextUtil.getCtxPath(request)%>/oneshopaccountcont.do" target="dataframe" class="topmenu_link_12">
				<bean:message key="menu.shop.oneshopaccount" />
				</a></td>
	        </tr>
	      </table>
      	</td>
      </tr>
      </table>
      
      <table width="197" border="0" cellspacing="0" cellpadding="0">
      <tr>
      	<td width="7">&nbsp;</td>
      	<td width=172>
	      <table align=center background="<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg" width="182" height="31" border="0" align=center cellpadding="0" cellspacing="0"  style="cursor:hand" onclick="">
	        <tr> 	          
	          <td width="172" align=center><a href="javascript:showContent('<%= ContextUtil.getCtxPath(request)%>/contend.do');" class="topmenu_link_12">
				<bean:message key="menu.shop.consumecompare" />
				</a></td>
	        </tr>
	      </table>
      	</td>
      </tr>
      </table>
      
      <table width="197" border="0" cellspacing="0" cellpadding="0">
      <tr>
      	<td width="7">&nbsp;</td>
      	<td width=172>
	      <table align=center background="<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg" width="182" height="31" border="0" align=center cellpadding="0" cellspacing="0"  style="cursor:hand" onclick="">
	        <tr> 	          
	          <td width="172" align=center><a href="javascript:showContent('<%= ContextUtil.getCtxPath(request)%>/contend.do');" class="topmenu_link_12">
				<bean:message key="menu.shop.visit" />
				</a></td>
	        </tr>
	      </table>
      	</td>
      </tr>
      </table>
      
      <table width="100%" height="9" border="0" cellpadding="0" cellspacing="0">
        <tr> 
          <td></td>
        </tr>
      </table>
</body>