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
function incept(tag){
  var sflag = 0;
  if(document.all.apiItemList.checked==true){
     ec.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=allocationInfoIncept&tag="+tag;     
   	 ec.submit();
  }else{
          for(var i=0;i<document.all.apiItemList.length;i++){
              if(document.all.apiItemList[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
   			  ec.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=allocationInfoIncept&tag="+tag;    
   			  ec.submit()
          }else if(sflag<1){
          	  alert("您还未选择要接收的安置信息！");
          }else{           
   			  ec.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=allocationInfoIncept&tag="+tag;    
   			  ec.submit();
          } 
}
}
function DoSelectall(){
  if(document.all.apiItemList!=null&&document.all.apiItemList.length>1){   
       for(var i=0;i<document.all.apiItemList.length;i++){
              document.all.apiItemList[i].checked=true;
       }
       
  }
  else if(document.all.apiItemList!=null){
       document.all.apiItemList.checked=true;       
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoNotselectall(){
  
  if(document.all.apiItemList!=null&&document.all.apiItemList.length>1){   
       for(var i=0;i<document.all.apiItemList.length;i++){
              document.all.apiItemList[i].checked=false;
       }
       
  }
  else if(document.all.apiItemList!=null){
       document.all.apiItemList.checked=false;       
  }
  else{
       alert("当前无记录！");
  }
}

function DoReverseselect(){
   
   if(document.all.apiItemList!=null&&document.all.apiItemList.length>1){   
       for(var i=0;i<document.all.apiItemList.length;i++){
           if(document.all.apiItemList[i].checked)
              document.all.apiItemList[i].checked=false;
           else if(!document.all.apiItemList[i].checked)
              document.all.apiItemList[i].checked=true;
       }
       
  }
  else if(document.all.apiItemList!=null){
      if(document.all.apiItemList.checked)
          document.all.apiItemList.checked=false; 
      else if(!document.all.apiItemList.checked)
          document.all.apiItemList.checked=true;    
  }
  else{
       alert("当前无记录！");
  }
  

}
function DoView(id){
    window.open("wlArrivalDtlAction.do?method=loadWlArrivalDtlInfo4Search&tag=1&wlArrivalDtlId="+id,"detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}
</SCRIPT>

</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>

		<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
			<tr>
				<td align="left" valign="top">

					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td height="25" align="left" valign="top">
								<html:form action="/lf/wlArrivalDtlAction" method="post">
									<table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">到货安置确认</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
										</tr>
									</table>
							</td>
						</tr>
						</html:form>

      <tr>
        <td height="20" align="center" valign="middle" colspan="2">
        <ec:table items="allocationInfoList" var="allocationInfo" rowsDisplayed="10" action="wlArrivalDtlAction.do?method=loadAllocationList4All" >
								
				<ec:exportXls fileName="allocationInfoList" tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="50" headerStyle="text-align:center" style="text-align: center">
						<input type="checkbox" name="apiItemList" value="${allocationInfo.alId}" style="border:0px"/>
					</ec:column>
					
					<ec:column property="wlmc" title="名称" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					>
					<a href="javascript:DoView('${allocationInfo.wlArrivalDtlId}')">${allocationInfo.wlmc}</a>
					</ec:column>
					<ec:column property="mtlSpn" title="型号" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="xlmc" title="物料小类" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="mtlSource" title="物料来源" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="placeNum" title="安置数量" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="xqName" title="校区" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="bdName" title="楼宇" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="rmName" title="房间" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="managerName" title="管理员" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
				</ec:row>
			</ec:table></td>
      </tr>

      <tr>
                    <td><table width="99%" border="0">
        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()" >   
          			<input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()" >
          			<input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()" >
        		</td>
        <td height="40" align="right" valign="middle" colspan="2">
          <input name="Submit31" type="button" class="button_nor" value="接 收" onClick="incept('1')">
          <input name="Submit31" type="button" class="button_nor" value="不接收" onClick="incept('0')"></td>
          			</tr>
		</table></td>
      </tr>
    </table></td>
  </tr>
</table>
</body>
</html>
