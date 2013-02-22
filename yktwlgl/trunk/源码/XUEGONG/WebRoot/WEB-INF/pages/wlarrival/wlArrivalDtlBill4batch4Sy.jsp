<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>

<html>
<head>
<title>上海复旦大学物料库存及仓储管理系统</title>
<meta http-equiv="Content-Type" content="text/html;">
<%@ include file="/pages/components/calendar/calendar.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
<SCRIPT language=javascript>
function baocun(elements){
    if(doCheckForm(elements)!=false){
    	wlArrivalDtlBillForm.action = "<c:url value="/lf/wlArrivalDtlAction.do"/>?method=saveWlArrivalDtl4Batch&tag=1";
		wlArrivalDtlBillForm.submit();
	}
}
function back(){
    wlArrivalDtlBillForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=listWlArrivalDtlByState";
	wlArrivalDtlBillForm.submit();
}
function doCheckForm(elements)
{
	var len = elements.length;

	for(var i=0;i< len ;i++ )
	{
		var field = elements[i];
		if(field.name=='arrivalNum'){
				if(field.value!=''){
					if(!isInt(field.value))
				    {
						msg(field.title+"必须是数字");
						field.select();
						return false;
				    }
				    if(elements['purDtlId'].value!=''&&(field.value)>(elements['tempArrivalNum'].value)){
				    	msg(field.title+"到货数只能小于或等于采购数量\n\n此处可填写的最大到货数为:"+elements['tempArrivalNum'].value)
				    	field.select();
						return false;
				    }
				}
		}
		if(field.name=='procurePrice'){
				if(field.value!=''){
					if(!isDouble(field.value))
				    {
						msg(field.title+"请确定输入合法数值");
						field.select();
						return false;
				    }
				}
		}
		if(field.name=='DtlMemo'){

					if(field.value.length>300)
				    {
						msg(field.title+"请将备注的输入长度限制在300个字符以内！！");
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
function doCheckForm(elements)
{
	var len = elements.length;

	for(var i=0;i< len ;i++ )
	{
		var field = elements[i];
		if(field.name=='arrivalNum'){
				if(field.value!=''){	
					if(!isInt(field.value))
				    {
						msg(field.title+"必须是数字");
						field.select();
						return false;
				    }
				}
				    if(elements['purDtlId'].value!=''&&parseInt(field.value)>parseInt(elements['tempArrivalNum'].value)){
				    	msg(field.title+"到货数只能小于或等于采购数量");
				    	field.select();
						return false;
				    }
		}
		if(field.name=='DtlMemo'){

					if(field.value.length>300)
				    {
						msg(field.title+"请将备注的输入长度限制在300个字符以内！！");
						field.select();
						return false;
				    }
		}
	}
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

<%
String[] aa=null;
 aa=(String[])request.getAttribute("wlArrivalDtlIds");
for (int i=0;i<aa.length;i++){ 
	String bb=aa[i];
%>
<input type="hidden" name="wlArrivalDtlIds" value="<%=bb%>">
<%} %>
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
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
			<html:hidden property="wlArrivalId" />
			<html:hidden property="purDtlId" />
            <input type="hidden" name="ifChanged" value="0">
            <tr>
             <td align="right" valign="middle" class="tableHeader2" style="width:13%">物料名称</td>
              <td align="left" valign="middle" class="tableHeader3" style="width:20%">
                <html:hidden property="wlid" />
                <html:text property="wlmc" styleClass="input_box" readonly="true"/>
			</td>
              <td align="right" valign="middle" class="tableHeader2" style="width:13%">物料规格</td>
              <td align="left" valign="middle" class="tableHeader3" style="width:20%">
              <html:text property="wlsption" styleClass="input_box" readonly="true"/></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" style="width:13%">物料型号</td>
              <td align="left" valign="middle" class="tableHeader3" style="width:20%">
              <html:text property="wlmodel" styleClass="input_box" readonly="true"/></td>
             </tr>
            <tr align="center" valign=center>
            <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >用途大类</td>
              <td align="left" valign="middle" class="tableHeader3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="35">
              <input type="hidden" name="old_usageCategory" value="">
              <input type="hidden" name="new_usageCategory" value="">
              <html:hidden property="usageCategory" styleClass="input_box"/>
              <html:select property="s_usageCategory" styleClass="select01" onchange="changeUsageCategory(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="uclist" labelProperty="usageCategoryName" property="id" />
              </html:select>

                  <input name="tempUsageCategory" style="input_box" maxlength="50" value="<%=request.getParameter("tempUsageCategory")==null||request.getParameter("tempUsageCategory").equals("null")?"":request.getParameter("tempUsageCategory")%>" readonly="readonly"/>
                  </td>
                  <td width="20">&nbsp;</td>
                  <td width="20" align="right">
                  <input name="addUsageCategory" type="button" value="查找" onclick="javascript:window.open('<c:url value="/gyf/deptUsageCategoryAction.do"/>?method=search4List&formName=wlArrivalDtlBillForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
                  </td>                   
                </tr></table>
              </td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >物料单位</td>
              <td align="left" valign="middle" class="tableHeader3"> 
              <html:text property="wldw" styleClass="input_box" readonly="true"/></td>
			  <td align="right" valign="middle" class="tableHeader2" >是否附件</td>
              <td align="left" valign="middle" class="tableHeader3" >
              	<html:hidden property="ifAppendix"/>
              	<html:text property="ifAppendixName" styleClass="input_box" readonly="true"/>
              </td>
              <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >用途说明</td>
              <td align="left" valign="middle" class="tableHeader3" colspan="6">
              <html:textarea property="usage" styleClass="input_box" rows="3" cols="80" readonly="true"/></td>
              
              </tr>
            <tr align="center" valign=center>
              <td align="right" valign="middle" class="tableHeader2" >采购经办人</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="proPersonId" styleClass="input_box">
                  <html:option value="">请选择</html:option>	
				  <html:options collection="deptUserList" labelProperty="personName" property="code" />             
              </html:select>
              </td>
              <td align="right" valign="middle" class="tableHeader2" >采购单价</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="procurePrice" styleClass="input_box"/>元</td>
               <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >采购日期</td>
              <td align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td><html:text property="procureDate" styleClass="input_box" readonly="true"/></td>
                  <td width="25" align="right" ><img id="selectprocureDate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="采购日期" style="cursor:pointer"></td>
                </tr>
              </table></td>
            </tr>
            <tr align="center" valign=center>
              <td align="right" valign="middle" class="tableHeader2" >物料来源</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="mtlSource" styleClass="input_box">
                  <html:option value="">请选择</html:option>	
				  <html:options collection="wlSList" labelProperty="dictCaption" property="dictValue" />
              </html:select></td>
              <td align="right" valign="middle" class="tableHeader2" >到货数量</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:hidden property="tempArrivalNum" styleClass="input_box"/>
              <html:text property="arrivalNum" styleClass="input_box"/></td>
              <td align="right" valign="middle" class="tableHeader2" >到货日期</td>
              <td align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td><html:text property="arrivalDate" styleClass="input_box" readonly="true"/></td>
                  <td width="25" align="right" ><img id="selectarrivalDate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="到货日期" style="cursor:pointer"></td>
                </tr>
              </table></td>
            </tr>

            
            <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >生产厂家</td>
              <td align="left" valign="middle" class="tableHeader3" ><table><tr><td>
              <input type="hidden" name="new_producterId" value="">
              <html:hidden property="producterId" styleClass="input_box"/>
              <html:select property="s_producterId" styleClass="select01" onchange="changeProducter(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="scslist" labelProperty="companyName" property="id" />
              </html:select>
              <input type="hidden" name="scsid" value="<%=request.getParameter("scsid")==null||request.getParameter("scsid").equals("null")?"":request.getParameter("scsid")%>"/>
               <input name="tempProducter" style="input_box" maxlength="50" value="<%=request.getParameter("tempProducter")==null||request.getParameter("tempProducter").equals("null")?"":request.getParameter("tempProducter")%>" readonly="readonly"/>
              </td><td><input name="addProducter" type="button" value="查找" onclick="javascript:window.open('<c:url value="/gyf/deptCompanyAction.do"/>?method=search4List&cmyType=1&formName=wlArrivalDtlBillForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
              </td></tr></table></td>
              <td align="right" valign="middle" class="tableHeader2" >供应商</td>
              <td align="left" valign="middle" class="tableHeader3"><table><tr><td>
              <input type="hidden" name="new_providerId" value="">
              <html:hidden property="providerId" styleClass="input_box"/>
              <html:select property="s_providerId" styleClass="select01" onchange="changeProvider(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="gyslist" labelProperty="companyName" property="id" />
              </html:select>
              <input type="hidden" name="gysid" value="<%=request.getParameter("gysid")==null||request.getParameter("gysid").equals("null")?"":request.getParameter("gysid")%>"/>
             <input name="tempProvider" style="input_box" maxlength="50" value="<%=request.getParameter("tempProvider")==null||request.getParameter("tempProvider").equals("null")?"":request.getParameter("tempProvider")%>" readonly="readonly"/>
              </td><td><input name="addProvider" type="button" value="查找" onclick="javascript:window.open('<c:url value="/gyf/deptCompanyAction.do"/>?method=search4List&cmyType=2&formName=wlArrivalDtlBillForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
              </td></tr></table></td>
              
             <td align="right" valign="middle" class="tableHeader2" >合同号码</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="contractNo" styleClass="input_box" maxlength="200"/></td>
            </tr>
            
            <tr align="center" valign=center>
              <td align="right" valign="middle" class="tableHeader2" >发票号码</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="receiptNo" styleClass="input_box" maxlength="200"/></td>
  
              <td align="right" valign="middle" class="tableHeader2" >经费来源</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="fundSource" styleClass="input_box" maxlength="200"/></td>
              <td align="right" valign="middle" class="tableHeader2" >入帐日期</td>
			  <td align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td><html:text property="accountDate" styleClass="input_box" readonly="true"/></td>
                  <td width="25" align="right" ><img id="selectaccountDate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="入帐日期" style="cursor:pointer"></td>
                </tr>
              </table></td>
            </tr>
            
                        <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >维修商</td>
              <td align="left" valign="middle" class="tableHeader3" ><table><tr><td>
              <input type="hidden" name="new_maintainerid" value="">
              <html:hidden property="maintainerid" styleClass="input_box"/>
              <html:select property="s_maintainerid" styleClass="select01" onchange="changeMaintainer(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="wxsList" labelProperty="companyName" property="id" />
              </html:select>
              <input name="tempMaintainer" style="input_box" maxlength="50" value="<%=request.getParameter("tempMaintainer")==null||request.getParameter("tempMaintainer").equals("null")?"":request.getParameter("tempMaintainer")%>" readonly="readonly"/>
              </td><td><input name="addMaintainer" type="button" value="查找" onclick="javascript:window.open('<c:url value="/gyf/deptCompanyAction.do"/>?method=search4List&cmyType=3&formName=wlArrivalDtlBillForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
              </td></tr></table></td>                                        
  
              <td align="right" valign="middle" class="tableHeader2" >保修期</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="warrantyPeriod" styleClass="input_box"/>年</td>
              <td align="right" valign="middle" class="tableHeader2" >到发票日期</td>
			  <td align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td><html:text property="receiptDate" styleClass="input_box" readonly="true"/></td>
                  <td width="25" align="right" ><img id="selectreceiptDate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="到发票日期" style="cursor:pointer"></td>
                </tr>
              </table></td>
            </tr>
           <script type="text/javascript">
                								new calendar("procureDate", "selectprocureDate", "%Y-%m-%d");
                								new calendar("arrivalDate", "selectarrivalDate", "%Y-%m-%d");
                								new calendar("accountDate", "selectaccountDate", "%Y-%m-%d");
                								new calendar("receiptDate", "selectreceiptDate", "%Y-%m-%d");            
           </script>
            <tr align="center" valign=center>	
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >到货经办人</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="arrPersonId" styleClass="input_box">
                  <html:option value="">请选择</html:option>	
				  <html:options collection="deptUserList" labelProperty="personName" property="code" />
              </html:select></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >保管人</td>
              <td colspan="3" align="left" valign="middle" class="tableHeader3" >             
              <table><tr><td>
              <html:hidden property="acpid" styleClass="input_box"/>
              <html:select property="s_acpid" styleClass="select01" onchange="changeAcpid(this)">
                 <html:option value="">请选择	</html:option>	
				 <html:options collection="acplist" labelProperty="personName" property="id" />
              </html:select>
              <input name="tempAcpPerson" style="input_box" maxlength="50" value="<%=request.getParameter("tempAcpPerson")==null||request.getParameter("tempAcpPerson").equals("null")?"":request.getParameter("tempAcpPerson")%>" readonly="readonly"/>
              </td><td><input name="addAcpPerson" type="button" value="查找" onclick="javascript:window.open('<c:url value="/gyf/deptOtherPersonAction.do"/>?method=search4List&formName=wlArrivalDtlBillForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
              </td></tr></table></td> 									    
              </tr>
            <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >备注</td>
              <td colspan="5" align="left" valign="middle" class="tableHeader3" >
              <html:textarea property="DtlMemo" styleClass="" rows="3" cols="80"/></td>
              </tr>
          </tbody>
        </table>        </td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle">
        
          <input name="Submit" type="button" class="button_nor" value="保 存" onClick="baocun(document.forms[0].elements)" >
&nbsp;
<input name="Submit2" type="button" class="button_nor" value="返 回" onClick="back()"></td>
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
setTimeout('DoInit()',30);
function DoInit(){
  var dl,xl,wl,dept,wxs,uc,ifap,j;
  
	 var uclist = document.wlArrivalDtlBillForm.elements["s_usageCategory"];
     var scslist = document.wlArrivalDtlBillForm.elements["s_producterId"];
     var gyslist = document.wlArrivalDtlBillForm.elements["s_providerId"];
	 var wxslist = document.wlArrivalDtlBillForm.elements["s_maintainerid"];
	 var acplist = document.wlArrivalDtlBillForm.elements["s_acpid"];
	 
	 uc = uclist.options[uclist.selectedIndex].value;
     var sccj = scslist.options[scslist.selectedIndex].value;
     var gys = gyslist.options[gyslist.selectedIndex].value;
     wxs = wxslist.options[wxslist.selectedIndex].value;
     var acp = acplist.options[acplist.selectedIndex].value;
     
  var hasuc=false;
  var hassccj=false;
  var hasgys=false;
  var haswxs=false;
  var hasacp=false;
  
   for(var j=0;j<document.wlArrivalDtlBillForm.elements["s_usageCategory"].length;j++){
      if(document.wlArrivalDtlBillForm.elements["s_usageCategory"][j].value==uc){
	     document.wlArrivalDtlBillForm.elements["s_usageCategory"][j].selected=true;
	     hasuc=true;
	  }
   }
   for(var j=0;j<document.wlArrivalDtlBillForm.elements["s_producterId"].length;j++){
      if(document.wlArrivalDtlBillForm.elements["s_producterId"][j].value==sccj){
	     document.wlArrivalDtlBillForm.elements["s_producterId"][j].selected=true;
	     hassccj=true;
	  }
   }
   for(var j=0;j<document.wlArrivalDtlBillForm.elements["s_providerId"].length;j++){
      if(document.wlArrivalDtlBillForm.elements["s_providerId"][j].value==gys){
	     document.wlArrivalDtlBillForm.elements["s_providerId"][j].selected=true;
	     hasgys=true;
	  }
   }
   for(var j=0;j<document.wlArrivalDtlBillForm.elements["s_maintainerid"].length;j++){
      if(document.wlArrivalDtlBillForm.elements["s_maintainerid"][j].value==gys){
	     document.wlArrivalDtlBillForm.elements["s_maintainerid"][j].selected=true;
	     haswxs=true;
	  }
   }
   for(var j=0;j<document.wlArrivalDtlBillForm.elements["s_acpid"].length;j++){
      if(document.wlArrivalDtlBillForm.elements["s_acpid"][j].value==gys){
	     document.wlArrivalDtlBillForm.elements["s_acpid"][j].selected=true;
	     hasacp=true;
	  }
   }
   if(hasuc){
       document.wlArrivalDtlBillForm.elements["s_usageCategory"].style.display='';
       document.wlArrivalDtlBillForm.elements["tempUsageCategory"].style.display='none';
   }else{
       document.wlArrivalDtlBillForm.elements["s_usageCategory"].style.display='none';
       document.wlArrivalDtlBillForm.elements["tempUsageCategory"].style.display='';   
   }
   if(hassccj){
       document.wlArrivalDtlBillForm.elements["s_producterId"].style.display='';
       document.wlArrivalDtlBillForm.elements["tempProducter"].style.display='none';
   }
   else{
       document.wlArrivalDtlBillForm.elements["s_producterId"].style.display='none';
       document.wlArrivalDtlBillForm.elements["tempProducter"].style.display='';   
   }
   if(hasgys){
       document.wlArrivalDtlBillForm.elements["s_providerId"].style.display='';
       document.wlArrivalDtlBillForm.elements["tempProvider"].style.display='none';
   }
   else{
       document.wlArrivalDtlBillForm.elements["s_providerId"].style.display='none';
       document.wlArrivalDtlBillForm.elements["tempProvider"].style.display='';   
   }   
   if(haswxs){
       document.wlArrivalDtlBillForm.elements["s_maintainerid"].style.display='';
       document.wlArrivalDtlBillForm.elements["tempMaintainer"].style.display='none';
   }
   else{
       document.wlArrivalDtlBillForm.elements["s_maintainerid"].style.display='none';
       document.wlArrivalDtlBillForm.elements["tempMaintainer"].style.display='';   
   }
   if(hasacp){
       document.wlArrivalDtlBillForm.elements["s_acpid"].style.display='';
       document.wlArrivalDtlBillForm.elements["tempAcpPerson"].style.display='none';
   }
   else{
       document.wlArrivalDtlBillForm.elements["s_acpid"].style.display='none';
       document.wlArrivalDtlBillForm.elements["tempAcpPerson"].style.display='';   
   }
}
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