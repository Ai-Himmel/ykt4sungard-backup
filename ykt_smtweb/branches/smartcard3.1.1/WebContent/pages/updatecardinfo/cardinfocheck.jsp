<%@ page contentType="text/html; charset=GBK"  %>
<%@page import="com.kingstargroup.fdykt.dto.UpdateInfoDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>  
		<title>请确认是否更新</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
			<%
			String cardphyid = request.getAttribute("CardPhyId")== null ? "":request.getAttribute("CardPhyId").toString();;
			UpdateInfoDTO updateinfo = request.getAttribute("UpdateInfoDTO")==null?null:(UpdateInfoDTO)request.getAttribute("UpdateInfoDTO");
			String feetype = updateinfo == null ? "":String.valueOf(updateinfo.getFeetype());
            String expiredate =   updateinfo == null ? "": updateinfo.getExpiredate();
            String custname = updateinfo == null? "":updateinfo.getAccname();
            String stuempno = updateinfo==null?"":updateinfo.getStuempno();
            String feename = updateinfo == null ? "":updateinfo.getFeename();
		
		%>
		<script language="javascript">
		function writeCard(){
			    errmsg.innerHTML="<b>请不要移走卡片，系统确认中，请稍后...</b>";
			    var CardPhyId ='<%=cardphyid%>';
				var ret = checkresultForm.all.RFScanner.ReadCardPocket(1,CardPhyId);
				if(ret == 0){
					var cardbal = checkresultForm.all.RFScanner.GetPacketInfo("cardbal");
					var dptCardCnt =  checkresultForm.all.RFScanner.GetPacketInfo("dpt_card_cnt");
					var payCardCnt = checkresultForm.all.RFScanner.GetPacketInfo("dpt_card_cnt");
					checkresultForm.all.CardPhyId.value=CardPhyId;
					checkresultForm.all.cardbal.value = cardbal;
					checkresultForm.all.dptCardCnt.value = dptCardCnt;
					checkresultForm.all.payCardCnt.value = payCardCnt;
					checkresultForm.submit();
				}else if(ret == 1){
					alert("请放置卡片...");
					return false;
				}else{
					alert("请正确放置卡片...");
					return false;
				}
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
		<style type="text/css">
		.样式12 {
		font-family: "宋体"; 
		color: #000000; 
		font-size: 16px; 
		}
		.样式13 {
		font-family: "黑体"; 
		color: #000000; 
		font-size: 18px; 
		}
		.样式14 {
		font-family: "宋体"; 
		color: #ff0000; 
		font-size: 25px; 
		}
	}
	</style>
	</head>
	<body scroll="no">
		<form action="/smartcardweb/updateCardInfo.do" method="post"
			name="checkresultForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/czjg.gif" width="314"
									height="82" />
											<input type="hidden" name="CardPhyId" />
											<input type="hidden" name="cardbal" />
											<input type="hidden" name="dptCardCnt" />
											<input type="hidden" name="payCardCnt" />
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									
									<tr>
									<td height="40" class="样式13">
                                         	 客户类别
					                </td>
					                <td>
					                	<bean:write name="UpdateInfoDTO" property="feename"/>
									</td>
									</tr>
									<tr>
									<td height="40" class="样式13">
                                          	 学/工号
					                </td>
									<td>
										<bean:write name="UpdateInfoDTO" property="stuempno"/>
									</td>
									</tr>
									<tr>
									<td height="40" class="样式13">
											 姓名
										</td>
										<td>
										<bean:write name="UpdateInfoDTO" property="accname"/>
										</td>
									</tr>
									<tr>
										<td height="40" class="样式13">
											有效期
										</td>
										<td>
											<bean:write name="UpdateInfoDTO" property="expiredate"/>
										</td>
									</tr>
									<tr>
										<td height="160" align="center"class="样式14" id="errmsg"
											colspan="4">
										  	<b><html:errors />
											 请确认放好卡! &nbsp;</b>
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:writeCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/main.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','/smartcardweb/pages/images/backa.gif',1)"><img
													src="/smartcardweb/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
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
				height="0" />
		</form>
	</body>
</html>

