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
            function insertDoolList(){
                var doorBtn = document.getElementById("doorBtn");
                doorBtn.disabled = "disabled";
                doorBtn.title = "�Զ��·��Ž���Ա�������ܻ����һ��ʱ�䣬�����ڶ�ʱ�����ٴ��·���";
                var url = "doorList.do?method=insertDoorList";
                new Ajax.Request(url,
                  {
                    method:'post',
                    onSuccess: function(result){
                        if(result.responseText.indexOf("error:")!=0){
                        } else {
                            alert(result.responseText);
                        }
                    }
                  });
            }
        </script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> �·����� </font> </strong>
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
                        <tr align="center">
                            <td>
                                &nbsp;
                                <input name="Submit" id="doorBtn"  width="50" type="button" class="button_nor" value="�Զ��·��Ž���Ա����" onclick="insertDoolList();">
                            </td>
                        </tr>
                    </table>
				</form>
		</div>
	</body>
</html:html>
