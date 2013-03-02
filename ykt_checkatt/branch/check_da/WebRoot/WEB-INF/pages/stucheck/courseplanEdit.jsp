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
        <script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
        <script src="<c:url value="/pages/scripts/department.js"/>" type="text/javascript"></script>
        <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
        <script type="text/javascript">
            function changeArea(){
                var schoolarea = document.forms[0].areaCode.value;
                OPT.getBuildList(schoolarea,changeAreaCallback);
            }
            function changeBuild(){
                var build = document.forms[0].build.value;
                OPT.getRoomnameList(build,changeBuildCallback);
            }
            function changeAreaCallback(result){
                DWRUtil.removeAllOptions("build");
                DWRUtil.removeAllOptions("roomname");
                DWRUtil.addOptions("build", { '':'��ѡ��'});
                DWRUtil.addOptions("roomname", { '':'��ѡ��'});
                DWRUtil.addOptions("build", result);
            }
            function changeBuildCallback(result){
                DWRUtil.removeAllOptions("roomname");
                DWRUtil.addOptions("roomname", { '':'��ѡ��'});
                DWRUtil.addOptions("roomname", result);
            }
            function setValue(id,name) {
                var inputObj = document.getElementById("departmentName");
                //inputObj.value = name;
                var p_oSel = document.getElementById("bindclasses"); 
                addSingleContent(id,name,p_oSel);
            }
            function addSingleContent(p_aVal, p_aText, p_oSel) {
                var nLength = p_oSel.length;
                var bTag = 0;

                for (var i = 0; i < nLength; i++) {
                    if ((p_aText == p_oSel.options[i].text) && (p_aVal == p_oSel.options[i].value)) {
                        bTag = 1;
                        break;
                    }
                    if ((p_aVal == "") || (p_aText == "")) {
                        bTag = 1;
                        break;
                    }
                }
                if (bTag == 0) {
                    p_oSel.options[nLength] = new Option(p_aText, nLength);
                    p_oSel.options[nLength].value = p_aVal;
                }
            }
            function deleteContent(p_oSel) {
                for(var i=0;i<p_oSel.length;i++){
                    if(p_oSel.options[i].selected==true){
                        p_oSel.options.remove(i);
                        i--;
                    }
                }
            }
            function deleteAllContent(p_oSel) {
                p_oSel.length = 0;
            }
            function SelectAll(){
                for(var i=0;i<document.forms[0].bindclasses.length;i++){
                    document.forms[0].bindclasses.options[i].selected=true;
                }
                var url = "coursePlan.do?method=updateCourseplan";
                new Ajax.Request(url,
                  {
                    method:'post',
                    parameters: Form.serialize(document.forms[0]),
                    onSuccess: function(result){
                        if(result.responseText.indexOf("error:")!=0){
                            window.close();
                            window.opener.document.forms[0].submit();
                        } else {
                            alert(result.responseText);
                        }
                    }
                  });
            }
        </script>
	</head>
	<body>
	
	<html:form  action="/coursePlan.do?method=updateCourseplan" method="post" >
        <html:hidden property="planId"/>
        <html:hidden property="gardno" value="100"/>    
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium">���ڼƻ��޸� </font> </strong>
				</div>
				<div id="lineDiv" class="hrLine">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td class="tdborderLine"></td>
						</tr>
						<tr>
							<td align="center"><logic:present name="result" ><bean:write name="result"/></logic:present> </td>
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
								<span class="medium">У��</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
							  <html:select property="areaCode" onchange="changeArea();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="areaList" property="areaCode" labelProperty="areaName"/>
                              </html:select>
							</td>
						</tr>
                        <tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">¥�� </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
						     <html:select property="build" onchange="changeBuild();">
                                  <html:option value="">��ѡ��</html:option>
                                  <html:options collection="buildList" property="build" labelProperty="build"/>
                             </html:select>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">����</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
							<html:select property="roomname">
                                 <html:option value="">��ѡ��</html:option>
                                 <html:options collection="roomnameList" property="roomname" labelProperty="roomname"/>
                             </html:select>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�༶</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                                <html:select property="bindclasses" multiple="multiple" size="10" ondblclick="deleteContent(this);" style="width:62%;">
                                    <html:options collection="departments" property="id" labelProperty="name" />
                                </html:select>
                                <br>
                                <input type="text" id="departmentName" onclick="getDepartments('departmentName','deptSelect');"  onkeyup="search('departmentName','deptSelect');" size="55" />
                                <UL class=droplist id="deptSelect" style="position:absolute;z-index:1;width:307px;height:200px;display:none" onmouseover="drop_mouseover('deptSelect');" onmouseout="drop_mouseout('deptSelect');">
                                </UL>
                                &nbsp;&nbsp;&nbsp;&nbsp;<INPUT onclick="deleteContent(this.form.bindclasses);" type=button value="ɾ  ��" class="button">
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">��ʦ����</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="stuempNo"  maxlength="10" />															
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">��ʦ����</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="custName"  maxlength="10" />
							</td>
						</tr>
					 
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�ڼ���</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="useWeek" maxlength="10" />
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">����</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="week" maxlength="10" />
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">ʹ������</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="useDate" maxlength="10" />
                                <img id="calDate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("useDate", "calDate", "%Y%m%d");
                                </script>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">��ʼ�δ�</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
							<html:select property="beginClassNum" >
                                 <html:options collection="timeList" property="classNum" labelProperty="classNum"/>
                             </html:select>
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�����δ�</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
							<html:select property="endClassNum">
                                 <html:options collection="timeList" property="classNum" labelProperty="classNum"/>
                             </html:select>
							</td>
						</tr>
                        <tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�Ƿ���Ҫ����</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                                <html:checkbox property="ischeck" value="1" />
							</td>
						</tr>
                        <tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5">�Ƿ���Ҫ����</span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                                <html:checkbox property="isopen" value="1" />
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="button" class="submitButton" onclick="SelectAll();" value=" ��  �� ">
								<input name="Submit22" type="button" class="submitButton" value=" �� �� " onclick="window.close();">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</table>
</html:form>
	 
</html:html>
