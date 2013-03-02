<%@ page pageEncoding="GBK"%>
<%@ page import="com.kingstargroup.conference.common.StringUtil"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ page import="com.kingstargroup.conference.common.DateUtilExtend"%>

<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConference"%>

<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa"%>
<head>

	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css"
		rel="stylesheet" type="text/css" />
	<html:base />

	<style>
body{ margin:30px 10px 10px 10px; padding:0px;
font-size:12px; background-color:#F7F7F7;}
h1{
	color:#990000;
	font-family: "黑体";
	font-size:30px;
	text-align:center;
}
.mytitle{ font-size:14px; text-align:center;}
.table{ background-color:#FFFFFF; border:1px solid #CCCCCC; text-align:left; padding:10px; font-size:14px; width:96%; }
.table_content td{border-bottom:1px dotted #CCCCCC; line-height:40px;}
.table_content{ height:213px;vertical-align: middle}
.top{ vertical-align:top;}
.middle{ vertical-align:middle;}
.select{ background-color:#A9D0EB; border:1px solid #73ADDF; padding:5px; text-align:left; margin:18px 0px;}
.bigimg{ border:3px solid #E6E6E6;
}
.img{ text-align:center;}
.img img{ border:3px solid #DFDFDF;}
.img td{ text-align:center; width:12.5%; padding:5px 5px 0px 5px; vertical-align:top;}
</style>

</head>



<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0"
	ondblclick="holeset();">

	<form action="<%=ContextUtil.getCtxPath(request)%>/picreport.do"
		name="signAnalyseForm" method="post">
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<%
						TConference conference = (TConference) request
						.getAttribute("conference");
				int totleattendee = Integer.parseInt(request.getAttribute(
						"totleattendee").toString());
				int signednum = Integer.parseInt(request.getAttribute("signednum")
						.toString());
				int leavenum = Integer.parseInt(request.getAttribute("leavenum")
						.toString());
				int unsignnum = Integer.parseInt(request.getAttribute("unsignnum")
						.toString());
				float signRate = 0;
				if (totleattendee > 0) {
					signRate = signednum * 10000 / totleattendee / 100.00f;
				}
			%>
			<tr>
				<td height="12" align="center" valign="middle">
					<input type="hidden" name="timeout"
						value="<%=request.getAttribute("timeout") == null ? "9900"
					: request.getAttribute("timeout")%>">
				</td>
			</tr>
			<tr>
				<td>

					<h1>
						<%=conference.getConName()%>
					</h1>
				</td>
			</tr>
			<tr>
				<td class="mytitle">
					<strong><bean:message key="conference.confdate" />:</strong>
					<%=conference.getConEnddate()%>
					--
					<%=DateUtilExtend.reFormatTime(conference.getConBegintime()
							.toString()
							+ "00")%>
					<strong><bean:message key="conference.assembly" />: </strong>
					<%=GetDictionary.getAssemblyNameById(conference
									.getRoomId())%>
				</td>
			</tr>
			<tr>
				<td>
					<table width="100%" border="0" cellspacing="0" cellpadding="0"
						class="select">
						<tr>
							<td>
								<label>
									<select name="interface" class="select01"
										onchange="javascript:changinterface(this.value);">
										<OPTION value="justprev2">
											<bean:message key="conference.picshow" />
										</OPTION>
										<OPTION value="prev">
											<bean:message key="conference.totalinfo" />
										</OPTION>
										<OPTION value="justprev1">
											<bean:message key="conference.showinfo" />
										</OPTION>

										<OPTION value="prev1">
											<bean:message key="conference.cycleinfo" />
										</OPTION>
									</select>
								</label>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td>
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td class="middle" width="35%">
								<table width="100%" border="0" cellspacing="0" cellpadding="0"
									class="table">
									<tr>
										<td>
											<table width="100%" border="0" cellpadding="0"
												cellspacing="0" class="table_content" >
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="attendee.custname" />: </strong>
														<%=StringUtil.nullConvertToString(request
							.getAttribute("cutName"))%>
							</font>
													</td>
												</tr>
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="attendee.dept" />: </strong>
														<%=StringUtil.nullConvertToString(request
							.getAttribute("deptName"))%>
							</font>
													</td>
												</tr>
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="sign.signtime" />: </strong>
														<%=request.getAttribute("attendtime") == null ? ""
					: DateUtilExtend.reFormatTime((String) request
							.getAttribute("attendtime"))%>
							</font>
													</td>
												</tr>
											</table>
										</td>
									</tr>
								</table>
							</td>
							<td align="center">
								<img
									src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=0&stuempNo=<%=StringUtil.nullConvertToString(request.getAttribute("stuempNo"))%>&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
									height="280" width="200">
							</td>
							<td class="middle" width="35%">
								<table width="100%" border="0" align="right" cellpadding="0"
									cellspacing="0" class="table">
									<tr>
										<td class="top" width="40%" valign="middle">
											<table width="100%" border="0" cellpadding="0"
												cellspacing="0" class="table_content" >
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="analyse.attendper" />:
														</strong>
													</font>
													<font size="4" color="red">
														<%=signRate%>
														<%="%"%>
													</font>
													</td>
												</tr>
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="sign.totle" />: </strong>
														<%=totleattendee%>
														</font>
													</td>
												</tr>
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="sign.fact" />: </strong>
														<%=signednum%>
														</font>
													</td>
												</tr>
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="sign.leave" />: </strong>
														<%=leavenum%>
														</font>
													</td>
												</tr>
												<tr>
													<td>
													<font size="4">
														<strong><bean:message key="sign.nosign" />: </strong>
														<%=unsignnum%>
														</font>
													</td>
												</tr>
											</table>
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td style="padding-top:18px;">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td width="14">
								<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop1.gif" width="14" height="14" />
							</td>
							<td background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop2.gif">
								&nbsp;
							</td>
							<td width="14">
								<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop3.gif" width="14" height="14" />
							</td>
						</tr>
						<tr>
							<td
								style="border-left:1px solid #8CD4FA;background-color:#DFF1FD">
								&nbsp;
							</td>
							<td style="background-color:#DFF1FD">
								<table width="100%" border="0" cellspacing="0" cellpadding="0"
									class="img">
									<tr>
										<td height="100" width="12%" align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=0&stuempNo=<%=StringUtil.nullConvertToString(request.getAttribute("stuempNo"))%>&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
										<td height="100" width="13%" align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=1&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
										<td height="100" width="12%" align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=2&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
										<td height="100" width="13%" align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=3&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
										<td height="100" width="12%" align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=4&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
										<td height="100" width="13%" align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=5&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
										<td height="100" width="12%" align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=6&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
										<td align="center">
											<img
												src='/conference/ecardimage?confid=<%=request.getAttribute("confid")%>&id=7&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>'
												height="100">
										</td>
									</tr>
									<tr>
										<%
											List attList = (List) request.getAttribute("attList");
											if (attList != null) {
												Iterator iter = attList.iterator();
												int i = 0;
												boolean flag = true;
												while (iter.hasNext()) {
													HashMap row = (HashMap) iter.next();
													String firstName = StringUtil.nullConvertToString(request
													.getAttribute("cutName"));
													if (flag) {
												if (!row.get("cutName").equals(firstName)) {
													continue;
												} else {
													flag = false;
												}
													}
													i++;
													if (i > 8) {
												break;
													}
													if (i / 2 == 0) {
										%>
										<td height="100" width="12%" align="center">
											<%=row.get("cutName")%>
											<br>
											<br>
											<%=row.get("deptName")%>
										</td>
										<%
										} else {
										%>
										<td height="100" width="13%" align="center">
											<%=row.get("cutName")%>
											<br>
											<br>
											<%=row.get("deptName")%>
										</td>
										<%
												}
												}
												for (; i < 8; i++) {
													if (i / 2 == 0) {
										%>
										<td height="100" width="12%" align="left">
											&nbsp;
										</td>
										<%
										} else {
										%>
										<td height="100" width="13%" align="left">
											&nbsp;
										</td>
										<%
												}
												}
											} else {
										%>
										<td height="100" width="12%" align="center">
											&nbsp;
										</td>
										<td height="100" width="13%" align="center">
											&nbsp;
										</td>
										<td height="100" width="12%" align="center">
											&nbsp;
										</td>
										<td height="100" width="13%" align="center">
											&nbsp;
										</td>
										<td height="100" width="12%" align="center">
											&nbsp;
										</td>
										<td height="100" width="13%" align="center">
											&nbsp;
										</td>
										<td height="100" width="12%" align="center">
											&nbsp;
										</td>
										<td align="center">
											&nbsp;
										</td>

										<%
										}
										%>
									</tr>
								</table>
							</td>
							<td
								style="border-right:1px solid #8CD4FA; background-color:#DFF1FD">
								&nbsp;
							</td>
						</tr>
						<tr>
							<td>
								<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom1.gif" width="14" height="14" />
							</td>
							<td
								style="border-bottom:1px solid #8CD4FA; background-color:#DEF0FE">
								&nbsp;
							</td>
							<td>
								<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom3.gif" width="13" height="14" />
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</form>
	<script language="javascript">
var XMLHttpReq;
 	//创建XMLHttpRequest对象       
    function createXMLHttpRequest() {
		if(window.XMLHttpRequest) { //Mozilla 浏览器
			XMLHttpReq = new XMLHttpRequest();
		}
		else if (window.ActiveXObject) { // IE浏览器
			try {
				XMLHttpReq = new ActiveXObject("Msxml2.XMLHTTP");
			} catch (e) {
				try {
					XMLHttpReq = new ActiveXObject("Microsoft.XMLHTTP");
				} catch (e) {}
			}
		}
	}
	//发送请求函数
	function sendRequest() {
		createXMLHttpRequest();
        var url = "<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=request.getAttribute("confid")%>&attendeesign=prev2test&selecttype=totle&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>";
		XMLHttpReq.open("POST", url, true);
		XMLHttpReq.onreadystatechange = processResponse;//指定响应函数
		XMLHttpReq.send(null);  // 发送请求
	}
	// 处理返回信息函数
    function processResponse() {
    	if (XMLHttpReq.readyState == 4) { // 判断对象状态
        	if (XMLHttpReq.status == 200) { // 信息已经成功返回，开始处理信息
				DisplayHot();
				setTimeout("sendRequest()", 5000);
            } else { //页面不正常
                window.alert("请确保网络通畅。");
            }
        }
    }
    function DisplayHot() {
	    var flag = XMLHttpReq.responseText;
	    if(flag==1){
	    	document.location='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=request.getAttribute("confid")%>&attendeesign=justprev2&selecttype=totle&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>';
	    }
	}


</script>

	<script>
	function holeset(){
		if(parent.document.getElementById('subnavframe').style.display==''){
			parent.document.getElementById('subnavframe').style.display='none';
			parent.document.getElementById('top').style.display='none';
			parent.document.getElementById('bottom').style.display='none';
		}else{
			parent.document.getElementById('subnavframe').style.display='';
			parent.document.getElementById('top').style.display='';
			parent.document.getElementById('bottom').style.display='';
		}
		
	}
	
	function changinterface(interface){
	var tag = interface;
	window.location.href='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request, "confid")%>&selecttype=totle&attendeesign='+tag;
	}
	
	function cancelPage() {
      	self.location = '<%=ContextUtil.getCtxPath(request)%>/anal/totalquery.do';
	}
</script>

	<script language="javascript">
window.onload=function()
{
  	sendRequest();

}


</script>

</body>
