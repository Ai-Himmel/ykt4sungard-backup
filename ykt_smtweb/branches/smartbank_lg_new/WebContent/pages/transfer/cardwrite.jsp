<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title>返回信息</title>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet" type="text/css" />
		<%
		    String password = request.getParameter("password").toString();
		    String cardno = request.getParameter("cardno").toString();
		    
		%>
		
		<script type="text/JavaScript">
		   function  transfer(){
			var cardId ='<%=cardno%>';
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
			document.all.RFScanner.PortNo=device_port;
			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
			var ret = document.all.RFScanner.ReadCardPocket(1,cardId,"");
			if(ret == 0){
				var doworkret = document.all.RFScanner.MySendRequest(serverbase+"dealTransfer.do","cardId="+cardId);
				if(doworkret == 0){
					//转账成功，显示成功页
					
				}else if(doworkret == -1){
					//写卡失败
					window.location='<%=path%>/pages/sidy/recardwrite.jsp';
				}else{
					window.location='<%=path%>/pages/sidy/getsidyfailue.jsp';	
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
	</head>
	<%
	   
	%>
  <body scroll="no" onload="transfer()">
	  <div id="mid_top"></div>
			<div id="middle">
				<div  id="screencenter">
		  
		        <table> 
			    <tr ><td class="msgcenter"><b>转账中请稍候......
			    </b>
			    <td class="msgcenter"><b>提示：转账过程中请勿将校园卡拿离读卡区！
			    </b>
			    </td>

		      </table>	        
		         </div>
			</div>
	 <div id="bottom"></div>
	 <object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
				    codebase="<%=path%>/rf35.cab#version=2,0,0,7"></object>
	</body>
</html>


