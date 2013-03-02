<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>


<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
<script language="javascript">
	alert('<%=msg%>');
</script>
<%}%>
<body>
<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
�����ƶȲ�������
</font>
</strong>
</div>
<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
<tr> 
      <td height="40" align="left" valign="middle" class="tdborder02"> <input name="Submit" type="button" class="button_nor" value="���" onclick="window.location.href='workConf.do?method=addWorkConf_step1';" > &nbsp; <input name="Submit" type="button" class="button_nor" value="�鿴ȫ��" onclick="window.location.href='workConf.do?method=search';"> 
      </td>
    </tr>
<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>

<div>
<form name="searchWorkConf" action="workConf.do?method=search" method="post">
���ڲ�������:&nbsp;
<input name="search_workConfName" class="input_box"  maxlength=20>&nbsp; 
<input name="Submit" type="submit" class="button_nor" value="�� ѯ" >     
</form>
</div>

<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
</div>
<div id="operationDiv"  style="display :<c:out value='${show}' default='none'/>">
			<%@ include file="/pages/common/messages.jsp"%>
			<span class="operations"> <img src="<c:url value="/pages/images/icon/16x16/delete.gif"/>" align="top">&nbsp;<A href="#" onclick="javascript:batch_del(document.forms.ec,'�����ƶ�','<c:url value="workConf.do?method=delete" />');">ɾ ��</A> </span>
		</div>
<div id="tableDiv" style="display :<c:out value='${show}' default='none'/>">
			<ec:table items="workConfList" var="workConf" rowsDisplayed="5" action="workConf.do?method=search">
				<ec:exportXls fileName="leaveInfoList.xls" tooltip="���� Excel" />
				<ec:row>
				<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" style="text-align: center">
						<input type="checkbox" name="itemlist" value="${workConf.workconfid}" style="border:0px" />
					</ec:column>
					<ec:column property="confname" title="���ڲ�������" width="80" />
					<ec:column property="permitlatetime" title="����ٵ�" width="60" />
					<ec:column property="preearly" title="��������" width="80" />
					<ec:column property="ondutyad" title="�ϰ���ǰ�򿨲�����" width="120" />
					<ec:column property="offdutyovertime" title="�°��ͺ�򿨲�����" width="120" />
					<ec:column property="update" title="�޸�" width="40" sortable="false">
					<a href="workConf.do?method=update_step1&workConfid=${workConf.workconfid}">�޸�</a>
					</ec:column>
				</ec:row>
			</ec:table>

</div>