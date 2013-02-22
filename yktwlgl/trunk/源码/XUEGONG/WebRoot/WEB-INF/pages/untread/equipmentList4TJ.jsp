<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
<head>
<title>上海复旦大学物料库存及仓储管理系统</title>
<meta http-equiv="Content-Type" content="text/html;">

<%@ include file="/pages/components/calendar/calendar.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
<script>
function back(){
   var tag = '<%=request.getAttribute("tag")%>';
   if(tag=='0'){
	ec.action="<c:url value="/lf/untreadTJAction.do"/>?method=tj4TypeName";
	ec.submit();
   }else if(tag=='1'){
   	ec.action="<c:url value="/lf/untreadTJAction.do"/>?method=tj4Scs";
	ec.submit();
   }else{
   	ec.action="<c:url value="/lf/untreadTJAction.do"/>?method=tj4Gys";
	ec.submit();
   }
}
</script>
</head>
<body  bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<br>
<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
 
  <tr>
    <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top"><table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">设备信息</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td height="35" align="center" valign="middle" class="mediumblack">设备列表</td>
      </tr>
      <jodd:form bean="request">      
      <tr>
        <td height="20" align="center" valign="middle">
         <ec:table items="showlist" var="eqpJBInfo" rowsDisplayed="10" action="equipmentAction.do?method=loadList4TJ" >
			
				<ec:exportXls fileName="equipmentList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="equipmentNo" title="设备编号" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					>
					<a href="javascript:DoView('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a>
					</ec:column>
					<ec:column property="assetNo" title="资产号" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					/>
					<ec:column property="serialNo" title="序列号" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					/>
					<ec:column property="xlmc" title="小类" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					/>
					<ec:column property="wlmc" title="名称" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="70" 
					/>
					<ec:column property="eqpModel" title="型号"  
						headerStyle="text-align:center" 
						style="text-align: left"
						width="60" 
					/>
					<ec:column property="deptName" title="资产所属" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="110" 
					/>
					<ec:column property="eqpSource" title="来源" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="40" 
					/>
					<ec:column property="managerName" title="管理员" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="50" 
					/>
					<ec:column property="recordDate" title="退货时间" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    cell="date" 
					    format="yyyy-MM-dd" 
					    width="60" 
					/>
													
				</ec:row>
			</ec:table>
        </td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle">        
          <input name="Submit3" type="button" class="button_nor" value="返 回" onClick="back()">
        </td>
      </tr>
      </jodd:form>
    </table></td>
  </tr>
</table>
</body>
</html>

<script>

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
   if(request.getAttribute("ablist")!=null)
       resultset2=(String[][])request.getAttribute("ablist");//读取校区、楼宇对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>");//产生javascript二维数组，对应楼宇id、楼宇名称、校区id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>
function DoFind(){

    if(document.eqpsearchForm.elements["search_djc"]!=null&&document.eqpsearchForm.elements["search_djc"].value!=''&&isNaN(document.eqpsearchForm.elements["search_djc"].value)){
        alert("采购单价从必须填写数字！");
        return;
    }
    if(document.eqpsearchForm.elements["search_djd"]!=null&&document.eqpsearchForm.elements["search_djd"].value!=''&&isNaN(document.eqpsearchForm.elements["search_djd"].value)){
        alert("采购单价到必须填写数字！");
        return;
    }
    
    eqpsearchForm.action="equipmentAction.do?method=search4SBList";
    eqpsearchForm.submit();

}
function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpsearchForm.elements["search_wlxl"].length=1; //清空原小类列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.eqpsearchForm.elements["search_wlxl"].options[document.eqpsearchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.eqpsearchForm.elements["search_wlxl"].options[document.eqpsearchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpsearchForm.elements["search_louyu"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpsearchForm.elements["search_louyu"].options[document.eqpsearchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpsearchForm.elements["search_louyu"].options[document.eqpsearchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
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
       alert("当前无记录！");
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
       alert("当前无记录！");
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
       alert("当前无记录！");
  }
  

}

function DoUpdate(){
 
   var sflag=0;
   
   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择要修改的设备记录！");
              return;
          } 
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的设备记录！");
              return;        
        }
   }
   
   document.forms.ec.action="equipmentAction.do?method=load4update";       
   document.forms.ec.submit();
   
  
  
}

function DoView(eno){

    window.open("../gyf/equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function ChangeQueryMode(btn){

    if(btn.value=='高级查询'){
       document.eqpsearchForm.querymode.value="2";
       btn.value='简单查询';
       tr1.style.display='';
       tr2.style.display='';
       tr3.style.display='';
       tr4.style.display='';
       tr5.style.display='';
       tr6.style.display='';
       tr7.style.display='';
       tr8.style.display='';
       tr9.style.display='';
       tr10.style.display='';
    }
    else if(btn.value=='简单查询'){
       document.eqpsearchForm.querymode.value="1";
       btn.value='高级查询';
       tr1.style.display='none';
       tr2.style.display='none';
       tr3.style.display='none'; 
       tr4.style.display='none';
       tr5.style.display='none';
       tr6.style.display='none';
       tr7.style.display='none';
       tr8.style.display='none';
       tr9.style.display='none';
       tr10.style.display='none';
    }

}
function add(){
	  var sflag = 0;
  if(document.all.cbgroup.checked==true){
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=addUntread";
	ec.submit();
  }else{
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=addUntread";
	ec.submit();
          }else if(sflag<1){
          	  alert("请选择物料信息！");
          }else{
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=addUntread";
	ec.submit();
          } 
  }
}
function DoClear(){

    document.eqpsearchForm.elements["search_bh"].value="";
    document.eqpsearchForm.elements["search_zch"].value="";
    document.eqpsearchForm.elements["search_haszch"].value="";
    document.eqpsearchForm.elements["search_haszch"].options[0].selected=true;
    document.eqpsearchForm.elements["search_xlh"].value="";
    document.eqpsearchForm.elements["search_wldl"].value="";
    document.eqpsearchForm.elements["search_wldl"].options[0].selected=true;
    document.eqpsearchForm.elements["search_wlxl"].value="";
    document.eqpsearchForm.elements["search_wlxl"].options[0].selected=true;
    document.eqpsearchForm.elements["search_wlmc"].value="";
    document.eqpsearchForm.elements["search_xh"].value="";
    document.eqpsearchForm.elements["search_hth"].value="";
    document.eqpsearchForm.elements["search_sccj"].value="";
    document.eqpsearchForm.elements["search_sccj"].options[0].selected=true;
    
    document.eqpsearchForm.elements["search_ly"].value="";
    document.eqpsearchForm.elements["search_ly"].options[0].selected=true;
    document.eqpsearchForm.elements["search_fj"].value="";
    document.eqpsearchForm.elements["search_fj"].options[0].selected=true;
    document.eqpsearchForm.elements["search_sjssh"].value="";
    document.eqpsearchForm.elements["search_gly"].value="";
    document.eqpsearchForm.elements["search_gys"].value="";
    document.eqpsearchForm.elements["search_gys"].options[0].selected=true;
    document.eqpsearchForm.elements["search_wxs"].value="";
    document.eqpsearchForm.elements["search_wxs"].options[0].selected=true;    
    document.eqpsearchForm.elements["search_dhh"].value="";
    document.eqpsearchForm.elements["search_dhrqc"].value="";
    document.eqpsearchForm.elements["search_dhrqd"].value="";
    document.eqpsearchForm.elements["search_cgrqc"].value="";
    document.eqpsearchForm.elements["search_rzrqc"].value="";
    document.eqpsearchForm.elements["search_dfprqc"].value="";
    document.eqpsearchForm.elements["search_cgrqd"].value="";
    document.eqpsearchForm.elements["search_rzrqd"].value="";
    document.eqpsearchForm.elements["search_dfprqd"].value="";
    document.eqpsearchForm.elements["search_djc"].value="";
    document.eqpsearchForm.elements["search_djd"].value="";
    document.eqpsearchForm.elements["search_fphm"].value="";
    document.eqpsearchForm.elements["search_jfly"].value="";
    document.eqpsearchForm.elements["search_cgjbr"].value="";
    document.eqpsearchForm.elements["search_dhjbr"].value="";
    document.eqpsearchForm.elements["search_pfdx"].value="";
    document.eqpsearchForm.elements["search_pfdx"].options[0].selected=true;
    document.eqpsearchForm.elements["search_xq"].value="";
    document.eqpsearchForm.elements["search_xq"].options[0].selected=true;
    document.eqpsearchForm.elements["search_louyu"].value="";
    document.eqpsearchForm.elements["search_louyu"].options[0].selected=true;
    document.eqpsearchForm.elements["search_jfkf"].value="";
    document.eqpsearchForm.elements["search_jgbh"].value="";
    document.eqpsearchForm.elements["search_sbzt"].value="";
    document.eqpsearchForm.elements["search_sbzt"].options[0].selected=true;
    document.eqpsearchForm.elements["search_ipv4dz"].value="";
    document.eqpsearchForm.elements["search_fwqym1"].value="";
    document.eqpsearchForm.elements["search_sljhjip"].value="";
}

</SCRIPT>

