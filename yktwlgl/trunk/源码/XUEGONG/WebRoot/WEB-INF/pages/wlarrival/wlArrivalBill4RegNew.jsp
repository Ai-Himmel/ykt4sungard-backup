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
	wlArrivalBillForm.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=openNewWlArrivalDtlBill";
	wlArrivalBillForm.submit();
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
    	ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
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
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
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
    		ec.action="<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=deleteWlArrivalDtlInfo&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
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
      </tr>
      <tr>
        <td height="20" align="right" valign="middle" class="tdborder02" colspan="2">
        	<input name="Submit" type="button" class="button_nor" value="保 存" onClick="save()">
        </td>
      </tr>
      
    

        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()" ><input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()" ><input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()" >
        		</td>
        <td height="40" align="right" valign="middle" colspan="2">
         

        	<tr>
         <td height="40" align="right" valign="middle" colspan="2">
                    </td>
                    </tr>
    </table></td></tr>

</table>
</body>
</html>
