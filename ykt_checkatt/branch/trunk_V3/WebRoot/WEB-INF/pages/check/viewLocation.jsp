<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
		<script>
			function addDeviceLocation(deviceid,devicename,deviceTypeName){
				var deviceTable = document.getElementById("deviceTable");
				var row = deviceTable.insertRow(deviceTable.rows.length);
				row.id = deviceid;
				var deviceNameCell = row.insertCell(0);
				deviceNameCell.innerHTML = devicename;
				var deviceTypeCell = row.insertCell(1);
				deviceTypeCell.innerHTML = deviceTypeName
				
				var operCell = row.insertCell(2);
				var deleteAction = '<a href="javascript:void(0);" onclick="deleteDeviceLocation('+deviceid+');">删除</a>';
				operCell.innerHTML = deleteAction;
			}
			function deleteDeviceLocation(deviceid){
				var form = document.deleteForm;
				form.deviceId.value=deviceid;
		        var url = "location.do?method=deleteDeviceLocation";
		        new Ajax.Request(url,
		        {
		            method:'post',
		            parameters: Form.serialize(form),
		            onSuccess: function(result) {
		            	if(""==result.responseText){
		            		var row = document.getElementById(deviceid);
		    				var deviceTable = document.getElementById("deviceTable");
		    				deviceTable.deleteRow(row.rowIndex);		
		            	} else {
		            		alert(result.responseText);	
		            	}
		            }
		        });
			}
			function selectDevice(){
				var locationId = document.getElementById("checkLocation.id").value;
	            var url = "location.do?method=selectDevice&locationId="+locationId;
	            window.open (url, "", "height=200, width=400, scrollbars=no, resizable=no,top=200,left=300");
			}
		</script>
	</head>
	<body>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> 考勤区域设置 </font> </strong>
				</div>
				<div id=lineDiv class="hrLine">
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
			<html:form action="location.do?method=saveLocation" method="post">
			<html:hidden property="checkLocation.id" />
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr align="center" valign=center>
							<td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">名称：</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<html:text property="checkLocation.name" styleClass="input_box" maxlength="100"/>
								
								
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> 设备： </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<table width="90%" id="deviceTable">
									<tr>
										<td width="30%">
										<logic:notEmpty property="checkLocation.id" name="locationForm">
											<a href="javascript:void(0);" onclick="selectDevice();">添加设备</a>
										</logic:notEmpty>
										</td>
										<td width="20%"></td>
										<td></td>
									</tr>
									<c:forEach var="deviceLocation" items="${deviceLocations}">
										<tr id="<c:out value="${deviceLocation.DEVICEID}" />">
											<td ><c:out value="${deviceLocation.DEVICENAME}" /></td>
											<td >
												<c:choose>
													<c:when test="${'1'==deviceLocation.CHECKTYPE}">CHECKIN设备</c:when>
													<c:when test="${'2'==deviceLocation.CHECKTYPE}">CHECKOUT设备</c:when>
													<c:when test="${'3'==deviceLocation.CHECKTYPE}">计时考勤设备</c:when>
													<c:when test="${'4'==deviceLocation.CHECKTYPE}">普通考勤设备</c:when>
												</c:choose>
											</td>
											<td><a href="javascript:void(0);" onclick="deleteDeviceLocation('<c:out value="${deviceLocation.DEVICEID}" />');">删除</a></td>
										</tr>
									</c:forEach>
								</table>
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="submit" class="submitButton" value=" 保存 ">
								<input name="Submit22" type="button" class="submitButton" value=" 取 消 " onclick="history.back();">

							</td>
						</tr>
					</tbody>
				</table>
			</html:form>
			<form name="deleteForm">
				<input type="hidden" name="deviceId" value=""/>
			</form>
			</tr>
	</body>
	</table>
</html>
