<%@ page contentType="text/html;charset=GBK"%>
<%@page import="com.kingstar.itemconfig.Configitem"%>
<%@page import="com.kingstargroup.fdykt.util.DateUtil"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
    <head>
        <title>网络转账确认</title>
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
            type="text/css" />
        <script language="javascript">
        function checkcfgfee(){
           var ras = document.getElementsByName('gid');
           var select=false;
			for(var i = 0;i<ras.length;i++){
			  if(ras[i].checked==true){
			   select=true;
			   break;
			 }
			} 
            if(select){
                document.selectForm.submit();
            }else{
                alert("请选择需要收费的项目！");
            }
        }
      </script>
        <script type="text/JavaScript">
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
    </script>
        <style type="text/css">
        .样式12 {
	        font-family: "宋体"; 
	        color: #000000; 
	        font-size: 16px; 
        }
        .样式13 {
	        font-family: "黑体"; 
	        color: #000000; 
	        font-size: 20px; 
	        border-collapse :collapse;
        }
        .样式14 {
	        font-family: "黑体"; 
	        color: #ff0000; 
	        font-size: 18px; 
        }
    }
    </style>
    </head>
    <body scroll="no">
        <form action="/smartcardweb/cfgfeeputin.do" method="post"
            name="selectForm">
            <div id="mid_top"></div>
            <div id="middle">
                <div id="Layer1">
                    <div id="content">
                        <div id="content_left"></div>
                        <div id="content_middle">
                            <div align="center">
                                <img src="/smartcardweb/pages/images/czjg.gif" width="314"
                                    height="82" />
                            </div>
                            <div id="content_input">
                                <table width="80%" border="0" align="center" cellpadding="0"
                                    cellspacing="0" height="320" class="box">
                                    <tr>
                                       <td height="320" align="left" class="样式13" id="msg" valign="top">
                                    <% Configitem cfgitemArr[] = (Configitem[])request.getAttribute("cfgitemArr");
                                        for(int i=0;i<cfgitemArr.length;i++){
                                            Configitem cfgitem = cfgitemArr[i];
                                            String starttime = cfgitem.getStartTime();
                                            String endtime = cfgitem.getEndTime();
                                            String display = cfgitem.getDisplay();
                                            String gid = cfgitem.getGid();
                                            String shopid = cfgitem.getShopId();
                                            String name = cfgitem.getName();
                                            String now = DateUtil.getNow("yyyy-MM-dd");
                                            if("true".equals(display)){
	                                            if(DateUtil.checkSpecialTimeSequence(starttime,now,"yyyy-MM-dd")<=0 && DateUtil.checkSpecialTimeSequence(endtime,now,"yyyy-MM-dd")>=0){
	                                  %>
	 
                                                  <input type="radio" name="gid" value="<%=gid%>"><%=name%> 【起始:<%=starttime%> 截止:<%=endtime%>】
                                                   <br>
                                                    <br>
	                                        <%
	                                            }else{
	                                        %>	 

                                                   <input type="radio" name="gid" value="<%=gid%>" disabled="disabled"><font color="gray"><%=name%> 【起始:<%=starttime%> 截止:<%=endtime%>】</font>                                                                                             
	                                               <br>
	                                                <br>
	                                                <%
	                                            }	                                            
                                            }
                                        }
                                        
                                     %>
                                      </td>
                                            </tr> 
                                     
                                </table>
                            </div>
                            <div id="content_buttom">
                                <table>
                                    <tr>
                                        <td align="center">
                                            <a onclick="javascript:checkcfgfee();"
                                                onmouseup="MM_swapImgRestore()"
                                                onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
                                                    src="/smartcardweb/pages/images/send.gif" name="send"
                                                    width="109" height="48" border="0" id="send" /> </a>
                                        </td>
                                        <td>
                                            <a
                                                onclick="javascript: window.location='/smartcardweb/main.do';"
                                                onmouseup="MM_swapImgRestore()"
                                                onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
                                                    src="/smartcardweb/pages/images/cancel.gif" name="cancel"
                                                    width="109" height="48" border="0" id="cancel" /> </a>
                                        </td>
                                    </tr>
                                </table>
                            </div>
                        </div>
                        <div id="content_right"></div>
                    </div>
                </div>
            </div>
            <div id="bottom"></div>
        </form>
    </body>
</html>

