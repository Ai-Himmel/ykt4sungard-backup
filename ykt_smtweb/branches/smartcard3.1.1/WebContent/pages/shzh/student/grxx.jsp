<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="java.util.Map" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%
	Map student = (Map)request.getAttribute("student");
%>
<html>
    <head>
        <title>个人信息</title>
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
        <link href="/smartcardweb/pages/css/menu.css" rel="stylesheet" type="text/css" />
        
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
            //-->
            </script>
	        <style type="text/css">
	        .样式5 {
	            font-family: "宋体"; 
	            color: #000000;
	            font-size: 18px;
	        }
	        .样式13 {
	            font-family: "黑体"; 
	            color: #ff0000; 
	            font-size: 18px; 
	            }
	        </style>
	        <script type="text/javascript">
				function easytabs(active,url) {
					var tabcount = 3;
					for (i = 1; i <= tabcount; i++) {
						document.getElementById("tablink" + i).className = 'tab' + i;
					}
					document.getElementById("tablink" + active).className = 'tab' + active + ' tabactive';
					for (i = 1; i <= tabcount; i++) {
						document.getElementById("li" + i).className = 'tab' + i;
					}
					document.getElementById("li" + active).className = 'tab' + active + ' tabactive';
					window.location= url;
				}											
			</script>
    </head>
    <body scroll="no"
		onload="MM_preloadImages('/smartcardweb/pages/images/backa.gif')">
		<div id="mid_top">
			<div class="menu">
				<ul style="width:420px;">
					<li class="tabactive" id="li1">
						<a href="javascript:easytabs('1','/smartcardweb/student/grxx.do');" id="tablink1" class="tab1 tabactive">个人信息</a>
					</li>
					<li id="li2">
						<a href="javascript:easytabs('2','/smartcardweb/student/jcxx.do');" id="tablink2" class="tab2">奖学金信息</a>
					</li>
					<li id="li3">
						<a href="javascript:easytabs('3','/smartcardweb/pages/shzh/funcinfo.jsp');" id="tablink3" class="tab3">就业信息</a>
					</li>
				</ul>
			</div>
		</div>
		<div id="middle">
			<div id="Layer1">
				<div id="content">
					<div id="content_left"></div>
					<div id="content_middle">
						<div align="center" style="height:80px;">
							
						</div>
						<div id="content_input">
							<table width="80%" border="0" align="center" cellpadding="0"
								cellspacing="0" class="box">
								<tr>
									<td height="30" class="样式13">学&nbsp;&nbsp;&nbsp;号</td>
									<td><%=student.get("XH") %></td>
								</tr>
								<tr>
									<td height="30" class="样式13">姓&nbsp;&nbsp;&nbsp;名</td>
									<td><%=student.get("XM") %></td>
								</tr>
								<tr>
									<td width="320" height="30" class="样式13">班&nbsp;&nbsp;&nbsp;级</td>
									<td><%=student.get("BH") %></td>
								</tr>
								<tr>
									<td height="30" class="样式13">出生日期</td>
									<td><%=student.get("CSRQ") %></td>
								</tr>
								<tr>
									<td height="35" class="样式13">籍&nbsp;&nbsp;&nbsp;贯</td>
									<td><%=student.get("JG") %></td>
								</tr>

								<tr>
									<td height="35" class="样式13">学籍状态</td>
									<td><%=student.get("XJZT") %></td>
								</tr>
							</table>
						</div>
						<div id="content_buttom">
							<a onclick="javascript: window.location='/smartcardweb/shzhstudent.do';"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('Image2','','/smartcardweb/pages/images/backa.gif',1)"><img
									src="/smartcardweb/pages/images/back.gif" name="Image2"
									width="109" height="48" border="0" id="Image2" /> </a>
						</div>
					</div>
					<div id="content_right"></div>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
	</body>
</html>

