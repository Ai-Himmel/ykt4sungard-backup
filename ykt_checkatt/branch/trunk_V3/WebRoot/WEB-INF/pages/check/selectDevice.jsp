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
			function bindDevice(){
				var form = document.forms[0];
		        var url = "location.do?method=saveDeviceLocation";
		        new Ajax.Request(url,
		        {
		            method:'post',
		            parameters: Form.serialize(form),
		            onSuccess: function(result) {
		            	if(""==result.responseText){
			            	var deviceId = form.deviceId;
			            	var deviceType = form.deviceType;
			            	var deviceName = deviceId.options[deviceId.selectedIndex].text;
            				var deviceTypeName = deviceType.options[deviceType.selectedIndex].text;
		            		window.opener.addDeviceLocation(deviceId.value,deviceName,deviceTypeName);
		            		window.close();
		            	} else {
		            		alert(result.responseText);	
		            	}
		            }
		        });
			}	
		</script>
	</head>
	<body>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> 考勤设备绑定 </font> </strong>
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
				<form>
				<input type="hidden" name="locationId" value="<c:out value="${locationId}" />"/>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr align="center" valign=center>
							<td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium">名称：</span>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<select name="deviceId">
									<c:forEach var="device" items="${deviceList}">
										<option value="<c:out value="${device.DEVICEID}" />"><c:out value="${device.DEVICENAME}" /></option>	
									</c:forEach>
								</select>	
							</td>
						</tr>
						<tr>
							<td width="22%" align="right" valign="middle" bgcolor="#D1DAE9">
								<span class="medium STYLE5"> 设备类型： </span>
							</td>
							<td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
								<select name="deviceType">
									<option value="1">CHECKIN设备</option>
									<option value="2">CHECKOUT设备</option>
									<option value="3">计时考勤设备</option>
									<option value="4">普通考勤设备</option>
								</select>	
							</td>
						</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="button" class="submitButton" value=" 保存 " onclick="bindDevice();">
								<input name="Submit22" type="button" class="submitButton" value=" 关闭 " onclick="window.close();">

							</td>
						</tr>
					</tbody>
				</table>
				</form>
			</tr>
	</body>
	</table>
</html>
