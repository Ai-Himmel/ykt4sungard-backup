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
function search(){
    wlArrivalDtlSearchForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=listWlArrivalDtlByState";
	wlArrivalDtlSearchForm.submit();
}
function add(){
if(wlArrivalDtlSearchForm.elements['wlArrivalId'].value!=''){
	wlArrivalDtlSearchForm.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=openNewWlArrivalDtlBill";
	wlArrivalDtlSearchForm.submit();
	}else{
	alert('请先保存主单！！');
	}
}

function deleteDtl(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"]!=undefined){
    if(ec.elements["itemList"].checked==true){
           var t = eval("document.forms[0]['"+document.forms[1]['itemList'].value+"'][6].value");
           if(t!='<%=Constants.notSubmitID%>'){
               alert("被选中的到货明细已经提交，不能删除。请重新选择！！！");
              return false;
           }
    	ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&tag=1";
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
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&tag=1";
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
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&tag=1";
			ec.submit();
    	}else if(counte<1){
      	  	alert('请选择要删除的明细记录');
   	 	}
   	 	
    }
    }else{
    	alert('当前无明细记录！！');
    }
}

function save(){
    if(wlArrivalDtlSearchForm.elements["memo"].value.length<=300){
    	wlArrivalDtlSearchForm.action = "<c:url value = "/lf/wlArrivalBillAction.do"/>?method=saveWlArrivalInfo";
		wlArrivalDtlSearchForm.submit();
	}else{
	alert('请先保存主单!!!');
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
    	
    	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Sy&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
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
    	    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Sy&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
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
    		ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlsInfo4Sy&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
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
if(wlArrivalDtlSearchForm.elements['wlArrivalId'].value!=''){
 	wlArrivalDtlSearchForm.action = "<c:url value="/lf/PurDtlAction4Search.do"/>?method=load4PurDtlList";
	wlArrivalDtlSearchForm.submit();
	}else{
	alert('请先保存主单!!!');
	}
}
function back(){
 	wlArrivalDtlSearchForm.action = "<c:url value="/lf/wlArrivalAction.do"/>?method=loadWlArrivalList4RegSearch";
	wlArrivalDtlSearchForm.submit();
}
function DoView(id){
    wlArrivalDtlSearchForm.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Sy&wlArrivalDtlId="+id;
	wlArrivalDtlSearchForm.submit();
}
function DoView3(id,id1){
    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Reg&wlArrivalDtlId="+id1+"&wlArrivalId="+id+"&flag=1";
	ec.submit();
}

function DoView2(id,id1){
    if(confirm("确定已经填写到货明细？")){
    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Reg&wlArrivalDtlId="+id1+"&wlArrivalId="+id+"&flag=1";
	ec.submit();
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
	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=submitWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&tag=1&flag=1";
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
	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=submitWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&tag=1&flag=1";
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
	ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=submitWlArrivalDtl&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>&tag=1&flag=1";
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
        width=99% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
 <html:form action="/lf/wlArrivalDtlAction4Search" method="post">
 <jodd:form bean="request">
            <input type="hidden" name="ec_i" />
            <input type="hidden" name="ec_p" />
            <input type="hidden" name="ec_crd" />    
            <input type="hidden" name="search_dtlState" />
</jodd:form>
          <tbody>
             <tr align="center" valign="center">
          <td width="13%" class="tableHeader2" >物料大类</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" >
               <html:select property="search_dlid" styleClass="select01" onchange="changeXl(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="dllist" labelProperty="dlmc" property="id" />
               </html:select></td>
          <td width="13%" class="tableHeader2" >物料小类</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" >
               <html:select property="search_xlid" styleClass="select01" onchange="changeWl(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="xllist" labelProperty="xlmc" property="id" />
               </html:select>
          </td>
          <td width="13%" class="tableHeader2" >物料名称</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" >
          	   <html:select property="search_wlid" styleClass="select01">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="wllist" labelProperty="wlmc" property="id" />
               </html:select>
          </td>
        </tr>
        <tr align="center" valign="center">
          <td height="13%" class="tableHeader2" >物料型号</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" >
          	<html:text property="search_wlxh" styleClass="input_box" maxlength="50"/>
          </td>
          <td width="13%" class="tableHeader2" >是否附件</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td>
          	   <html:select property="search_ifAppendix" styleClass="select01">
                 <html:option value="">请选择	</html:option>	
				 <html:option value="0">否</html:option>
				 <html:option value="1">是</html:option>
               </html:select>
              </td>
              </tr>
          </table></td>
          <td width="13%" class="tableHeader2" >明细状态</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" >
			<html:select property="search_dtlState" styleClass="select01">
                <html:option value="">请选择	</html:option>	
                <html:option value="<%=Constants.wlANotSubID%>"><%=Constants.wlANotSubName%></html:option>
				<html:option value="<%=Constants.wlASubID%>"><%=Constants.wlASubName%></html:option>
				<html:option value="<%=Constants.wlPassingID%>"><%=Constants.wlPassingName%></html:option>
				<html:option value="<%=Constants.wlNotPassID%>"><%=Constants.wlNotPassName%></html:option>
				<html:option value="<%=Constants.wlPassingID%>"><%=Constants.wlPassingName%></html:option>
            </html:select>
          </td>
        </tr>
        <tr align="center" valign="center">
          <td width="13%" class="tableHeader2" >生产厂家</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" >          	   
          	<html:select property="search_producterId" styleClass="select01">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="scslist" labelProperty="companyName" property="id" />
            </html:select></td>
          <td width="13%" class="tableHeader2" >供应商</td>
          <td width="37%" align="left" valign="middle" class="tableHeader3" colspan=3>
            <html:select property="search_providerId" styleClass="select01">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="gyslist" labelProperty="companyName" property="id" />
            </html:select>
		  </td>
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
        <td height="40" align="right" valign="middle" class="tdborder02" colspan=2>
          <input name="Submit" type="button" class="button_nor" onClick="search()" value="查 询" >
&nbsp;<input name="Submit2" type="button" class="button_nor" value="重 置" onclick="DoClear()"></td>
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
      <c:if test="${wlArrivalDtlList!=null}">
      <tr>
        <td height="20" align="center" valign="middle" colspan="2">
        <ec:table items="wlArrivalDtlList" var="wlArrival" rowsDisplayed="10" action="wlArrivalDtlAction4Search.do?method=listWlArrivalDtlByState" >	

				<ec:exportXls fileName="wlArrivalDtlList.xls" tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="50" headerStyle="text-align:center" style="text-align: center">
						<input type="checkbox" name="itemList" value="${wlArrival.wlArrivalDtlId}" style="border:0px"/>
					</ec:column>
					<ec:column property="wlmc" title="物料名称" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" >
					    <c:choose>
											<c:when test="${wlArrival.state=='未提交'}">
											 <a href="javascript:DoView1('${wlArrival.wlArrivalDtlId}')">${wlArrival.wlmc}</a>
											</c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='已提交'}">
											 <a href="javascript:DoView1('${wlArrival.wlArrivalDtlId}')"><font color="black">${wlArrival.wlmc}</font></a>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='审批通过'}">
											<a href="javascript:DoView1('${wlArrival.wlArrivalDtlId}')"><font color="green">${wlArrival.wlmc}</font></a>
										    </c:when>
				                            </c:choose>
				                            <c:choose>
						                    <c:when test="${wlArrival.state=='审批不通过'}">
											<a href="javascript:DoView1('${wlArrival.wlArrivalDtlId}')"><font color="red">${wlArrival.wlmc}</font></a>
										    </c:when>
				                            </c:choose>
					</ec:column>       
					<ec:column property="arrivalNum" title="到货数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					>
					<c:choose>
										<c:when test="${wlArrival.state=='未提交'}">
											${wlArrival.arrivalNum}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.arrivalNum}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.arrivalNum}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${s.arrivalNum}</font>
										</c:when>
				                        </c:choose>
				                        </ec:column>
				<ec:column property="alledTNum" title="已安置货物数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
										<c:when test="${wlArrival.state=='未提交'}">
											${wlArrival.alledTNum}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.alledTNum}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.alledTNum}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${wlArrival.alledTNum}</font>
										</c:when>
				                        </c:choose>
				                        </ec:column>
					<ec:column property="waitNum" title="已接收安置货物数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
										<c:when test="${wlArrival.state=='未提交'}">
											${wlArrival.waitNum}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.waitNum}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.waitNum}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${wlArrival.waitNum}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="ifaccount" title="是否已入帐" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
										<c:when test="${wlArrival.state=='未提交'}">
											${wlArrival.ifaccount}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.ifaccount}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.ifaccount}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${wlArrival.ifaccount}</font>
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
											${wlArrival.ifreceiptavl}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.ifreceiptavl}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.ifreceiptavl}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${wlArrival.ifreceiptavl}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="providerName" title="供应商" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					>
					<c:choose>
					<c:when test="${wlArrival.state=='未提交'}">
											${wlArrival.providerName}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.providerName}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.providerName}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${wlArrival.providerName}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="producterName" title="生产商" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					>
					<c:choose>
					<c:when test="${wlArrival.state=='未提交'}">
											${wlArrival.producterName}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.producterName}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.producterName}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${wlArrival.producterName}</font>
										</c:when>
				                        </c:choose>
					</ec:column>
					<ec:column property="state" title="明细状态" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<c:choose>
					<c:when test="${wlArrival.state=='未提交'}">
											${wlArrival.state}
										</c:when>
				                        </c:choose>
				                        <c:choose>
				                        <c:when test="${wlArrival.state=='已提交'}">
											<font color="black">${wlArrival.state}</font>
										</c:when>
				                        </c:choose>
										<c:choose>
										<c:when test="${wlArrival.state=='审批通过'}">
											<font color="green">${wlArrival.state}</font>
										</c:when>
										</c:choose>	
										<c:choose>
										<c:when test="${wlArrival.state=='审批不通过'}">
											<font color="red">${wlArrival.state}</font>
										</c:when>
				                        </c:choose>
					
					</ec:column>
					<ec:column property="producerName" title="安置情况" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<!--  a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')">安置情况一览</a-->
					<c:choose>
					<c:when test="${wlArrival.state=='未提交'}">
			
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')">安置中</a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')">未安置</a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')">安置完成</a>
					</c:if>
					</c:when>
				    </c:choose>
				    	<c:choose>
					<c:when test="${wlArrival.state=='已提交'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">安置中</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">未安置</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">安置完成</font></a>
					</c:if>
					</c:when>
				    </c:choose>
				      	<c:choose>
					<c:when test="${wlArrival.state=='审批通过'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="green">安置中</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="green">未安置</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="green">安置完成</font></a>
					</c:if>
					</c:when>
				    </c:choose>
				          	<c:choose>
					<c:when test="${wlArrival.state=='审批不通过'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="red">安置中</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="red">未安置</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="red">安置完成</font></a>
					</c:if>
					</c:when>
				    </c:choose>
				            	<c:choose>
					<c:when test="${wlArrival.state=='审批中'}">
				
					<c:if test="${wlArrival.arrivalNum>wlArrival.alledTNum&&wlArrival.alledTNum>0}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">安置中</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==0}">
					<a href="javascript:DoView2('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">未安置</font></a>
					</c:if>
					<c:if test="${wlArrival.alledTNum==wlArrival.arrivalNum}">
					<a href="javascript:DoView3('${wlArrival.wlArrivalId}','${wlArrival.wlArrivalDtlId}')"><font color="black">安置完成</font></a>
					</c:if>
					</c:when>
				    </c:choose>
					</ec:column>

				</ec:row>
			</ec:table></td>
      </tr>
    </c:if>

        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()" ><input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()" ><input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()" >
        		</td>
        <td height="40" align="right" valign="middle" colspan="2">
          <input name="Submit34" type="button" class="button_nor" value="修改明细"  onClick="modify()"><input name="Submit33" type="button" class="button_nor" value="删除明细" onClick="deleteDtl()"><input name="Submit35" type="button" class="button_nor" value="提交明细" onClick="submit()"></td>
</tr>
		
      <tr>               <td><table width="99%" border="0">
		</table></td>
    </table></td></tr>
  </tr>
</table>
</body>
</html>
<script>
function DoClear(){
	document.wlArrivalDtlSearchForm.elements["search_dlid"].options[0].selected=true;
    document.wlArrivalDtlSearchForm.elements["search_xlid"].options[0].selected=true;
    document.wlArrivalDtlSearchForm.elements["search_wlid"].options[0].selected=true;
    document.wlArrivalDtlSearchForm.elements["search_wlxh"].value="";
    document.wlArrivalDtlSearchForm.elements["search_ifAppendix"].options[0].selected=true;
    document.wlArrivalDtlSearchForm.elements["search_dtlState"].options[0].selected=true;
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
setTimeout('DoInit()',30);
function DoInit(){
  var dl,xl,wl,dept,wxs,uc,ifap,j;

     var dllist = document.wlArrivalDtlSearchForm.elements["search_dlid"];
     var xllist = document.wlArrivalDtlSearchForm.elements["search_xlid"];
     var wllist = document.wlArrivalDtlSearchForm.elements["search_wlid"];

     dl = document.wlArrivalDtlSearchForm.elements["search_dlid"].value;
     xl = document.wlArrivalDtlSearchForm.elements["search_xlid"].value;
     wl = document.wlArrivalDtlSearchForm.elements["search_wlid"].value;
     
   if(dl!="")
      changeXl(dllist);
   for(j=0;j<xllist.length;j++){
      if(xllist[j].value==xl)
	     xllist[j].selected=true;
   }		 
   if(xl!="")
        changeWl(xllist);
      for(j=0;j<wllist.length;j++){
      if(wllist[j].value==wl)
	     wllist[j].selected=true;
   }
}

function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   

   document.wlArrivalDtlSearchForm.elements["search_xlid"].length=1; //清空原小类列表

   document.wlArrivalDtlSearchForm.elements["search_wlid"].length=1; //清空原名称列表      


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
      for (i=0;i < datacount2; i++)
      {
          document.wlArrivalDtlSearchForm.elements["search_wlid"].options[document.wlArrivalDtlSearchForm.elements["search_wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
    }
   xllist = document.wlArrivalDtlSearchForm.elements["search_xlid"];
}

function changeWl(sel){
   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   document.wlArrivalDtlSearchForm.elements["search_wlid"].length=1; //清空原名称列表        
   
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.wlArrivalDtlSearchForm.elements["search_wlid"].options[document.wlArrivalDtlSearchForm.elements["search_wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
      for (i=0;i < datacount; i++){
          if (dataset[i][0] == id){
             document.wlArrivalDtlSearchForm.elements["search_dlid"].value=dataset[i][2];
          }
      }
    }else{
       
       for (i=0;i < datacount2; i++)
      {
          document.wlArrivalDtlSearchForm.elements["search_wlid"].options[document.wlArrivalDtlSearchForm.elements["search_wlid"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   wllist = document.wlArrivalDtlSearchForm.elements["search_wlid"];

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
         alert("上级设备与本设备相同!");
         return;
}
     
//if(document.all.tempwlmc.value!=''&&document.all.ifChanged.value=='1')
//     changeWlid(document.all.wlid);

if(document.all.ifChanged.value=='0'){ 
    alert("您没有修改任何字段。");
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
	wlArrivalDtlSearchForm.action="equipmentAction.do?method=batchupdate";
	wlArrivalDtlSearchForm.submit();
	}
else{
    alert("您没有修改任何字段。");
    return;
}
}

function DoBack(){   
   wlArrivalDtlSearchForm.action="equipmentAction.do?method=search4List&listNum='all'";
   wlArrivalDtlSearchForm.submit();
}
</script>