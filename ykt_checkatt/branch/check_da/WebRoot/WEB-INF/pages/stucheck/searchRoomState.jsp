<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>   
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script> 
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> �����Ͽν����õ�״̬ </font> </strong>
		</div>
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<jodd:form bean="request">
				<html:form action="roomElec.do?method=getRoomElec" method="post" >
				 <tr> 
				   <td>
				   &nbsp;У  ��
                    <html:select property="schoolarea">
                        <html:option value="">��ѡ��</html:option>
                        <html:options collection="areaList" property="areaCode" labelProperty="areaName"/>
                    </html:select>
                   </td> 
            		<td>&nbsp;</td>
            		<td>&nbsp;</td>
            		<td>&nbsp;</td>
            		<td>
					<input name="Submit" width="50" type="button" class="button_nor" value="��  ѯ" onclick="docheck()">
					</td>
					</tr>
				</html:form>
			</jodd:form>
		</div>
	
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
				<td height="40" align="left" valign="middle" class="tdborder02">
					
					&nbsp;&nbsp;&nbsp;
					
				</td>
			</tr>
		</table>	
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="roomElecList" var="roomelec"  rowsDisplayed="50"
			    action="roomElec.do?method=getRoomElec"
			    locale="zh_CN"
			       filterable="false"
			    >
				<ec:exportXls fileName="roomelec.xls"  tooltip="���� Excel" />
				<ec:row>
					<ec:column property="areaname"  title="У��" width="15%" sortable="false"/>
					<ec:column property="build" title="¥��" width="15%"  />
					<ec:column property="roomname" title="����" width="15%" />
					<ec:column property="usedate" title="�Ͽ�����" width="15%"  />
					<ec:column property="begintime" title="��ʼʱ��" width="15%" />
					<ec:column property="endtime" title="����ʱ��" width="15%"/>
					<!-- ec:column property="state" title="�õ�״̬" width="60" headerStyle="text-align:center" style="text-align:center"  /-->
					<ec:column property="statename" title="�õ�״̬" width="10%" sortable="false" />
					<!--  ec:column property="serialno" title="��ˮ��" width="60" headerStyle="text-align:center" style="text-align:center"  /-->
				</ec:row>
			</ec:table>
		</div>
		
	</body>
</html>
<SCRIPT language='javascript'>
function docheck(){
    document.forms[0].submit();
}
function renderRow(row) {
    switch (row.cells[6].innerText) {
        case "��ʱδ�ϵ�":
            row.cells[6].style.background= "#FE3E00";
            break;
    }
}
window.setInterval(docheck , 60000);
renderTable('ec_table');
</SCRIPT>

