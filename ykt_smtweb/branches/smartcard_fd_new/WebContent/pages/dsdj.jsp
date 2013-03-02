<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ include  file="/pages/init.jsp"%>
<script language="javascript" src="<%=path%>/pages/js/util.js">
</script><html xmlns="http://www.w3.org/1999/xhtml">
 <% 
	   
	  String group =request.getAttribute("group")==null?"":request.getAttribute("group").toString();
	  %>
	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css">
          
    </style>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
			
		<script>
		    function window.document.onkeydown()
		 {     
		   var  butt = showKeyName(event);
		   // alert(event.keyCode);
		   if(butt=="<%=left1%>"){
		     window.location='<%=path%>/logsys.do?para=cityHotspot&group=<%=group%>';
		     return;
		    }
		    if(butt=="<%=right4%>"){
		     window.location='<%=path%>/pages/index.jsp';
		     return;
		    }
		    
		  }
		</script>	
	</head>
  
	
	<body scroll="no" onkeydown="return (event.keyCode!=8)">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layerleft">
				<div id="mid_center">
					<ul>   
					   <%if("2".equals(group)) {%>
							<li 
							onmouseup="this.style.background='url(<%=path%>/pages/images/hlwf.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/hlwfa.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/hlwf.gif)"
							onclick="javascript: window.location='<%=path%>/logsys.do?para=cityHotspot&group=<%=group%>';">
							</li>
						<%} %>
							
					  <%  if("1".equals(group)){%>		
					      	<li 
							onmouseup="this.style.background='url(<%=path%>/pages/images/wfcz.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/wfcz.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/wfcz.gif)"
							onclick="javascript: window.location='<%=path%>/logsys.do?para=cityHotspot&group=<%=group%>';"></li>
					  <% }%>	
					  <li></li>	
					  <li></li>
					</ul>
				</div>
			</div>
			<div id="Layerright">
				<div id="mid_center">
					<ul>
                        <li></li>
                        <li></li>
                        <li></li>
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/fhcd.gif)"
							onclick="javascript: window.location='<%=path%>/pages/index.jsp';"></li>	
							
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>

	</body>
</html>
