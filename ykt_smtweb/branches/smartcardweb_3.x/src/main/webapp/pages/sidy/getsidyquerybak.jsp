<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page import="com.kingstargroup.fdykt.dto.TTifSubsidyDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
    <head>
        <title>补助领取确认</title>
        <link href="pages/css/css.css" rel="stylesheet" type="text/css" />
        <%
        String cardphyno = (String) request.getAttribute("cardphyno");
        String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
        String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
        String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
        String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
        %>
        <script language="javascript">
        function dogetsubquery(finishcount){
            var cardphyno ='<%=cardphyno%>';
            var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
            var device_port = '<%=read_card_device_port%>';
            document.all.RFScanner.PortNo=device_port;
            var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");            
           if(rrt == 0){
            var ret = document.all.RFScanner.ReadCardPocket(1,cardId,"");
            if(ret == 0){
                var sidyno = document.all.RFScanner.ReadCardSidyNo(cardId,"");
                if(sidyno>=0){
                    var doworkret = document.all.RFScanner.MySendRequest(serverbase+"getSidy.do","cardId="+cardId+"&sidyno="+sidyno);
                    if(doworkret == 0){
                    //领取成功
                    document.forms[0].cardphyno.value=cardphyno;
                    document.forms[0].sidyno.value=sidyno;
                    document.forms[0].submit();
                }else if(doworkret == -1){
                    //写卡失败
                    window.location='/smartcardweb/pages/sidy/recardwrite.jsp';
                }else if(doworkret == 1){
                    //领取失败
                    window.location='/smartcardweb/pages/sidy/getsidyfailue.jsp';                   
                }else{
                    window.location='/smartcardweb/pages/sidy/getsidyfailue.jsp';   
                }
              }else{
                    alert("请正确放置卡片...");
              }
                
            }else if(ret == 1){
                alert("请放置卡片...");
            }else{
                alert("请正确放置卡片...");
            }
            }else{
                alert("网络不通，请稍后重试...");
            }
        }
      </script>
        <script type="text/JavaScript">
    <!--
    function MM_swapImgRestore() { //v3.0
      var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
    }
    
    function MM_preloadImages() { //v3.0
      var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
        var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
        if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
    }
    
    function MM_findObj(n, d) { //v4.01
      var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
        d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
      if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
      for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
      if(!x && d.getElementById) x=d.getElementById(n); return x;
    }
    
    function MM_swapImage() { //v3.0
      var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
       if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
    }
    function gotoNextPage(page){
        document.pagequery.page.value = page;
        document.pagequery.submit();
    }
    //-->
    </script>
        <style type="text/css">
        .样式12 {
        font-family: "宋体"; 
        color: #000000; 
        font-size: 14px;        
        }
        .样式13 {
        font-family: "黑体"; 
        color: #000000; 
        font-size: 16px; 
        }
        .样式14 {
        font-family: "宋体"; 
        color: #000000; 
        font-size: 16px; 
        font-weight: bold;
        }
        </style>
    </head>
    <%
        String tpage = (String)request.getAttribute("page");
        int p = Integer.parseInt(tpage);
    %>

    <body scroll="no" >
        <form  name="writeCardForm" action="/smartcardweb/sidyList.do">
            <input type="hidden" name="cardphyno" />
            <input type="hidden" name="sidyno" />
        </form>
        <form  name="pagequery"  action="/smartcardweb/sidypagequery.do"  method="post">
           <input name="page" type="hidden" value="1" />
            <div id="mid_top"></div>
            <div id="middle">
                <div id="Layer1">
                    <div id="content">
                        <div id="content_left"></div>
                        <div id="content_middle">
                            <div align="center">
                                <img src="/smartcardweb/pages/images/bz.gif" width="314"
                                height="82" />
                            </div>
                            <div id="content_input">
                            <table width="100%" border="0" align="center" cellpadding="0"
                                cellspacing="0" class="box">
                                <tr>
                                    <td colspan="8" class="样式14">
                                        您的补助明细如下：
                                    </td>
                                </tr>
                                <tr align="center">

                                    <td align="center" class="样式13" width="20%">
                                        补助批次号
                                    </td>
                                    <td align="center" class="样式13" width="20%">
                                        客户号
                                    </td>
                                    <td align="center" class="样式13" width="15%">
                                        补助类型
                                    </td>
                                    <td align="center" class="样式13" width="10%">
                                        发生日期
                                    </td>
                                    <<td align="center" class="样式13" width="10%">
                                        领取日期
                                    </td>
                                    <!--  
                                    <td align="center" class="样式13" width="80">
                                        截至日期
                                    </td>-->
                                    <td align="center" class="样式13" width="15%">
                                        补助金额（元）
                                    </td>
                                    <td align="center" class="样式13" width="15%">
                                        状态
                                    </td>

                                </tr>
                                <%
                                    int serial_no = 1;
                                    int count = 0;
                                %>
                                <logic:iterate id="ttifsidy" name="ttifsidys" offset="0">
                                    <%
                                            TTifSubsidyDTO ts = (TTifSubsidyDTO) ttifsidy;
                                            String tx_date = ts.getPutdate();

                                            String get_date = ts.getGetdate();
                                            count++;
                                    %>
                                    <tr align="center">
                                        <td height="20">
                                            <div align="center" class="样式12">
                                                <bean:write name="ttifsidy" property="subsidyNo" />
                                                &nbsp;
                                            </div>
                                        </td>
                                        <td height="20">
                                            <div align="center" class="样式12">
                                                <bean:write name="ttifsidy" property="custNo" />
                                                &nbsp;
                                            </div>
                                        </td>
                                        <td height="20">
                                            <div align="center" class="样式12">
                                                <bean:write name="ttifsidy" property="subsidytype" />
                                                &nbsp;
                                            </div>
                                        </td>
                                        <td height="20">
                                            <div align="center" class="样式12">
                                                <%=tx_date%>
                                            </div>
                                        </td>
                                        <td height="20">
                                            <div align="center" class="样式12">
                                                <%=get_date%>
                                                
                                            </div>
                                        </td>
                                        <!-- 
                                        <td height="20">
                                            <div align="center" class="样式12"> 
                                               
                                            </div>
                                        </td>-->  
                                        <td height="20">
                                            <div align="center" class="样式12">
                                                <bean:write name="ttifsidy" property="amount" format="0.00" />
                                                &nbsp;
                                            </div>
                                        </td>
                                        <td height="20">
                                            <div align="center" class="样式12">
                                                <bean:write name="ttifsidy" property="status" />
                                                &nbsp;
                                            </div>
                                        </td>
                                    </tr>
                                </logic:iterate>
                                <%
                                for (int i = count; i < 10; i++) {
                                %>
                                <tr>
                                    <td height="20" class="样式12">
                                        &nbsp;
                                    </td>
                                    <td>
                                        &nbsp;
                                    </td>
                                    <td>
                                        &nbsp;
                                    </td>
                                    <td>
                                        &nbsp;
                                    </td>
                                    <td>
                                        &nbsp;
                                    </td>
                                
                                    <td>
                                        &nbsp;
                                    </td>
                                </tr>
                                <%
                                }
                                %>
                                <tr>
                                    <td align="left" colspan="8" class="样式14">
                                        <%
                                            String tcount = (String)request.getAttribute("count");
                                            int max = Integer.parseInt(tcount);
                                            if (max - (max / 10) * 10 > 0)
                                                max = max / 10 + 1;
                                            else
                                                max = max / 10;
                                        %>
                                        总共
                                        <%=max%>
                                        页 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 当前第
                                        <%=p%>
                                        页
                                    </td>
                                </tr>
                            </table>
                        </div>
                            
                            <div id="content_buttom">
                            <%
                                        if (p > 1) {
                                    %>
                                        <a onclick="javascript:gotoNextPage(<%=p - 1%>)"
                                            onmouseout="MM_swapImgRestore()"
                                            onmousedown="MM_swapImage('previce','','/smartcardweb/pages/images/previcea.gif',1)"><img
                                                src="/smartcardweb/pages/images/previce.gif" name="previce"
                                                width="109" height="48" border="0" id="previce" /> </a>
                                    <%
                                        }
                                        if (p < max) {
                                    %>
                                        <a onclick="javascript:gotoNextPage(<%=p + 1%>)"
                                            onmouseout="MM_swapImgRestore()"
                                            onmousedown="MM_swapImage('next','','/smartcardweb/pages/images/nexta.gif',1)"><img
                                                src="/smartcardweb/pages/images/next.gif" name="next"
                                                width="109" height="48" border="0" id="next" /> </a>
                                    <%
                                    }
                                    if( p == max ){
                                    %>
                                            <a onclick="javascript:dogetsubquery('<%=count%>');"
                                                onmouseup="MM_swapImgRestore()"
                                                onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
                                                    src="/smartcardweb/pages/images/send.gif" name="send"
                                                    width="109" height="48" border="0" id="send" /> </a>
                                    <%} %>
                                        
                                    <a
                                                onclick="javascript: window.location='/smartcardweb/index.do';"
                                                onmouseup="MM_swapImgRestore()"
                                                onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
                                                    src="/smartcardweb/pages/images/cancel.gif" name="cancel"  
                                                    width="109" height="48" border="0" id="cancel" /> </a>
                                    
                            </div>
                        </div>
                        <div id="content_right"></div>
                    </div>
                </div>
            </div>
            <div id="bottom"></div>
            <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
        </form>

    </body>
</html>


