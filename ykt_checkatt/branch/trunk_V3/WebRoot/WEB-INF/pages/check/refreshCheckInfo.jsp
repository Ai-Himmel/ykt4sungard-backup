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
			function refreshCheckInfo(){
				var refreshButton = document.getElementById("refreshButton");
				refreshButton.value = "正在处理，请稍候...";
				refreshButton.disabled = true;
				
				var form = document.forms[0];
		        var url = "checkInfo.do?method=refreshCheckInfo";
		        new Ajax.Request(url,
		        {
		            method:'post',
		            parameters: Form.serialize(form),
		            onSuccess: function(result) {
		            	alert(result.responseText);	
		            	refreshButton.value = "生成考勤数据";	
	            		refreshButton.disabled = false;
		            }
		        });
			}
			function changeStatus(status){
				var statusInput = document.getElementById("status");
				statusInput.value= status;
				disableBtn(status);				
				var form = document.forms[0];
		        var url = "checkInfo.do?method=autoCreateCheckInfo";
		        new Ajax.Request(url,
		        {
		            method:'post',
		            parameters: Form.serialize(form),
		            onSuccess: function(result) {
		            	if(""==result.responseText){
		            		success(status);	
		            	} else {
		            		alert(result.responseText);	
		            		failure(status);	
		            	}
		            }
		        });
			}
			function disableBtn(status){
				var openBtn = document.getElementById("openBtn");
				var closeBtn = document.getElementById("closeBtn");
				if("open"==status){
					openBtn.disabled = true;
				} else if("close"==status){
					closeBtn.disabled = true;
				}
			}
			function success(status){
				var openBtn = document.getElementById("openBtn");
				var closeBtn = document.getElementById("closeBtn");
				if("close"==status){
					openBtn.disabled = false;
				} else if("open"==status){
					closeBtn.disabled = false;
				}
			}
			function failure(status){
				var openBtn = document.getElementById("openBtn");
				var closeBtn = document.getElementById("closeBtn");
				if("open"==status){
					openBtn.disabled = false;
				} else if("close"==status){
					closeBtn.disabled = false;
				}
			}
		</script>
	</head>
	<body>
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 生成考勤信息 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div>
			<form name="create" method="post">
			<input type="hidden" name="status" id="status"/>
				<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
					<tr>
						<td height="40" align="middle" valign="middle" class="tdborder02">
							日期范围:
							<input class="input_box" style="width:80" maxlength=20 name="startDate" readonly="readonly" value="<c:out value='${yesterday}' />" onclick="change();">
							<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
							<input class="input_box" style="width:80" maxlength=20 name="endDate" readonly="readonly" value="<c:out value='${yesterday}' />" onclick="change();">
							<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt=check style="cursor:pointer">
							<script type="text/javascript">
                				new calendar("startDate", "calBegin", "%Y%m%d");
                				new calendar("endDate", "calEnd", "%Y%m%d");
            				</script>
						    &nbsp;
							<input id="refreshButton" type="button" class="submitButton" value="生成考勤数据" onclick="refreshCheckInfo();">
						</td>
					</tr>
				</table>
				<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
					<tr>
						<td height="40" align="center" valign="middle" class="tdborder02">
							<input id="openBtn" name="Submit" type="button" class="submitButton" value="启动自动生成数据功能" <c:out value='${open}' default="disabled"/> onclick="changeStatus('open');">
							&nbsp;&nbsp;
							<input id="closeBtn" name="Submit" type="button" class="submitButton" value="关闭自动生成数据功能" <c:out value='${close}' default="disabled"/> onclick="changeStatus('close');">
						</td>
					</tr>
				</table>
			</form>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
	</body>
</html>
