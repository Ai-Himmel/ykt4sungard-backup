<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.web.util.Constants"%>
<html>
<head>
<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>
<meta http-equiv="Content-Type" content="text/html;">

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

<SCRIPT language=javascript>
	
function doInit(){
    var tempList = ec.elements["itemList"];
    if(tempList!=null){
    	for(var i=0;i<tempList.length;i++){

        	if(tempList[i].type == 'hidden'){

        		tempList[i].disabled = true;
        	}    	
    	}
    }
}
function search(){
    wlArrivalDtlSearchForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=loadWlArrivalDtlList4Check";
	wlArrivalDtlSearchForm.submit();
}

function doUpdateDtl(){
  var sflag = 0;
 
  var itemList=document.all.itemList.value;
  //alert(itemList);
  if(document.all.itemList.checked==true){
  
     ec.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&flag=1";    
   	 ec.submit();
  }else{
          for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
              alert("ֻ��ѡ��һ���ɹ��������޸�");
              return;
          }else if(sflag<1){
          	  alert("��ѡ��һ��Ҫ�޸ĵĲɹ����룡");
          }else{
           
   			  ec.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&flag=1";   
   			  ec.submit();
          } 
}
}
function look(){
  var sflag = 0;
  if(document.all.itemList.checked==true){
  
     ec.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Check";    
   	 ec.submit();
  }else{
          for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
              alert("ֻ��ѡ��һ���ɹ��������޸�");
              return;
          }else if(sflag<1){
          	  alert("��ѡ��һ��Ҫ�޸ĵĲɹ����룡");
          }else{
           
   			  ec.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Check";    
   			  ec.submit();
          } 
}
}
function pass(){
  var sflag = 0;
  var gflag = 0;
  var ids="";
  
   if(document.all.itemList!=null&&document.all.itemList.length>1){
          for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   gflag=gflag+1; 
                   ids=ids+document.all.itemList[i].value+",";                                                 
              }
          }           
         if(gflag==0){
              alert("��ѡ��һ��Ҫ��˵Ĳɹ����룡");
              return;
          } 
   }
  if(document.all.itemList.checked==true){
     gflag=1;
     ids=ids+document.all.itemList.value+",";
     wlArrivalDtlSearchForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkPass4Batch&idset="+ids.substring(0,ids.length-1)+"&idcount="+gflag;  
   	 wlArrivalDtlSearchForm.submit();
  }else{
          for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
              
   			  wlArrivalDtlSearchForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkPass4Batch&idset="+ids.substring(0,ids.length-1)+"&idcount="+gflag;    
   			  wlArrivalDtlSearchForm.submit()
          }else if(sflag<1){
          	  alert("��ѡ��һ��Ҫ�޸ĵĲɹ����룡");
          }else{             
   			  wlArrivalDtlSearchForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkPass4Batch&idset="+ids.substring(0,ids.length-1)+"&idcount="+gflag;  
   			  wlArrivalDtlSearchForm.submit();
          } 
}
}
function noPass(){
  var sflag = 0;
  var gflag = 0;
  var ids="";
  
   if(document.all.itemList!=null&&document.all.itemList.length>1){
          for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   gflag=gflag+1; 
                   ids=ids+document.all.itemList[i].value+",";                                                 
              }
          }           
         if(gflag==0){
              alert("��ѡ��һ��Ҫ��˵Ĳɹ����룡");
              return;
          } 
   }
  if(document.all.itemList.checked==true){
       gflag=1;
     ids=ids+document.all.itemList.value+",";
   wlArrivalDtlSearchForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkNoPass4Batch&idset="+ids.substring(0,ids.length-1)+"&idcount="+gflag;    
   wlArrivalDtlSearchForm.submit();
  }else{
          for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
  			  wlArrivalDtlSearchForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkNoPass4Batch&idset="+ids.substring(0,ids.length-1)+"&idcount="+gflag;    
 			  wlArrivalDtlSearchForm.submit();
          }else if(sflag<1){
          	  alert("��ѡ��һ��Ҫ�޸ĵĲɹ����룡");
          }else{           
   			     wlArrivalDtlSearchForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkNoPass4Batch&idset="+ids.substring(0,ids.length-1)+"&idcount="+gflag;    
   				 wlArrivalDtlSearchForm.submit();
          } 
}
}
function DoView(id){
    wlArrivalDtlSearchForm.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Check&wlArrivalDtlId="+id;
	wlArrivalDtlSearchForm.submit();
}
function DoSelectall(){
  if(document.all.itemList!=null&&document.all.itemList.length>1){   
       for(var i=0;i<document.all.itemList.length;i++){
              document.all.itemList[i].checked=true;
       }
       
  }
  else if(document.all.itemList!=null){
       document.all.itemList.checked=true;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoNotselectall(){
  
  if(document.all.itemList!=null&&document.all.itemList.length>1){   
       for(var i=0;i<document.all.itemList.length;i++){
              document.all.itemList[i].checked=false;
       }
       
  }
  else if(document.all.itemList!=null){
       document.all.itemList.checked=false;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
}

function DoReverseselect(){
   
   if(document.all.itemList!=null&&document.all.itemList.length>1){   
       for(var i=0;i<document.all.itemList.length;i++){
           if(document.all.itemList[i].checked)
              document.all.itemList[i].checked=false;
           else if(!document.all.itemList[i].checked)
              document.all.itemList[i].checked=true;
       }
       
  }
  else if(document.all.itemList!=null){
      if(document.all.itemList.checked)
          document.all.itemList.checked=false; 
      else if(!document.all.itemList.checked)
          document.all.itemList.checked=true;    
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}
</SCRIPT>
</head>
<body  bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<br>

<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
  <tr>
    <td align="left" valign="top">
    
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top">
        <html:form action="/lf/wlArrivalDtlAction4Search" method="post">
        <table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">��������</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td height="40" align="center" valign="top"><table 
        width=99% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>

          <tbody>
            <tr align="center" valign="center">
          <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >���ϴ���</td>
          <td width="20%" align="left" valign="middle" class="tableHeader3" >
               <html:select property="search_dlid" styleClass="select01" onchange="changeXl(this)">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="dllist" labelProperty="dlmc" property="id" />
               </html:select></td>
          <td width="13%" align="left" valign="middle" class="tableHeader2" >����С��</td>
          <td width="20%" align="left" valign="middle" class="tableHeader3" >
               <html:select property="search_xlid" styleClass="select01" onchange="changeWl(this)">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="xllist" labelProperty="xlmc" property="id" />
               </html:select>
          </td>
          
        </tr>
        <tr align="center" valign="center">
          <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�����ͺ�</td>
          <td width="20%" align="left" valign="middle" class="tableHeader3" >
          	<html:text property="search_wlxh" styleClass="input_box" maxlength="50"/>
          </td>
          <td width="13%" align="left" valign="middle" class="tableHeader2" >�Ƿ񸽼�</td>
          <td width="20%" align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td>
          	   <html:select property="search_ifAppendix" styleClass="select01">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:option value="0">��</html:option>
				 <html:option value="1">��</html:option>
               </html:select>
              </td>
              </tr>
          </table></td>
         
        </tr>
        <tr align="center" valign="center">
          <td width="13%" align="left" valign="middle" class="tableHeader2" >��������</td>
          <td width="20%" align="left" valign="middle" class="tableHeader3" >          	   
          	<html:select property="search_producterId" styleClass="select01">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="scslist" labelProperty="companyName" property="id" />
            </html:select></td>
          <td width="13%" align="left" valign="middle" class="tableHeader2" >��Ӧ��</td>
          <td width="20%" align="left" valign="middle" class="tableHeader3" colspan=3>
            <html:select property="search_providerId" styleClass="select01">
                 <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="gyslist" labelProperty="companyName" property="id" />
            </html:select>
		  </td>
        </tr>
          </tbody>
		  
        </table>    </td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle" class="tdborder02">
          <input name="Submit" type="button" class="button_nor" onClick="search()" value="�� ѯ" >
&nbsp;<input name="Submit2" type="button" class="button_nor" value="�� ��" onclick="DoClear()"></td>
      </tr>
      <input name="checkMemo" type="hidden" value="">
      </html:form>
      <tr>
        <td height="35" align="center" valign="middle" class="mediumblack">������ϸ���б�</td>
      </tr>
      <tr>
        <td height="20" align="center" valign="middle">
        <ec:table items="wlArrivalDtlList" var="wlArrivalDtl" rowsDisplayed="10" action="wlArrivalDtlAction4Search.do?method=loadWlArrivalDtlList4Check" >
			    <ec:parameter name="search_dlid" />
				<ec:parameter name="search_xlid" />
				<ec:parameter name="search_wlid" />
				<ec:parameter name="search_wlxh" />		
				<ec:parameter name="search_ifAppendix" />
				<ec:parameter name="search_dtlState" />
				<ec:parameter name="search_producterId" />
				<ec:parameter name="search_providerId" />							
				<ec:exportXls fileName="wlArrivalDtlList.xls" tooltip="���� Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="50" headerStyle="text-align:center" style="text-align: center">
						<input type="checkbox" name="itemList" value="${wlArrivalDtl.wlArrivalDtlId}" style="border:0px"/>
					</ec:column>
					<ec:column property="wlmc" title="��������" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="ifAppendix" title="�Ƿ񸽼�" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="arrivalNum" title="������" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="providerName" title="��Ӧ��" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="producterName" title="������" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="producerName" title="�������" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					>
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')">�������һ��</a>
					</ec:column>
				</ec:row>

			</ec:table>
</td>
      </tr>
<tr><td>
<c:if test="${listSize=='0'}">  
 <div id="opt_div_105295_367628" style="display:none">
</c:if>
<table>
 <form name="tempForm" action="" method="post">
      <tr>
              <td width="5%" style="background-color: #D1DAE9;font-family:����;font-size: 12px;text-align:center;text-valign:middle;font-weight: bold;">�������</td>
              <td width="95%" align="left" valign="middle" class="tableHeader3" >
                  <textarea name="checkOpinion" cols="75" onchange="javascript:document.wlArrivalDtlSearchForm.checkMemo.value=this.value;"></textarea>
              </td>
         
</tr>
   </form>  
      <tr>
              <td>
          			<input name="selectall" type="button" class="button_nor" value="ȫ ѡ" onClick="DoSelectall()" >&nbsp;<input name="notselectall" type="button" class="button_nor" value="ȫ��ѡ" onClick="DoNotselectall()" >&nbsp;<input name="reverseselect" type="button" class="button_nor" value="�� ѡ" onClick="DoReverseselect()" >
        		</td>
        <td height="40" align="right" valign="middle">
<input name="Submit1" type="button" class="button_nor" value="�� ��"  onClick="doUpdateDtl()">
<input name="Submit1" type="button" class="button_nor" value="ͨ ��"  onClick="pass()">
<input name="Submit3" type="button" class="button_nor" value="��ͨ��" onClick="noPass()">
<input name="Submit2" type="button" class="button_nor" value="�� ��" onClick="look()">

</td>		
      </tr></table></td></tr> 
<c:if test="${listSize=='0'}">  
</div>
</c:if> 
    </table></td>
  </tr>
</table>

</body>

</html>
<script>
function DoClear(){
	document.wlArrivalDtlSearchForm.elements["search_dlid"].options[0].selected=true;
    document.wlArrivalDtlSearchForm.elements["search_xlid"].options[0].selected=true;    
    document.wlArrivalDtlSearchForm.elements["search_wlxh"].value="";
    document.wlArrivalDtlSearchForm.elements["search_ifAppendix"].options[0].selected=true;    
    document.wlArrivalDtlSearchForm.elements["search_producterId"].options[0].selected=true;
    document.wlArrivalDtlSearchForm.elements["search_providerId"].options[0].selected=true;
}
</SCRIPT>
<script>
	var idcount=0;
    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("dxlist")!=null)
       resultset=(String[][])request.getAttribute("dxlist");//��ȡ��С���Ӧ����
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//����javascript��ά���飬��ӦС��id��С�����ơ�����id
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
   if(request.getAttribute("xmlist")!=null)
       resultset2=(String[][])request.getAttribute("xmlist");//��ȡС�ࡢ���ƶ�Ӧ����
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//����javascript��ά���飬��Ӧ����id���������ơ����ϵ�λ��С��id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<script type="text/javascript">
setTimeout('doInit()',30);
setTimeout('DoInit()',30);
function DoInit(){
  var dl,xl,wl,dept,wxs,uc,ifap,j;

     var dllist = document.wlArrivalDtlSearchForm.elements["search_dlid"];
     var xllist = document.wlArrivalDtlSearchForm.elements["search_xlid"];    

     dl = dllist.options[dllist.selectedIndex].value;
     xl = xllist.options[xllist.selectedIndex].value;    
     
   if(dl!="")
      changeXl(dllist);
   for(j=0;j<xllist.length;j++){
      if(xllist[j].value==xl)
	     xllist[j].selected=true;
   }		 
   
}

function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   

   document.wlArrivalDtlSearchForm.elements["search_xlid"].length=1; //���ԭС���б�
  

   if(id!="")
                 
      for (i=0;i < datacount; i++)
      {

         if (dataset[i][2] == id)
          {   

             document.wlArrivalDtlSearchForm.elements["search_xlid"].options[document.wlArrivalDtlSearchForm.elements["search_xlid"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.wlArrivalDtlSearchForm.elements["search_xlid"].options[document.wlArrivalDtlSearchForm.elements["search_xlid"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
      
    }
   xllist = document.wlArrivalDtlSearchForm.elements["search_xlid"];
}

function changeWl(sel){
   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
      
   
   if(id!=""){     
     
      for (i=0;i < datacount; i++){
          if (dataset[i][0] == id){
             document.wlArrivalDtlSearchForm.elements["search_dlid"].value=dataset[i][2];
          }
      }
    }
   
}



function changeAssetNo(obj){

    document.all.new_assetNo.value=obj.value;
    document.all.ifChanged.value="1";
    
}

function changeSerialNo(obj){
    
    document.all.new_serialNo.value=obj.value;
    document.all.ifChanged.value="1";
        
}

function changeWlid(obj){

    document.all.new_wlid.value=obj.value;
    document.all.ifChanged.value="1";
    
}

function changeEqpModel(obj){

    document.all.new_eqpModel.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeEqpSption(obj){

    document.all.new_eqpSption.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeIfAppendix(obj){

    document.all.new_ifAppendix.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeUpeqpNo(obj){
    
    document.all.new_upeqpNo.value=obj.value;
    if(document.all.new_upeqpNo.value==document.wlArrivalDtlSearchForm.elements["equipmentInfo.equipmentNo"].value){    
        document.all.hasConflict.value="1";
    }    
    document.all.ifChanged.value="1";
}

function changeDeptid(obj){

    document.all.new_deptid.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeMaintainerid(obj){

    document.all.new_maintainerid.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeUsageCategory(obj){

    document.all.new_usageCategory.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeEqpUsage(obj){

    document.all.new_eqpUsage.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeMemo(obj){

    document.all.new_memo.value=obj.value;
    document.all.ifChanged.value="1";
}

function doSave(){

if(document.all.hasConflict.value=="1"){
         alert("�ϼ��豸�뱾�豸��ͬ!");
         return;
}
     
//if(document.all.tempwlmc.value!=''&&document.all.ifChanged.value=='1')
//     changeWlid(document.all.wlid);

if(document.all.ifChanged.value=='0'){ 
    alert("��û���޸��κ��ֶΡ�");
    return;
}

if(document.all.ifChanged.value=='1'&&doCheckForm(wlArrivalDtlSearchForm)){
	wlArrivalDtlSearchForm.action="equipmentAction.do?method=update";
	wlArrivalDtlSearchForm.submit();
	}
}

function BchangeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.bs_xlid.length=1; //���ԭС���б�
   document.all.bs_wlid.length=1; //���ԭ�����б�        
   document.all.bwldw.value="";//��յ�λ��
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.all.bs_xlid.options[document.all.bs_xlid.length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.all.bs_xlid.options[document.all.bs_xlid.length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function BchangeWl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.bs_wlid.length=1; //���ԭ�����б�        
   document.all.bwldw.value="";//��յ�λ��
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.all.bs_wlid.options[document.all.bs_wlid.length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
       alert("wl is null");
       for (i=0;i < datacount2; i++)
      {
          document.all.bs_wlid.options[document.all.bs_wlid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function BchangeDW(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][0] == id)
          {   
             document.all.bwldw.value=dataset2[i][2];                
          }
      }
    else
       document.all.bwldw.value="";

}

function BchangeAssetNo(obj){
    alert(1);
    var shead=obj.value.substring(0,3)
    var first=parseInt(obj.value.substring(3));
    
    for (var i=0;i<idset.length;i++){          
        eval("document.all."+idset[i]+"new_assetNo.value='"+shead+first+"';"); 
        alert(eval("document.all."+idset[i]+"new_assetNo.value"));
        first=first+1;
    }
    document.all.ifChanged.value="1";
    
}

function BchangeSerialNo(obj){    
    
    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_serialNo.value=obj.value;");        
    
    document.all.ifChanged.value="1";
    
}

function BchangeWlid(obj){
    
    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_wlid.value=obj.value;");        
    document.all.ifChanged.value="1";
    
}

function BchangeEqpModel(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_eqpModel.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeEqpSption(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_eqpSption.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeIfAppendix(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_ifAppendix.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeUpeqpNo(obj){
    var ids=obj.value;
    var idarray=new Array(); 
    var i=0;     
    while(ids.length>0){//�����ŷָ����ַ�������������
       var id;
       var bpos=ids.indexOf(',');
       if(bpos!=-1){
           id=ids.substring(0,bpos);
           ids=ids.substring(bpos+1);
       }
       else{
           id=ids;
           ids=ids.substring(ids.length);
       }
       idarray[i]=id;       
       i++;
    }
    if(idarray.length>1){
      for (var i=0;i<idset.length;i++){          
        eval("document.all."+idset[i]+"new_upeqpNo.value=idarray[i];"); 
        if(eval("document.all."+idset[i]+"new_upeqpNo.value==document.all.equipmentNo_"+idset[i]+".value")){
             document.all.hasConflict.value="1";
        }     
      } 
    }
    else if(idarray.length==1){
        for (var i=0;i<idset.length;i++){          
        eval("document.all."+idset[i]+"new_upeqpNo.value=idarray[0];");  
        if(eval("document.all."+idset[i]+"new_upeqpNo.value==document.all.equipmentNo_"+idset[i]+".value")){
             document.all.hasConflict.value="1";
        }  
      }
    }
          
    document.all.ifChanged.value="1";
}

function BchangeDeptid(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_deptid.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeMaintainerid(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_maintainerid.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeUsageCategory(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_usageCategory.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeEqpUsage(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_eqpUsage.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeMemo(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_memo.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function doBatchSave(){

if(document.all.bupeqpNo.value!=''&&document.all.ifChanged.value=='1'){
     BchangeUpeqpNo(document.all.bupeqpNo);
     if(document.all.hasConflict.value=="1"){
         alert("�ϼ��豸�뱾�豸��ͬ!");
         return;
     }     
}
if(document.all.btempwlmc.value!=''&&document.all.ifChanged.value=='1')
     BchangeWlid(document.all.bwlid);
     
if(document.all.bmaintainerid.value!=''&&document.all.ifChanged.value=='1')
     BchangeMaintainerid(document.all.bmaintainerid);
     
if(document.all.busageCategory.value!=''&&document.all.ifChanged.value=='1')
     BchangeUsageCategory(document.all.busageCategory);

if(document.all.ifChanged.value=='1'){
	wlArrivalDtlSearchForm.action="equipmentAction.do?method=batchupdate";
	wlArrivalDtlSearchForm.submit();
	}
else{
    alert("��û���޸��κ��ֶΡ�");
    return;
}
}

function DoBack(){   
   wlArrivalDtlSearchForm.action="equipmentAction.do?method=search4List&listNum='all'";
   wlArrivalDtlSearchForm.submit();
}
</script>