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
		<html:form action="/gyf/yhpAction.do?method=tongji4YhpKucun" method="post">

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
												�׺�Ʒ���ͳ��
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
											<tr id="tr9" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													��������
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_sccj" styleClass="select01">
														<html:option value="">��ѡ��	</html:option>
														<html:options collection="sccjlist" labelProperty="companyName" property="id" />
													</html:select>
												</td>
												<td align="right" valign="middle" class="tableHeader2">
													�׺�Ʒ����
												</td>
												<td align="left" valign="middle" class="tableHeader3" colspan="3">
													<html:text property="search_wlmc" styleClass="input_box" maxlength="100" />
												</td>
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
										�׺�Ʒ���ͳ��
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
													<td valign="middle" class="tableHeader">
														�ɷ�����
													</td>
													<td valign="middle" class="tableHeader">
														����У��
													</td>
													<td valign="middle" class="tableHeader">
														����¥��
													</td>
													<td valign="middle" class="tableHeader">
														���ڿⷿ
													</td>
													<td valign="middle" class="tableHeader">
														Ʒ ��
													</td>
													<td valign="middle" class="tableHeader">
														�������
													</td>
													<%if (request.getAttribute("ifLimit").equals("0")) {%>
													<td valign="middle" class="tableHeader">
														�� ��
													</td>
													<%}%>
												</tr>
												<%int j = 0;%>
												<logic:iterate name="tongjilist" id="tl" type="java.util.Map" indexId="i">
													<tr align="center" valign="middle" <%if(j%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
														<td align="center" valign="middle">
															<bean:write name="tl" property="pfCategoryName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hpf" value="<bean:write name="tl" property="pfCategoryName" />">
															<bean:write name="tl" property="collegeAreaName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hxq" value="<bean:write name="tl" property="pfCategoryName" /><bean:write name="tl" property="collegeAreaName" />">
															<bean:write name="tl" property="lymc" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hly" value="<bean:write name="tl" property="pfCategoryName" /><bean:write name="tl" property="collegeAreaName" /><bean:write name="tl" property="lymc" />">
															<bean:write name="tl" property="roommc" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hrm" value="<bean:write name="tl" property="pfCategoryName" /><bean:write name="tl" property="collegeAreaName" /><bean:write name="tl" property="lymc" /><bean:write name="tl" property="roommc" />">
															<a
																href="javascript:DoView('<bean:write name="tl" property="wlid"/>','<bean:write name="tl" property="roomid" />','<bean:write name="tl" property="lyid"/>','<bean:write name="tl" property="collegeArea" />','<bean:write name="tl" property="pfCategory" />')"><bean:write name="tl" property="wlmc" />
															</a>&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write	name="tl" property="yhpNum" />&nbsp;
														</td>
														<%if (request.getAttribute("ifLimit").equals("0")) {%>
														<td align="center" valign="middle">
															<bean:write name="tl" property="yhpSum" />
															&nbsp;
														</td>
														<%}%>
													</tr>
												</logic:iterate>
												<logic:present name="tongjitotal" scope="request">
													<logic:iterate name="tongjitotal" id="tlt" type="java.util.Map">
														<tr height="26" align="center" valign="middle" bgcolor="#FF9999" style="font-weight:bold">
															<td align="center" valign="middle">
																�� ��
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<%if (request.getAttribute("ifLimit").equals("0")) {%>
															<td align="center" valign="middle">
																<bean:write name="tlt" property="yhpSum" />
																&nbsp;
															</td>
															<%}%>
														</tr>
													</logic:iterate>
												</logic:present>
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
    
  var area=document.yhpsearchForm.elements["search_xq"].value;
  var building=document.yhpsearchForm.elements["search_louyu"].value;
  var room=document.yhpsearchForm.elements["search_jfkf"].value;
  
  if(area!='')
      changeBd(document.yhpsearchForm.elements["search_xq"]);
  for(var j=0;j<document.yhpsearchForm.elements["search_louyu"].length;j++){
      if(document.yhpsearchForm.elements["search_louyu"][j].value==building)
	     document.yhpsearchForm.elements["search_louyu"][j].selected=true;					
  }
  
  if(building!='')
      changeRm(document.yhpsearchForm.elements["search_louyu"]);
  for(var j=0;j<document.yhpsearchForm.elements["search_jfkf"].length;j++){
      if(document.yhpsearchForm.elements["search_jfkf"][j].value==room)
	     document.yhpsearchForm.elements["search_jfkf"][j].selected=true;					
  }
  
  if(document.all.maintable!=null)
      uniteTable(document.all.maintable,4);
      
}  

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.yhpsearchForm.elements["search_louyu"].length=1; //���ԭ¥���б�
   document.yhpsearchForm.elements["search_jfkf"].length=1; //���ԭ�����б�        
      
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.yhpsearchForm.elements["search_louyu"].options[document.yhpsearchForm.elements["search_louyu"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.yhpsearchForm.elements["search_louyu"].options[document.yhpsearchForm.elements["search_louyu"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function changeRm(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.yhpsearchForm.elements["search_jfkf"].length=1; //���ԭ�����б�        
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.yhpsearchForm.elements["search_jfkf"].options[document.yhpsearchForm.elements["search_jfkf"].length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
       alert("wl is null");
       for (i=0;i < datacount2; i++)
      {
          document.yhpsearchForm.elements["search_jfkf"].options[document.yhpsearchForm.elements["search_jfkf"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function zchSetup(sel){

   alert(sel.value);

}

function DoFind(){
   
   yhpsearchForm.action="yhpAction.do?method=tongji4YhpKucun&doexl=0";
   yhpsearchForm.submit();

}

function DoView(wl,rm,bd,xq,pf){

    yhpsearchForm.action="yhpAction.do?method=load4Detail&wlid="+wl+"&room="+rm+"&building="+bd+"&area="+xq+"&pfdx="+pf;
    yhpsearchForm.submit();
}

function DoExport(){
   
   yhpsearchForm.action="yhpAction.do?method=tongji4YhpKucun&doexl=1";
   yhpsearchForm.submit();

}


function DoClear(){
        
    document.yhpsearchForm.elements["search_xq"].value="";
    document.yhpsearchForm.elements["search_louyu"].value="";
    document.yhpsearchForm.elements["search_jfkf"].value="";
    document.yhpsearchForm.elements["search_sccj"].value="";
    document.yhpsearchForm.elements["search_wlmc"].value="";
}

function uniteTable(thistab,colLength){
var rn=thistab.rows.length;//ȡ������
var rowspann=0;

for(j=colLength-1;j>=0;j--){//�ӵ�0�п�ʼ���ϲ�������
for(i=rn-1;i>0;i--){//�ӵ�����һ�п�ʼ���ϼ��

if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText){//������һ�бȽϣ����������ȾͺϼƵ�ǰ�еĺϲ���������ɾ����ǰ�С�
if(thistab.rows[i].cells[j].children(0)!=null&&thistab.rows[i-1].cells[j].children(0)!=null&&thistab.rows[i].cells[j].children(0).value==thistab.rows[i-1].cells[j].children(0).value){//��ǰ��һ�е�ֵ������������,�����������ֵ���ж��Ƿ�����һ�е�ֵһ�����һ���ͺϼƵ�ǰ�еĺϲ���������ɾ����ǰ�С�
	rowspann+=thistab.rows[i].cells[j].rowSpan;	
	thistab.rows[i].deleteCell(j);	
}else if(thistab.rows[i].cells[j].children(0)==null&&thistab.rows[i-1].cells[j].children(0)==null){//�����������ֵ�����һ��������ֻ�ܺϲ�����	    
		rowspann+=thistab.rows[i].cells[j].rowSpan;		
		thistab.rows[i].deleteCell(j);			
}
else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//������Ⱦ���ɵ�ǰ��ͬ���ݵĺϲ���
rowspann=0;
}

}else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//������Ⱦ���ɵ�ǰ��ͬ���ݵĺϲ���
rowspann=0;
}
}
//����ޱ�ͷ�ı�
if(i==0&&rowspann>0){
thistab.rows[i].cells[j].rowSpan+=rowspann;//������Ⱦ���ɵ�ǰ��ͬ���ݵĺϲ���
rowspann=0;
}

}
}

</SCRIPT>

