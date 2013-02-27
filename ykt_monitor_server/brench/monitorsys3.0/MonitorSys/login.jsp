<%@ page language="java" pageEncoding="GBK"%>
<%@ include file="/pages/commons/init.jsp"%>
<html>
    <head>
        <title>南京大学校园一卡通监控运维平台</title>


<SCRIPT LANGUAGE="javascript" FOR="window" EVENT="onload">
<!--
    document.form1.username.focus();
-->
</SCRIPT>

<style type="text/css">
input {
font-family:Arial,Verdana,Helvetica,sans-serif;
font-size:9pt;
}

.ViewHeader {
    background-color: #FFDEAD;
    font-family: Arial, Helvetica, sans-serif;
    font-size: 9pt;
}


.NavBarTabs {
    background-color: #D27E00;
}

<!--
.style1 {
    font-family: "Arial"
}

.style2 {
    font-size: x-large;
    font-weight: bold;
    color: #663300;
}

.style4 {
    color: #663300;
    font-weight: bold;
}
-->
</style>
    </head>
    <body MARGINHEIGHT="0" marginwidth="0" leftmargin="0" topmargin="0">
        <table cellpadding="0" border="0" cellspacing="0" width="100%"
            height="100%">
            <tr valign="top" height="0%">
                <td bgcolor="Black">
                    &nbsp;
                </td>
            </tr>
            <tr valign="top" height="100%">
                <td>
                    <table align="center" cellspacing="0" cellpadding="30" border="0"
                        width="100%" height="106%" bgcolor="#FFDEAD">
                        <tr valign="top">
                            <td>
                                <html:form action="login.do?method=login">
                                    <table border="0" cellpadding="3" cellspacing="0"
                                        align="center">
                                        <tr>
                                            <td height="75" colspan="2">
                                            </td>
                                        </tr>
                                        <tr>
                                            <td height="15" colspan="3" valign="top" nowrap="nowrap"
                                                class="PageHeader style1">
                                                <span class="style2">&#27426;&#36814;&#20351;&#29992;</span>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td height="7" colspan="3" valign="top" nowrap="nowrap"
                                                class="PageHeader">
                                                <span class="style4"><font size="3">南京大学校园一卡通监控运维平台</font>
                                                </span>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td colspan="3" valign="top" nowrap="nowrap" height="8"
                                                class="PageHeader">
                                                &nbsp;
                                            </td>
                                        </tr>
                                        <tr>
                                            <td width="13">
                                                <b></b>
                                            </td>
                                            <td width="66">
                                                <b><font face="Arial" size="2">用户名：</font>
                                                </b>
                                            </td>
                                            <td width="194">
                                                <b><font face="Arial" size="2"><html:text property="UserName" size="15"></html:text>
                                                </font>
                                                </b>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>
                                                <div align="left">
                                                    <b></b>
                                                </div>
                                            </td>
                                            <td>
                                                <b><font face="Arial" size="2">密&nbsp;&nbsp;&nbsp;码：</font>
                                                </b>
                                            </td>
                                            <td width="194">
                                                <b><font face="Arial" size="2"><html:password property="PassWord" size="15"></html:password>
                                                </font>
                                                </b>
                                            </td>
                                        </tr>
                                    </table>
                                    <p align="center">
                                          <html:image src="/monitorsys/pages/images/Button_Login.gif" border="0"></html:image>
  
                                    </p>
                                    <p align="center">
                                        <b><font face="Arial" size="3" color="red"><html:errors/> </font>
                                        </b>
                                    </p>
                                    <div align="left">
                                    </div>
                               </html:form>
                            </td>
                        </tr>
                        <tr valign="top">
                            <td>
                                &nbsp;
                            </td>
                        </tr>
                    </table>

                    <div align="center"></div>
                    <div align="center"></div>
                    <div align="center">  </div>
                </td>
            </tr>
            <tr valign="bottom" height="0%">
                <td>
                    <table class="NavBarTabs" width="100%" height="20" cellspacing="0"
                        cellpadding="0" border="0">
                        <tr>
                            <td Class="Copyright" align="center">
                                Copyright 2005-2009 Nanjin University All Rights Reserved
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
        </table>

    </body>
</html>