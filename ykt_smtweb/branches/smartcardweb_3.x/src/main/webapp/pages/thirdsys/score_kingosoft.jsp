<%@ page import="org.apache.commons.codec.digest.DigestUtils" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="java.util.Calendar" %>
<%@ page contentType="text/html;charset=GBK"
         errorPage="/smartcardweb/index.htm" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<html>
<head>
    <title>查询结果</title>
    <link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css"/>
    <script type="text/JavaScript">
        function MM_swapImgRestore() { //v3.0
            var i,x,a = document.MM_sr;
            for (i = 0; a && i < a.length && (x = a[i]) && x.oSrc; i++) x.src = x.oSrc;
        }

        function MM_preloadImages() { //v3.0
            var d = document;
            if (d.images) {
                if (!d.MM_p) d.MM_p = new Array();
                var i,j = d.MM_p.length,a = MM_preloadImages.arguments;
                for (i = 0; i < a.length; i++)
                    if (a[i].indexOf("#") != 0) {
                        d.MM_p[j] = new Image;
                        d.MM_p[j++].src = a[i];
                    }
            }
        }

        function MM_findObj(n, d) { //v4.01
            var p,i,x;
            if (!d) d = document;
            if ((p = n.indexOf("?")) > 0 && parent.frames.length) {
                d = parent.frames[n.substring(p + 1)].document;
                n = n.substring(0, p);
            }
            if (!(x = d[n]) && d.all) x = d.all[n];
            for (i = 0; !x && i < d.forms.length; i++) x = d.forms[i][n];
            for (i = 0; !x && d.layers && i < d.layers.length; i++) x = MM_findObj(n, d.layers[i].document);
            if (!x && d.getElementById) x = d.getElementById(n);
            return x;
        }

        function MM_swapImage() { //v3.0
            var i,j = 0,x,a = MM_swapImage.arguments;
            document.MM_sr = new Array;
            for (i = 0; i < (a.length - 2); i += 3)
                if ((x = MM_findObj(a[i])) != null) {
                    document.MM_sr[j++] = x;
                    if (!x.oSrc) x.oSrc = x.src;
                    x.src = a[i + 2];
                }
        }
        function gotoNextPage(page) {
            document.pagequery.page.value = page;
            document.pagequery.submit();
        }
    </script>
</head>
<%
    String schoolCode="12357";
    SimpleDateFormat simpleFormat = new SimpleDateFormat("yyyyMMdd");
    String currdate=simpleFormat.format(Calendar.getInstance().getTime());
    String stuempno=(String)session.getAttribute("stuempno");
    String cardno=(String)session.getAttribute("cardphyid");
    String md5String = DigestUtils.md5Hex(schoolCode + currdate + stuempno);
	if (stuempno==null){
        if (cardno==null){
            response.sendRedirect("/smartcardweb/logon.do");
        }else{
            out.write("<script>alter('您的卡片为匿名临时卡,无法查询成绩!');</script>");
        }
	}
%>
<body scroll="no"
      onload="MM_preloadImages('/smartcardweb/pages/images/previcea.gif','/smartcardweb/pages/images/nexta.gif','/smartcardweb/pages/images/backa.gif')">
<form name="pagequery" action="/smartcardweb/pagequery.do"
      method="post">
    <input name="page" type="hidden" value="1"/>
</form>
<div id="mid_top"></div>
<div id="middle">
    <div id="Layer1">
        <div id="content">
            <div id="content_left"></div>
            <div id="content_middle">
                <div align="center">
                    <img src="/smartcardweb/pages/images/result.gif" width="314"
                         height="82"/>
                </div>
                <div id="content_input">
                    <iframe width="100%" src="http://jw.ynjtc.com/JWWEB/_data/index_CXXSCJ.aspx?xh=<%=stuempno%>&str=<%=md5String%>"></iframe>
                </div>
                <div id="content_buttom">
                    <a onclick="javascript: window.location='/smartcardweb/main.do'"
                       onmouseout="MM_swapImgRestore()"
                       onmousedown="MM_swapImage('back','','/smartcardweb/pages/images/backa.gif',1)"><img
                            src="/smartcardweb/pages/images/back.gif" name="back"
                            width="109" height="48" border="0" id="back"/> </a>
                </div>
            </div>
            <div id="content_right"></div>
        </div>
    </div>
</div>
<div id="bottom"></div>
<object id="RFScanner"
        classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
        height="0"></object>
</body>
</html>

