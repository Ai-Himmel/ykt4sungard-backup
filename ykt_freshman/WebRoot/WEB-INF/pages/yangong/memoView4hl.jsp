<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.DictionaryId"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.web.help.StudentWithAllInfo"%>
<%@ page import="java.util.Map"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">备注</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >
    <html:form action="/dormAppBillAction" method="post">
    <table width=80% border=1 align=center cellpadding=1 cellspacing=0 id=submenu1 line-height=30px>
        <tbody>
        
        <tr align="center" valign=center>
            <td align="left" valign="middle" class="tableHeader3" style="letter-spacing:2px;line-height:15px">
            	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<bean:write name="dormAppBillForm" property="memo"/>
            </td>
        </tr>



        </tbody>
      </table>
      <table width=80% border=0 align=center cellpadding=1 cellspacing=0 >
              <tr align="center" valign=center>
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF">
            <input name="Submit22" type="button" class="button_nor" value="取消" onClick="javascript:self.close();">
            </td>
        </tr>
        </table>
      </html:form></td>
  </tr>
</table>
</body>