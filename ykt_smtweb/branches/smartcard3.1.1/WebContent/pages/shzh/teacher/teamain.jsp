<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html>
	<head>
		<title>��ʦר��</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css">

</style>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
	</head>
    <body scroll="no">
        <div id="mid_top"></div>
        <div id="middle">
            <div id="Layer2">
                <div id="mid_center1">
                    <ul>
                        <li style="cursor: pointer;" onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';">��ѧ��Ϣ</li>
                        <li style="cursor: pointer;" onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';">������Ϣ</li>
                        <li style="cursor: pointer;" onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';">�豸��Ϣ</li>
                        <li style="cursor: pointer;" onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';">����֪ͨ</li>
                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center2">
                    <ul>
                     	<li style="cursor: pointer;" onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';">������Ϣ</li>   
                        <li style="cursor: pointer;" onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';">ͼ�����Ϣ</li>   
                        <li style="cursor: pointer;" onclick="javascript: window.location='/smartcardweb/pages/shzh/funcinfo.jsp';">���Ѽ�¼</li>
                        
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
