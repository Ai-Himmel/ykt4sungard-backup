<%@ page pageEncoding="GBK"%>
<%@ page import="java.util.Iterator"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page import="java.util.List"%>
<%@ page import="com.kingstargroup.conference.common.DateUtilExtend"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConference"%>
<%@ page import="com.kingstargroup.conference.common.StringUtil"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="/html/commons/init.jsp"%>

<head>
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css">
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
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" ondblclick="javascript:holeset();">
	<%
				TConference conference = (TConference) request
				.getAttribute("conference");
		int totleattendee = Integer.parseInt(request.getAttribute(
				"totleattendee").toString());
		int signednum = Integer.parseInt(request.getAttribute("signednum")
				.toString());
		int leavenum = Integer.parseInt(request.getAttribute("leavenum")
				.toString());
		List leavelist = (List) request.getAttribute("leavelist");
		int replacenum = Integer.parseInt(request
				.getAttribute("replacenum").toString());
		List replacelist = (List) request.getAttribute("replacelist");
		int csignednum = Integer.parseInt(request
				.getAttribute("csignednum").toString());
		List csignedlist = (List) request.getAttribute("csignedlist");
		int unsignnum = Integer.parseInt(request.getAttribute("unsignnum")
				.toString());
//		List unsignlist = (List) request.getAttribute("unsignlist");
		float signRate = 0;
		if (totleattendee > 0) {
			signRate = signednum * 10000 / totleattendee / 100.00f;
		}
	%>
	<form id="SignPreview" name="SignPreview"
		action="<%=ContextUtil.getCtxPath(request)%>/preview.do" method="post">
		<table width="100%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="25" align="center" valign="middle">
				<input type="hidden" name="timeout"
									value="<%=request.getAttribute("timeout") == null ? "9900"
					: request.getAttribute("timeout")%>">
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					<table width="100%"border="0" cellpadding="0"
						cellspacing="0">
						<tr align="center" valign="middle">
							<td width="100%" align="center" valign="middle">								
								<h1><%=conference.getConName()%></h1>
							</td>
						</tr>

					</table>
				</td>
			</tr>
			<tr>
				<td height="42" align="center" valign="middle">
					<table width="95%" height="42" border="0" cellpadding="0"
						cellspacing="0">
						<tr align="center" valign="middle">
							<td width="35%" class="medium">
							
								<select name="interface" class="select01"
									onchange="javascript:changinterface(this.value);">
									<OPTION value="justprev1">
										<bean:message key="conference.showinfo" />
									</OPTION>
									<OPTION value="prev">
										<bean:message key="conference.totalinfo" />
									</OPTION>									
									<OPTION value="justprev2">
										<bean:message key="conference.picshow" />
									</OPTION>
									<OPTION value="prev1">
										<bean:message key="conference.cycleinfo" />
									</OPTION>
								</select>
								&nbsp;&nbsp;&nbsp;&nbsp;
							<input type="hidden" name="timeout" value="<%=request.getAttribute("timeout")==null?"9900":request.getAttribute("timeout")%>">
							</td>
							<td align="left" class="medium">
								<bean:message key="conference.confdate" />
								&nbsp;:&nbsp;
								<%=conference.getConEnddate()%>
								-
								<%=DateUtilExtend.reFormatTime(conference.getConBegintime()
							.toString()
							+ "00")%>
								&nbsp; &nbsp;
								<bean:message key="conference.assembly" />
								&nbsp;:&nbsp;
								<%=GetDictionary.getAssemblyNameById(conference
									.getRoomId())%>
								&nbsp;&nbsp;
							</td>
							<td align="center" valign="middle" class="medium"
								style="color: red;font: bold">
								<a><bean:message key="analyse.attendper" />[<%=signRate%>%]</a>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="95%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td>&nbsp;
								
						  </td>
							<td width="70%" height="25" align="center" valign="middle"
								class="medium">
								<a
									href='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request, "confid")%>&selecttype=totle&attendeesign=sign'>
									<bean:message key="sign.signed" />[<%=csignednum%>]</a>
							</td>
							<td align="center" valign="middle">&nbsp;
								
						  </td>

							<td align="center" valign="middle">&nbsp;
								
							</td>
							<td width="30%" height="25" align="center" valign="middle" class="medium"><bean:message key="sign.preview" />
							</td>

						</tr>
						<tr>
							<td width="10">&nbsp;
								
							</td>
							<td align="center" valign="top">
								<table width="100%" height="100%" border="0" cellpadding="0"
									cellspacing="0">
									<tr>
										<td align="left" valign="top" bgcolor="#DEF2FD">
											<table width="100%" border="0" cellpadding="0"
												cellspacing="0">
												<tr>
													<td width="14">
														<img
															src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop1.gif"
															width="14" height="14">
													</td>
													<td
														background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop2.gif">
														<img
															src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop2.gif"
															width="5" height="14">
													</td>
													<td width="14">
														<img
															src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/lefttop3.gif"
															width="14" height="14">
													</td>
												</tr>
											</table>
										</td>
									</tr>
									<tr>
										<td align="left" valign="top">
											<table width="100%" height="410" border="0" cellpadding="0"
												cellspacing="0">
												<tr>
													<td width="1" bgcolor="#8CD4FA">
														<img src="leftline.gif" width="1" height="3">
													</td>
													<td height="100%" align="center" valign="top"
														bgcolor="#DEF2FD">
														<table width="90%" border="0" cellspacing="0"
															cellpadding="0">
															<tr align="center" valign="middle">
																<td class="medium" width="25%">
																	<bean:message key="attendee.custname" />
																</td>
																<td class="medium" width="50%">
																	<bean:message key="attendee.dept" />
																</td>
								
																<td class="medium">
																	<bean:message key="sign.signtime" />
																</td>
															</tr>
															<%
																Iterator iter = csignedlist.iterator();
																int i = 0;
																while (iter.hasNext()) {
																	HashMap row = (HashMap) iter.next();
																	i++;
																	if (i > 18) {
																		break;
																	}
															%>
															<tr align="center" valign="middle">
																<td class="medium"
																	title="<%=StringUtil.nullConvertToString(row.get("dutyName"))%>">
																	<%=row.get("cutName")%>
																</td>
																<td class="medium">
																	<%=row.get("deptName")%>
																</td>
						
																<td class="medium">
																	<%=DateUtilExtend.reFormatTime(row.get("attendTime")
								.toString())%>
																</td>
															</tr>
															<%
															}
															%>
														</table>
													</td>
													<td width="1" bgcolor="#8CD4FA">
														<img src="leftline.gif" width="1" height="3">
													</td>
												</tr>
											</table>
										</td>
									</tr>
									<tr>
										<td align="left" valign="top">
											<table width="100%" border="0" cellpadding="0"
												cellspacing="0">
												<tr>
													<td width="14">
														<img
															src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom1.gif"
															width="14" height="14">
													</td>
													<td
														background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom2.gif">
														<img
															src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom2.gif"
															width="6" height="14">
													</td>
													<td width="14">
														<img
															src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/leftbottom3.gif"
															width="14" height="14">
													</td>
												</tr>
											</table>
										</td>
									</tr>
								</table>
							</td>
							<td width="14" align="center" valign="middle">&nbsp;
								
							</td>
							<td width="16" align="center" valign="middle">&nbsp;
								
							</td>
							<td width="10%" align="center" valign="top">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td align="center" valign="top">
											<table width="100%" border="0" cellspacing="0"
												cellpadding="0">
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellpadding="0"
															cellspacing="0">
															<tr>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop1.gif"
																		width="13" height="13">
																</td>
																<td
																	background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif"
																		width="7" height="13">
																</td>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop3.gif"
																		width="13" height="13">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellspacing="0"
															cellpadding="0">
															<tr>
																<td width="1" bgcolor="#BCE2F5">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif"
																		width="1" height="2">
																</td>
																<td align="center" valign="top" bgcolor="#F2F2F2">
																	<table width="98%" border="0" cellspacing="0"
																		cellpadding="0">
																		<tr align="center" valign="middle">
																			<td width="56%" class="medium">
																				<bean:message key="sign.totle" />
																			</td>
																			<td align="left" class="medium"
																				style="color: red;font: bold">
																				<%=totleattendee%>
																			</td>
																		</tr>
																		<tr align="center" valign="middle">
																			<td class="medium">
																				<bean:message key="sign.fact" />
																			</td>
																			<td align="left" class="medium"
																				style="color: red;font: bold">
																				<%=signednum%>
																			</td>
																		</tr>
																		<tr align="center" valign="middle">
																			<td class="medium">
																				<bean:message key="sign.leave" />
																			</td>
																			<td align="left" class="medium"
																				style="color: red;font: bold">
																				<%=leavenum%>
																			</td>
																		</tr>
																		<tr align="center" valign="middle">
																			<td class="medium">
																				<bean:message key="sign.replace" />
																			</td>
																			<td align="left" class="medium"
																				style="color: red;font: bold">
																				<%=replacenum%>
																			</td>
																		</tr>
																		<tr align="center" valign="middle">
																			<td class="medium">
																				<bean:message key="sign.nosign" />
																			</td>
																			<td align="left" class="medium"
																				style="color: red;font: bold">
																				<%=unsignnum%>
																			</td>
																		</tr>
																	</table>
																</td>
																<td width="1" bgcolor="#BCE2F5">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif"
																		width="1" height="2">
																	<img src="rightline.gif" width="1" height="2">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellpadding="0"
															cellspacing="0">
															<tr>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom1.gif"
																		width="13" height="14">
																</td>
																<td
																	background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif"
																		width="6" height="14">
																</td>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom3.gif"
																		width="13" height="14">
																</td>
															</tr>
														</table>
													</td>
												</tr>
											</table>
										</td>
									</tr>

									<tr>
										<td align="center" valign="middle" class="medium">
											<a
												href='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request, "confid")%>&selecttype=totle&attendeesign=leave'>
												<bean:message key="sign.leave" />[<%=leavenum%>]</a>
										</td>
									</tr>

									<tr>
										<td align="left">
											<table width="100%" border="0" cellspacing="0"
												cellpadding="0">
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellpadding="0"
															cellspacing="0">
															<tr>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop1.gif"
																		width="13" height="13">
																</td>
																<td
																	background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif"
																		width="7" height="13">
																</td>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop3.gif"
																		width="13" height="13">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellspacing="0"
															cellpadding="0">
															<tr>
																<td width="1" bgcolor="#BCE2F5">
																	<img src="rightline.gif" width="1" height="2">
																</td>
																<td height="95" align="center" valign="top"
																	bgcolor="#F2F2F2">
																	<table width="98%" border="0" cellspacing="0"
																		cellpadding="0">
																		<tr align="center" valign="middle">
																			<td class="medium">
																				<bean:message key="attendee.custname" />
																			</td>
																			<td class="medium">
																				<bean:message key="attendee.dept" />
																			</td>
																		</tr>
																		<%
																			Iterator iter3 = leavelist.iterator();
																			int i3 = 0;
																			while (iter3.hasNext()) {
																				HashMap row3 = (HashMap) iter3.next();
																				i3++;
																				if (i3 > 3) {
																					break;
																				}
																		%>
																		<tr align="center" valign="middle">
																			<td class="medium"
																				title="<%=StringUtil.nullConvertToString(row3.get("dutyName"))%>">
																				<%=row3.get("cutName")%>
																			</td>
																			<td class="medium">
																				<%=row3.get("deptName")%>
																			</td>
																		</tr>
																		<%
																		}
																		%>
																	</table>
																</td>
																<td width="1" bgcolor="#BCE2F5">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif"
																		width="1" height="2">
																	<img src="rightline.gif" width="1" height="2">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellpadding="0"
															cellspacing="0">
															<tr>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom1.gif"
																		width="13" height="14">
																</td>
																<td
																	background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif"
																		width="6" height="14">
																</td>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom3.gif"
																		width="13" height="14">
																</td>
															</tr>
														</table>
													</td>
												</tr>
											</table>
										</td>
									</tr>
									<tr>
										<td height="25" align="center" class="medium">
											<a
												href='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request, "confid")%>&selecttype=totle&attendeesign=replace'>
												<bean:message key="sign.replace" />[<%=replacenum%>]</a>
										</td>
									</tr>
									<tr>
										<td align="center" valign="top">
											<table width="100%" border="0" cellspacing="0"
												cellpadding="0">
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellpadding="0"
															cellspacing="0">
															<tr>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop1.gif"
																		width="13" height="13">
																</td>
																<td
																	background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop2.gif"
																		width="7" height="13">
																</td>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/righttop3.gif"
																		width="13" height="13">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellspacing="0"
															cellpadding="0">
															<tr>
																<td width="1" bgcolor="#BCE2F5">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif"
																		width="1" height="2">
																</td>
																<td height="95" align="center" valign="top"
																	bgcolor="#F2F2F2">
																	<table width="98%" border="0" cellspacing="0"
																		cellpadding="0">
																		<tr align="center" valign="middle">
																			<td class="medium">
																				<bean:message key="rep.name" />
																			</td>
																			<!--  <td class="medium"><bean:message key="attendee.dept"/></td>-->
																			<td class="medium">
																				<bean:message key="reped.name" />
																			</td>
																		</tr>
																		<%
																			Iterator iter4 = replacelist.iterator();
																			int i4 = 0;

																			while (iter4.hasNext()) {
																				HashMap row4 = (HashMap) iter4.next();
																				i4++;
																				if (i4 > 3) {
																					break;
																				}
																		%>
																		<tr align="center" valign="middle">
																			<td class="medium"
																				title="<%=StringUtil.nullConvertToString(row4.get("deptName"))%>">
																				<%=row4.get("repName")%>
																			</td>
																			<!-- <td class="medium"><%=StringUtil.nullConvertToString(row4.get("deptName"))%></td>-->
																			<td class="medium">
																				<%=row4.get("cutName")%>
																			</td>
																		</tr>
																		<%
																		}
																		%>
																	</table>
																</td>
																<td width="1" bgcolor="#BCE2F5">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightline.gif"
																		width="1" height="2">
																	<img src="rightline.gif" width="1" height="2">
																</td>
															</tr>
														</table>
													</td>
												</tr>
												<tr>
													<td align="left" valign="top">
														<table width="100%" border="0" cellpadding="0"
															cellspacing="0">
															<tr>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom1.gif"
																		width="13" height="14">
																</td>
																<td
																	background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom2.gif"
																		width="6" height="14">
																</td>
																<td width="13">
																	<img
																		src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/rightbottom3.gif"
																		width="13" height="14">
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
					</table>
				</td>
			</tr>

		</table>
	</form>

</body>
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
        var url = "<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=request.getAttribute("confid")%>&attendeesign=prev1test&selecttype=totle&attendtime=<%=StringUtil.nullConvertToString(request
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
				setTimeout("sendRequest()", 2000);
            } else { //页面不正常
                window.alert("请确保网络通畅。");
            }
        }
    }
    function DisplayHot() {
	    var flag = XMLHttpReq.responseText;
	    if(flag==1){
	    	document.location='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=request.getAttribute("confid")%>&attendeesign=justprev1&selecttype=totle&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>';
	    }
	}


</script>
<script>
function changinterface(interface){
	var tag = interface;
	window.location.href='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request, "confid")%>&selecttype=totle&attendeesign='+tag;
}

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
</script>

<script language="javascript">

window.onload=function()
{
 sendRequest();
}


</script>