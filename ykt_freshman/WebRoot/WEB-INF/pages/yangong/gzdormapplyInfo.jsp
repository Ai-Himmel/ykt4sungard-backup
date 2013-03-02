<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.DictionaryId"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.web.help.StudentWithAllInfo"%>
<%@ page import="java.util.Map"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>

<SCRIPT language=javascript>
function baocun(){
	if(document.all.name.value==""){
		alert("学生姓名不能为空,请搜索学生信息!");
	}else if(document.all.district.value==""){
	    alert("学生住址所在区域不能为空！");
	}else if(document.all.memo.value!=""){
		if(document.all.memo.value.length>180){
			alert("备注过长，请重输！");
		}else{
			dormAppBillForm.action = "<c:url value="/dormAppBillAction.do"/>?method=saveGzdormappInfo";
			dormAppBillForm.submit();
		}
	}else{
	    dormAppBillForm.action = "<c:url value="/dormAppBillAction.do"/>?method=saveGzdormappInfo";
		dormAppBillForm.submit();
	}
}
function dosearch1(){
	var studentNo = document.forms[0].elements["studentNo"].value;
	dormAppBillForm.action="<c:url value="/dormAppBillAction.do"/>?method=getStudentInfoByStudentNo&studentNo="+studentNo;
	dormAppBillForm.submit();
}
function dosearch2(){
	var enterenceNo = document.forms[0].elements["enterenceNo"].value;
	dormAppBillForm.action="<c:url value="/dormAppBillAction.do"/>?method=getStudentInfoByEnterenceNo&enterenceNo="+enterenceNo;
	dormAppBillForm.submit();
}
	 function my_onload(){	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		} 	
	 }
	 window.onload=my_onload;
</SCRIPT>


<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生住宿申请登记</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >
    <html:form action="/dormAppBillAction" method="post">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
        <tbody>

          <html:hidden property="id" />
          <INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">学号</font></td>
            <td width="32%" align="left" valign="middle" class="tableHeader3" >
            <html:text property="studentNo" styleClass="input_box" maxlength="20"/>
            <input name="Submit222" type="button" class="button_nor" value="搜索" onClick="javascript:dosearch1();">
            </td>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">录取通知书号</font></td>
            <td width="32%" align="left" valign="middle" class="tableHeader3" >
            <html:text property="enterenceNo" styleClass="input_box" maxlength="20"/>
            <input name="Submit223" type="button" class="button_nor" value="搜索" onClick="javascript:dosearch2();">
            </td>
          </tr>
          <c:if test="${gzStu!=null}">
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">姓名</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <input type="text" name="name" value="<%=((Map)request.getAttribute("gzStu")).get("stuName") %>" Class="input_box" style="background:#ECE6E6" readonly="true"/>
            </td>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">性别</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <input type="text" name="sex" value="<%=((Map)request.getAttribute("gzStu")).get("gender") %>" class="input_box" style="background:#ECE6E6" readonly="true"/>
            </td>
          </tr>
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">班级</font></td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3">
            <input type="text" name="class" value="<%=((Map)request.getAttribute("gzStu")).get("className") %>" class="input_box" style="background:#ECE6E6" readonly="true"/>
            </td>
          </tr>
          </c:if>
          <c:if test="${gzStu==null}">
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">姓名</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <input type="text" name="name" value="" Class="input_box" style="background:#ECE6E6" readonly="true"/>
            </td>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">性别</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <input type="text" name="sex" value="" class="input_box" style="background:#ECE6E6" readonly="true"/>
            </td>
          </tr>
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">班级</font></td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3">
            <input type="text" name="class" value="" class="input_box" style="background:#ECE6E6" readonly="true"/>
            </td>
          </c:if>
          </tbody>
</table><br>
<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1><tbody>
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">住址所在区县</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
       
			<html:select styleClass="select01" property="district" >
				<html:option value="">-----------------------</html:option>
				<html:options collection="districtList" labelProperty="dictCaption" property="id.dictValue" />
				</html:select>         
            </td>
          </tr>
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">详细住址</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <html:text property="curAddress" styleClass="input_box" maxlength="60" size="80" style="width:450"/>&nbsp;&nbsp;&nbsp;<font color="red">例如:浦东新区德平路345弄68号301</font>
            </td>
          </tr>
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">联系电话</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <html:text property="curTelephone" styleClass="input_box" maxlength="30"/>
            </td>
          </tr>
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">是否需要住宿</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <c:if test="${ifNeedDorm==null}">
            <input type="checkbox" name="item" value="1" />
            </c:if>
            <c:if test="${ifNeedDorm==''}">
            <input type="checkbox" name="item" value="1" />
            </c:if>
            <c:if test="${ifNeedDorm=='0'}">
            <input type="checkbox" name="item" value="1" />
            </c:if>
            <c:if test="${ifNeedDorm=='1'}">
            <input type="checkbox" name="item" value="1" checked/>
            </c:if>&nbsp;&nbsp;<font color="red"><bean:message bundle="classmanage" key="student.need" /></font>
            </td>
          </tr>
          <tr align="center" valign=center>
            <td width="17%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><font class="medium">备注</font></td>
            <td align="left" valign="middle" class="tableHeader3" >
            <html:textarea property="memo" styleClass="" rows="3" cols="80"/>
            </td>
          </tr>


        </tbody>
      </table></html:form></td>
  </tr>
  <tr align="center" valign=center>
      <td height="30" colspan="2" align="right" valign="middle" bgcolor="#FFFFFF" ><input name="Submit22" type="button" class="button_nor" value="保存" onClick="javascript:baocun();">
        &nbsp;&nbsp;
      </td>
  </tr>  
</table>
</body>
