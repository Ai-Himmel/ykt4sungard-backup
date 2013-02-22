<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.web.util.Constants"%>
<html>
<head>
<title>上海复旦大学物料库存及仓储管理系统</title>
<meta http-equiv="Content-Type" content="text/html;">

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

<SCRIPT language=javascript>

setTimeout('doInit()',30);
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
function add(){
if(wlArrivalBillForm.elements['wlArrivalId'].value!=''){
	wlArrivalBillForm.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=openNewWlArrivalDtlBill&flag=1";
	wlArrivalBillForm.submit();
	}else{
	alert('请先保存主单！！');
	}
}

function deletePurDtl(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][6].value");
           if(t!='<%=Constants.notSubmitID%>'){
               alert("被选中的到货明细已经提交，不能删除。请重新选择！！！");
              return false;
           }
    	ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&flag=1";
		ec.submit();
    }else{
        for(i=0;i<ec.elements["itemList"].length;i++){
       	if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       	}
       	}
       	if(counte==1){
       	
      for(var i=0;i<document.forms[1]['itemList'].length;i++){
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");             
           if(t!='<%=Constants.notSubmitID%>'){
               alert("被选中的到货明细已经提交，不能删除。请重新选择！！！");
              return false;
           }
    	}
	  }
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&flag=1";
			ec.submit();
   		}else if(counte>1){
   		
   	  for(var i=0;i<document.forms[1]['itemList'].length;i++){
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");
          
           if(t!='<%=Constants.notSubmitID%>'){
               alert("被选中的到货明细已经提交，不能删除。请重新选择！！！");
              return false;
           }
    	}
	  }
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&flag=1";
			ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要删除的明细记录');
   	 	}
   	 	
    }
    }else{
    	alert('当前无明细记录！！');
    }
}
function doUpdateDtl(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){       

           var t = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][6].value");           
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.noCheckID%>'){
               alert("被选中的到货明细已经在审批或者已经通过审批，不能被修改。请重新选择！！！");
              return false;
           }
    	
    	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&flag=2";
     	ec.submit();

    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
      for(var i=0;i<document.forms[1]['itemList'].length;i++){  
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");             
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.notPassID%>'){
              alert("被选中的到货明细已经在审批或者已经通过审批，不能被修改。请重新选择！！！");
              return false;
           }
    	}
	  } 
    	    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&flag=2";
     		ec.submit();
   		}else if(counte>1){
   		
   	  for(var i=0;i<document.forms[1]['itemList'].length;i++){
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");          
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.noCheckID%>'){
              alert("被选中的到货明细中至少有一条已经在审批或者已经通过审批，不能被修改。请重新选择！！！");
              return false;
           }
    	}
	  } 
    		ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlsInfo4Reg&wlArrivalId=null&flag=2";
     		ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要修改的明细记录');
   	 	}
    }
    }else{
    	alert('当前无明细记录！！');
    }
}
function save(){
    if(wlArrivalBillForm.elements["memo"].value.length<=300){
    	wlArrivalBillForm.action = "<c:url value = "/lf/wlArrivalBillAction.do"/>?method=saveWlArrivalInfo";
		wlArrivalBillForm.submit();
	}else{
	alert('备注输入过长,请将长度限制在300字符以内!!!');
	}
}
function modify(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){       

           var t = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][6].value");
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.noCheckID%>'){
               alert("被选中的到货明细已经在审批或者已经通过审批，不能被修改。请重新选择！！！");
              return false;
           }
    	
    	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     	ec.submit();

    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
      for(var i=0;i<document.forms[1]['itemList'].length;i++){  
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");      
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.notPassID%>'){
              alert("被选中的到货明细已经在审批或者已经通过审批，不能被修改。请重新选择！！！");
              return false;
           }
    	}
	  } 
    	    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     		ec.submit();
   		}else if(counte>1){
   		
   	  for(var i=0;i<document.forms[1]['itemList'].length;i++){
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");
           if(t!='<%=Constants.notSubmitID%>'&&t!='<%=Constants.noCheckID%>'){
              alert("被选中的到货明细中至少有一条已经在审批或者已经通过审批，不能被修改。请重新选择！！！");
              return false;
           }
    	}
	  } 
    		ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlsInfo4Reg&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     		ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要修改的明细记录');
   	 	}
    }
    }else{
    	alert('当前无明细记录！！');
    }
}
function rz(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){                               
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=account&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=account&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
   		}else if(counte>1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=account&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要修改的明细记录');
   	 	}
    }   
     }else{
    	alert('当前无明细记录！！');
    }
}
function unrz(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){                               
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=unaccount&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=unaccount&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
   		}else if(counte>1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=unaccount&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要修改的明细记录');
   	 	}
    }
 }else{
    	alert('当前无明细记录！！');
    }
}
function fpdq(){
    var i = 0;
    var counte = 0;
     if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){                               
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=receiptavl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=receiptavl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
   		}else if(counte>1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=receiptavl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要修改的明细记录');
   	 	}
    }
    
 }else{
    	alert('当前无明细记录！！');
    }
}
function unfpdq(){
    var i = 0;
    var counte = 0;
         if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){                               
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=unreceiptavl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=unreceiptavl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
   		}else if(counte>1){
 	ec.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=unreceiptavl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要修改的明细记录');
   	 	}
    }
    
 }else{
    	alert('当前无明细记录！！');
    }
}
function moduleAdd(){
if(wlArrivalBillForm.elements['wlArrivalId'].value!=''){
 	wlArrivalBillForm.action = "<c:url value="/lf/PurDtlAction4Search.do"/>?method=load4PurDtlList";
	wlArrivalBillForm.submit();
	}else{
	alert('请先保存主单!!!');
	}
}
function back(){
 	wlArrivalBillForm.action = "<c:url value="/lf/wlArrivalAction.do"/>?method=loadWlArrivalList4RegSearch";
	wlArrivalBillForm.submit();
}
function DoView(id){
    wlArrivalBillForm.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Reg&wlArrivalDtlId="+id;
	wlArrivalBillForm.submit();
}
function DoView2(id){
    if(confirm("确定已经填写到货明细？")){
    wlArrivalBillForm.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Reg&wlArrivalDtlId="+id;
	wlArrivalBillForm.submit();
	}
}
function DoView1(id){
    window.open("wlArrivalDtlAction.do?method=loadWlArrivalDtlInfo4Search&tag=1&wlArrivalDtlId="+id,"detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}
function submit(){
  var sflag = 0;
  if(ec.elements["itemList"]!=undefined){
  if(document.all.itemList.checked==true){
  	//提交之前 先对提交的明细记录做检验，只要有一条记录不符合提交条件 停止全部的提交动作
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][0].value");
           var k = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][1].value");
           var g = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][2].value");
           var h = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][3].value");
           var n = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][6].value");
           if(t!=k||t!=g||k!=g||(n!='<%=Constants.notSubmitID%>'&&n!='<%=Constants.notPassID%>')){
              alert("所选择明细中，有至少一条不满足提交条件，请重新选择！！！");
              return false;
           }
	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=submitWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
  }else{
          for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
         	//提交之前 先对提交的明细记录做检验，只要有一条记录不符合提交条件 停止全部的提交动作
    for(var i=0;i<document.forms[1]['itemList'].length;i++){
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][0].value");
           var k = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][1].value");
           var g = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][2].value");
           var h = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][3].value");
           var n = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");
           if(t!=k||t!=g||k!=g||(n!='<%=Constants.notSubmitID%>'&&n!='<%=Constants.notPassID%>')){
              alert("所选择明细中，有至少一条不能被提交，请重新选择！！！");
              return false;
           }
    	}
	}
	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=submitWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
          }else if(sflag<1){
          	  alert("请选择要提交的到货单！");
          }else{
          	//提交之前 先对提交的明细记录做检验，只要有一条记录不符合提交条件 停止全部的提交动作
    for(var i=0;i<document.forms[1]['itemList'].length;i++){
		if(document.forms[1]['itemList'][i].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][0].value");
           var k = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][1].value");
           var g = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][2].value");
           var h = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][3].value");
           var n = eval("document.forms[0]['"+document.forms[1]['itemList'][i].value+"'][6].value");
           
           if(t!=k||t!=g||k!=g||(n!='<%=Constants.notSubmitID%>'&&n!='<%=Constants.notPassID%>')){
              alert("所选择明细中，有至少一条不能被提交，请重新选择！！！");
              return false;
           }
    	}
	}
	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=submitWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
	ec.submit();
          } 
  }
  }else{
  	alert('当前无明细记录！！');
  }
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
       alert("当前无记录！");
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
       alert("当前无记录！");
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
       alert("当前无记录！");
  }
  

}
</SCRIPT>

</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
     
<br>
<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
  <tr>
    <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top" colspan="2"><table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">到货登记</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td height="40" align="center" valign="top" colspan="2"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
 <html:form action="/lf/wlArrivalBillAction" method="post">
 <jodd:form bean="request">
            <input type="hidden" name="ec_i" />
            <input type="hidden" name="ec_p" />
            <input type="hidden" name="ec_crd" />
            <input type="hidden" name="search_wlArrivalId" />
            <input type="hidden" name="search_regPName" />
            <input type="hidden" name="search_regTimeStart" />     
            <input type="hidden" name="search_regTimeEnd" />
</jodd:form>
          <tbody>
            <tr align="center" valign=center>
              <td width="13%" align="left" valign="middle" class="tableHeader2" >到货单号</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <html:hidden property="wlArrivalId" styleClass="input_box" />
              <bean:write name="wlArrivalBillForm" property="wlArrivalId"/>
              </td>
              
				<td width="13%" align="left" valign="middle" class="tableHeader2" >登记人</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalBillForm" property="regPName"/>
              <html:hidden property="regUName" styleClass="input_box" />
              </td>
            </tr>
            <tr align="center" valign=center>
            
              
              
              <td width="13%" align="left" valign="middle" class="tableHeader2" >部门</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
                <html:hidden property="deptCode" styleClass=""/>
                <bean:write name="wlArrivalBillForm" property="deptName"/>
				</td>

              <td width="13%" align="left" valign="middle" class="tableHeader2" >登记日期</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                  <tr>
                    <td>
                    <bean:write name="wlArrivalBillForm" property="regDate"/>
                    <html:hidden property="regDate" styleClass="input_box"/></td>
                    <td width="25" align="right" valign="middle" ></td>
                  </tr>
              </table></td>
            </tr>
            <tr align="center" valign=center>
              <td width="13%" align="left" valign="middle" class="tableHeader2" >备注</td>
              <td width="87%" colspan="3" align="left" valign="middle" class="tableHeader3" >
				<html:textarea property="memo" styleClass="" rows="3" cols="100"/></td>
              </tr>
          </tbody>
        </table>        </td>
      </tr>
            		<logic:present name="wlArrivalDtlList" scope="request">
						<logic:iterate name="wlArrivalDtlList" id="wlArrivalDtl" type="java.util.Map">
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="arrivalNum"/>"/>
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="alledTNum"/>"/>
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="waitNum"/>"/>
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="unincertNum"/>"/>
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="ifaccount"/>"/>
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="ifreceiptavl"/>"/>
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="stateID"/>"/>
							<input type="hidden" id="<bean:write name="wlArrivalDtl" property="wlArrivalDtlId"/>" value="<bean:write name="wlArrivalDtl" property="mtlSource"/>"/>
							
						</logic:iterate>
					</logic:present>
      </html:form>
      <tr>
        <td height="20" align="right" valign="middle" class="tdborder02" colspan="2">
        	<input name="Submit" type="button" class="button_nor" value="保 存" onClick="save()">
        </td>
      </tr>
      
      <tr>
        <td width="30%" height="25" align="left" valign="top"><table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">到货单明细</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td><td width="70%" align="right"></td>
      </tr>

      <tr>
        <td height="20" align="center" valign="middle" colspan="2">
        <ec:table items="wlArrivalDtlList" var="wlArrivalDtl" rowsDisplayed="10" action="wlArrivalBillAction.do?method=loadWlArrivalInfo4Reg" >	
				<ec:exportXls fileName="wlArrivalDtlList.xls" tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="50" headerStyle="text-align:center" style="text-align: center">
						<input type="checkbox" name="itemList" value="${wlArrivalDtl.wlArrivalDtlId}" style="border:0px"/>
					</ec:column>
					<ec:column property="wlmc" title="物料名称" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" >
					    <c:choose>
											<c:when test="${wlArrivalDtl.state=='未提交'}">
											 <a href="javascript:DoView1('${wlArrivalDtl.wlArrivalDtlId}')">${wlArrivalDtl.wlmc}</a>
											</c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrivalDtl.state=='已提交'}">
											 <a href="javascript:DoView1('${wlArrivalDtl.wlArrivalDtlId}')"><font color="black">${wlArrivalDtl.wlmc}</font></a>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrivalDtl.state=='审批通过'}">
											<a href="javascript:DoView1('${wlArrivalDtl.wlArrivalDtlId}')"><font color="green">${wlArrivalDtl.wlmc}</font></a>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<a href="javascript:DoView1('${wlArrivalDtl.wlArrivalDtlId}')"><font color="red">${wlArrivalDtl.wlmc}</font></a>
										    </c:when>
				                            </c:choose>
					</ec:column>    
					<ec:column property="arrivalNum" title="到货数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					>
					<c:choose>
										<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.arrivalNum}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.arrivalNum}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.arrivalNum}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.arrivalNum}</font>
										</c:when>
				                        </c:choose>
				                        </ec:column>
					<ec:column property="alledTNum" title="已安置货物数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
										<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.alledTNum}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.alledTNum}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.alledTNum}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.alledTNum}</font>
										</c:when>
				                        </c:choose>
				                        </ec:column>
					<ec:column property="waitNum" title="已接收安置货物数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
										<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.waitNum}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.waitNum}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.waitNum}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.waitNum}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="ifaccount" title="是否已入帐" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
										<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.ifaccount}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.ifaccount}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.ifaccount}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.ifaccount}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="ifreceiptavl" title="发票是否到齐" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
					<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.ifreceiptavl}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.ifreceiptavl}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.ifreceiptavl}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.ifreceiptavl}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="providerName" title="供应商" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					>
					<c:choose>
					<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.providerName}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.providerName}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.providerName}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.providerName}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="producterName" title="生产商" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					>
					<c:choose>
					<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.producterName}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.producterName}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.producterName}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.producterName}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="state" title="明细状态" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
					<c:when test="${wlArrivalDtl.state=='未提交'}">
											${wlArrivalDtl.state}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<font color="black">${wlArrivalDtl.state}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<font color="green">${wlArrivalDtl.state}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red">${wlArrivalDtl.state}</font>
										</c:when>
				                        </c:choose>
					
					</ec:column>
					<ec:column property="producerName" title="安置情况" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
					<c:when test="${wlArrivalDtl.state=='未提交'}">
											<c:if test="${wlArrivalDtl.arrivalNum>wlArrivalDtl.alledTNum&&wlArrivalDtl.alledTNum>0}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')">安置中</a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrivalDtl.wlArrivalDtlId}')">未安置</a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==wlArrivalDtl.arrivalNum}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')">安置完成</a>
					</c:if>
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrivalDtl.state=='已提交'}">
											<c:if test="${wlArrivalDtl.arrivalNum>wlArrivalDtl.alledTNum&&wlArrivalDtl.alledTNum>0}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')"><font color="black">安置中</font></a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrivalDtl.wlArrivalDtlId}')"><font color="black">未安置</font></a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==wlArrivalDtl.arrivalNum}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')"><font color="black">安置完成</font></a>
					</c:if>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批通过'}">
											<c:if test="${wlArrivalDtl.arrivalNum>wlArrivalDtl.alledTNum&&wlArrivalDtl.alledTNum>0}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')"><font color="green">安置中</font></a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrivalDtl.wlArrivalDtlId}')"><font color="green">未安置</font></a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==wlArrivalDtl.arrivalNum}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')"><font color="green">安置完成</font></a>
					</c:if>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrivalDtl.state=='审批不通过'}">
											<font color="red"><c:if test="${wlArrivalDtl.arrivalNum>wlArrivalDtl.alledTNum&&wlArrivalDtl.alledTNum>0}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')"><font color="red">安置中</font></a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrivalDtl.wlArrivalDtlId}')"><font color="red">未安置</font></a>
					</c:if>
					<c:if test="${wlArrivalDtl.alledTNum==wlArrivalDtl.arrivalNum}">
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')"><font color="red">安置完成</font></a>
					</c:if></font>
										</c:when>
				                        </c:choose>		
					</ec:column>

				</ec:row>
			</ec:table></td>
      </tr>

        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()" ><input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()" ><input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()" >
        		</td>
        <td height="40" align="right" valign="middle" colspan="2">
          <input name="Submit36" type="button" class="button_nor" value="新增明细" onClick="add()">
          <input name="Submit3" type="button" class="button_nor" value="修改明细" onClick="doUpdateDtl()">
		  <input name="Submit33" type="button" class="button_nor" value="删除明细" onClick="deletePurDtl()">
		  <input name="Submit32" type="button" class="button_nor" value="采购明细" onClick="moduleAdd()">
		  <input name="Submit35" type="button" class="button_nor" value="提交明细" onClick="submit()">
		  <input name="Submit31" type="button" class="button_nor" value="返 回" onClick="back()"></td>
</tr>

        	<tr>
         <td height="40" align="right" valign="middle" colspan="2">
                    </td>
                    </tr>
    </table></td></tr>

</table>
</body>
</html>
