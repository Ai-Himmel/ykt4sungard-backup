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
        <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
        <script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
        <script type="text/javascript">
            function isCheck(checkItem) {
                for(var i = 0;i < checkItem.length; i ++) {
                    if(checkItem[i].type == "checkbox" && checkItem[i].checked ) {
                        return true;
                    }
                }
                return false;
            }

            function process(){
                var checkItem=document.getElementsByName("itemlist");
                if(checkItem.length==0){
                    return;
                } else {
                    if(!isCheck(checkItem)){
                        alert("��ѡ��༶��");
                        return;
                    }
                }

                var analyseBtn = document.getElementById("analyseBtn");
                var processBtn = document.getElementById("processBtn");
                analyseBtn.disabled = "disabled";
                processBtn.disabled = "disabled";
                var infoSpan = document.getElementById("info");
                infoSpan.style.display = "";
                var url = "historyCheck.do?method=process";
                new Ajax.Request(url,
                  {
                    method:'post',
                    parameters: Form.serialize(document.forms.ec),
                    onSuccess: function(result){
                        analyseBtn.disabled = "";
                        if(result.responseText.indexOf("error:")!=0){
                            infoSpan.innerHTML = result.responseText;
                        } else {
                            infoSpan.style.display = "none";
                            alert(result.responseText);
                        }
                    }
                  });
            }
            function analyse(){
                var year = document.getElementById("createYear").value;
                if(year==""){
                    alert("��ѡ�񴴽���ݣ�");
                    return false;
                }
                document.forms[0].submit();
            }
            function changeFaculty(){
	            var pid = document.forms[0].pid.value;
	            OPT.findAreaFromDepartment(pid,changeFacultyCallback);
            }
            function changeFacultyCallback(result){
                DWRUtil.removeAllOptions("areaCode");
                DWRUtil.addOptions("areaCode", { '':'��ѡ��'});
                DWRUtil.addOptions("areaCode", result,"AREACODE","AREANAME");
            }
        </script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ��ʷ����ά�� </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
				<html:form action="historyCheck.do?method=analyse" method="post">
                    <table width="100%">
                        <tr>
                            <td align="center">
                                ��&nbsp;&nbsp;��&nbsp;&nbsp;��&nbsp;&nbsp;�ݣ�
                                <html:select property="createYear">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options name="yearList"/>
                                </html:select>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Ժ&nbsp;&nbsp;ϵ��
                                <html:select property="pid" onchange="changeFaculty();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="facultyList" property="ID" labelProperty="NAME"/>
                                </html:select>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;У&nbsp;&nbsp;����
                                <html:select property="areaCode">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                                </html:select>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                <input id="analyseBtn"  width="50" type="button" class="button_nor" value="��  ��" onclick="analyse();">
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                <input id="processBtn"  width="50" type="button" class="button_nor" value="��  ��" onclick="process();">
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                <span style="color:red;display:none;" id="info">���ڴ�����...</span>
                            </td>
                        </tr>
                    </table>
				</html:form>
		</div>
        <div id="tableDiv">
            <logic:present name="departmentList">
			<ec:table items="departmentList" var="department" sortable="true" showPagination="false" action="historyCheck.do?method=analyse" locale="zh_CN" filterable="false">
				<ec:exportXls fileName="teacherClass.xls"  tooltip="���� Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="4%">
					    <input type="checkbox" name="itemlist" value="${department.deptId}" style="border:0px" checked="checked"/>
					</ec:column>
					<ec:column property="deptId" title="�༶����" width="20%" filterable="false"  escapeAutoFormat="true"/>
					<ec:column property="deptName" title="�༶����" width="36%"/>
					<ec:column property="faculty" title="Ժϵ" width="15%" escapeAutoFormat="true"/>
                    <ec:column property="areaName" title="У��" width="15%"/>
                    <ec:column property="createYear" title="�������" width="10%" escapeAutoFormat="true"/>
                    <ec:parameter name="itemlist" value=""/>
				</ec:row>
			</ec:table>
            </logic:present>
		</div>
	</body>
</html:html>
