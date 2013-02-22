<%@page pageEncoding="GBK"%>
<%@ page import="java.util.*"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.business.domain.DeptInfo"%>
<html>
	<head>
		<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script src="<c:url value="/pages/scripts/util.js"/>" type="text/javascript"></script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<%String curentDeptName = "";
			DeptInfo deptInfo = new DeptInfo();
			if (request.getSession().getAttribute("currentDept") != null) {
				deptInfo = (DeptInfo) request.getSession().getAttribute(
						"currentDept");
			}

			curentDeptName = deptInfo.getDeptName();

			%>

		<br>


		<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">

			<html:form action="/wxg/dictionarys.do?method=getDictionarys" method="post">
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
												�û������ֵ�ά��
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
											<input type="hidden" name="updateid" value="">
											<tr align="center" valign=center>
												<td width="20%" height="26" align="right" valign="middle" class="tableHeader2">
													�ֵ����
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="querylb" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:option value="1">������Դ</html:option>
														<html:option value="2">�ɷ�����</html:option>
														<html:option value="5">�豸�ɷ�ԭ��</html:option>
														<html:option value="6">�׺�Ʒ�ɷ�ԭ��</html:option>
														<html:option value="7">У��</html:option>
													</html:select>
												</td>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													״̬
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="dictstate" styleClass="select01">
														<html:option value="">��ѡ��	</html:option>
														<html:option value="1">ʹ��</html:option>
														<html:option value="0">����</html:option>
														<html:option value="9">���ñ���</html:option>
													</html:select>
												</td>
											</tr>
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
							<logic:present name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="<bean:write name="repeatSet" />">
							</logic:present>
							<logic:notPresent name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="alwaysExist" scope="request">
								<input name="halwaysExist" type="hidden" value="<bean:write name="alwaysExist" />">
							</logic:present>
							<logic:notPresent name="alwaysExist" scope="request">
								<input name="halwaysExist" type="hidden" value="">
							</logic:notPresent>
							<input type="hidden" name="ec_p" value="<%=request.getParameter("ec_p")==null?"1":request.getParameter("ec_p")%>">
							<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i")==null?"":request.getParameter("ec_i")%>">
							<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd")==null?"":request.getParameter("ec_crd")%>">
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									�����ֵ�ά��
								</td>
							</tr>
							<tr>
								<td height="20" align="center" valign="middle">
									<ec:table items="dictionarys" var="diction" autoIncludeParameters="false" rowsDisplayed="10" action="dictionarys.do?method=getDictionarys">
										<ec:exportXls fileName="dictList.xls" tooltip="���� Excel" />
										<ec:parameter name="querylb" />
										<ec:parameter name="dictstate" />
										<ec:row>
											<ec:column property="checkbox" title="ѡ��" sortable="false" width="30" headerStyle="text-align:center" style="text-align: left">
												<input type="checkbox" name="cbgroup" value="${diction.dictValue}" style="border:0px" />
											</ec:column>
											<ec:column property="dictCaption" title="�ֵ���ֵ" headerStyle="text-align:center" style="text-align: left" width="80">
												<c:choose>
													<c:when test="${diction.isValid=='0'}">
														<font color="#A8A8A8">${diction.dictCaption}</font>&nbsp;
					</c:when>
												</c:choose>
											</ec:column>
											<ec:column property="dictName" title="�ֵ����" headerStyle="text-align:center" style="text-align: left" width="80">
												<c:choose>
													<c:when test="${diction.isValid=='0'}">
														<font color="#A8A8A8">${diction.dictName}</font>&nbsp;
					</c:when>
												</c:choose>
											</ec:column>
											<ec:column property="isValidName" title="״̬" headerStyle="text-align:center" style="text-align: left" width="80">
												<c:choose>
													<c:when test="${diction.isValid=='0'}">
														<font color="#A8A8A8">${diction.isValidName}</font>&nbsp;
					</c:when>
												</c:choose>
											</ec:column>
											<ec:column property="updatorName" title="������" headerStyle="text-align:center" style="text-align: left" width="80">
												<c:choose>
													<c:when test="${diction.isValid=='0'}">
														<font color="#A8A8A8">${diction.updatorName}</font>&nbsp;
					</c:when>
												</c:choose>
											</ec:column>
											<ec:column property="updateTime" title="��������" headerStyle="text-align:center" style="text-align: left" width="90">
												<c:choose>
													<c:when test="${diction.isValid=='0'}">
														<font color="#A8A8A8">${diction.updateTime}</font>&nbsp;
					</c:when>
												</c:choose>
											</ec:column>

										</ec:row>
									</ec:table>

								</td>
							</tr>
							<%if (((java.util.ArrayList) request.getAttribute("dictionarys"))
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
												</td>
												<td height="40" align="right" valign="middle">
													<input name="bupdate" type="button" class="button_nor" value="�� ��" onClick="DoUpdate()">
													<input name="bnotuse" type="button" class="button_nor" value="�� ��" onClick="javascript:DoUse('0');">
													<input name="buse" type="button" class="button_nor" value="ʹ ��" onClick="javascript:DoUse('1');">
													<input name="badd" type="button" class="button_nor" value="�� ��" onClick="javascript:add();">
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<%} else {%>
							<tr>
								<td height="40" align="right" valign="middle">
									<input name="badd" type="button" class="button_nor" value="�� ��" onClick="javascript:add();">
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

setTimeout('init()',10);
function init(){
       
  if(document.dictForm.hmsg.value=='dok')
       alert("���óɹ���");
  else if(document.dictForm.hmsg.value=='dfail')
       alert("����ʧ�ܣ�");
  if(document.dictForm.hrepeatSet.value!='')
       alert(document.dictForm.hrepeatSet.value+" �ظ����ã�");
  if(document.dictForm.halwaysExist.value!='')
       alert(document.dictForm.halwaysExist.value+" Ϊ������,���ܸ���״̬��");
   
}  

function add(){
	document.forms.ec.action="dictionarys.do?method=load4Add";
	document.forms.ec.submit();
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
              alert("��ѡ��Ҫ�޸ĵ��ֵ��");
              return;
          } 
          else
              document.dictForm.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("��ѡ��Ҫ�޸ĵ��ֵ��");
              return;        
        }
        else
            document.dictForm.updateid.value=document.all.cbgroup.value;
   
   }   
      
   document.forms.ec.action="dictionarys.do?method=load4Update&dictId="+document.dictForm.updateid.value;
   document.forms.ec.submit();

}

function DoUse(str){

   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   var id=document.all.cbgroup[i].value;                   
                   ids=ids+"'"+id+"'"+",";                                                 
              }
          }           
         if(sflag==0){
              alert("��ѡ���ֵ��");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              var id=document.all.cbgroup.value;              
              ids=ids+"'"+id+"'"+",";      
        }
        else{
            alert("��ѡ���ֵ��");
            return;   
        }            
   }

if(str=='0'&&document.dictForm.querylb.value=='7'){   
   if(confirm("����У��ͬʱ�������У���µ�¥�����ͻ������ƣ���ȷ��Ҫ�������ֵ�����")){      
       dictForm.action="dictionarys.do?method=setDict&dictIds="+ids.substring(0,ids.length-1)+"&setdictstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       dictForm.submit();     
   }
   else
      return;	
}
else if(str=='0'){
   if(confirm("��ȷ��Ҫ�������ֵ�����")){      
       dictForm.action="dictionarys.do?method=setDict&dictIds="+ids.substring(0,ids.length-1)+"&setdictstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       dictForm.submit();     
   }
   else
      return;

}
if(str=='1'){   
   if(confirm("��ȷ��Ҫʹ�ø��ֵ�����")){
       dictForm.action="dictionarys.do?method=setDict&dictIds="+ids.substring(0,ids.length-1)+"&setdictstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       dictForm.submit();
   }
   else
      return;	
}

}

function DoClear(){ 
    
    document.dictForm.elements["querylb"].value=""; 
    document.dictForm.elements["dictstate"].value="";

}
</script>
