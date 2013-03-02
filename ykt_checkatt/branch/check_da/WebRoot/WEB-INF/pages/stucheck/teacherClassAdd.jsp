<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>

<html:html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel="stylesheet">
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel="stylesheet">
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
        <script src="<c:url value="/pages/scripts/department.js"/>" type="text/javascript"></script>
        <script type="text/javascript">
            var msg = '<%=request.getAttribute("msg")!=null?request.getAttribute("msg"):""%>';
            if(msg!=''){
                alert(msg);
            }
            function setValue(id,name) {
                var inputObj = document.getElementById("teacherClass.deptId");
                var nameObj = document.getElementById("shortName");
                inputObj.value = id;
                nameObj.value = name;
            }
            function validate(){
                var stuempno = document.getElementById("teacherClass.stuempno");
                var deptId = document.getElementById("teacherClass.deptId");
                var areaCode = document.forms[0].areaCode;
                var shortName = document.forms[0].shortName;
                if(stuempno.value==""){
                    alert("��ʦ���ű���");
                    stuempno.focus();
                    return false;
                }
                if(deptId.value==""){
                    alert("�༶�������");
                    deptId.focus();
                    return false;
                }
                if(areaCode.value==""){
                    alert("��ѡ��У��");
                    areaCode.focus();
                    return false;
                }
                if(shortName.value==""){
                    alert("�༶���Ʊ���");
                    shortName.focus();
                    return false;
                }
                return true;
            }
        </script>
	</head>
	<body>

	<html:form  action="/teacherClassSearch.do?method=saveTeacherClass" method="post" >
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> ���Ӹ���Ա�༶��ϵ </font> </strong>
				</div>
				<div id="lineDiv" class="hrLine">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td class="tdborderLine"></td>
						</tr>
					</table>
				</div>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
					<tbody>
						<tr align="center" valign="center">
							<td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">��ʦ����</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
							    <html:text property="teacherClass.stuempno" styleClass="input_box" maxlength="30" />
								<font color="#ff0000">*</font>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�༶���� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                                <html:text property="teacherClass.deptId" styleClass="input_box" maxlength="50" />
								<font color="#ff0000">*</font>
                                <input type="text" id="departmentName" onclick="getDepartments('departmentName','deptSelect');"  onkeyup="search('departmentName','deptSelect');" size="55" />
                                <UL class=droplist id="deptSelect" style="position:absolute;z-index:1;width:307px;height:200px;display:none" onmouseover="drop_mouseover('deptSelect');" onmouseout="drop_mouseout('deptSelect');">
                                </UL>
							</td>
						</tr>
                        <tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�༶���� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                                <html:text property="shortName" styleClass="input_box" maxlength="100"/>
								<font color="#ff0000">*</font>
							</td>
						</tr>

						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">У�� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                                <html:select property="areaCode">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="areaList" property="areaCode" labelProperty="areaName"/>
                                </html:select>
								<font color="#ff0000">*</font>
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="button" class="submitButton" value=" �� �� " onclick="if(validate()==false) return false;forms[0].submit();">
								<input name="Submit22" type="button" class="submitButton" value=" �� �� " onclick="history.back();">
							</td>
						</tr>
					</tbody>
				</table>
			</tr>
        </table>
	</body>
	</table>
</html:form>

</html:html>