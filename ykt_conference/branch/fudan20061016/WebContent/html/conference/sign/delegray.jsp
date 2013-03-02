<%@ page pageEncoding="GBK"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConference"%>
	<%@ page import="com.kingstargroup.conference.common.DateUtilExtend"%>
	<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page import="com.kingstargroup.conference.common.StringUtil"%>
<head>
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css"
		rel="stylesheet" type="text/css" />
	<html:base />	
	<style>
body{ margin:30px 10px 10px 10px; padding:0px;
font-size:12px; background-color:#F7F7F7;}
h1{
	color:#990000;
	font-family: "黑体";
	font-size:25px;
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
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0" ondblclick="javascript:holeset();">
	<form name="DelegrayPreview" id="SignPreview"
		action="<%=ContextUtil.getCtxPath(request)%>/preview.do" method=post>
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td colspan="3" height="1">
					&nbsp;<input type="hidden" name="timeout"
									value="<%=request.getAttribute("timeout") == null ? "9900"
					: request.getAttribute("timeout")%>">
				</td>
			</tr>
			<%
						TConference conference = (TConference) request
						.getAttribute("conference");
			%>
			
			<tr>
				<td align="center" valign="middle" colspan="3">
					<table width="100%"　border="0" cellpadding="0"
						cellspacing="0">
						<tr align="center" valign="bottom">
							<td width="100%" align="center" valign="middle">
								<h1><%=conference.getConName()%></h1>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle" colspan="3">
					<table width="100%" border="0" cellpadding="0"
						cellspacing="0">
						<tr align="center" valign="middle">
							<td align="center" valign="middle" class="medium">
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
						</tr>
					</table>
				</td>
			</tr>
			
			<tr>
				<td align="center" valign="top" width="48%">
					<ec:table var="pres1" items="delegraylist1" filterable="false" 
						imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
						rowsDisplayed="100" showPagination="false" 
						action="${pageContext.request.contextPath}/preview.do"
						form="DelegrayPreview" >
						<ec:row highlightRow="true" >
							<ec:column property="dlgtName" headerStyle="text-align:center"
								filterable="true" 
								title='<%= GetProperty.getProperties("attendee.allot.delegray",getServletContext())%>'>
								<a href="<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=delegray&id=${pres1.delegray}"><font size="3">${pres1.dlgtName}</font></a>
							</ec:column>
							<ec:column property="attendee" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.totle",getServletContext())%>'>
								<font size="3">${pres1.attendee}</font>
							</ec:column>
							<ec:column property="fact" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.fact",getServletContext())%>' >
							<font size="3">${pres1.fact}</font>
							</ec:column>
							<ec:column property="ratio" headerStyle="text-align:center"
								style="text-align:center " filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.ratio",getServletContext())%>'>
								<font size="3">${pres1.ratio}<%="%"%></font>
							</ec:column>
						</ec:row>
					</ec:table>
				</td>
				<td>
				&nbsp;
				</td>
				<td align="center" valign="top"  width="48%">
				<ec:table var="pres2" items="delegraylist2" filterable="false" 
						imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
						rowsDisplayed="100" showPagination="false" 
						action="${pageContext.request.contextPath}/preview.do"
						form="DelegrayPreview" >
						<ec:row highlightRow="true">
							<ec:column property="dlgtName" headerStyle="text-align:center"
								filterable="true"
								title='<%= GetProperty.getProperties("attendee.allot.delegray",getServletContext())%>'>
								<a href="<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=delegray&id=${pres2.delegray}"><font size="3">${pres2.dlgtName}</font></a>
							</ec:column>
							<ec:column property="attendee" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.totle",getServletContext())%>'>
								<font size="3">${pres2.attendee}</font>
							</ec:column>
							<ec:column property="fact" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.fact",getServletContext())%>' >
								<font size="3">${pres2.fact}</font>
							</ec:column>
							<ec:column property="ratio" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.ratio",getServletContext())%>'>
								<font size="3">${pres2.ratio}<%="%"%></font>
							</ec:column>
						</ec:row>
					</ec:table>
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
        var url = "<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=request.getAttribute("confid")%>&selecttype=delegraytest&attendtime=<%=StringUtil.nullConvertToString(request
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
				interval();
				setTimeout("sendRequest()", 2000);
            } else { //页面不正常
                window.alert("请确保网络通畅。");
            }
        }
    }
    function DisplayHot() {
	    var flag = XMLHttpReq.responseText;
	    if(flag==1){
	    	document.location='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=request.getAttribute("confid")%>&selecttype=delegray&attendtime=<%=StringUtil.nullConvertToString(request
							.getAttribute("attendtime"))%>';
	    }
	}


</script>
	<script>
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/sign/preview.do';
	}
</script>

<script>

var duration=document.getElementById("timeout").value;
var endTime = new Date().getTime() + duration + 100;
function interval()
{
    var n=(endTime-new Date().getTime())/1000;
    if(n<0) return;
    duration -= 1000;
    document.getElementById("timeout").value = duration;
    setTimeout(interval, 1000);
    
}
window.onload=function()
{
    setTimeout("window.location.href='<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request, "confid")%>&selecttype=totle&attendeesign=prev1'", duration);
    sendRequest();
    interval();
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


</body>
