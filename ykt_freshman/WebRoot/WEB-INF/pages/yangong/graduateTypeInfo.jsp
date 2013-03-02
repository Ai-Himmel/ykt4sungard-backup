<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.DictionaryId"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>

<%@ page import="java.util.Map"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>

<SCRIPT language=javascript>

function baocun(){
    if(document.graduateTypeForm.elements["graduateType"].value==''){    
        alert("住宿管理类别不能为空！");
        return;
    }
    graduateTypeForm.action = "<c:url value="/graduateTypeBillAction.do"/>?method=saveGraduateTypeInfo";
	graduateTypeForm.submit();
}
function clean(){
	document.graduateTypeForm.elements["graduateType"].value="";
}

</SCRIPT>


<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">研究生住宿管理类别维护</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" ><table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#ffffff id=submenu1>
        <tbody>
          <html:form action="/graduateTypeBillAction" method="post">
          
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><strong><font class="medium">研究生类型</font></strong></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <html:hidden property="id" />
            <html:text property="graduateType" styleClass="input_box" maxlength="12"/>
            </td>
          </tr>
          
          <tr align="center" valign=center>
            <td height="30" colspan="2" align="right" valign="middle" bgcolor="#FFFFFF" ><input name="Submit22" type="button" class="button_nor" value="确定" onClick="javascript:baocun();">
              &nbsp;&nbsp;
              <input name="Submit22" type="button" class="button_nor" value="返回" onClick="javascript:history.go(-1);"></td>
          </tr>
          </html:form>
        </tbody>
      </table></td>
  </tr>
</table>
</body>
