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
	<body leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/yhpdispatchAction.do?method=rcd4YhpDispatch" method="post">

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
												����⾭���¼
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
											<tr id="tr8" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													����У��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_xq" styleClass="select01" onchange="changeBd(this)">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													����¥��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_louyu" styleClass="select01" onchange="changeRm(this)">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													���ڿⷿ
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_jfkf" styleClass="select01">
														<html:option value="">��ѡ��</html:option>
														<html:options collection="roomlist" labelProperty="roommc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													��/���
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_inorout" styleClass="select01">
														<html:option value="">��ѡ��	</html:option>
														<html:option value="1">���</html:option>
														<html:option value="2">����</html:option>
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													ԭ ��
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_pfyy" styleClass="select01">
														<html:option value="">��ѡ��	</html:option>
														<html:options collection="yhppfReasonlist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													������
												</td>
												<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" nowrap="nowrap">
													<html:text property="search_jbr" styleClass="input_box" maxlength="50" />
													&nbsp;
													<select name="s_indeptornot" onchange="doChange(this)">
														<option value="">
															��ѡ��
														</option>
														<option value="1">
															�ڲ���Ա
														</option>
														<option value="0">
															�ⲿ��Ա
														</option>
													</select>
													<html:hidden property="search_indeptornot" />
												</td>
											</tr>
											<tr id="tr9" align="center" valign=center>
												<td align="right" valign="middle" class="tableHeader2">
													�׺�Ʒ����
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_wlmc" styleClass="input_box" maxlength="100" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													��ʼ����
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_begindate" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_begindate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��ʼ����" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													��������
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_enddate" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_enddate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<script type="text/javascript">
                new calendar("search_begindate", "select_begindate", "%Y-%m-%d");
                new calendar("search_enddate", "select_enddate", "%Y-%m-%d");
           </script>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">
									<input name="Submit" type="button" class="button_nor" value="�� ѯ" onclick="DoFind()">
									<input name="Submit2" type="button" class="button_nor" value="�� ��" onclick="DoClear()">
								</td>

							</tr>

							<logic:present name="tongjilist" scope="request">

								<tr>
									<td height="35" align="center" valign="middle" class="mediumblack">
										����⾭���¼
									</td>
								</tr>
								<tr>
									<td height="30" align="right" valign="middle" colspan="2">
										<a href="javascript:DoExport()"><IMG src="<c:url value="/pages/style/default/images/xls.gif"/>" border="0"></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
									</td>
								</tr>
								<tr>
									<td height="24" align="center" valign="middle">
										<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#3F738B bordercolordark=#ffffff id=maintable>
											<tbody>
												<tr align="center" valign=center>
													<td width="20%" valign="middle" class="tableHeader">
														Ʒ ��
													</td>
													<td width="8%" valign="middle" class="tableHeader">
														��/���
													</td>
													<td width="10%" valign="middle" class="tableHeader">
														ԭ ��
													</td>
													<td width="10%" valign="middle" class="tableHeader">
														��������
													</td>
													<td width="10%" valign="middle" class="tableHeader">
														��ʼ���
													</td>
													<td width="10%" valign="middle" class="tableHeader">
														�������
													</td>
													<td width="8%" valign="middle" class="tableHeader">
														������
													</td>
													<td width="10%" valign="middle" class="tableHeader">
														�豸����Ա
													</td>
													<td valign="middle" class="tableHeader">
														��������
													</td>
												</tr>
												<%int j = 0;%>
												<logic:iterate name="tongjilist" id="tl" type="java.util.Map" indexId="i">
													<tr align="center" valign="middle" <%if(j%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
														<td align="center" valign="middle">
															<a href="javascript:DoView('<bean:write name="tl" property="id" />')"><bean:write name="tl" property="wlmc" /></a>&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="inoroutName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="pfReason" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="pfNum" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="beginNo" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="endNo" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="actPersonName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="applyPersonName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="tl" property="recordDate" formatKey="dateFormat" />
															&nbsp;
														</td>
													</tr>
												</logic:iterate>
											</tbody>
										</table>
									</td>
								</tr>
							</logic:present>
						</table>
					</td>
				</tr>
			</table>
		</html:form>
	</body>
</html>

<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("ablist")!=null)
       resultset=(String[][])request.getAttribute("ablist");//��ȡУ����¥���Ӧ����
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//����javascript��ά���飬��Ӧ¥��id��¥�����ơ�У��id
     <%
     }
   }
   %>
   datacount=<%=count%>;

</script>
<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("bmlist")!=null)
       resultset2=(String[][])request.getAttribute("bmlist");//��ȡ¥������Ӧ����
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//����javascript��ά���飬��Ӧ����id���������ơ������ʶ��¥��id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){
    
  var area=document.yhpdispatchForm.elements["search_xq"].value;
  var building=document.yhpdispatchForm.elements["search_louyu"].value;
  var room=document.yhpdispatchForm.elements["search_jfkf"].value;
  
  if(area!='')
      changeBd(document.yhpdispatchForm.elements["search_xq"]);
  for(var j=0;j<document.yhpdispatchForm.elements["search_louyu"].length;j++){
      if(document.yhpdispatchForm.elements["search_louyu"][j].value==building)
	     document.yhpdispatchForm.elements["search_louyu"][j].selected=true;					
  }
  
  if(building!='')
      changeRm(document.yhpdispatchForm.elements["search_louyu"]);
  for(var j=0;j<document.yhpdispatchForm.elements["search_jfkf"].length;j++){
      if(document.yhpdispatchForm.elements["search_jfkf"][j].value==room)
	     document.yhpdispatchForm.elements["search_jfkf"][j].selected=true;					
  }
  
  var indeptornot=document.yhpdispatchForm.elements["search_indeptornot"].value;
  for(var j=0;j<document.yhpdispatchForm.elements["s_indeptornot"].length;j++){
      if(document.yhpdispatchForm.elements["s_indeptornot"][j].value==indeptornot)
	     document.yhpdispatchForm.elements["s_indeptornot"][j].selected=true;					
  }
  
}  

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.yhpdispatchForm.elements["search_louyu"].length=1; //���ԭ¥���б�
   document.yhpdispatchForm.elements["search_jfkf"].length=1; //���ԭ�����б�        
      
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.yhpdispatchForm.elements["search_louyu"].options[document.yhpdispatchForm.elements["search_louyu"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.yhpdispatchForm.elements["search_louyu"].options[document.yhpdispatchForm.elements["search_louyu"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function changeRm(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.yhpdispatchForm.elements["search_jfkf"].length=1; //���ԭ�����б�        
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.yhpdispatchForm.elements["search_jfkf"].options[document.yhpdispatchForm.elements["search_jfkf"].length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
       alert("wl is null");
       for (i=0;i < datacount2; i++)
      {
          document.yhpdispatchForm.elements["search_jfkf"].options[document.yhpdispatchForm.elements["search_jfkf"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function zchSetup(sel){

   alert(sel.value);

}

function doChange(sel){

    document.yhpdispatchForm.elements["search_indeptornot"].value=sel.value;
    
}

function DoFind(){

if(document.yhpdispatchForm.elements["search_jfkf"].value==''){
    alert("��ѡ��Ҫ��ѯ�Ŀⷿ��");
    return;
}
   
   yhpdispatchForm.action="yhpdispatchAction.do?method=rcd4YhpDispatch&doexl=0";
   yhpdispatchForm.submit();

}

function DoView(eno){

    window.open("yhpdispatchAction.do?method=load4view&dispatchId="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoExport(){
   
   yhpdispatchForm.action="yhpdispatchAction.do?method=rcd4YhpDispatch&doexl=1";
   yhpdispatchForm.submit();

}


function DoClear(){
        
    document.yhpdispatchForm.elements["search_xq"].value="";
    document.yhpdispatchForm.elements["search_louyu"].value="";
    document.yhpdispatchForm.elements["search_jfkf"].value="";
    document.yhpdispatchForm.elements["search_wlmc"].value="";    
    document.yhpdispatchForm.elements["search_begindate"].value="";
    document.yhpdispatchForm.elements["search_enddate"].value="";
    document.yhpdispatchForm.elements["search_inorout"].value="";    
    document.yhpdispatchForm.elements["search_pfyy"].value="";
    document.yhpdispatchForm.elements["search_jbr"].value="";
    
    document.yhpdispatchForm.elements["search_indeptornot"].value="";
    document.yhpdispatchForm.elements["s_indeptornot"].value="";
}

</SCRIPT>

