<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title>������Ϣ</title>
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
					//ת�˳ɹ�����ʾ�ɹ�ҳ
					
				}else if(doworkret == -1){
					//д��ʧ��
					window.location='<%=path%>/pages/sidy/recardwrite.jsp';
				}else{
					window.location='<%=path%>/pages/sidy/getsidyfailue.jsp';	
				}

			}else if(ret == 1){
				alert("����ÿ�Ƭ...");
			}else{
				alert("����ȷ���ÿ�Ƭ...");
			}
			}else{
				alert("���粻ͨ�����Ժ�����...");
			}
		}
		</script>
		<style type="text/css">
		.��ʽ5 {
			font-family: "����"; 
			color: #000000;
			font-size: 18px;
		}
		.��ʽ13 {
		font-family: "����"; 
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
			    <tr ><td class="msgcenter"><b>ת�������Ժ�......
			    </b>
			    <td class="msgcenter"><b>��ʾ��ת�˹���������У԰�������������
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


