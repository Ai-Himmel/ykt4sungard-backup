<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>

<html>
<head>
<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>
<meta http-equiv="Content-Type" content="text/html;">

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
<SCRIPT language=javascript>
function baocun(elements){
     if(doCheckForm(elements)!=false){
    	allocationInfoForm.action = "<c:url value="/lf/allocationAction.do"/>?method=updateAllocationInfo4batch";
		allocationInfoForm.submit();
		}
}
function back(){
		allocationInfoForm.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Sy";
		allocationInfoForm.submit();
}
function doCheckForm(elements)
{
	var len = elements.length;

	for(var i=0;i< len ;i++ )
	{
		var field = elements[i];
		if(field.name=='placeNum'){
				if(field.value!=''){
					if(!isInt(field.value))
				    {
						msg(field.title+"����������");
						field.select();
						return false;
				    }
				    alert(elements['allocationInfoIds'].length);
				    if((field.value)*elements['allocationInfoIds'].length>(elements['placeableNum'].value))
				    {
				    	msg(field.title+"������ֻ��С�ڻ���ڵ�������\n\n�˴�����д���������Ϊ��"+parseInt(elements['placeableNum'].value/elements['allocationInfoIds'].length));
				    	field.select();
						return false;
				    }
				}
		}
		if(field.name=='bdid'){

					if(elements['xqId'].value!='')
				    {
						msg(field.title+"��ѡ��¥��");
						field.select();
						return false;
				    }
		}
		if(field.name=='rmid'){

					if(elements['bdid'].value!='')
				    {
						msg(field.title+"��ѡ�񷿼�");
						field.select();
						return false;
				    }
		}
	}
}

function isInt(value){
	var returnValue = true;
	var re =  new RegExp("^([0-9]+)$");
	if(value.search(re) == -1)
	{
	returnValue=false;
	}
	return returnValue;
}
function isDouble(value){
	var returnValue = true;
	var re =  new RegExp("^(([0-9]+)|([0-9]+.[0-9]{2})|([0-9]+.[0-9]{1}))$");
	if(value.search(re) == -1)
	{
	returnValue=false;
	}
	return returnValue;
}
function msg(message)
{
	message = "\n�������Ϲ���ϵͳ������ʾ\n\n======================================           \n\n"+message;
	message += "\n\n======================================           ";
	alert(message);
}

</SCRIPT>

</head>
<html:form action="/lf/allocationAction.do" method="post">
<jodd:form bean="request">
            <input type="hidden" name="ec_i" />
            <input type="hidden" name="ec_p" />
            <input type="hidden" name="ec_crd" />
            <input type="hidden" name="search_dlid" />
            <input type="hidden" name="search_xlid" />
            <input type="hidden" name="search_wlid" />     
            <input type="hidden" name="search_wlxh" />
            <input type="hidden" name="search_ifAppendix" />
            <input type="hidden" name="search_dtlState" />
            <input type="hidden" name="search_producterId" />     
            <input type="hidden" name="search_providerId" />	
</jodd:form>
<body  bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<br>
<%
String[] aa=null;
 aa=(String[])request.getAttribute("untreadIdList");
for (int i=0;i<aa.length;i++){ 
	String bb=aa[i];
%>
<input type="hidden" name="allocationInfoIds" value="<%=bb%>">
<%} %>
<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
  <tr>
    <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top"><table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">�������ñ�</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td height="40" align="center" valign="top">
        <html:hidden property="placeableNum" styleClass="input_box"/>
        <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <html:hidden property="wlArrivalDtlId" styleClass="input_box"/>
            <html:hidden property="wlArrivalId" styleClass="input_box"/>
            <tr align="center" valign=center>              
              <td align="left" valign="middle" class="tableHeader2" style="width:15%">���ö���</td>
              <td align="left" valign="middle" class="tableHeader3"style="width:20%" >
              <html:select property="pfId" styleClass="select01">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="azdxList" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" style="width:15%">У��</td>
              <td align="left" valign="middle" class="tableHeader3" style="width:20%">
              <html:select property="xqId" styleClass="select01" onchange="changeBd(this)">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="xqList" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>
              </tr>
            <tr align="center" valign=center>              
              <td width="15%" align="left" valign="middle" class="tableHeader2" >¥��</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="35">
                  <html:hidden property="bdid" styleClass="input_box"/>
                  <html:select property="s_bdid" styleClass="select01" onchange="changeRm(this);changeBdid(this)">
                      <html:option value="">��ѡ��</html:option>	
				      <html:options collection="louyuList" labelProperty="lymc" property="id" />
				  </html:select>
    
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="40" align="right">
                  <input name="tempbuilding" style="input_box" maxlength="50" value="<%=request.getParameter("tempbuilding")==null||request.getParameter("tempbuilding").equals("null")?"":request.getParameter("tempbuilding")%>" readonly="readonly"/>
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="20" align="right">
                  <input name="addBuilding" type="button" value="����" onclick="javascript:window.open('<c:url value="/gyf/deptBuildingAction.do"/>?method=search4List&formName=allocationInfoForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');" >
                  </td>                   
                </tr></table>
              </td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="35">
                  <html:hidden property="rmid" styleClass="input_box"/>
                  <html:select property="s_rmid" styleClass="select01" onchange="changeRmid(this)">
                      <html:option value="">��ѡ��</html:option>	
				      <html:options collection="roomList" labelProperty="roommc" property="id" />
				  </html:select>
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="40" align="right">
                  <input name="temproom" style="input_box" maxlength="50" value="<%=request.getParameter("temproom")==null||request.getParameter("temproom").equals("null")?"":request.getParameter("temproom")%>" readonly="readonly"/>
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="20" align="right">
                  <input name="addRoom" type="button" value="����" onclick="javascript:window.open('<c:url value="/gyf/deptRoomAction.do"/>?method=search4List&formName=allocationInfoForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');" >
                  </td>                   
                </tr></table>
			  </td>
            </tr>
            <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ϸ�ص�</td>
              <td align="left" valign="middle" class="tableHeader3" colspan="3">
              <html:textarea property="place" styleClass="" rows="3" cols="80"/>
              </td>             
            </tr>
            <tr align="center" valign=center>
               <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��������</td>
              <td align="left" valign="middle" class="tableHeader3" >

              <html:text property="placeNum" styleClass="input_box"/></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����Ա</td>
              <td align="left" valign="middle" class="tableHeader3" >
			  <html:select property="managerId" styleClass="select01">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="managerList" labelProperty="personName" property="code" />
              </html:select>
              </td>                         
            </tr>
            <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ע</td>
              <td colspan="3" align="left" valign="middle" class="tableHeader3" >
              <html:textarea property="placeMemo" styleClass="" rows="3" cols="80"/></td>
              </tr>
          </tbody>
        </table>        </td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle">
          <input name="Submit" type="button" class="button_nor" value="�� ��" onClick="javascript:baocun(document.forms[0].elements);">
&nbsp;
<input name="Submit2" type="button" class="button_nor" value="�� ��" onClick="javascript:back();"></td>
      </tr>
      
      
      
    </table></td>
  </tr>
</table>

</body>
</html:form>
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
setTimeout('DoInit()',10);
function DoInit(){
  var pr,uc,pf,xq,bd,rm,mg,acp;
  
     //alert("idcount="+idcount);

     pf=document.allocationInfoForm.elements["pfId"].value;
     xq=document.allocationInfoForm.elements["xqId"].value;
     bd=document.allocationInfoForm.elements["bdid"].value;
     rm=document.allocationInfoForm.elements["rmid"].value;
     mg=document.allocationInfoForm.elements["managerId"].value;


   for(var i=0;i<document.allocationInfoForm.elements["pfId"].length;i++){//�ɷ�����
       if(document.allocationInfoForm.elements["pfId"][i].value==pf)
            document.allocationInfoForm.elements["pfId"][i].selected=true;
   }
  
  for(var i=0;i<document.allocationInfoForm.elements["xqId"].length;i++){//У��
       if(document.allocationInfoForm.elements["xqId"][i].value==xq)
            document.allocationInfoForm.elements["xqId"][i].selected=true;  
   }
   if(xq!='')
      changeBd(document.allocationInfoForm.elements["s_xqid"]);
      for(var j=0;j<document.allocationInfoForm.elements["s_bdid"].length;j++){
      if(document.allocationInfoForm.elements["s_bdid"][j].value==bd)
	     document.allocationInfoForm.elements["s_bdid"][j].selected=true;
	  }			
   
   if(bd!='')
        changeRm(document.allocationInfoForm.elements["s_bdid"]);
   for(var j=0;j<document.allocationInfoForm.elements["s_rmid"].length;j++){
      if(document.allocationInfoForm.elements["s_rmid"][j].value==rm){
	     document.allocationInfoForm.elements["s_rmid"][j].selected=true;
	     
	  }
   }   
   
   for(var i=0;i<document.allocationInfoForm.elements["managerId"].length;i++){//�¹���Ա
       if(document.allocationInfoForm.elements["managerId"][i].value==mg)
            document.allocationInfoForm.elements["managerId"][i].selected=true;
   }	
}

function changeBdid(sel){
    document.all.bdid.value=sel.value;
}
function changeRmid(sel){
    document.all.rmid.value=sel.value;
}
function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_bdid.length=1; //���ԭ¥���б�
   document.all.s_rmid.length=1; //���ԭ�����б�        
      
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.all.s_bdid.options[document.all.s_bdid.length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.all.s_bdid.options[document.all.s_bdid.length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}
function changeRm(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_rmid.length=1; //���ԭ�����б�        
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
       
       for (i=0;i < datacount2; i++)
      {
          document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
}
</SCRIPT>