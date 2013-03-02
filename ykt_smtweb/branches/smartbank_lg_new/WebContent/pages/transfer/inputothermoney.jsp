<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html xmlns="http://www.w3.org/1999/xhtml">
<head>

<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	<%  	
	    String   bankno = session.getAttribute("bankno").toString();
	%>
	
	<script language="javascript">
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
	   function  check(){
	        var re =/^[0-9]*[1-9][0-9]*$/　　
	        var msg = document.getElementById("msg");
	        var money = document.inmoneyForm.money.value
	        if(money==""){
	          return false;
	        }
	        if(money>500){
	          msg.innerHTML="最大限额500元";
	          document.inmoneyForm.money.focus();
	          return false;
	        }
	        if(!re.test(money)){
	          msg.innerHTML="请输入整数金额";
	          document.inmoneyForm.money.focus();
	          return false;
	        }
	   		inmoneyForm.submit();  			
	   }
	</script>
	<body 	 scroll="no" onload="javascript:document.inmoneyForm.money.focus();">
	  <form name="inmoneyForm" action="<%=path%>/transferbankpwd.do" method="post" >
	   <div id="mid_top"></div>
		<div id="middle">
		 <div  id="screencenter">
		
		 <table> 
			<tr ><td class="msgcenter">
                  <b>请输入转账金额</b>
					 <input   type="text"  maxlength="3"   class="inputbox" size="10" name="money"  />
               </td>
            </tr>
            <tr>   
			<td  align="left" class="msgcenter" id="msg">
			        
		    </td></tr>
		 </table>	        
		</div>
		<div id="buttonbottom">
		     <table>       
			        <tr>
						 <td align="left" width="200">
								<a onclick="javascript:check();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
						</td>
						<td  align="right" width="200">
								<a
												onclick="javascript: window.location='<%=path%>/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
						</td>
					</tr>
			       </table>
		</div>
		
		</div>
		
		<div id="bottom"></div>
			<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
			codebase="<%=path%>/rf35.cab#version=2,0,0,7"></object>
		</form>
	</body>
</html>

