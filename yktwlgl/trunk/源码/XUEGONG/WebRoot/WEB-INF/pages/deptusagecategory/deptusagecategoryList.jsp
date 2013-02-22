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
		<%String jaddNum = request.getAttribute("addNum") == null ? ""
					: (String) request.getAttribute("addNum");
%>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/deptUsageCategoryAction.do?method=search4List" method="post">
			<input type=hidden name="ucState">
			<input type=hidden name="ucName">



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
												������;��������
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<input type="hidden" name="formName" value="<%=request.getAttribute("formName")==null?"":request.getAttribute("formName")%>">
										<tbody>
											<input type="hidden" name="addNum" value="<%=request.getAttribute("addNum")==null?"":request.getAttribute("addNum")%>">
											<input type="hidden" name="updateid" value="">
											<input type="hidden" name="noNew" value="<%=request.getAttribute("noNew")==null?"0":request.getAttribute("noNew")%>">
											<tr align="center" valign=center>
												<td width="20%" align="left" valign="middle" class="tableHeader2">
													��;��������
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_usageCategoryname" styleClass="input_boxlong" maxlength="100" />
												</td>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													״̬
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="search_ucstate" styleClass="select01">
														<html:option value="">��ѡ��	</html:option>
														<html:options collection="mcztlist" labelProperty="ztName" property="ztCode" />
													</html:select>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">

									<input name="Submit" type="button" class="button_nor" value="�� ѯ" onclick="DoFind()">
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
							<logic:present name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="<bean:write name="repeatSet" />">
							</logic:present>
							<logic:notPresent name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="">
							</logic:notPresent>
							<input type="hidden" name="ec_p" value="<%=request.getParameter("ec_p")==null?"1":request.getParameter("ec_p")%>">
							<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i")==null?"":request.getParameter("ec_i")%>">
							<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd")==null?"":request.getParameter("ec_crd")%>">
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									�����������õ���;�����б�
								</td>
							</tr>
							<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="uclist" var="uc" autoIncludeParameters="false" rowsDisplayed="10" action="deptUsageCategoryAction.do?method=search4List">

											<ec:exportXls fileName="usagecategoryList.xls" tooltip="���� Excel" />
											<ec:parameter name="search_usageCategoryname" />
											<ec:parameter name="search_ucstate" />
											<ec:parameter name="formName" />
											<ec:parameter name="addNum" />
											<ec:row>
												<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
													<input type="checkbox" name="cbgroup" value="${uc.idmc}" style="border:0px" />
												</ec:column>
												<ec:column property="usageCategoryName" title="��;��������" headerStyle="text-align:center" style="text-align: left" width="150">
													<c:choose>
														<c:when test="${uc.state=='02'}">
															<font color="#A8A8A8">${uc.usageCategoryName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${uc.state=='00'}">
															<font color="#FF9999">${uc.usageCategoryName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="stateName" title="״̬" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${uc.state=='02'}">
															<font color="#A8A8A8">${uc.stateName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${uc.state=='00'}">
															<font color="#FF9999">${uc.stateName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updatorName" title="������" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${uc.state=='02'}">
															<font color="#A8A8A8">${uc.updatorName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${uc.state=='00'}">
															<font color="#FF9999">${uc.updatorName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updateTime" title="��������" headerStyle="text-align:center" style="text-align: left" width="100">
													<c:choose>
														<c:when test="${uc.state=='02'}">
															<font color="#A8A8A8">${uc.updateTime}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${uc.state=='00'}">
															<font color="#FF9999">${uc.updateTime}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
											</ec:row>
										</ec:table>
									</td>
								</tr>
								<%if (((java.util.ArrayList) request.getAttribute("uclist")).size() > 0) {%>
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
														<%if (request.getAttribute("addNum") == null
						|| request.getAttribute("addNum").equals("")) {%>
														<input name="bupdate" type="button" class="button_nor" value="�� ��" onClick="DoUpdate()">
														<input name="bnotuse" type="button" class="button_nor" value="����/��ͨ��" onClick="DoUse('02')">
														<input name="buse" type="button" class="button_nor" value="ʹ��/ͨ��" onClick="DoUse('01')">
														<%if (request.getAttribute("noNew") == null
							|| request.getAttribute("noNew").equals("")
							|| request.getAttribute("noNew").equals("0")) {%>
														<input name="Submit4" type="button" class="button_nor" value="�� ��" onClick="DoAdd()">
														<%}%>
														<%} else {%>
														<input name="selectOK" type="button" class="button_nor" value="ȷ ��" onClick="addUc()">
														<input name="Submit4" type="button" class="button_nor" value="�� ��" onClick="DoAdd()">														
														<%}%>
													</td>
												</tr>
											</tbody>
										</table>
									</td>
								</tr>
								<%} else {%>
								<%if (request.getAttribute("noNew") == null
						|| request.getAttribute("noNew").equals("")
						|| request.getAttribute("noNew").equals("0")) {%>
								<tr>
									<td height="40" align="right" valign="middle">
										<input name="Submit4" type="button" class="button_nor" value="�� ��" onClick="DoAdd()">
									</td>
								</tr>
								<%}%>
								<%}%>
							</jodd:form>
						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){

  if(document.deptUsageCategoryForm.formName.value!=''){
      if(document.all.selectOK!=null)
          document.all.selectOK.style.display='';//��ʾȷ����ť      
  }
  else{
      if(document.all.selectOK!=null)
          document.all.selectOK.style.display='none';//����ʾȷ����ť

  }
  
  if(document.deptUsageCategoryForm.hmsg.value=='dok')
       alert("���óɹ���");
  else if(document.deptUsageCategoryForm.hmsg.value=='dfail')
       alert("����ʧ�ܣ�");
  if(document.deptUsageCategoryForm.hrepeatSet.value!='')
       alert(document.deptUsageCategoryForm.hrepeatSet.value+" �ظ����ã�");
}

function addUc(){   
   
   var sflag=0;
   
   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("��ѡ����;�������ƣ�");
              return;
          }
          if(sflag>1){
              alert("ֻ��ѡ��һ����;�������ƣ�");
              return;
          }           
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("��ѡ����;�������ƣ�");
              return;        
        }
   }   
   
   var wlid="";
   var wlmc="";
   if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   var idmc=document.all.cbgroup[i].value;
                   var pos=idmc.indexOf('_');
                   if(pos!=-1){
                        wlid=idmc.substring(0,pos);
                        wlmc=idmc.substring(pos+1,idmc.length); 
                   }                                                  
              }
       }
   
   }
   else{
        if(document.all.cbgroup.checked){
             var idmc=document.all.cbgroup.value;
                   var pos=idmc.indexOf('_');
                   if(pos!=-1){
                        wlid=idmc.substring(0,pos);
                        wlmc=idmc.substring(pos+1,idmc.length); 
                   }              
        }
   
   }  
   
   var targetForm=document.deptUsageCategoryForm.formName.value;   
   
   if(parseInt(document.deptUsageCategoryForm.addNum.value)==1||eval("opener."+targetForm+".busageCategory==null")){   
       eval("opener."+targetForm+".usageCategory.value=wlid;");       
       var haswl=false;
       for(var j=0;j<eval("opener."+targetForm+".s_usageCategory.length");j++){
          if(eval("opener."+targetForm+".s_usageCategory[j].value")==wlid){
	         eval("opener."+targetForm+".s_usageCategory[j].selected=true;");
	         haswl=true;
	      }
       }   
       eval("opener."+targetForm+".tempUsageCategory.value=wlmc;")
       if(eval("opener."+targetForm+".new_usageCategory!=null"))
           eval("opener."+targetForm+".new_usageCategory.value=opener."+targetForm+".usageCategory.value;");
       if(eval("opener."+targetForm+".ifChanged!=null"))
           eval("opener."+targetForm+".ifChanged.value='1';");
       
       if(haswl){
           eval("opener."+targetForm+".tempUsageCategory.style.display='none';");
           eval("opener."+targetForm+".s_usageCategory.style.display='';");
       }
       else{
           eval("opener."+targetForm+".s_usageCategory.style.display='none';");
           eval("opener."+targetForm+".tempUsageCategory.style.display='';");
       }
   }
   else if(parseInt(document.deptUsageCategoryForm.addNum.value)>1){
       eval("opener."+targetForm+".busageCategory.value=wlid;");
       var haswl=false;
       for(var j=0;j<eval("opener."+targetForm+".bs_usageCategory.length");j++){
          if(eval("opener."+targetForm+".bs_usageCategory[j].value")==wlid){
	         eval("opener."+targetForm+".bs_usageCategory[j].selected=true;");
	         haswl=true;
	      }
       }   
       eval("opener."+targetForm+".btempUsageCategory.value=wlmc;");
       eval("opener."+targetForm+".ifChanged.value='1';");
       
       if(haswl){
           eval("opener."+targetForm+".btempUsageCategory.style.display='none';");
           eval("opener."+targetForm+".bs_usageCategory.style.display='';");
       }
       else{
           eval("opener."+targetForm+".bs_usageCategory.style.display='none';");
           eval("opener."+targetForm+".btempUsageCategory.style.display='';");
       }
   }
   this.window.close();

}

function DoFind(){

   var ucstate=document.deptUsageCategoryForm.elements["search_ucstate"].value;
   var ucname=document.deptUsageCategoryForm.elements["search_usageCategoryname"].value;
   
   if(document.deptUsageCategoryForm.addNum.value!=''){
     // if(ucname.length%2!=0)
     //       ucname=ucname+"Ի";
     
      deptUsageCategoryForm.action="deptUsageCategoryAction.do?method=search4List";
      deptUsageCategoryForm.submit();
      //window.open('deptUsageCategoryAction.do?method=search4List&ucState='+ucstate+'&ucName='+ucname+'&formName='+document.deptUsageCategoryForm.formName.value+'&addNum='+document.deptUsageCategoryForm.addNum.value,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
   }
   else{
      deptUsageCategoryForm.action="deptUsageCategoryAction.do?method=search4List";
      deptUsageCategoryForm.submit();
   
   }

}

function DoAdd(){
   if(document.deptUsageCategoryForm.addNum.value!='')
       window.open('deptUsageCategoryAction.do?method=load4Add&addNum='+document.deptUsageCategoryForm.addNum.value+'&formName='+document.deptUsageCategoryForm.formName.value,'nextwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
   else{
       document.forms.ec.action="deptUsageCategoryAction.do?method=load4Add&search_ucstate="+document.deptUsageCategoryForm.elements["search_ucstate"].value;
       document.forms.ec.submit();
   
   }

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

function DoUpdate(){

   var sflag=0;
   var cb=0;

   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;   
                   cb=i;                                  
              }
          } 
          if(sflag>1){
                       alert("ֻ��ѡ��һ����¼�����޸ģ�");
                       return;
          }         
          
          else if(sflag==0){
              alert("��ѡ��Ҫ�޸ĵ���;���࣡");
              return;
          } 
          else
              document.deptUsageCategoryForm.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("��ѡ��Ҫ�޸ĵ���;���࣡");
              return;        
        }
        else
            document.deptUsageCategoryForm.updateid.value=document.all.cbgroup.value;
   
   }   
   if(document.deptUsageCategoryForm.addNum.value!='')
       window.open('deptUsageCategoryAction.do?method=load4Update&ucId='+document.deptUsageCategoryForm.updateid.value+'&addNum='+document.deptUsageCategoryForm.addNum.value,'nextwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
   else{   
       document.forms.ec.action="deptUsageCategoryAction.do?method=load4Update&ucId="+document.deptUsageCategoryForm.updateid.value+"&search_ucstate="+document.deptUsageCategoryForm.elements["search_ucstate"].value;
       document.forms.ec.submit();
   }
}

function DoUse(str){

   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   var id=document.all.cbgroup[i].value;
                   var pos=id.indexOf('_');
                   if(pos!=-1)
                       id=id.substring(0,pos);
                   ids=ids+"'"+id+"'"+",";                                                 
              }
          }           
         if(sflag==0){
              alert("��ѡ����;���࣡");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              var id=document.all.cbgroup.value;
              var pos=id.indexOf('_');
              if(pos!=-1)
                  id=id.substring(0,pos);
              ids=ids+"'"+id+"'"+",";      
        }
        else{
            alert("��ѡ����;���࣡");
            return;   
        }            
   }

if(str=='02'){   
   if(confirm("��ȷ��Ҫ��������;������")){
       deptUsageCategoryForm.action="deptUsageCategoryAction.do?method=setUsageCategory&ucIds="+ids.substring(0,ids.length-1)+"&ucstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptUsageCategoryForm.submit();
   }
   else
      return;
}
if(str=='01'){   
   if(confirm("��ȷ��Ҫʹ�ø���;������")){
       deptUsageCategoryForm.action="deptUsageCategoryAction.do?method=setUsageCategory&ucIds="+ids.substring(0,ids.length-1)+"&ucstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptUsageCategoryForm.submit();
   }
   else
      return;
}


}

function DoClear(){

    document.deptUsageCategoryForm.elements["search_usageCategoryname"].value="";
    document.deptUsageCategoryForm.elements["search_ucstate"].value="";
}

</SCRIPT>
