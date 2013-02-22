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
function baocun(elements){
    if(doCheckForm(elements)!= false){
    	allocationInfoForm.action = "<c:url value="/lf/allocationAction.do"/>?method=saveAllocationInfo&tag=1";
		allocationInfoForm.submit();
	}
}
function back(elements){
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
					if(field.value=='')
				    {
						msg(field.title+"请输入安置数量");
						field.select();
						return false;
				    }
					if(!isInt(field.value))
				    {
						msg(field.title+"必须是数字");
						field.select();
						return false;
				    }
				    
				    if(parseInt(field.value)>parseInt(elements['placeableNum'].value))
				    {
				    	msg(field.title+"安置数只能小于或等于到货数量");
				    	field.select();
						return false;
				    }
		}
		if(field.name=='placeNum'){

					if(!isInt(field.value))
				    {
						msg(field.title+"请确定输入合法数值");
						field.select();
						return false;
				    }
		}
		if(field.name=='pfId'){

					if(field.value=='')
				    {
						msg(field.title+"请选择安置对象");
						field.select();
						return false;
				    }
		}
		if(field.name=='rmid'){

					if(field.value=='')
				    {
						msg(field.title+"请选择房间");
						field.select();
						return false;
				    }
		}
		if(field.name=='placeMemo'){

					if(field.value.length>300)
				    {
						msg(field.title+"请将备注的输入长度限制在300个字符以内！！");
						field.select();
						return false;
				    }
		}
		if(field.name=='place'){

					if(field.value.length>300)
				    {
						msg(field.title+"请将详细地址的输入长度限制在300个字符以内！！");
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
	message = "\n复旦物料管理系统友情提示\n\n======================================           \n\n"+message;
	message += "\n\n======================================           ";
	alert(message);
}

</SCRIPT>

</head>
<html:form action="/lf/allocationAction" method="post">
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
<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
  <tr>
    <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top"><table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">到货安置表</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <html:hidden property="wlArrivalId" styleClass="input_box"/>
            <html:hidden property="wlArrivalDtlId" styleClass="input_box"/>
            <html:hidden property="alId" styleClass="input_box"/>
            <tr align="center" valign=center>              
              <td width="13%" class="tableHeader2" ><font color="red" style="font-weight:normal">*&nbsp;</font>安置对象</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <html:hidden property="pfId" styleClass="input_box"/>
              <html:select property="s_pfid" styleClass="select01">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="azdxList" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>
              <td width="13%" class="tableHeader2" >校区</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <html:hidden property="xqId" styleClass="input_box"/>
              <html:select property="s_xqid" styleClass="select01" onchange="changeBd(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="xqList" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>
              </tr>
            <tr align="center" valign=center>              
              <td width="13%" class="tableHeader2" >楼宇</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="35">
                  <html:hidden property="bdid" styleClass="input_box"/>
                  <html:select property="s_bdid" styleClass="select01" onchange="changeRm(this);changeBdid(this)">
                      <html:option value="">请选择</html:option>	
				      <html:options collection="louyuList" labelProperty="lymc" property="id" />
				  </html:select>
    
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="40" align="right">
                  <input name="tempbuilding" style="input_box" maxlength="50" value="<%=request.getParameter("tempbuilding")==null||request.getParameter("tempbuilding").equals("null")?"":request.getParameter("tempbuilding")%>" readonly="readonly"/>
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="20" align="right">
                  <input name="addBuilding" type="button" value="查找" onclick="javascript:window.open('<c:url value="/gyf/deptBuildingAction.do"/>?method=search4List&formName=allocationInfoForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');" >
                  </td>                   
                </tr></table>
              </td>
              <td width="13%" class="tableHeader2" onchange="changeBefore(this)"><font color="red" style="font-weight:normal">*&nbsp;</font>房间</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="35">
                  <html:hidden property="rmid" styleClass="input_box"/>
                  <html:select property="s_rmid" styleClass="select01" onchange="changeRmid(this)">
                      <html:option value="">请选择</html:option>	
				      <html:options collection="roomList" labelProperty="roommc" property="id" />
				  </html:select>
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="40" align="right">
                  <input name="temproom" style="input_box" maxlength="50" value="<%=request.getParameter("temproom")==null||request.getParameter("temproom").equals("null")?"":request.getParameter("temproom")%>" readonly="readonly"/>
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="20" align="right">
                  <input name="addRoom" type="button" value="查找" onclick="javascript:window.open('<c:url value="/gyf/deptRoomAction.do"/>?method=search4List&formName=allocationInfoForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');" >
                  </td>                   
                </tr></table>
			  </td>
            </tr>
            <tr align="center" valign=center>
              <td width="13%" class="tableHeader2" >详细地点</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" colspan="3">
              <html:textarea property="place" styleClass="" rows="3" cols="80"/>
              </td>             
            </tr>
            <tr align="center" valign=center>
               <td width="13%" class="tableHeader2" ><font color="red" style="font-weight:normal">*&nbsp;</font>安置数量</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <html:hidden property="placeableNum" styleClass="input_box"/>
              <html:text property="placeNum" styleClass="input_box"/></td>
              <td width="13%" class="tableHeader2" ><font color="red" style="font-weight:normal">*&nbsp;</font>管理员</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
			  <html:select property="managerId" styleClass="select01">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="managerList" labelProperty="personName" property="code" />
              </html:select>
              </td>                         
            </tr>
            <tr align="center" valign=center>
              <td width="13%" class="tableHeader2" >备注</td>
              <td width="87%" colspan="3" align="left" valign="middle" class="tableHeader3" >
              <html:textarea property="placeMemo" styleClass="" rows="3" cols="80"/></td>
              </tr>
          </tbody>
        </table>        </td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle">
          <input name="Submit" type="button" class="button_nor" value="保 存" onClick="javascript:baocun(document.forms[0].elements);">
&nbsp;
<input name="Submit2" type="button" class="button_nor" value="返 回" onClick="javascript:back(document.forms[0].elements);"></td>
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
       resultset=(String[][])request.getAttribute("ablist");//读取校区、楼宇对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应楼宇id、楼宇名称、校区id
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
       resultset2=(String[][])request.getAttribute("bmlist");//读取楼宇、房间对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//产生javascript二维数组，对应房间id、房间名称、房间标识、楼宇id
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
   	 var hasbd=false;
   	 var hasrm=false;
   	 var haspf=false;
   	 var hasxq=false;
   	 for(var j=0;j<document.allocationInfoForm.elements["s_pfid"].length;j++){
     	if(document.allocationInfoForm.elements["s_pfid"][j].value==pf){
	    	document.allocationInfoForm.elements["s_pfid"][j].selected=true;
	     	var haspf=true;
	     }
	 }	
   	 for(var j=0;j<document.allocationInfoForm.elements["s_xqid"].length;j++){
     	if(document.allocationInfoForm.elements["s_xqid"][j].value==xq){
	    	document.allocationInfoForm.elements["s_xqid"][j].selected=true;
	     	var hasxq=true;
	     }
	 }	
	 if(xq!="")
       changeBd(document.allocationInfoForm.elements["s_xqid"]);
     for(var j=0;j<document.allocationInfoForm.elements["s_bdid"].length;j++){
     	if(document.allocationInfoForm.elements["s_bdid"][j].value==bd){
	    	document.allocationInfoForm.elements["s_bdid"][j].selected=true;
	     	var hasbd=true;
	     }
	 }	
	 if(bd!="")
       changeRm(document.allocationInfoForm.elements["s_bdid"]);
	 for(var j=0;j<document.allocationInfoForm.elements["s_rmid"].length;j++){
     	if(document.allocationInfoForm.elements["s_rmid"][j].value==rm){
	    	document.allocationInfoForm.elements["s_rmid"][j].selected=true;
	    	var hasrm=true;
	 	}
   	 }   
   if(haspf){
       document.allocationInfoForm.elements["s_pfid"].style.display='';
       document.allocationInfoForm.elements["tempbuilding"].style.display='none';
   }else{
       document.allocationInfoForm.elements["s_pfid"].style.display='none';
       document.allocationInfoForm.elements["tempbuilding"].style.display='';
   }
   if(hasxq){
       document.allocationInfoForm.elements["s_xqid"].style.display='';
       document.allocationInfoForm.elements["tempbuilding"].style.display='none';
   }else{
       document.allocationInfoForm.elements["s_xqid"].style.display='none';
       document.allocationInfoForm.elements["tempbuilding"].style.display='';
   }
   if(hasbd){
       document.allocationInfoForm.elements["s_bdid"].style.display='';
       document.allocationInfoForm.elements["tempbuilding"].style.display='none';
   }else{
       document.allocationInfoForm.elements["s_bdid"].style.display='none';
       document.allocationInfoForm.elements["tempbuilding"].style.display='';
   }
   if(hasrm){
       document.allocationInfoForm.elements["s_rmid"].style.display='';
       document.allocationInfoForm.elements["temproom"].style.display='none';
   }
   else{
       document.allocationInfoForm.elements["s_rmid"].style.display='none';
       document.allocationInfoForm.elements["temproom"].style.display='';
   }
}

function changeBdid(sel){
    document.all.bdid.value=sel.value;
}
function changeRmid(sel){
	alert('111');
    document.all.rmid.value=sel.value;
}
function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;

   document.all.s_bdid.length=1; //清空原楼宇列表
   document.all.s_rmid.length=1; //清空原房间列表        
 
   if(id!=""){

      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {  
             document.allocationInfoForm.elements["s_bdid"].options[document.allocationInfoForm.elements["s_bdid"].length]=new Option(dataset[i][1], dataset[i][0]);                         
          }
      }
    }else{
       for (i=0;i < datacount; i++)
      {
          document.all.s_bdid.options[document.all.s_bdid.length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
      for (i=0;i < datacount2; i++)
      {
          document.allocationInfoForm.elements["s_rmid"].options[document.allocationInfoForm.elements["s_rmid"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
    }

}
function changeRm(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_rmid.length=1; //清空原房间列表        
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
      for (i=0;i < datacount; i++){
          if (dataset[i][0] == id){
             document.allocationInfoForm.elements["s_xqid"].value=dataset[i][2];
          }
      }
    }else{
       
       for (i=0;i < datacount2; i++)
      {
          document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
      }
    }
}
function changeBefore(sel){
   var id;        
   var i;        
alert('000');
   id=sel.options[sel.selectedIndex].value;

   if(id!="")
      for (i=0;i < datacount2; i++)
      {
          if (dataset2[i][0] == id)
          {   
             document.allocationInfoForm.elements["s_bdid"].value=dataset2[i][3];              
             for (i=0;i < datacount; i++){
                 if (dataset[i][0] == document.allocationInfoForm.elements["s_bdid"].value){
                     document.allocationInfoForm.elements["xqId"].value=dataset[i][2];
                 }
             }               
          }
      }
}
</SCRIPT>
