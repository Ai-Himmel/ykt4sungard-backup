<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>卡卡转账扣卡</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
            String cardphyno = request.getAttribute("cardphyno") == null ? "" : request
                    .getAttribute("cardphyno").toString();
	        String cardbalance = request.getAttribute("cardbalance") == null ? "" : request
                    .getAttribute("cardbalance").toString();
	        String cardcnt =  request.getAttribute("cardcnt") == null ? "" : request
                    .getAttribute("cardcnt").toString();
	        String outcardphyno =  request.getAttribute("outcardphyno") == null ? "" : request
                    .getAttribute("outcardphyno").toString();
	        String outcardbalance =  request.getAttribute("outcardbalance") == null ? "" : request
                    .getAttribute("outcardbalance").toString();
	        String outcardcnt =  request.getAttribute("outcardcnt") == null ? "" : request
                    .getAttribute("outcardcnt").toString();
            String money = request.getAttribute("money") == null ? "" : request
                    .getAttribute("money").toString();                    
            String serialNo = request.getAttribute("serialNo") == null ? ""
                    : request.getAttribute("serialNo").toString();
            String cardAmount = request.getAttribute("cardAmount") == null ? ""
                    : request.getAttribute("cardAmount").toString();
            String outCardAmount = request.getAttribute("outCardAmount") == null ? ""
                    : request.getAttribute("outCardAmount").toString();
            String saddr = request.getAttribute("saddr") == null ? ""
                    : request.getAttribute("saddr").toString();
            String sphone3 = request.getAttribute("sphone3") == null ? ""
                    : request.getAttribute("sphone3").toString();
            String webserverip = KSConfiguration.getInstance().getProperty(
                    "webserverip");
            String webserverport = KSConfiguration.getInstance().getProperty(
                    "webserverport");
            String webserverapp = KSConfiguration.getInstance().getProperty(
                    "webserverapp");
            String read_card_device_port = KSConfiguration.getInstance()
                    .getProperty("read_card_device_port", "0");

		%>
		<script type="text/JavaScript">     
		function writeCard(){
            var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
            var device_port = '<%=read_card_device_port%>';
            var cardphyno = '<%=cardphyno%>';
            var cardcnt = '<%=cardcnt%>';
            var cardAmount = '<%=cardAmount%>';
            var t_money = '<%=money%>';
            var serial_no = '<%=serialNo%>';
            writeCardForm.all.RFScanner.PortNo=device_port;
            var ret = writeCardForm.all.RFScanner.CardTransWriteCard(cardAmount,cardphyno,cardcnt);
            if(ret==0){//扣款成功
                writeCardForm.action='/smartcardweb/cardcardtransnext.do';
                writeCardForm.submit();                
            }else if(ret==10){
                writeCardForm.action='/smartcardweb/outcardrewritecard.do';
                writeCardForm.submit();
            }else{
                window.location='/smartcardweb/pages/cardcard/outcardwriteerror.jsp'; 
            }
        }
		
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
	<body scroll="no" onload="javascript:writeCard();">
		<form action="/smartcardweb/cardtransnext.do" method="post"
			name="writeCardForm">
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
								<table width="50%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">

									<tr>
										<td height="320" align="center" class="样式13" id="msg">
											<input type="hidden" name="cardphyno"
												value="<%=request.getAttribute("cardphyno") == null ? "0"
					: request.getAttribute("cardphyno")%>" />
					                        <input type="hidden" name="cardbalance"
                                                value="<%=request.getAttribute("cardbalance") == null ? "0"
                    : request.getAttribute("cardbalance")%>" />
                                            <input type="hidden" name="cardcnt"
                                                value="<%=request.getAttribute("cardcnt") == null ? "0"
                    : request.getAttribute("cardcnt")%>" />
                                            <input type="hidden" name="outcardphyno"
                                                value="<%=request.getAttribute("outcardphyno") == null ? "0"
                    : request.getAttribute("outcardphyno")%>" />
                                            <input type="hidden" name="outcardbalance"
                                                value="<%=request.getAttribute("outcardbalance") == null ? "0"
                    : request.getAttribute("outcardbalance")%>" />
                                            <input type="hidden" name="outcardcnt"
                                                value="<%=request.getAttribute("outcardcnt") == null ? "0"
                    : request.getAttribute("outcardcnt")%>" />                                            
											<input type="hidden" name="money"
												value="<%=request.getAttribute("money") == null ? "0"
					: request.getAttribute("money")%>" />
											<input type="hidden" name="outCardAmount"
												value="<%=request.getAttribute("outCardAmount") == null ? "0"
					: request.getAttribute("outCardAmount")%>" />
					                       <input type="hidden" name="cardAmount"
                                                value="<%=request.getAttribute("cardAmount") == null ? "0"
                    : request.getAttribute("cardAmount")%>" />
											<input type="hidden" name="serialNo"
												value="<%=request.getAttribute("serialNo") == null ? ""
					: request.getAttribute("serialNo")%>" />
											<input type="hidden" name="sphone3"
												value="<%=request.getAttribute("sphone3") == null ? ""
					: request.getAttribute("sphone3")%>" />
					                        <input type="hidden" name="saddr"
                                                value="<%=request.getAttribute("saddr") == null ? ""
                    : request.getAttribute("saddr")%>" />
											正在写卡、扣款!请稍后...
											<br />
											(可能需要等待一段时间，请不要移动卡片！)
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">

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
				height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>



