<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.web.util.Constants"%>
<html>
	<head>
		<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

		<SCRIPT language=javascript>
	
function doUpdateDtl(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemlist"]!=undefined){
    if(ec.elements["itemlist"].checked==true){       

           var t = eval("document.forms[0]['"+document.forms[1]['itemlist'].value+"'].value");
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.noCheckID%>'){
               alert("��ѡ�еĵ�����ϸ�Ѿ������������Ѿ�ͨ�����������ܱ��޸ġ�������ѡ�񣡣���");
              return false;
           }
    	
    	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     	ec.submit();

    }else{
       	for(i=0;i<ec.elements["itemlist"].length;i++){
       		if(ec.elements["itemlist"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
      for(var i=0;i<document.forms[1]['itemlist'].length;i++){  
		if(document.forms[1]['itemlist'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemlist'][i].value+"'].value");      
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.notPassID%>'){
              alert("��ѡ�еĵ�����ϸ�Ѿ������������Ѿ�ͨ�����������ܱ��޸ġ�������ѡ�񣡣���");
              return false;
           }
    	}
	  } 
    	    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     		ec.submit();
   		}else if(counte>1){
   		
   	  for(var i=0;i<document.forms[1]['itemlist'].length;i++){
		if(document.forms[1]['itemlist'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemlist'][i].value+"'].value");
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.noCheckID%>'){
              alert("��ѡ�еĵ�����ϸ��������һ���Ѿ������������Ѿ�ͨ�����������ܱ��޸ġ�������ѡ�񣡣���");
              return false;
           }
    	}
	  } 
    		ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlsInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     		ec.submit();
    	}else if(counte<1){
      	  	alert('��ѡ��Ҫ�޸ĵ���ϸ��¼');
   	 	}
    }
    }else{
    	alert('��ǰ����ϸ��¼����');
    }
}
function DoView3(id,id1){
    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Reg&wlArrivalDtlId="+id1+"&wlArrivalId="+id;
	ec.submit();
}

function DoView2(id,id1){
    if(confirm("ȷ���Ѿ���д������ϸ��")){
    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Reg&wlArrivalDtlId="+id1+"&wlArrivalId="+id;
	ec.submit();
	}
}
function DoView1(id){
    window.open("wlArrivalDtlAction.do?method=loadWlArrivalDtlInfo4Search&tag=1&wlArrivalDtlId="+id,"detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}
function deletePurDtl(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemlist"]!=undefined){
    if(ec.elements["itemlist"].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemlist'].value+"'].value");
           if(t!='<%=Constants.notSubmitID%>'){
               alert("��ѡ�еĵ�����ϸ�Ѿ��ύ������ɾ����������ѡ�񣡣���");
              return false;
           }
    	ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
		ec.submit();
    }else{
        for(i=0;i<ec.elements["itemlist"].length;i++){
       	if(ec.elements["itemlist"][i].checked == true){
       	   		++counte; 	  
       	}
       	}
       	if(counte==1){
       	
      for(var i=0;i<document.forms[1]['itemlist'].length;i++){
		if(document.forms[1]['itemlist'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemlist'][i].value+"'].value");
           if(t!='<%=Constants.notSubmitID%>'){
               alert("��ѡ�еĵ�����ϸ�Ѿ��ύ������ɾ����������ѡ�񣡣���");
              return false;
           }
    	}
	  }
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
			ec.submit();
   		}else if(counte>1){
   		
   	  for(var i=0;i<document.forms[1]['itemlist'].length;i++){
		if(document.forms[1]['itemlist'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemlist'][i].value+"'].value");
           if(t!='<%=Constants.notSubmitID%>'){
               alert("��ѡ�еĵ�����ϸ�Ѿ��ύ������ɾ����������ѡ�񣡣���");
              return false;
           }
    	}
	  }
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
			ec.submit();
    	}else if(counte<1){
      	  	alert('��ѡ��Ҫɾ������ϸ��¼');
   	 	}
   	 	
    }
    }else{
    	alert('��ǰ����ϸ��¼����');
    }
}
function search(){
    wlArrivalSearchForm.action = "<c:url value="/lf/wlArrivalAction.do"/>?method=loadWlArrivalList4RegSearch";
	wlArrivalSearchForm.submit();
}
function add(){
    wlArrivalSearchForm.action = "<c:url value="/lf/wlArrivalBillAction.do"/>?method=openNewWlArrivalBill";
	wlArrivalSearchForm.submit();
}

function doUpdate(id){
     ec.action="<c:url value="/lf/wlArrivalBillAction.do"/>?method=loadWlArrivalInfo4Reg&wlArrivalId="+id;    
   	 ec.submit();
}
function DoSelectall(){
  if(document.all.itemlist!=null&&document.all.itemlist.length>1){   
       for(var i=0;i<document.all.itemlist.length;i++){
              document.all.itemlist[i].checked=true;
       }
       
  }
  else if(document.all.itemlist!=null){
       document.all.itemlist.checked=true;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}
function DoView(id,purId){
    window.open("purDtlAction.do?method=load4PurDtlInfo4Show&tag=1&purDtlId="+id+"&purId="+purId,"detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}
function DoNotselectall(){
  
  if(document.all.itemlist!=null&&document.all.itemlist.length>1){   
       for(var i=0;i<document.all.itemlist.length;i++){
              document.all.itemlist[i].checked=false;
       }
       
  }
  else if(document.all.itemlist!=null){
       document.all.itemlist.checked=false;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
}

function DoReverseselect(){
   
   if(document.all.itemlist!=null&&document.all.itemlist.length>1){   
       for(var i=0;i<document.all.itemlist.length;i++){
           if(document.all.itemlist[i].checked)
              document.all.itemlist[i].checked=false;
           else if(!document.all.itemlist[i].checked)
              document.all.itemlist[i].checked=true;
       }
       
  }
  else if(document.all.itemlist!=null){
      if(document.all.itemlist.checked)
          document.all.itemlist.checked=false; 
      else if(!document.all.itemlist.checked)
          document.all.itemlist.checked=true;    
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" style="padding-left:10px">
		<br>

		<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td align="left" valign="top">

					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td height="25" align="left" valign="top">
								<html:form action="/lf/wlArrivalAction" method="post">
									<table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr><td width="10" bgcolor="#0066CA">&nbsp;</td>
											<td bgcolor="#0066CA" class="mediumwhite">�����Ǽ�</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
										</tr>
									</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="center" valign="top">
								<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>

									<tbody>
										<tr align="center" valign=center>
											<td width="13%" align="left" valign="middle" class="tableHeader2">
												��������
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<html:text property="search_wlArrivalId" styleClass="input_box" maxlength="50" />
											</td>
											<td width="13%" align="left" valign="middle" class="tableHeader2">
												�Ǽ���
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<html:text property="search_regPName" styleClass="input_box" maxlength="50" />
											</td>
										</tr>
										<tr align="center" valign=center>
											<td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
												�Ǽ�����
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3" colspan=3>
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td>
															<html:text property="search_regTimeStart" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectStartTime" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="��ʼ����" style="cursor:pointer">
														</td>
														<td>&nbsp;��&nbsp;</td>
														<td>
															<html:text property="search_regTimeEnd" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectEndTime" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="��������" style="cursor:pointer">
														</td>
													</tr>
												</table>
											</td>
										</tr>
									<script type="text/javascript">
                						new calendar("search_regTimeStart", "selectStartTime", "%Y-%m-%d");
               			 				new calendar("search_regTimeEnd", "selectEndTime", "%Y-%m-%d");
           							</script>
									</tbody>

								</table>
							</td>
						</tr>
					<logic:present name="wlArrList" scope="request">
						<logic:iterate name="wlArrList" id="wlArrivalDtl" type="java.util.Map">
													
						</logic:iterate>
					</logic:present>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<input name="Submit" type="button" class="button_nor" onClick="search()" value="�� ѯ">
								&nbsp;
								<input name="Submit2" type="button" class="button_nor" value="�� ��" onclick="DoClear()">
							</td>
						</tr>
						<logic:present name="wlArrList" scope="request">
							<logic:iterate name="wlArrList" id="wlArrival" type="java.util.Map">
								<input type="hidden" id="<bean:write name="wlArrival" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrival" property="stateID"/>"/>
							</logic:iterate>
						</logic:present>
						</html:form>
						<tr>
							<td height="35" align="center" valign="middle" class="mediumblack">
								������ϸ�б�
							</td>
						</tr>
						<tr>
							<td height="20" align="center" valign="middle">
								<ec:table items="wlArrList" var="wlArrival" rowsDisplayed="10"
									action="wlArrivalAction.do?method=loadWlArrivalList4RegSearch">
			    <ec:parameter name="search_wlArrivalId" />
				<ec:parameter name="search_regPName" />
				<ec:parameter name="search_regTimeStart" />
				<ec:parameter name="search_regTimeEnd" />
									<ec:exportXls fileName="wlArrList.xls" tooltip="���� Excel" />
									<ec:row>
										<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="50"
											headerStyle="text-align:center" style="text-align: center">
											<c:choose>
						                    <c:when test="${wlArrival.state=='δ�ύ'}">
											<input type="checkbox" name="itemlist" value="${wlArrival.wlArrivalDtlId}" style="border:0px" />
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black"><input type="checkbox" name="itemlist" value="${wlArrival.wlArrivalDtlId}" style="border:0px" /></font>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green"><input type="checkbox" name="itemlist" value="${wlArrival.wlArrivalDtlId}" style="border:0px" /></font>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red"><input type="checkbox" name="itemlist" value="${wlArrival.wlArrivalDtlId}" style="border:0px" /></font>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='������'}">
											<font color="black"><input type="checkbox" name="itemlist" value="${wlArrival.wlArrivalDtlId}" style="border:0px" /></font>
										    </c:when>
				                            </c:choose>
										</ec:column>
										<ec:column property="wlArrivalId" title="��������" headerStyle="text-align:center" style="text-align: center"
											width="90" >
											<c:choose>
											<c:when test="${wlArrival.state=='δ�ύ'}">
											<a href="javascript:doUpdate('${wlArrival.wlArrivalId}')">${wlArrival.wlArrivalId}</a>
											</c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='���ύ'}">
											<a href="javascript:doUpdate('${wlArrival.wlArrivalId}')"><font color="black">${wlArrival.wlArrivalId}</font></a>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='����ͨ��'}">
											<a href="javascript:doUpdate('${wlArrival.wlArrivalId}')"><font color="green">${wlArrival.wlArrivalId}</font></a>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='������ͨ��'}">
											<a href="javascript:doUpdate('${wlArrival.wlArrivalId}')"><font color="red">${wlArrival.wlArrivalId}</font></a>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='������'}">
											<a href="javascript:doUpdate('${wlArrival.wlArrivalId}')"><font color="black">${wlArrival.wlArrivalId}</font></a>
										    </c:when>
				                            </c:choose>
										</ec:column>
										<ec:column property="rcdPersonName" title="�Ǽ���" headerStyle="text-align:center" style="text-align: center"
											width="60" 
									    >
									    <c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.rcdPersonName}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.rcdPersonName}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.rcdPersonName}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.rcdPersonName}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.rcdPersonName}</font>
										</c:when>
				                        </c:choose>
									    </ec:column>
										<ec:column property="wlmc" title="��������" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" 
										>
										<c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.wlmc}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.wlmc}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.wlmc}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.wlmc}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.wlmc}</font>
										</c:when>
				                        </c:choose>
									    </ec:column>
										<ec:column property="appName" title="�ɹ�������" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80">
										    <c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											<c:if test="${wlArrival.appName!=''}">
										    <a href="javascript:DoView('${wlArrival.purDtlId}','${wlArrival.purId}')">${wlArrival.appName}</a>
										    </c:if>
										    <c:if test="${wlArrival.appName==''}">
										    &nbsp;
										    </c:if>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<c:if test="${wlArrival.appName!=''}">
										    <a href="javascript:DoView('${wlArrival.purDtlId}','${wlArrival.purId}')"><font color="black">${wlArrival.appName}</font></a>
										    </c:if>
										    <c:if test="${wlArrival.appName==''}">
										    &nbsp;
										    </c:if>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<c:if test="${wlArrival.appName!=''}">
										    <a href="javascript:DoView('${wlArrival.purDtlId}','${wlArrival.purId}')"><font color="green">${wlArrival.appName}</font></a>
										    </c:if>
										    <c:if test="${wlArrival.appName==''}">
										    &nbsp;
										    </c:if>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<c:if test="${wlArrival.appName!=''}">
										    <a href="javascript:DoView('${wlArrival.purDtlId}','${wlArrival.purId}')"><font color="red">${wlArrival.appName}</font></a>
										    </c:if>
										    <c:if test="${wlArrival.appName==''}">
										    &nbsp;
										    </c:if>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<c:if test="${wlArrival.appName!=''}">
										    <a href="javascript:DoView('${wlArrival.purDtlId}','${wlArrival.purId}')"><font color="black">${wlArrival.appName}</font></a>
										    </c:if>
										    <c:if test="${wlArrival.appName==''}">
										    &nbsp;
										    </c:if>
										</c:when>
				                        </c:choose>										    
										</ec:column>
										<ec:column property="arrivalNum" title="������" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="60" 
										>
										<c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.arrivalNum}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.arrivalNum}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.arrivalNum}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.arrivalNum}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.arrivalNum}</font>
										</c:when>
				                        </c:choose>
									    </ec:column>
										<ec:column property="ifaccount" title="�Ƿ�������" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" 
										>
										<c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.ifaccount}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.ifaccount}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.ifaccount}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.ifaccount}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.ifaccount}</font>
										</c:when>
				                        </c:choose>
									    </ec:column>
										<ec:column property="ifreceiptavl" title="��Ʊ�Ƿ���" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" 
										>
										<c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.ifreceiptavl}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.ifreceiptavl}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.ifreceiptavl}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.ifreceiptavl}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.ifreceiptavl}</font>
										</c:when>										
				                        </c:choose>				                        
									    </ec:column>
										<ec:column property="providerName" title="��Ӧ��" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="130" 
										>
										<c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.providerName}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.providerName}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.providerName}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.providerName}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.providerName}</font>
										</c:when>
				                        </c:choose>
									    </ec:column>
										<ec:column property="producterName" title="������" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="130" 
										>
										<c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.producterName}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.producterName}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.producterName}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.producterName}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.producterName}</font>
										</c:when>
				                        </c:choose>
									    </ec:column>
										<ec:column property="state" title="��ϸ״̬" 
										    headerStyle="text-align:center" 
										    style="text-align: center"
										    width="80" 
										>
										<c:choose>
										<c:when test="${wlArrival.state=='δ�ύ'}">
											${wlArrival.state}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='���ύ'}">
											<font color="black">${wlArrival.state}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='����ͨ��'}">
											<font color="green">${wlArrival.state}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='������ͨ��'}">
											<font color="red">${wlArrival.state}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='������'}">
											<font color="black">${wlArrival.state}</font>
										</c:when>
				                        </c:choose>
									    </ec:column>	
									    <ec:column property="producerName" title="�������" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
					<c:when test="${wlArrival.state=='δ�ύ'}">
			
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')">������</a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')">δ����</a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')">�������</a>
					</c:if>
					</c:when>
				    </c:choose>
				    	<c:choose>
					<c:when test="${wlArrival.state=='���ύ'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">������</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">δ����</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">�������</font></a>
					</c:if>
					</c:when>
				    </c:choose>
				      	<c:choose>
					<c:when test="${wlArrival.state=='����ͨ��'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="green">������</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="green">δ����</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="green">�������</font></a>
					</c:if>
					</c:when>
				    </c:choose>
				          	<c:choose>
					<c:when test="${wlArrival.state=='������ͨ��'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="red">������</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="red">δ����</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="red">�������</font></a>
					</c:if>
					</c:when>
				    </c:choose>
				            	<c:choose>
					<c:when test="${wlArrival.state=='������'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">������</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">δ����</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">�������</font></a>
					</c:if>
					</c:when>
				    </c:choose>
					</ec:column>
									    
									</ec:row>
								</ec:table>
							</td>
						</tr>
						<tr>
						         <td><table width="99%" border="0">
        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="ȫ ѡ" onClick="DoSelectall()" ><input name="notselectall" type="button" class="button_nor" value="ȫ��ѡ" onClick="DoNotselectall()" ><input name="reverseselect" type="button" class="button_nor" value="�� ѡ" onClick="DoReverseselect()" >
        		</td>
							<td height="40" align="right" valign="middle">
								<input name="Submit1" type="button" class="button_nor" value="��������" onClick="add()">
								<input name="Submit3" type="button" class="button_nor" value="�޸���ϸ" onClick="doUpdateDtl()">
								<input name="Submit33" type="button" class="button_nor" value="ɾ����ϸ" onClick="deletePurDtl()">
								
							</td>
							          	</tr>
		</table></td>
						</tr>
					</table>
				</td>
			</tr>
		</table>

	</body>

</html>
<script>
function DoClear(){
    document.wlArrivalSearchForm.elements["search_wlArrivalId"].value="";
    document.wlArrivalSearchForm.elements["search_regPName"].value="";
    document.wlArrivalSearchForm.elements["search_regTimeStart"].value="";
    document.wlArrivalSearchForm.elements["search_regTimeEnd"].value="";
}
</SCRIPT>
           <script type="text/javascript">
                new calendar("search_regTimeStart", "search_regTimeStart", "%Y-%m-%d");
                new calendar("search_regTimeEnd", "search_regTimeEnd", "%Y-%m-%d");
           </script>