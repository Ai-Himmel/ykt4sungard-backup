<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ include  file="/pages/init.jsp"%>
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<script language="javascript" src="<%=path%>/pages/js/util.js"></script>
        
	</head>
	
	<script>
	  
	
	  function window.document.onkeydown()
		{     
		   var  butt = showKeyName(event);
		   // alert(event.keyCode);
		   if(butt=="<%=left1%>"){
		     window.location='<%=path%>/pages/yhkw.jsp';
		     return;
		   }
		   if(butt=="<%=left2%>"){
		     window.location='<%=path%>/pages/xykw.jsp';
		     return;
		   }
		   if(butt=="<%=left3%>"){
		        window.location = '<%=path%>/dsdj.do?deviceId='+deviceId;
	
		   }
		   if(butt=="<%=left4%>"){
		     window.location='<%=path%>/pages/zzyw.jsp';
		     return;
		   }
		   
		   
		   
		   if(butt=="<%=right1%>"){
		     window.location='<%=path%>/pages/cardmoney.jsp';
		     return;
		   }
		   
		    if(butt=="<%=right2%>"){
		     window.location='<%=path%>/pages/news.htm';
		     return;
		   }
		   
		  
		   if(butt=="<%=right3%>"){
		      window.location='<%=path%>/pages/help.htm';
		      return;
		   }
		}
		
	function GetHeader(src) { 
		  var ForReading=1; 
          var fso=new ActiveXObject("Scripting.FileSystemObject"); 
          var f=fso.OpenTextFile(src,ForReading); 
          return(f.ReadAll()); 
   } 
   function   readfile(){
	      var arr=GetHeader("c:\\smartcard.txt").split("\r\n");
	      if(arr !=null && arr.length>0){
	       // alert(arr[0].substring(arr[0].indexOf("=")+1,arr[0].length));
	        return  arr[0].substring(arr[0].indexOf("=")+1,arr[0].length);
	      }else{
	        return "";
	      }
  }
    var  deviceId=readfile();

    function dsdj(){
       window.location = '<%=path%>/dsdj.do?deviceId='+deviceId;
    }
    function doRef() 
	{   
		var url = '<%=path%>/monitor.do?deviceId='+deviceId; 
		var xmlhttp = new ActiveXObject("Microsoft.XMLHTTP"); 
		xmlhttp.abort() ; 
		xmlhttp.open( "post", url , true ); 
		xmlhttp.onreadystatechange = onSendSelf ; 
		xmlhttp.send() ; 
		function onSendSelf() 
		{ 
			if( xmlhttp.readyState != 4 ) 
			{ 
				return ; 
			} 
		}
	}  
      setInterval("doRef()" , 90000);  //单位毫秒  
	</script>
	

   
	<body scroll="no" onkeydown="return (event.keyCode!=8)">
	 
	  <form  name="form1" method="post" action="<%=path%>/monitor.do" target="self">

	
		<div id="mid_top"></div>
		
		<div id="middle">
			<div id="Layer2">
			 
				<div id="mid_center">
					<ul>
					
					   <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/yhkw.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/yhkw.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/yhkwa.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/yhkw.gif)"
							onclick="javascript: window.location='<%=path%>/pages/yhkw.jsp';"></li>
					  <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/xykw.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/xykw.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/xykwa.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/xykw.gif)"
							onclick="javascript: window.location='<%=path%>/pages/xykw.jsp';"></li>		

						<li
							onmouseout="this.style.background='url(<%=path%>/pages/images/zzyw.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/zzyw.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/zzywa.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/zzyw.gif)"
							onclick="javascript: window.location='<%=path%>/pages/zzyw.jsp';"></li>		
						
					</ul>
					</div>
				
			</div>
			<div id="Layer3">
				<div id="mid_center">
					<ul>
				
						
						 <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/kye.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/kye.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/kyea.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/kye.gif)"
							onclick="javascript: window.location='<%=path%>/pages/cardmoney.jsp';"></li>
						
						<li
							onmouseout="this.style.background='url(<%=path%>/pages/images/h2.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/h2.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/h2a.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/h2.gif)"
							onclick="javascript: window.location='<%=path%>/pages/news.htm';"></li>	
						
		
						<li
							onmouseout="this.style.background='url(<%=path%>/pages/images/h6.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/h6.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/h6a.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/h6.gif)"
							onclick="javascript: window.location='<%=path%>/pages/help.htm';"></li>

					</ul>        
		   
				</div>
				
			</div>
			
		</div>
	
		<div id="bottom">
	  	
		</div>
	
		
		<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
										codebase="<%=path%>/rf35.cab#version=2,0,0,7"></object>
		  </form>							
	</body>
</html>

