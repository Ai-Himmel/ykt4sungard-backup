<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
<head>
<title>无标题文档</title>

<meta http-equiv="Content-Type" content="text/html;">
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

<SCRIPT language=javascript>
 var num = 0;
function add(){
  var sflag = 0;
  if(document.all.itemListModel.checked==true){
    ec.action = "<c:url value="/lf/wlArrivalBillAction.do"/>?method=addWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
  }else{
          for(var i=0;i<document.all.itemListModel.length;i++){
              if(document.all.itemListModel[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
    ec.action = "<c:url value="/lf/wlArrivalBillAction.do"/>?method=addWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
          }else if(sflag<1){
          	  alert("请选择采购明细！");
          }else{
    ec.action = "<c:url value="/lf/wlArrivalBillAction.do"/>?method=addWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
          } 
  }
}
function show(){		
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"].checked==true){
    	    ec.action = "<c:url value = "/lf/purDtlAction.do"/>?method=load4PurDtlInfo4Show&tag=2";
     		ec.submit();
    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
 			ec.action = "<c:url value = "/lf/purDtlAction.do"/>?method=load4PurDtlInfo4Show&tag=2";
     		ec.submit();
   		}else if(counte>1){
    		alert('不能同时查看多条明细');
    	}else if(counte<1){
      	  	alert('请选择要修改的明细记录');
   	 	}
    }		
}
function search(){
    purDtlSearchForm.action = "<c:url value="/lf/PurDtlAction4Search.do"/>?method=load4PurDtlList4TJ";
	purDtlSearchForm.submit();
}
function back(){
     if(document.all.tag.value=='1'){
        wlArrivalDtlSearchForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=tj4Scs";
	 	wlArrivalDtlSearchForm.submit();
	 }else{
	    wlArrivalDtlSearchForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=tj4Gys";
	    wlArrivalDtlSearchForm.submit();
	 }
}
function DoView(id){
    wlArrivalDtlSearchForm.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4TJ&wlArrivalDtlId="+id;
	wlArrivalDtlSearchForm.submit();
}
function DoView1(id){
    window.open("wlArrivalDtlAction.do?method=loadWlArrivalDtlInfo4Search&tag=1&wlArrivalDtlId="+id,"detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}
</SCRIPT>
<script>

var idcount=0;
idset=new Array();

<%
   int idsCount=0;
   String[] idsSet=null;
   if(request.getAttribute("ids")!=null)
       idsSet=(String[])request.getAttribute("ids");//读取设备号数组
   
   if(idsSet!=null){
     for(idsCount=0;idsCount<idsSet.length;idsCount++)
     {
     %>
      idset[<%=idsCount%>] = new Array("<%=idsSet[idsCount]%>");//产生javascript数组，对应小类id、小类名称、大类id
     <%
     }
   }
   %>
   idcount=<%=idsCount%>;
</script>
</head>

<body  bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<br>
<table width="99%" align="left" border="0" cellpadding="0" cellspacing="0" style="padding-left:10px">
  <html:form action="/lf/wlArrivalDtlAction4Search" method="post">
  <jodd:form bean="request">
            <input type="hidden" name="ec_i" />
            <input type="hidden" name="ec_p" />
            <input type="hidden" name="ec_crd" />
            <input type="hidden" name="dlid" />
            <input type="hidden" name="xlid" />
            <input type="hidden" name="wlid" /> 
            <input type="hidden" name="scsid" />
            <input type="hidden" name="gysid" /> 
            <input type="hidden" name="search_dlid" />
            <input type="hidden" name="search_xlid" />
            <input type="hidden" name="search_wlid" />     
            <input type="hidden" name="search_wlxh" />
            <input type="hidden" name="search_ifAppendix" />
            <input type="hidden" name="search_dtlState" />
            <input type="hidden" name="search_producterId" />     
            <input type="hidden" name="search_providerId" />	
</jodd:form>
<input type="hidden" name="tag" value="<%=request.getAttribute("tag")%>"/>
  <tr>
    <td height="25" align="left" valign="top">
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top">
    <table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
    </table></td>
  </tr>
  <input type="hidden" name="wlArrivalId" value="<%=request.getAttribute("wlArrivalId")%>"/>
  <tr>
    <td height="40" align="center" valign="top">
    <table 
        width="100%" border="1" align="center" 
      cellpadding="1" cellspacing="0" bordercolor="#FFFFFF"       id="submenu1">
  <tr>
    <td height="25" align="left" valign="top">
    <table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td width="10" bgcolor="#0066CA">&nbsp;</td>
        <td width="99" bgcolor="#0066CA" class="mediumwhite">到货统计明细</td>
        <td width="40"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20" /></td>
      </tr>
    </table></td>
  </tr>
  </html:form>
  						<tr>
							<td height="35" align="center" valign="middle" class="mediumblack">
								到货统计明细列表
							</td>
						</tr>
   <tr>
        <td height="20" align="center" valign="middle" colspan="2">
        <ec:table items="wlArrivalDtlList" var="wlArrivalDtl" rowsDisplayed="10" action="wlArrivalDtlAction4Search.do?method=loadList4TJ" >	
				<ec:exportXls fileName="wlArrivalDtlList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="tempwlmc" title="物料名称" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" >
					    <a href="javascript:DoView1('${wlArrivalDtl.wlArrvialDtlId}')">${wlArrivalDtl.tempwlmc}</a>
					</ec:column>    
					<ec:column property="arrivalNum" title="到货数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="alledTNum" title="已安置货物数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="waitNum" title="已接收安置货物数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="ifaccount" title="是否已入帐" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="ifreceiptavl" title="发票是否到齐" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="providerName" title="供应商" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="producterName" title="生产商" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="dtlState" title="明细状态" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="recordDate" title="到货时间" 
					    headerStyle="text-align:center" 
					    style="text-align: center" 
					    cell="date" 
					    format="yyyy-MM-dd" 
					    width="80" 
					/>
					<ec:column property="producerName" title="安置情况" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<a href="javascript:DoView('${wlArrivalDtl.wlArrvialDtlId}')">安置情况一览</a>
					</ec:column>

				</ec:row>
			</ec:table></td>
      </tr>
            <tr>
        <td height="40" align="right" valign="middle" colspan="2">
          <input name="Submit31" type="button" class="button_nor" value="返 回" onClick="back()"></td>
      </tr>
</table>

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
   

   document.purDtlSearchForm.elements["search_xlid"].length=1; //清空原小类列表

   document.purDtlSearchForm.elements["search_wlid"].length=1; //清空原名称列表      


   if(id!="")
                 
      for (i=0;i < datacount; i++)
      {

         if (dataset[i][2] == id)
          {   

             document.purDtlSearchForm.elements["search_xlid"].options[document.purDtlSearchForm.elements["search_xlid"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.purDtlSearchForm.elements["search_xlid"].options[document.purDtlSearchForm.elements["search_xlid"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   xllist = document.purDtlSearchForm.elements["search_xlid"];

}

function changeWl(sel){
   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   document.purDtlSearchForm.elements["search_wlid"].length=1; //清空原名称列表        
   
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.purDtlSearchForm.elements["search_wlid"].options[document.purDtlSearchForm.elements["search_wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{
       
       for (i=0;i < datacount2; i++)
      {
          document.purDtlSearchForm.elements["search_wlid"].options[document.purDtlSearchForm.elements["search_wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   wllist = document.purDtlSearchForm.elements["search_wlid"];

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
    if(document.all.new_upeqpNo.value==document.purDtlSearchForm.elements["equipmentInfo.equipmentNo"].value){    
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
         alert("上级设备与本设备相同!");
         return;
}
     
//if(document.all.tempwlmc.value!=''&&document.all.ifChanged.value=='1')
//     changeWlid(document.all.wlid);

if(document.all.ifChanged.value=='0'){ 
    alert("您没有修改任何字段。");
    return;
}

if(document.all.ifChanged.value=='1'&&doCheckForm(purDtlSearchForm)){
	purDtlSearchForm.action="equipmentAction.do?method=update";
	purDtlSearchForm.submit();
	}
}

function BchangeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.bs_xlid.length=1; //清空原小类列表
   document.all.bs_wlid.length=1; //清空原名称列表        
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
        
   document.all.bs_wlid.length=1; //清空原名称列表        
   document.all.bwldw.value="";//清空单位框
   
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
	purDtlSearchForm.action="equipmentAction.do?method=batchupdate";
	purDtlSearchForm.submit();
	}
else{
    alert("您没有修改任何字段。");
    return;
}
}

function DoBack(){   
   purDtlSearchForm.action="equipmentAction.do?method=search4List&listNum='all'";
   purDtlSearchForm.submit();
}
</script>
