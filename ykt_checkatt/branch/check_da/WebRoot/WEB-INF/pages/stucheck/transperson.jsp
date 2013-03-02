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
		<SCRIPT language='javascript'>
	function docheck(){
		if(validate()==false){
            return;
		}
   		document.forms[0].submit();	
	}
	function validate()
	{
		var startDate=document.forms[0].beginDate.value;
		var endDate=document.forms[0].endDate.value;
		
		if(startDate>endDate)
		{		
			alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
			return false;
		}
	}
        </SCRIPT>
	</head>
	<%
	String beginDate="";
	if(request.getAttribute("beginDate")!=null){
		beginDate = request.getAttribute("beginDate").toString();
	}else if(session.getAttribute("beginDate")!=null){
	    beginDate = session.getAttribute("beginDate").toString();
	}
	String endDate="";
	if(request.getAttribute("endDate")!=null){
		endDate = request.getAttribute("endDate").toString();
	}else if(session.getAttribute("endDate")!=null){
	   endDate = session.getAttribute("endDate").toString();
	}
    %>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> �����õ紦����־ </font> </strong>
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
				<html:form action="transperson.do?method=transPersonList" method="post" >
				 <tr> 
				   <td>
				   &nbsp;У  ��
                    <html:select property="schoolarea">
                        <html:option value="">��ѡ��</html:option>
                        <html:options collection="areaList" property="areaCode" labelProperty="areaName"/>
                    </html:select>
                   </td> 
            		 <td>
					&nbsp; ��ʼ����
					<html:text property="beginDate" size="10"  readonly="readonly" value="<%=beginDate%>"/>			
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
					</td>
					 <td>
					&nbsp; ��������
					<html:text property="endDate" size="10"  readonly="readonly" value="<%=endDate%>"/>
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
					<script type="text/javascript">
		                new calendar("beginDate", "calBegin", "%Y%m%d");
		                new calendar("endDate", "calEnd", "%Y%m%d");
            		</script>
            		</td>
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
			<ec:table items="transpersonList" var="person"  rowsDisplayed="50"
			    action="transperson.do?method=transPersonList"
			    locale="zh_CN"
			       filterable="false"
			    >
				<ec:exportXls fileName="transperson.xls"  tooltip="���� Excel" />
				<ec:row>
					<ec:column property="areaname"  title="У��" width="17%" sortable="false"   />
					<ec:column property="build" title="¥��" width="17%"  />
					<ec:column property="roomname" title="����" width="17%" />
					<ec:column property="updatedate" title="��������" width="17%"/>
					<ec:column property="updatetime" title="����ʱ��" width="17%" />
					<ec:column property="personname" title="������" width="15%" />
				</ec:row>
			</ec:table>
		</div>
		
	</body>
</html>

