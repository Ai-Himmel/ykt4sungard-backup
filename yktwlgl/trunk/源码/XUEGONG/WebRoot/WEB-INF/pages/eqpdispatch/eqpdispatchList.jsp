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
		<html:form action="/gyf/eqpdispatchAction.do?method=search4List" method="post">

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
												�豸�ɷ��Ǽ�
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<tr align="center" valign=center>
												<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													�豸���
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_bh" styleClass="input_box" maxlength="32" />
												</td>
												<td width="20%" lign="left" valign="middle" class="tableHeader2">
													�豸�ʲ���
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_zch" styleClass="input_box" maxlength="50" />
												</td>
												<td width="15%" align="left" valign="middle" class="tableHeader2">
													�豸���к�
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_xlh" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													ԭ�ɷ�����
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_opfdx" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="pflist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													ԭ����У��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_oxq" styleClass="select01" onchange="changeOBd(this)">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													ԭ����¥��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_olouyu" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													���ɷ�����
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_npfdx" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="pflist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													������У��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_nxq" styleClass="select01" onchange="changeNBd(this)">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													������¥��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_nlouyu" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													�ɷ�ԭ��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_pfyy" styleClass="select01">
														<html:option value="">��ѡ��	</html:option>
														<html:options collection="eqppfReasonlist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													ԭ����Ա
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_ogly" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													�¹���Ա
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_ngly" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													������
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_sqr" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													�Ǽ����ڴ�
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_djrqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_djrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��ʼ����" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="right" valign="middle" class="tableHeader2">
													�Ǽ����ڵ�
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_djrqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_djrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
											</tr>
											<script type="text/javascript">
                new calendar("search_djrqc", "select_djrqc", "%Y-%m-%d");
                new calendar("search_djrqd", "select_djrqd", "%Y-%m-%d");
           </script>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">
									<input name="Submit" type="submit" class="button_nor" value="�� ѯ">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="�� ��" onclick="DoClear()">
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
							<logic:present name="ncdispatch" scope="request">
								<input name="hncdispatch" type="hidden" value="<bean:write name="ncdispatch" />">
							</logic:present>
							<logic:notPresent name="ncdispatch" scope="request">
								<input name="hncdispatch" type="hidden" value="">
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
									�豸�ɷ��б�
								</td>
							</tr>

							<tr>
								<td height="20" align="center" valign="middle">
									<ec:table items="eqplist" var="eqpJBInfo" autoIncludeParameters="false" rowsDisplayed="10" action="eqpdispatchAction.do?method=search4List">

										<ec:parameter name="search_bh" />
										<ec:parameter name="search_zch" />
										<ec:parameter name="search_xlh" />
										<ec:parameter name="search_opfdx" />
										<ec:parameter name="search_oxq" />
										<ec:parameter name="search_olouyu" />
										<ec:parameter name="search_npfdx" />
										<ec:parameter name="search_nxq" />
										<ec:parameter name="search_nlouyu" />
										<ec:parameter name="search_pfyy" />
										<ec:parameter name="search_ogly" />
										<ec:parameter name="search_ngly" />
										<ec:parameter name="search_sqr" />
										<ec:parameter name="search_djrqc" />
										<ec:parameter name="search_djrqd" />

										<ec:exportXls fileName="eqpdispatchList.xls" tooltip="���� Excel" />
										<ec:row>
											<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
												<input type="checkbox" name="cbgroup" value="${eqpJBInfo.id}" style="border:0px" onClick="doSel(this)" />																																		
											</ec:column>
											<ec:column property="equipmentNo" title="�鿴" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
													<a href="javascript:DoView('${eqpJBInfo.id}')">�鿴</a>
													</c:if>
													<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
													<a href="javascript:DoView('${eqpJBInfo.id}')">�鿴</a>
													</c:if>													
											</ec:column>
											<ec:column property="assetNo" title="�豸��ʶ" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
													<a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a>
													</c:if>
													<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
													<a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.assetNo}</a>
													</c:if>													
											</ec:column>					
											<ec:column property="opfCategory" title="ԭ�ɷ�" headerStyle="text-align:center" style="text-align: left" width="50" />
											<ec:column property="ocollegeArea" title="ԭУ��" headerStyle="text-align:center" style="text-align: left" width="60" />
											<ec:column property="olymc" title="ԭ¥��" headerStyle="text-align:center" style="text-align: left" width="50" />
											<ec:column property="npfCategory" title="���ɷ�" headerStyle="text-align:center" style="text-align: left" width="50" />
											<ec:column property="ncollegeArea" title="��У��" headerStyle="text-align:center" style="text-align: left" width="60" />
											<ec:column property="nlymc" title="��¥��" headerStyle="text-align:center" style="text-align: left" width="50" />
											<ec:column property="pfReason" title="ԭ��" headerStyle="text-align:center" style="text-align: left" width="40" />
											<ec:column property="omanagerName" title="ԭ����" headerStyle="text-align:center" style="text-align: left" width="50" />
											<ec:column property="nmanagerName" title="�¹���" headerStyle="text-align:center" style="text-align: left" width="50" />
											<ec:column property="managerCheckName" title="����״̬" headerStyle="text-align:center" style="text-align: left" width="50" />
											<ec:column property="usageCategory" title="��;����" headerStyle="text-align:center" style="text-align: left" width="60" />											
											<ec:column property="recordDate" title="����" cell="date" format="yyyy-MM-dd" headerStyle="text-align:center" style="text-align: left" width="80" />
										</ec:row>
									</ec:table>
								</td>
							</tr>
							<%if (((java.util.ArrayList) request.getAttribute("eqplist")).size() > 0) {%>
							<tr>
								<td height="40" align="left" valign="middle">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<tr align="center" valign=center>
												<td height="40" align="left" valign="middle">
													<input name="selectall" type="button" class="button_nor" value="ȫ ѡ" onClick="DoSelectall()">
													<input name="notselectall" type="button" class="button_nor" value="ȫ��ѡ" onClick="DoNotselectall()">
													<input name="reverseselect" type="button" class="button_nor" value="�� ѡ" onClick="DoReverseselect()">
												</td>
												<td height="40" align="right" valign="middle">
													<input name="bupdate" type="button" class="button_nor" value="���ɷ�" onClick="DoAdd()">
													&nbsp;
													<input name="bupdate" type="button" class="button_nor" value="�� ��" onClick="DoUpdate()">
													&nbsp;
													<input name="bupdate" type="button" class="button_nor" value="ɾ ��" onClick="DoDelete()">
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<%} else {%>
							<tr>
								<td height="40" align="right" valign="middle">
									<input name="bupdate" type="button" class="button_nor" value="���ɷ�" onClick="DoAdd()">
								</td>
							</tr>
							<%}%>

						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("ablist")!=null)
       resultset2=(String[][])request.getAttribute("ablist");//��ȡУ����¥���Ӧ����
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>");//����javascript��ά���飬��Ӧ¥��id��¥�����ơ�У��id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){
   
  var oarea=document.eqpdispatchForm.elements["search_oxq"].value;
  var obuilding=document.eqpdispatchForm.elements["search_olouyu"].value;
  
  if(oarea!='')
      changeOBd(document.eqpdispatchForm.elements["search_oxq"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_olouyu"].length;j++){
      if(document.eqpdispatchForm.elements["search_olouyu"][j].value==obuilding)
	     document.eqpdispatchForm.elements["search_olouyu"][j].selected=true;
					
  }
  
  var narea=document.eqpdispatchForm.elements["search_nxq"].value;
  var nbuilding=document.eqpdispatchForm.elements["search_nlouyu"].value;
  
  if(narea!='')
      changeNBd(document.eqpdispatchForm.elements["search_nxq"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_nlouyu"].length;j++){
      if(document.eqpdispatchForm.elements["search_nlouyu"][j].value==nbuilding)
	     document.eqpdispatchForm.elements["search_nlouyu"][j].selected=true;
					
  }
  
  if(document.eqpdispatchForm.hmsg.value=='9')
      alert("�����ظ����棡");
  if(document.eqpdispatchForm.hmsg.value=='dok')
       alert("ɾ���ɹ���");
  else if(document.eqpdispatchForm.hmsg.value=='dfail')
       alert("ɾ��ʧ�ܣ�");
  if(document.eqpdispatchForm.hnccols.value!='')
       alert(document.eqpdispatchForm.hnccols.value+" �������ɷ���¼���������л�����˵��豸�ɷ����룬����ɾ����");
  if(document.eqpdispatchForm.hncdispatch.value!='')
       alert(document.eqpdispatchForm.hncdispatch.value+" �ɷ������δ��������ʱ���������ɷ���");
  if(document.eqpdispatchForm.hncupdate.value!=''){
       alert("�޸�"+document.eqpdispatchForm.hncupdate.value+"���ɷ���¼��");
       alert("һ���豸ֻ���޸����µ��ɷ���¼������Ӧ���ɷ�����������л�����˽����������޸ģ�");
   }
}  

function changeOBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_olouyu"].length=1; //���ԭ¥���б�        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_olouyu"].options[document.eqpdispatchForm.elements["search_olouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpdispatchForm.elements["search_olouyu"].options[document.eqpdispatchForm.elements["search_olouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function changeNBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_nlouyu"].length=1; //���ԭ¥���б�        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_nlouyu"].options[document.eqpdispatchForm.elements["search_nlouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpdispatchForm.elements["search_nlouyu"].options[document.eqpdispatchForm.elements["search_nlouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function zchSetup(sel){

   alert(sel.value);

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

function DoAdd(){
   
   eqpdispatchForm.action="eqpdispatchAction.do?method=load4add";       
   eqpdispatchForm.submit();

}

function DoUpdate(){
 
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
              alert("��ѡ��Ҫ�޸ĵ��豸�ɷ���¼��");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              ids=ids+document.all.cbgroup.value+","; 
              sflag=sflag+1;     
        }
        else{
            alert("��ѡ��Ҫ�޸ĵ��豸�ɷ���¼��");
            return;   
        }            
   }
   
   document.forms.ec.action="eqpdispatchAction.do?method=load4update&idset="+ids.substring(0,ids.length-1)+"&idcount="+sflag;     
   document.forms.ec.submit();
   
  
  
}

function DoDelete(){

   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   ids=ids+"'"+document.all.cbgroup[i].value+"'"+",";                                                 
              }
          }           
         if(sflag==0){
              alert("��ѡ��Ҫɾ�����豸�ɷ���¼��");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              ids=ids+"'"+document.all.cbgroup.value+"'"+",";      
        }
        else{
            alert("��ѡ��Ҫɾ�����豸�ɷ���¼��");
            return;   
        }            
   }
   
   if(confirm("��ȷ��Ҫɾ�����豸�ɷ���¼��")){
       eqpdispatchForm.action="eqpdispatchAction.do?method=delete&dispatchIds="+ids.substring(0,ids.length-1);
       eqpdispatchForm.submit();
   }
   else
      return;

}

function DoView(eno){

    window.open("eqpdispatchAction.do?method=load4view&dispatchId="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoViewEqp(eno){

    window.open("equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=1000,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoClear(){

    document.eqpdispatchForm.elements["search_bh"].value="";
    document.eqpdispatchForm.elements["search_zch"].value="";    
    document.eqpdispatchForm.elements["search_xlh"].value="";
    
    document.eqpdispatchForm.elements["search_opfdx"].value="";
    document.eqpdispatchForm.elements["search_opfdx"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_oxq"].value="";
    document.eqpdispatchForm.elements["search_oxq"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_olouyu"].value="";
    document.eqpdispatchForm.elements["search_olouyu"].options[0].selected=true;
    
    document.eqpdispatchForm.elements["search_npfdx"].value="";
    document.eqpdispatchForm.elements["search_npfdx"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_nxq"].value="";
    document.eqpdispatchForm.elements["search_nxq"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_nlouyu"].value="";
    document.eqpdispatchForm.elements["search_nlouyu"].options[0].selected=true;
    
    document.eqpdispatchForm.elements["search_pfyy"].value="";
    document.eqpdispatchForm.elements["search_pfyy"].options[0].selected=true;    
    document.eqpdispatchForm.elements["search_ogly"].value="";
    document.eqpdispatchForm.elements["search_ngly"].value="";
    
    document.eqpdispatchForm.elements["search_sqr"].value="";
    document.eqpdispatchForm.elements["search_djrqc"].value="";
    document.eqpdispatchForm.elements["search_djrqd"].value="";
            
}

</SCRIPT>

