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
        <script type="text/javascript">
            function refreshCheck(btn,method){
                var btn = document.getElementById(btn);
                btn.disabled = "disabled";
                btn.title = "����ˢ�¿��ڣ������ĵȴ���";
                var url = "refreshCheck.do?method="+method;
                new Ajax.Request(url,
                  {
                    method:'post',
                    parameters: Form.serialize(document.forms[0]),
                    onSuccess: function(result){
                        if(result.responseText.indexOf("error:")!=0){
                            btn.disabled = "";
                            btn.title = "";
                        } else {
                            alert(result.responseText);
                            btn.disabled = "";
                        }
                    }
                  });
            }
        </script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ˢ�¿��� </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
				<form action="" method="post">
                    <table width="100%">
                        <tr>
                            <td align="right" width="20%">
                                &nbsp;
                                <input id="checkBtn"  width="50" type="button" class="button_nor" value="ˢ�¿��ڱ���" onclick="refreshCheck('checkBtn','refreshCheck');">
                            </td>
                            <td width="20%">
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��ʼʱ��&nbsp;&nbsp;&nbsp;&nbsp;
                                <input type="text" id="beginDate" name="beginDate" size="12" readonly="true"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                            </td>
                            <td width="20%">
                                &nbsp;����ʱ��&nbsp;&nbsp;&nbsp;&nbsp;
                                <input type="text" id="endDate" name="endDate" size="12" readonly="true"/>
                                <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                            </td>
                            <td>&nbsp;<font color="red">ˢ��ʦ�����ڱ����༶���ڱ�����������ѧ�ڱ���</font></td>
                        </tr>
                        <tr>
                            <td align="right" width="20%">      
                                &nbsp;
                                <input id="studentTermBtn"  width="50" type="button" class="button_nor" value="ˢ��ѧ��ѧ�ڱ���" onclick="refreshCheck('studentTermBtn','refreshStudentTermCheck');">
                            </td>
                            <td width="20%">
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ѧ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;
                                <select name="studentTerm">
                                    <option value="-1">��ѡ��</option>
                                    <c:forEach var="term" items="${terms}">
                                        <option value="<c:out value="${term.termId}"/>"><c:out value="${term.termName}"/></option>
                                    </c:forEach>
                                </select>
                            </td>
                            <td width="20%"></td>
                            <td>&nbsp;</td>
                        </tr>
                        <tr>
                            <td align="right" width="20%">
                                &nbsp;
                                <input id="teacherTermBtn"  width="50" type="button" class="button_nor"  value="ˢ�½�ʦѧ�ڱ���" onclick="refreshCheck('teacherTermBtn','refreshTeacherTermCheck');">
                            </td>
                            <td width="20%">
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ѧ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;
                                <select name="teacherTerm">
                                    <option value="-1">��ѡ��</option>
                                    <c:forEach var="term" items="${terms}">
                                        <option value="<c:out value="${term.termId}"/>"><c:out value="${term.termName}"/></option>
                                    </c:forEach>
                                </select>
                            </td>
                            <td width="20%"></td>
                            <td>&nbsp;</td>
                        </tr>
                        <tr>
                            <td align="right" width="20%">
                                &nbsp;
                                <input id="classTermBtn"  width="50" type="button" class="button_nor" value="ˢ�°༶ѧ�ڱ���" onclick="refreshCheck('classTermBtn','refreshClassTermCheck');">
                            </td>
                            <td width="20%">
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ѧ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;
                                <select name="classTerm">
                                    <option value="-1">��ѡ��</option>
                                    <c:forEach var="term" items="${terms}">
                                        <option value="<c:out value="${term.termId}"/>"><c:out value="${term.termName}"/></option>
                                    </c:forEach>
                                </select>
                            </td>
                            <td width="20%"></td>
                            <td>&nbsp;</td>
                        </tr>
                    </table>
				</form>
		</div>
	</body>
</html:html>
