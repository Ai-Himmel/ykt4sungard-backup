<%@ page contentType="text/html;charset=GBK"%>
<html>
    <head>
        <title>���ſ�Ѷ����Ա��½</title>
        <meta http-equiv="pragma" content="no-cache" />
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
            type="text/css" />
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
        function newsLogin(){
			var newsform = document.newsform;
			newsform.submit();
        }
        </script>
    </head>
    <body scroll="no">
    <form name="newsform" action="/smartcardweb/newslogin.do" method="post">
        <div id="mid_top"></div>
        <div id="middle">
            <div id="Layer1">
                <div id="content">
                    <div id="content_left"></div>
                    <div id="content_middle">
                        <div align="center">
                            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                <tr>
                                    <td height="80"></td>
                                </tr>
                            </table>
                        </div>

                        <div id="content_input">
                            <table width="95%" border="0" align="center" cellpadding="0"
                                cellspacing="20" >
								<tr>
									<td colspan="2" align="center"><font color="red"><%=request.getAttribute("error")==null?"":request.getAttribute("error").toString() %></font></td>
								</tr>
                                <tr>
                                	<td width="40%" align="right">
                                		�û�����
                                	</td>
                                	<td valign="top">
                                		<input type="text" name="newsuser" value="<%=request.getAttribute("newsuser")==null?"":request.getAttribute("newsuser").toString() %>"/>
                                	</td>
                                </tr>
                                <tr>
                                	<td align="right">
                                		���룺
                                	</td>
                                	<td valign="top">
                                		<input type="password" name="newspassword" value="<%=request.getAttribute("newspassword")==null?"":request.getAttribute("newspassword").toString() %>"/>
                                	</td>
                                </tr>
                            </table>
                        </div>
                        <div id="content_buttom">
                            <table>
                                <tr>
                                    <td>
                                        <a
                                            onclick="javascript:newsLogin();"
                                            onmouseup="MM_swapImgRestore()"
                                            onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/botton.gif',1)"><img
                                                src="/smartcardweb/pages/images/botton.gif" name="cancel"
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
         <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0"></object>
    </form>
    </body>
</html>


