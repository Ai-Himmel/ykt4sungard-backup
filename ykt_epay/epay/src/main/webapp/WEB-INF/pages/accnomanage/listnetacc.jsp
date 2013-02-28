<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>

<html>
<head>
    <title>一卡通支付</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link rel="stylesheet" type="text/css" href="<c:url value="/theme/displaytag/css/screen.css"/>"/>
    <link href="<c:url value="/theme/datePicker/skin/default/datepicker.css"/>" type="text/css" rel=stylesheet>
    <script language="javascript" type="text/javascript" src="<c:url value="/theme/datePicker/WdatePicker.js"/>"></script>
    <script type="text/javascript" src="<c:url value="/theme/scripts/global.js"/>" ></script>
    <script type="text/javascript" src="<c:url value="/theme/scripts/grid.js"/>" ></script>
    <script src="<c:url value="/theme/scripts/jquery-1.4.2.min.js"/>"	type="text/javascript"></script>

<script type="text/javascript">
  //全选checkbox 的处理方法
  function doallcheck(){
      var allche = document.getElementById("allid")
      var items = document.all["itemlist"];
      if(allche.checked == true){
           for (var i = 0; i < items.length; i++){
           items[i].checked = "checked";
          }  
      }else{
       for (var i = 0; i < items.length; i++){
         items[i].checked = false;
       }
      
     }
      
  }
  
  //当选中冻结校园卡时，卡类型才可用
  function selectcardType(){
   var frozencard = document.getElementById("frozencard")
   if(frozencard.checked == true){
        document.all.cardphytype.disabled=false;
   }else{
        document.all.cardphytype.disabled=true;
   }
  }
  
  function atleaseOneCheck()
{
    var items = document.all["itemlist"];
    if(items==null)
        return false;
    if(items.length>0){
	    for (var i = 0; i < items.length; i++)
	    {
	        if (items[i].checked == true)
	        {
	            return true;
	        }
	    }
	}else{
		if(items.checked == true){
			  return true;		   	 
		}
	}
    return false;
}
  

function registerirre(formname, entityName, action)
{
   var objfrm = document.forms[formname];
   var frozencard = document.getElementById("frozencard");
   var lockacc = document.getElementById("lockacc");
   var items = document.all["itemlist"];
   var accnos = '';
   
   if (!atleaseOneCheck())
    {
        alert('请至少选择一个' + entityName + '！');
        return;
    }
    
    if(frozencard.checked != true && lockacc.checked != true){
	    alert('锁定电子账户,冻结校园卡中至少选择一项操作!');
		return false;
	}
	if(frozencard.checked == true && document.all.cardphytype.value=="-1")
	{
		alert('请选择所需要冻结的卡类型');
		return false;
	}
	
	for (var i = 0; i < items.length; i++)
	    {
	        if (items[i].checked == true)
	        {
	            accnos = accnos+items[i].value+',';
	        }
	    }
   
     if (confirm("你确定要设置" + entityName + "的状态?"))
    {
        objfrm.action = action+"&accnos="+accnos+"&islockacc="+lockacc.checked+"&isfrozencard="+frozencard.checked+"&cardphytype="+document.all.cardphytype.value;
        objfrm.submit();
    }

}

</script>

</head>
<body>
<div class="content">
    <html:form action="netaccManager.do?method=listnetacc" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="searchTable">
            <tr class="T1">
                <td>
                    &nbsp;止付标志&nbsp;
                    <html:select property="stoppayflag" >
                        <html:option value="-1">-----请选择-----</html:option>
                        <html:option value="0">正常</html:option>
                        <html:option value="1">止付</html:option>
                    </html:select>
                    
                    &nbsp;账户状态&nbsp;
                    <html:select property="status" >
                        <html:option value="-1">-----请选择-----</html:option>
                        <html:option value="0">未激活</html:option>
                        <html:option value="1">正常</html:option>
                        <html:option value="2">锁定</html:option>
                        <html:option value="3">销户</html:option>
                    </html:select>
                    
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                </td>
                <td>
                    <select name="pageSize" onchange="changePageSize('netaccrecordForm')">
                        <option value="10" <c:if test="${'10' == pageSize}">selected="selected"</c:if>>10</option>
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    <br>
    <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr>
							<td width=15% height="20" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								<input type="checkbox" id="allid" onclick="doallcheck()">
							&nbsp;全选
							</td>
							<td width=10% align="left" valign="middle" bgcolor="#E7F1F5" class="tableHeader2">
								<input type="checkbox"  id="lockacc" name="lockacc" >
							&nbsp;锁定电子账户
							</td>
							<td width=10% align="left" valign="middle" bgcolor="#E7F1F5">
								<input type="checkbox" id="frozencard" name="frozencard" onclick="selectcardType()">
							&nbsp;冻结校园卡
							</td>
							<td width=15% align="left" valign="middle" bgcolor="#E7F1F5">
								<p></p>
								卡类型
							 <html:select property="cardphytype"  disabled="true" >
                             <html:option value="-1">-----------请选择-----------</html:option>
                             <html:options collection="cardphytypes" property="cardphytype" labelProperty="cardphytypename"/>
                             </html:select>
							</td>
							<td width=5% align="left" valign="middle" bgcolor="#E7F1F5" class="tdborder02">
								
								<input name="Submit" type="button" class="submitButton" value=" 设置 " onclick="registerirre('netaccrecordForm','电子钱包账户','<c:url value="netaccManager.do?method=setstatus" />');">
							</td>
					</tbody>
				</table>
		</html:form>		
    
    <div class="divTpad">
    <display:table name="netaccList" class="tablelist" export="false" id="row"
                   requestURI="netaccManager.do?method=listnetacc" form="netaccrecordForm">
        <display:column sortable="false" title="选择">
             <input type="checkbox"  name="itemlist" value="${row.accno}"/>
        </display:column>
        <display:column property="accno"  title="账号" />
        <display:column property="accname"  title="帐户名" />
        <display:column property="custid"  title="客户号" />
        <display:column property="stoppayflag"  title="止付标志" decorator="stopPayFlagDecorator"/>
        <display:column property="status"  title="帐户状态"  decorator="accStatusDecorator" />
        <display:column property="balance"  title="帐户余额" />
        <display:column property="lasttransdate"  title="上次交易日期" />
        <display:column property="opendate"  title="开户日期" />
        <display:column property="closedate"  title="登陆失败次数" />
        
        
    </display:table>
     <script type="text/javascript">
        $(document).ready(function(){
 			$("#row tbody tr").hover(function(){
 				$(this).addClass("hover");
 			},
 			function(){
 				$(this).removeClass("hover");
 			});
			$("#row tbody tr").click(
			  function () {
				$("#row tbody tr.selected").removeClass("selected");
				$(this).addClass("selected");
			  }); 
		});
		
	 <%String msg = (String) request.getAttribute("msg");
			if (msg != null) {
	%>
	alert('<%=msg%>');
	window.location.href="netaccManager.do?method=listnetacc";
	<%}%>

    </script>

    </div>
</div>
</body>

</html>
