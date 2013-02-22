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

function modify(){
    var i = 0;
    var counte = 0;
    if(ec.elements["itemList"].checked==true){                               
    	    ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Search&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     		ec.submit();
    }else{
       	for(i=0;i<ec.elements["itemList"].length;i++){
       		if(ec.elements["itemList"][i].checked == true){
       	   		++counte; 	  
       		}
  		}
    	if(counte==1){
 			ec.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadWlArrivalDtlInfo4Search&wlArrivalId=<%=request.getAttribute("wlArrivalId")%>";
     		ec.submit();
   		}else if(counte>1){
			alert('只能选择一条要查看的明细记录');
    	}else if(counte<1){
      	  	alert('请选择要查看的明细记录');
   	 	}
    }
}

function back(){
 	wlArrivalBillForm.action = "<c:url value="/lf/wlArrivalAction.do"/>?method=loadWlArrivalList4Search";
	wlArrivalBillForm.submit();
}
function DoView(id){
    wlArrivalBillForm.action = "<c:url value = "/lf/wlArrivalDtlAction.do"/>?method=loadAllocationList4Search&wlArrivalDtlId="+id;
	wlArrivalBillForm.submit();
}
function DoView1(id){
    window.open("wlArrivalDtlAction.do?method=loadWlArrivalDtlInfo4Search&tag=1&wlArrivalDtlId="+id,"detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
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
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
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
              <td width="13%" class="tableHeader2" >到货单号</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <html:hidden property="wlArrivalId" styleClass="input_box" />
              <bean:write name="wlArrivalBillForm" property="wlArrivalId"/>
               </td>
              
				<td width="13%" class="tableHeader2" >登记人</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalBillForm" property="regPName"/>
              <html:hidden property="regUName" styleClass="input_box" />
              </td>
            </tr>
            <tr align="center" valign=center>
            
              
              
              <td width="13%" class="tableHeader2" >部门</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" >
              <bean:write name="wlArrivalBillForm" property="deptName"/>
                <html:hidden property="deptCode" styleClass="input_box"/>
				</td>

              <td width="13%" class="tableHeader2" >登记日期</td>
              <td width="37%" align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                  <tr>
                    <td>
                    <bean:write name="wlArrivalBillForm" property="regDate"/>
                    </td>
                    <td width="25" align="right" valign="middle" ></td>
                  </tr>
              </table></td>
            </tr>
            <tr align="center" valign=center>
              <td width="13%" align="left" valign="middle" class="tableHeader2" >备注</td>
              <td width="87%" colspan="3" align="left" valign="middle" class="tableHeader4" >
              <bean:write name="wlArrivalBillForm" property="memo"/>
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
						</logic:iterate>
					</logic:present>
      </html:form>
      <tr>
        <td height="20" align="right" valign="middle" class="tdborder02" colspan="2"></td>
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
					<ec:column property="wlmc" title="物料名称" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="90" >
					    <a href="javascript:DoView1('${wlArrivalDtl.wlArrivalDtlId}')">${wlArrivalDtl.wlmc}</a>
					</ec:column>    
					<ec:column property="arrivalNum" title="到货数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="50" 
					/>
					<ec:column property="alledTNum" title="已安置货物数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="waitNum" title="待接收安置记录数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="incertedNum" title="已接收安置记录数" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="unincertNum" title="不接受安置记录数" 
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
					<ec:column property="state" title="明细状态" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="producerName" title="安置情况" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					>
					<a href="javascript:DoView('${wlArrivalDtl.wlArrivalDtlId}')">安置情况一览</a>
					</ec:column>

				</ec:row>
			</ec:table></td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle" colspan="2">
          <input name="Submit31" type="button" class="button_nor" value="返 回" onClick="back()"></td>
      </tr>
    </table></td>
  </tr>
</table>
</body>
</html>
