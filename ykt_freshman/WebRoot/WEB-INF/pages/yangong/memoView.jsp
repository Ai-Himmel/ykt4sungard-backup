<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.DictionaryId"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.web.help.StudentWithAllInfo"%>
<%@ page import="java.util.Map"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<SCRIPT language=javascript>

function baocun1(){
	if(document.all.memo.value.length>180){
		alert("备注过长，请重输！");
	}else{
		var gid = document.forms[0].elements["gid"].value;
		opener.DoSearch1(gid);
				self.close();
	    dormAppBillForm.action = "<c:url value="/dormAppBillAction.do"/>?method=saveMemo&tag=1";
		dormAppBillForm.submit();

	}
}
function baocun2(){
	if(document.all.memo.value.length>180){
		alert("备注过长，请重输！");
	}else{
		var gid = document.forms[0].elements["gid"].value;
		opener.DoSearch2(gid);
				self.close();
	    dormAppBillForm.action = "<c:url value="/dormAppBillAction.do"/>?method=saveMemo&tag=2";
		dormAppBillForm.submit();

	}
}

</SCRIPT>


<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">请输入备注</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >
    <html:form action="/dormAppBillAction" method="post">
    <table width=100% border=0 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
        <tbody>
        <input type="hidden" name="gid" value="<%=request.getAttribute("gid") %>" />
        <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">备注</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <html:textarea property="memo" styleClass="" rows="5" cols="50"/>
            </td>
        </tr>
        <tr align="center" valign=center>
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" colspan=2><input name="Submit22" type="button" class="button_nor" value="需要住宿" onClick="javascript:baocun1();">
              &nbsp;
            <input name="Submit22" type="button" class="button_nor" value="不需要住宿" onClick="javascript:baocun2();">
            &nbsp;
            <input name="Submit22" type="button" class="button_nor" value="取消" onClick="javascript:self.close();">
            </td>
        </tr>

        </tbody>
      </table>
      </html:form></td>
  </tr>
</table>
</body>