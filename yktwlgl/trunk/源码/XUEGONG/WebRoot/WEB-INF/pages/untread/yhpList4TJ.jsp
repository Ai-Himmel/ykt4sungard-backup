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
<html:form action="/lf/yhpAction" method="post">
<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top"><table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">易耗品信息</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
        </tr>
      </html:form>
      
      <tr>
        <td height="35" align="center" valign="middle" class="mediumblack">易耗品列表</td>
      </tr>
      <jodd:form bean="request">      
      <tr>
        <td height="20" align="center" valign="middle">
         <ec:table items="showlist" var="yhpInfo" rowsDisplayed="10" action="equipmentAction.do?method=loadList4TJ" >
			
				<ec:exportXls fileName="yhpList.xls" tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="yhpid" title="易耗品批号" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					>
					<a href="javascript:DoView('${yhpInfo.yhpid}')">${yhpInfo.yhpid}</a>
					</ec:column>					
					<ec:column property="wlmc" title="品名" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="90" 
					/>					
					<ec:column property="deptName" title="资产所属" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="110" 
					/>
					<ec:column property="yhpSource" title="来源" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="40" 
					/>
					<ec:column property="yhpNum" title="进货数量" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="60" 
					/>
					<ec:column property="beginNo" title="起始编号"  
						headerStyle="text-align:center" 
						style="text-align: left"
						width="60" 
					/>
					<ec:column property="endNo" title="结束编号"  
						headerStyle="text-align:center" 
						style="text-align: left"
						width="60" 
					/>		
	<%if(request.getAttribute("ifLimit").equals("0")){%>
					<ec:column property="untreadNum" title="退货数量" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="60" />
	<% }%>	
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

setTimeout('init()',10);

function DoFind(){

    yhpsearchForm.action="equipmentAction.do?method=search4YHPList";
    yhpsearchForm.submit();

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
          	  alert("请选择易耗品信息！");
          }else{
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=addUntread";
	ec.submit();
          } 
  }
}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.yhpsearchForm.elements["search_louyu"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.yhpsearchForm.elements["search_louyu"].options[document.yhpsearchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.yhpsearchForm.elements["search_louyu"].options[document.yhpsearchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

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
              alert("请选择要修改的易耗品记录！");
              return;
          } 
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的易耗品记录！");
              return;        
        }
   }
   
   document.forms.ec.action="yhpAction.do?method=load4update";       
   document.forms.ec.submit();
   
  
  
}

function DoView(eno){

    window.open("../gyf/yhpAction.do?method=load4view&yhpNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function ChangeQueryMode(btn){

    if(btn.value=='高级查询'){
       document.yhpsearchForm.querymode.value="2";
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
       tr11.style.display='';
       tr12.style.display='';
       tr13.style.display='';
    }
    else if(btn.value=='简单查询'){
       document.yhpsearchForm.querymode.value="1";
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
       tr11.style.display='none';
       tr12.style.display='none';
       tr13.style.display='none';
    }

}

function DoClear(){

    document.yhpsearchForm.elements["search_bh"].value="";    
    document.yhpsearchForm.elements["search_wlmc"].value="";
    document.yhpsearchForm.elements["search_bNo"].value="";
    document.yhpsearchForm.elements["search_eNo"].value="";
    document.yhpsearchForm.elements["search_hth"].value="";
    document.yhpsearchForm.elements["search_sccj"].value="";
    document.yhpsearchForm.elements["search_sccj"].options[0].selected=true;
    
    document.yhpsearchForm.elements["search_ly"].value="";
    document.yhpsearchForm.elements["search_ly"].options[0].selected=true;    
    document.yhpsearchForm.elements["search_gys"].value="";
    document.yhpsearchForm.elements["search_gys"].options[0].selected=true;     
    document.yhpsearchForm.elements["search_dhh"].value="";
    document.yhpsearchForm.elements["search_ytdl"].value="";
    document.yhpsearchForm.elements["search_ytdl"].options[0].selected=true; 
    document.yhpsearchForm.elements["search_yhpNumc"].value="";
    document.yhpsearchForm.elements["search_yhpNumd"].value="";
    document.yhpsearchForm.elements["search_curNumc"].value="";
    document.yhpsearchForm.elements["search_curNumd"].value="";
    document.yhpsearchForm.elements["search_dhrqc"].value="";
    document.yhpsearchForm.elements["search_dhrqd"].value="";
    document.yhpsearchForm.elements["search_cgrqc"].value="";
    document.yhpsearchForm.elements["search_rzrqc"].value="";
    document.yhpsearchForm.elements["search_dfprqc"].value="";
    document.yhpsearchForm.elements["search_cgrqd"].value="";
    document.yhpsearchForm.elements["search_rzrqd"].value="";
    document.yhpsearchForm.elements["search_dfprqd"].value="";
    document.yhpsearchForm.elements["search_djc"].value="";
    document.yhpsearchForm.elements["search_djd"].value="";
    document.yhpsearchForm.elements["search_fphm"].value="";
    document.yhpsearchForm.elements["search_jfly"].value="";
    document.yhpsearchForm.elements["search_cgjbr"].value="";
    document.yhpsearchForm.elements["search_dhjbr"].value="";
    document.yhpsearchForm.elements["search_pfdx"].value="";
    document.yhpsearchForm.elements["search_pfdx"].options[0].selected=true;
    document.yhpsearchForm.elements["search_xq"].value="";
    document.yhpsearchForm.elements["search_xq"].options[0].selected=true;
    document.yhpsearchForm.elements["search_louyu"].value="";
    document.yhpsearchForm.elements["search_louyu"].options[0].selected=true;
    document.yhpsearchForm.elements["search_jfkf"].value="";
    
}

</SCRIPT>

