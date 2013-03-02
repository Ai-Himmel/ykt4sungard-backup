<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>查询</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<script language="javascript">
        function addnum(num)
        {
		if(tradeSerialForm.nowinput.value=="1" && tradeSerialForm.begin.value.length < 8 ){
			tradeSerialForm.begin.value+=num;
		}
		else if(tradeSerialForm.nowinput.value=="2" && tradeSerialForm.end.value.length < 8 ){
			tradeSerialForm.end.value+=num;
		}
        }
        function backnum()
        {
		if(tradeSerialForm.nowinput.value=="1")
			tradeSerialForm.begin.value=tradeSerialForm.begin.value.substring(0,tradeSerialForm.begin.value.length-1);
		else if(tradeSerialForm.nowinput.value=="2")
			tradeSerialForm.end.value=tradeSerialForm.end.value.substring(0,tradeSerialForm.end.value.length-1);
			
		
        }        
        function tab()
        {
              if(tradeSerialForm.nowinput.value=="1")
                 tradeSerialForm.end.focus();
              else if(tradeSerialForm.nowinput.value=="2")
                 tradeSerialForm.begin.focus();
        }
        function setDate()
        {
            var dDate = new Date();
            var year= dDate.getFullYear();
            var month= dDate.getMonth()+1;
            var day=dDate.getDate();
            if(month<10) month="0"+month;
            if(day<10) day="0" +day;
            tradeSerialForm.end.value=year+""+month+""+day;

            year= dDate.getFullYear();
            month= dDate.getMonth();
            day=dDate.getDate();
            day=day-7;
            dDate=new Date(year,month,day);
            year= dDate.getFullYear();
            month= dDate.getMonth()+1;
            day=dDate.getDate();
            if(month<10) month="0"+month;
            if(day<10) day="0" +day;
            tradeSerialForm.begin.value=year+""+month+""+day;
            

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
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
	</head>
	<body scroll="no" onload="javascript:setDate();" >
		<form action="<%=path%>/querytradeserial.do" method="post"
			name="tradeSerialForm">

			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="<%=path%>/pages/images/input_date.gif" width="343"
									height="57" />
							</div>
							<div>
								<ul>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/0.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/0a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/0.gif)"
									onclick="javascript:addnum(0)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/1.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/1a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/1.gif)"
									onclick="javascript:addnum(1)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/2.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/2a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/2.gif)"
									onclick="javascript:addnum(2)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/3.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/3a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/3.gif)"
									onclick="javascript:addnum(3)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/4.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/4a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/4.gif)"
									onclick="javascript:addnum(4)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/5.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/5a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/5.gif)"
									onclick="javascript:addnum(5)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/6.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/6a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/6.gif)"
									onclick="javascript:addnum(6)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/7.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/7a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/7.gif)"
									onclick="javascript:addnum(7)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/8.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/8a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/8.gif)"
									onclick="javascript:addnum(8)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/9.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/9a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/9.gif)"
									onclick="javascript:addnum(9)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/del.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/dela.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/del.gif)"
									onclick="javascript:backnum()"></li>									
								</ul>
							</div>
							<div id="login_input">
								<table width="410" border="0" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="206" align="right">
											<img src="<%=path%>/pages/images/be_date.gif" width="114"
												height="24" />
												<input type="hidden" name="nowinput" value="1"/>
										</td>
										<td width="214">
											<input type="text" name="begin" size="20" maxlength="8" class="info"
												onfocus="javascript:tradeSerialForm.nowinput.value='1'"/>
										</td>
									</tr>
									<tr>
										<td align="right">
											<img src="<%=path%>/pages/images/end_date.gif"
												width="114" height="23" />
										</td>
										<td>
											<input name="end" type="text"
												onfocus="javascript:tradeSerialForm.nowinput.value='2'" class="info"
												size="20" maxlength="8"/>
										</td>
									</tr>
									<tr>
										<td class="info">
											<html:errors />&nbsp;
										</td>
									</tr>
									<tr>
										<td colspan="3" valign="bottom">
											例如:日期2007年7月23日,则输入格式为20070723
										</td>
									</tr>
								</table>
							</div>
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:tradeSerialForm.submit();" onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" />
											</a>
										</td>
										<td>
											<a onclick="javascript: window.location='<%=path%>/main.do';" onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" />
											</a>
										</td>
									</tr>
								</table>
							</div>
						</div>
						<div id="login_right"></div>
					</div>
				</div>
			</div>
			<div id="bottom"></div>
		</form>
	</body>
</html>