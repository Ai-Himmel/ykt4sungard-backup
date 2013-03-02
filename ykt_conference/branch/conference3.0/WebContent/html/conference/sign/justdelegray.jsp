<%@ page pageEncoding="GBK"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
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
	
</head>
<%String pretip = request.getAttribute("pretip").toString() ;%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0" ondblclick="javascript:holeset();">
	<form name="DelegrayPreview" id="SignPreview"
		action="<%=ContextUtil.getCtxPath(request)%>/preview.do" method=post>
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td>
					&nbsp;<input type="hidden" name="timeout"
									value="<%=request.getAttribute("timeout") == null ? "9900"
					: request.getAttribute("timeout")%>">
				</td>
			</tr>
			<tr>
				<td height="25" align="left" valign="middle"
					background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
					&nbsp;&nbsp;&nbsp;
					<span class="mediumwhite"><strong></strong> </span>&nbsp;
					<span class="mediumwhite"><strong></strong> </span>&nbsp;
					<span class="mediumwhite"><strong><%=pretip%> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="left" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<ec:table var="pres" items="delegraylist" filterable="false"
						imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
						rowsDisplayed="100"
						action="${pageContext.request.contextPath}/preview.do"
						form="DelegrayPreview">
						<ec:row highlightRow="true">
							<ec:column property="dlgtName" headerStyle="text-align:center"
								filterable="true" style="text-align:center" sortable="true"
								title='<%= GetProperty.getProperties("attendee.allot.delegray",getServletContext())%>'>
								<a href="<%=ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=justdelegray&id=${pres.delegray}">${pres.dlgtName}</a>
							</ec:column>
							<ec:column property="attendee" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.totle",getServletContext())%>'>
							</ec:column>
							<ec:column property="fact" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.fact",getServletContext())%>' />
							<ec:column property="ratio" headerStyle="text-align:center"
								style="text-align:center" filterable="true" sortable="true"
								title='<%= GetProperty.getProperties("sign.ratio",getServletContext())%>'>
								${pres.ratio}<%="%"%>
							</ec:column>
						</ec:row>
					</ec:table>
				</td>
			</tr>
		</table>
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="40" align="right" valign="middle" class="tdborder02">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.return"/>"
						onClick="javascript:renderCancelPage();">
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

window.onload=function()
{
	sendRequest();
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
