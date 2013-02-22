<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>

<html>
<head>
<title>上海复旦大学物料库存及仓储管理系统</title>
<meta http-equiv="Content-Type" content="text/html;">

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
<SCRIPT language=javascript>
function back(){
    wlArrivalDtlBillForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=loadWlArrivalDtlList4Check";
	wlArrivalDtlBillForm.submit();
}

</SCRIPT>

</head>
<body  bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<br>
<html:form action="/lf/wlArrivalDtlAction.do" method="post">
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
<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
  <tr>
    <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top"><table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">到货明细单</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
      </tr>
      <tr>
        <td height="40" align="center" valign="top"><table 
        width=99% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
			<html:hidden property="wlArrivalId" />
			<html:hidden property="wlArrivalDtlId" />
			<html:hidden property="purDtlId" />
            <input type="hidden" name="ifChanged" value="0">
            <tr>
             <td width="13%" align="right" valign="middle" class="tableHeader2" >物料名称</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3">
                <bean:write name="wlArrivalDtlBillForm" property="wlmc"/>
                
			</td>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >物料规格</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="wlsption"/>
              </td>
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >物料型号</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="wlmodel"/>
              </td>
             </tr>
            <tr align="center" valign=center>
            <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >用途大类</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3">
                  <bean:write name="wlArrivalDtlBillForm" property="usageCategory"/>
              </td>
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >物料单位</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3"> 
              <bean:write name="wlArrivalDtlBillForm" property="wldw"/>
              </td>
			  <td width="13%" align="right" valign="middle" class="tableHeader2" >是否附件</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="ifAppendixName"/>
              	
              </td>
              <tr align="center" valign=center>
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >用途说明</td>
              <td width="20%" align="left" valign="middle" class="tableHeader4" colspan="6">
              <bean:write name="wlArrivalDtlBillForm" property="usage"/>
              </td>
              
              </tr>
            <tr align="center" valign=center>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >采购经办人</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="proPersonId"/>
              
              </td>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >采购单价</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="procurePrice"/>
              &nbsp;元</td>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >采购日期</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
                <bean:write name="wlArrivalDtlBillForm" property="procureDate"/>
               </td>
            </tr>
            <tr align="center" valign=center>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >物料来源</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="mtlSource"/>            
              <td width="13%" align="right" valign="middle" class="tableHeader2" >到货数量</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="arrivalNum"/>
              </td>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >到货日期</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="arrivalDate"/>
              </td>
            </tr>

            
            <tr align="center" valign=center>
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >生产厂家</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" ><table><tr><td>
              <bean:write name="wlArrivalDtlBillForm" property="producterId"/>
              </td>
             </tr></table></td>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >供应商</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3"><table><tr><td>
              <bean:write name="wlArrivalDtlBillForm" property="providerId"/>
              </td>
             </tr></table></td>
             <td width="13%" align="right" valign="middle" class="tableHeader2" >合同号码</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="contractNo"/>
              </td>
            </tr>
            
            <tr align="center" valign=center>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >发票号码</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="receiptNo"/>
             </td>
  
              <td width="13%" align="right" valign="middle" class="tableHeader2" >经费来源</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
               <bean:write name="wlArrivalDtlBillForm" property="fundSource"/>
             </td>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >入帐日期</td>
			  <td width="20%" align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td><bean:write name="wlArrivalDtlBillForm" property="accountDate"/></td>
                  <td width="25" align="right" ></td>
                </tr>
              </table></td>
            </tr>
            
                        <tr align="center" valign=center>
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >维修商</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" ><table><tr><td>
              <bean:write name="wlArrivalDtlBillForm" property="maintainerid"/>
              
              </td></tr></table></td>                                        
  
              <td width="13%" align="right" valign="middle" class="tableHeader2" >保修期</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="warrantyPeriod"/>
              &nbsp;年</td>
              <td width="13%" align="right" valign="middle" class="tableHeader2" >到发票日期</td>
			  <td width="20%" align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td><bean:write name="wlArrivalDtlBillForm" property="receiptDate"/></td>
                  <td width="25" align="right" ></td>
                </tr>
              </table></td>
            </tr>
            
            <tr align="center" valign=center>	
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >到货经办人</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalDtlBillForm" property="arrPersonId"/>
              
               </td>
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >保管人</td>
              <td width="20%" colspan="3" align="left" valign="middle" class="tableHeader3" >             
              <table><tr><td>
              <bean:write name="wlArrivalDtlBillForm" property="acpid"/>
              
              </td></tr></table></td> 									    
              </tr>
            <tr align="center" valign=center>
              <td width="13%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >备注</td>
              <td width="20%" colspan="5" align="left" valign="middle" class="tableHeader4" >
              <bean:write name="wlArrivalDtlBillForm" property="DtlMemo"/>
              </td>
              </tr>
          </tbody>
        </table>        </td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle">
<input name="Submit2" type="button" class="button_nor" value="返 回" onClick="back()">
</td>
      </tr>
      <tr>
        <td height="40" align="left" valign="top">&nbsp;</td>
      </tr>
      
      
    </table></td>
  </tr>
</table>
</html:form>
</body>
</html>
<script>
	var idcount=0;
    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("dxlist")!=null)
       resultset=(String[][])request.getAttribute("dxlist");//读取大小类对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应小类id、小类名称、大类id
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
       resultset2=(String[][])request.getAttribute("xmlist");//读取小类、名称对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//产生javascript二维数组，对应名称id、物料名称、物料单位、小类id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<script type="text/javascript">

function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;

   document.purDtlBillForm.elements["xlid"].length=1; //清空原小类列表

   document.purDtlBillForm.elements["wlid"].length=1; //清空原名称列表      

   document.purDtlBillForm.elements["wldw"].value="";//清空单位框


   if(id!="")
                 
      for (i=0;i < datacount; i++)
      {

         if (dataset[i][2] == id)
          {   

             document.purDtlBillForm.elements["xlid"].options[document.purDtlBillForm.elements["xlid"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.purDtlBillForm.elements["xlid"].options[document.purDtlBillForm.elements["xlid"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   xllist = document.purDtlBillForm.elements["xlid"];

}

function changeWl(sel){
   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   document.purDtlBillForm.elements["wlid"].length=1; //清空原名称列表        
   document.purDtlBillForm.elements["wldw"].value="";//清空单位框
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.purDtlBillForm.elements["wlid"].options[document.purDtlBillForm.elements["wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
       
       for (i=0;i < datacount2; i++)
      {
          document.purDtlBillForm.elements["wlid"].options[document.purDtlBillForm.elements["wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   
    wllist = document.purDtlBillForm.elements["wlid"];
}

function changeDW(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][0] == id)
          {   
             document.purDtlBillForm.elements["wldw"].value=dataset2[i][2];                
          }
      }
    else
       document.purDtlBillForm.elements["wldw"].value="";

}

function changeAssetNo(obj){

    document.all.new_assetNo.value=obj.value;
    document.all.ifChanged.value="1";
    
}
function changeProducter(obj){

    document.all.producterId.value=obj.value;
    document.all.ifChanged.value="1";
}
function changeProvider(obj){

    document.all.providerId.value=obj.value;
    document.all.ifChanged.value="1";
}
function changeMaintainer(obj){

    document.all.maintainerid.value=obj.value;
    document.all.ifChanged.value="1";
}
function changeSerialNo(obj){
    
    document.all.new_serialNo.value=obj.value;
    document.all.ifChanged.value="1";
        
}

function changeAcpid(obj){
    document.all.acpid.value=obj.value;
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
    if(document.all.new_upeqpNo.value==document.purDtlBillForm.elements["equipmentInfo.equipmentNo"].value){    
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

    document.all.usageCategory.value=obj.value;
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
         alert("上级设备与本设备相同!");
         return;
}
     
//if(document.all.tempwlmc.value!=''&&document.all.ifChanged.value=='1')
//     changeWlid(document.all.wlid);

if(document.all.ifChanged.value=='0'){ 
    alert("您没有修改任何字段。");
    return;
}

if(document.all.ifChanged.value=='1'&&doCheckForm(purDtlBillForm)){
	purDtlBillForm.action="equipmentAction.do?method=update";
	purDtlBillForm.submit();
	}
}

function BchangeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.bs_xlid.length=1; //清空原小类列表
   document.all.bwlid.length=1; //清空原名称列表        
   document.all.bwldw.value="";//清空单位框
   
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
        
   document.all.bwlid.length=1; //清空原名称列表        
   document.all.bwldw.value="";//清空单位框
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.all.bwlid.options[document.all.bwlid.length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
       alert("wl is null");
       for (i=0;i < datacount2; i++)
      {
          document.all.bwlid.options[document.all.bwlid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
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
    while(ids.length>0){//将逗号分隔的字符串解析成数组
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
         alert("上级设备与本设备相同!");
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
	purDtlBillForm.action="equipmentAction.do?method=batchupdate";
	purDtlBillForm.submit();
	}
else{
    alert("您没有修改任何字段。");
    return;
}
}

function DoBack(){   
   purDtlBillForm.action="equipmentAction.do?method=search4List&listNum='all'";
   purDtlBillForm.submit();
}
</script>