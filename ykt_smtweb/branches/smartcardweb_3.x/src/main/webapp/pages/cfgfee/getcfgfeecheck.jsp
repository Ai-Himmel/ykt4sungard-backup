<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@page import="com.kingstar.itemconfig.Configitem"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Iterator"%>
<%@page import="java.util.Map.Entry"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>ר���շ�ȷ��</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
        String cardphyid = request.getAttribute("cardphyid")==null?"":request.getAttribute("cardphyid").toString();
        HashMap thirdpartinfo =  (HashMap)request.getAttribute("thirdpartinfo");
        String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
        String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
        String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
        String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
        %>
		<script language="javascript">
		 function readCard(){
              if(!document.all.send.disabled){
                	errmsg.innerHTML="�벻Ҫ���߿�Ƭ��ϵͳȷ���У����Ժ�...<br/>������Ҫ�ȴ�һ��ʱ��";       
                    var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
                    var device_port = '<%=read_card_device_port%>';
                    var cardphyid ='<%=cardphyid%>';
                    putinForm.all.RFScanner.PortNo=device_port;
                    var ret = putinForm.all.RFScanner.ReadCardPocket(1,cardphyid);
                    if(ret == 0){
                    	 var bala = putinForm.all.RFScanner.GetPacketInfo("cardbal");
                         var txCnt =  putinForm.all.RFScanner.GetPacketInfo("pay_card_cnt");
                        if(parseInt(putinForm.all.fee.value)*100<=parseInt(bala)){
                            putinForm.all.cardphyid.value=cardphyid;
                            putinForm.all.cardBala.value = bala;
                            putinForm.all.txCnt.value = txCnt;
                            putinForm.all.send.disabled = true;
                            putinForm.submit();
                        }else{
                            alert("�շѽ����˿�Ƭ���");
                            return false;
                        }
                    }else if(ret == 1){
                        alert("����ÿ�Ƭ...");
                        return false;
                    }else{
                        alert("����ȷ���ÿ�Ƭ...");
                        return false;
                    }
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
		.��ʽ12 {
			font-family: "����";
			color: #000000;
			font-size: 16px;
		}
		
		.��ʽ13 {
			font-family: "����";
			color: #000000;
			font-size: 18px;
		}
		
		.��ʽ14 {
			font-family: "����";
			color: #ff0000;
			font-size: 18px;
		}
		}
		</style>
	</head>
	<body scroll="no">
		<form action="/smartcardweb/cfgfeecheckin.do" method="post"
			name="putinForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/zz.gif" width="314"
									height="82" />
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="50" class="��ʽ13">
											�շ���Ŀ��
										</td>
										<td>
											<%
												Configitem cfgitem = (Configitem) request.getAttribute("cfgitem");
											%>
											<%= cfgitem.getName()%>
										</td>
									</tr>

									<tr>
										<td width="320" height="50" class="��ʽ13">
											�շѽ�
											<input type="hidden" name="gid" value="<%=request.getAttribute("gid")%>"/>
											<input type="hidden" name="fee" value="<%=request.getAttribute("fee")%>"/>
											 <input type="hidden" name="cardphyid" />
                                             <input type="hidden" name="cardBala" />
                                             <input type="hidden" name="txCnt" />    
										</td>
										<td>
											<%=request.getAttribute("fee") == null ? "" : request.getAttribute("fee")%>
											Ԫ
										</td>
									</tr>
                                      <%if(thirdpartinfo!=null&&thirdpartinfo.size()>0){
                                            for (Iterator iter = thirdpartinfo.entrySet().iterator(); iter.hasNext();) {    
                                                        Entry entry = (Entry) iter.next();
                                                        Object key = entry.getKey();
                                                        Object val = entry.getValue();
                                                 %>
                                                    <tr>
                                                        <td height="50" class="��ʽ13">
                                                            <%=key %>
                                                        </td>
                                                        <td>
                                                            <%=val%>
                                                        </td>
                                                    </tr>
                                                 <%
                                                 }                                          
                                               }
                                             %>

									<tr>
										<td height="<%=220-(thirdpartinfo==null?0:thirdpartinfo.size())*50%>" align="center" class="show" id="errmsg"
											colspan="2">
											<br>
											��ȷ�Ϸźÿ�! &nbsp;
											<br>
											<html:errors />
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:readCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/g_zzyw.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel', '', '/smartcardweb/pages/images/cancela.gif', 1)">
												<img src="/smartcardweb/pages/images/cancel.gif" name="cancel"
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
				height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>

