<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="java.util.List" %>
<html>
    <head>
        <title>新闻快讯维护</title>
        <meta http-equiv="pragma" content="no-cache" />
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
            type="text/css" />
        <script type="text/javascript" src="/smartcardweb/pages/javascript/prototype.js" ></script>
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
        function updateNews(){
			var newsform = document.newsform;
			newsform.submit();
        }
        function loadFile(fileName){
            var ulTag = document.getElementById("fileNames");
            var liTags = ulTag.childNodes;
            for(var i=0;i<liTags.length;i++){
                if(liTags[i].id==fileName){
                	liTags[i].style.backgroundColor="#0099FF";   
                } else {
                	liTags[i].style.backgroundColor="";    
                }
            }
            var url = "/smartcardweb/readnews.do?fileName="+fileName;
            new Ajax.Request(url,
            {
                method:'post',
                onSuccess: function(result) {
                    if (result.responseText.indexOf("error:") != 0) {
                    	document.getElementById("news").value=result.responseText; 
                    } else {
                    	alert(result.responseText);    		  
                    }
                }
            });
        }
        </script>
        <style type="text/css">
        .样式12 {
        font-family: "宋体"; 
        color: #000000; 
        font-size: 16px; 
        }
        </style>
    </head>
    <body scroll="no">
    <form name="newsform" action="/smartcardweb/updatenews.do" method="post">
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
                                cellspacing="0" >
								<tr>
									<td colspan=2"><font color="red"><%=request.getAttribute("error")==null?"":request.getAttribute("error").toString() %></font></td>
								</tr>
                                <tr>
                                	<td height="320" width="150px" valign="top">
                                	<ul id="fileNames" style="width:150px;height:310;overflow:auto;float:left;white-space:nowrap;font-size:16;line-height:23px;margin:0;padding:0;">
                                		<%
                                    		List<String> fileNames = (List<String>)request.getAttribute("fileNames");
                                    		for(int i=0;i<fileNames.size();i++){
                                    			if(i==0){
                                    	%>
                                    			<li style="height:23px;line-height:23px;margin:0;width:130px;cursor:hand;background-color:#0099FF;" onclick="javascript:loadFile('<%=fileNames.get(i) %>');" id="<%=fileNames.get(i) %>"><%=fileNames.get(i) %></li>
                                    	<%
                                    			} else {
                                    	%>
                                    			<li style="height:23px;line-height:23px;margin:0;width:130px;cursor:hand;" onclick="javascript:loadFile('<%=fileNames.get(i) %>');" id="<%=fileNames.get(i) %>"><%=fileNames.get(i) %></li>
                                    	<%
                                    			}
                                    	%>
                                    	<%
                                    		}	
                                    	%> 
                                	</ul>
                                	</td>
                                    <td  height="320" valign="top">
                                        <textarea rows="20" cols="90" name="news" id="news"><%=request.getAttribute("news")==null?"":request.getAttribute("news").toString() %></textarea>
                                    </td>
                                </tr>
                            </table>
                        </div>
                        <div id="content_buttom">
                            <table>
                                <tr>
                                    <td>
                                        <a
                                            onclick="javascript:updateNews();"
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


