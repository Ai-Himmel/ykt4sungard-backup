<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/eqpdispatchAction.do?method=managerAccept" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												����Ա���ȷ��
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<logic:present name="msg" scope="request">
								<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
							</logic:present>
							<logic:notPresent name="msg" scope="request">
								<input name="hmsg" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="nccols" scope="request">
								<input name="hnccols" type="hidden" value="<bean:write name="nccols" />">
							</logic:present>
							<logic:notPresent name="nccols" scope="request">
								<input name="hnccols" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="ncupdate" scope="request">
								<input name="hncupdate" type="hidden" value="<bean:write name="ncupdate" />">
							</logic:present>
							<logic:notPresent name="ncupdate" scope="request">
								<input name="hncupdate" type="hidden" value="">
							</logic:notPresent>
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									��ȷ�ϵ��豸�б�
								</td>
							</tr>
							<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="eqpacceptlist" var="eqpJBInfo" autoIncludeParameters="false" rowsDisplayed="10" action="eqpdispatchAction.do?method=search4ManagerAccept">

											<ec:exportXls fileName="eqpAcceptList.xls" tooltip="���� Excel" />
											<ec:row>
												<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
													<input type="checkbox" name="cbgroup" value="${eqpJBInfo.equipmentNo}" style="border:0px" onClick="doSel(this)" />
												</ec:column>
												<ec:column property="equipmentNo" title="�豸��ʶ" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
													<a href="javascript:DoView('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a>
													</c:if>
													<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
													<a href="javascript:DoView('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.assetNo}</a>
													</c:if>														
												</ec:column>												
												<ec:column property="serialNo" title="���к�" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="xlmc" title="С��" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="wlmc" title="����" headerStyle="text-align:center" style="text-align: left" width="90" />
												<ec:column property="omgName" title="ԭ����Ա" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="nmgName" title="�¹���Ա" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="managerCheckName" title="ȷ��״̬" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="dpcheckbox" title="�ɷ�" sortable="false" width="30" headerStyle="text-align:center" style="text-align: left">
													<c:if test="${eqpJBInfo.managerCheck=='0'}">
													<input type="checkbox" name="dpcbgroup" value="${eqpJBInfo.equipmentNo}" style="border:0px" />
												    </c:if>&nbsp;
												</ec:column>												
											</ec:row>

										</ec:table>
									</td>
								</tr>
								<%if (((java.util.ArrayList) request.getAttribute("eqpacceptlist"))
					.size() > 0) {%>
								<tr>
									<td height="40" align="left" valign="middle">
										<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
											<tbody>
												<tr align="center" valign=center>
													<td height="40" align="left" valign="middle">
														<input name="selectall" type="button" class="button_nor" value="ȫ ѡ" onClick="DoSelectall()">
														<input name="notselectall" type="button" class="button_nor" value="ȫ��ѡ" onClick="DoNotselectall()">
														<input name="reverseselect" type="button" class="button_nor" value="�� ѡ" onClick="DoReverseselect()">
													    <input name="Submit3" type="button" class="button_nor" value="ͬ ��" onClick="DoAccept('1')">
														<input name="Submit4" type="button" class="button_nor" value="��ͬ��" onClick="DoAccept('0')">
													</td>
													<td height="40" align="right" valign="middle">
														<input name="dpselectall" type="button" class="button_nor" value="ȫ ѡ" onClick="dpDoSelectall()">
														<input name="dpnotselectall" type="button" class="button_nor" value="ȫ��ѡ" onClick="dpDoNotselectall()">
														<input name="dpreverseselect" type="button" class="button_nor" value="�� ѡ" onClick="dpDoReverseselect()">
														<input name="Submit5" type="button" class="button_nor" value="�޸��ɷ�" onClick="DoUpdate()">
													</td>
												</tr>
											</tbody>
										</table>
									</td>
								</tr>
								<%}%>
							</jodd:form>
						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<SCRIPT language=javascript>

setTimeout('init()',50);
function init(){
  
  if(document.all.hmsg.value=='1')
       alert("�����ɹ���");
  else if(document.all.hmsg.value=='19')
       alert("�����ɹ�����ȴ������Ա�Թ���Ա��Ϣ������ˣ�")
  else if(document.all.hmsg.value=='0')
       alert("����ʧ�ܣ�");
  if(document.all.hnccols.value!='')
       alert(document.all.hnccols.value+" ��������У�������Ч��");
  if(document.eqpdispatchForm.hncupdate.value!=''){
       alert("�޸�"+document.eqpdispatchForm.hncupdate.value+"���ɷ���¼��");
       alert("һ���豸ֻ���޸����µ��ɷ���¼������Ӧ���ɷ�����������л�����˽����������޸ģ�");
   }
}

function doSel(sel){
//alert(sel.value);
}

function DoSelectall(){

  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=true;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoNotselectall(){
  
  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=false;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }

}

function DoReverseselect(){
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
           if(document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=false;
           else if(!document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
      if(document.all.cbgroup.checked)
          document.all.cbgroup.checked=false; 
      else if(!document.all.cbgroup.checked)
          document.all.cbgroup.checked=true;    
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoAccept(str){

   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   ids=ids+document.all.cbgroup[i].value+",";                                                 
              }
          }           
         if(sflag==0){
              alert("��ѡ��Ҫ�豸��¼��");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              ids=ids+document.all.cbgroup.value+","; 
              sflag=sflag+1;       
        }
        else{
            alert("��ѡ���豸��¼��");
            return;   
        }            
   }
   
   document.forms.ec.action="eqpdispatchAction.do?method=managerAccept&acceptState="+str+"&idset="+ids.substring(0,ids.length-1)+"&idcount="+sflag; ;     
   document.forms.ec.submit();
   
}

function dpDoSelectall(){

  if(document.all.dpcbgroup!=null&&document.all.dpcbgroup.length>1){   
       for(var i=0;i<document.all.dpcbgroup.length;i++){
              document.all.dpcbgroup[i].checked=true;
       }
       
  }
  else if(document.all.dpcbgroup!=null){
       document.all.dpcbgroup.checked=true;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function dpDoNotselectall(){
  
  if(document.all.dpcbgroup!=null&&document.all.dpcbgroup.length>1){   
       for(var i=0;i<document.all.dpcbgroup.length;i++){
              document.all.dpcbgroup[i].checked=false;
       }
       
  }
  else if(document.all.dpcbgroup!=null){
       document.all.dpcbgroup.checked=false;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }

}

function dpDoReverseselect(){
   
   if(document.all.dpcbgroup!=null&&document.all.dpcbgroup.length>1){   
       for(var i=0;i<document.all.dpcbgroup.length;i++){
           if(document.all.dpcbgroup[i].checked)
              document.all.dpcbgroup[i].checked=false;
           else if(!document.all.dpcbgroup[i].checked)
              document.all.dpcbgroup[i].checked=true;
       }
       
  }
  else if(document.all.dpcbgroup!=null){
      if(document.all.dpcbgroup.checked)
          document.all.dpcbgroup.checked=false; 
      else if(!document.all.dpcbgroup.checked)
          document.all.dpcbgroup.checked=true;    
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoUpdate(){
 
   var sflag=0;
   var ids="";
   
   if(document.all.dpcbgroup!=null&&document.all.dpcbgroup.length>1){
          for(var i=0;i<document.all.dpcbgroup.length;i++){
              if(document.all.dpcbgroup[i].checked){
                   sflag=sflag+1; 
                   ids=ids+"'"+document.all.dpcbgroup[i].value+"'"+",";                                                 
              }
          }           
         if(sflag==0){
              alert("��ѡ��Ҫ�޸��ɷ����豸��¼��");
              return;
          } 
   }
   else if(document.all.dpcbgroup!=null){
        if(document.all.dpcbgroup.checked){
              ids=ids+"'"+document.all.dpcbgroup.value+"'"+","; 
              sflag=sflag+1;     
        }
        else{
            alert("��ѡ��Ҫ�޸��ɷ����豸��¼��");
            return;   
        }            
   }
   else{
       alert("û�п����޸��ɷ����豸��¼��");
       return;
   }
   
   document.forms.ec.action="eqpdispatchAction.do?method=load4nmanagerupdate&idset="+ids.substring(0,ids.length-1)+"&idcount="+sflag;     
   document.forms.ec.submit();
   
  
  
}

function DoView(eno){

    window.open("equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

</SCRIPT>
