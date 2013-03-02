<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html>
	<head>
		<title>学生专栏</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css"></style>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
	</head>
    <body scroll="no">
        <div id="mid_top"></div>
        <div id="middle">
            <div id="Layer2">
                <div id="mid_center1">
                    <ul>
                    	<li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/jwxx.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/jwxxa.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/jwxx.gif)"
                            onclick="javascript: window.location='/smartcardweb/student/cjxx.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/tsgxx.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/tsgxxa.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/tsgxx.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xwtz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xwtza.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/xwtz.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';"></li>
                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center2">
                    <ul>
                    	<li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xsxx.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xsxxa.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/xsxx.gif)"
                            onclick="javascript: window.location='/smartcardweb/student/grxx.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xfjl.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xfjla.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/xfjl.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';"></li>
                       <%if(request.getSession().getAttribute("cardphyid")==null){ %>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/fhcd.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/index.jsp';"></li>
                       <%}else{%>
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/reset.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/reseta.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/reset.gif)"
                            onclick="javascript: window.location='/smartcardweb/usrexit.do';"></li>
                       <%} %>
                       

                    </ul>
                </div>
            </div>
        </div>
        <div id="bottom"></div>
        <object id="RFScanner"
            classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
            height="0"></object>
    </body>
</html>
