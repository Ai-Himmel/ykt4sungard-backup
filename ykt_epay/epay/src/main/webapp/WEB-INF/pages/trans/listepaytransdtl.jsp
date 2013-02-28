<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<% 
  String msg= request.getAttribute("msg")==null?"":request.getAttribute("msg").toString();
%>
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
        function oper(url,revflag,formname) {
           var objfrm = document.forms[formname];
           if(revflag==1){
            alert("该交易已冲正！");
            return;
           } 
           if (confirm("您确定要对该记录进行冲正操作吗？")) {
               objfrm.action = url;
               objfrm.submit();    
            }
           
        }
        function change(){
	        var msg ='<%=msg%>';
	       	if(msg!=''){
	       		alert(msg);
		    	window.location.href="epayTransManager.do?method=listEpayTransdtl";
	       	}
        }
    </script>
</head>

<body onload="change();">
<div class="content" >
    <html:form action="epayTransManager.do?method=listEpayTransdtl" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="searchTable">
            <tr class="T1">
                <td >
                    &nbsp;客户号&nbsp;&nbsp;&nbsp;&nbsp;<html:text property="custid" styleClass="input_box" maxlength="50"/>
                    &nbsp;学/工号&nbsp;&nbsp;<html:text property="stuempno" styleClass="input_box" maxlength="50"/>
                    &nbsp;流水状态&nbsp;
                    <html:select property="status" >
                        <html:option value="">-------请选择-------</html:option>
                        <html:option value="1">1 - 未处理</html:option>
                        <html:option value="2">2 - 失败</html:option>
                        <html:option value="3">3 - 成功</html:option>
                        <html:option value="4">4 - 异常流水</html:option>
                        <html:option value="5">5 - 无效流水</html:option>
                        <html:option value="6">6 - 重复流水</html:option>
                        <html:option value="7">7 - 消费失败流水</html:option>
                    </html:select>
                </td>
                <td >
                </td>
            </tr>
            
            <tr class="T1">
                <td>
                    &nbsp;开始时间&nbsp;<html:text property="starttime" styleClass="Wdate"  onclick="WdatePicker({dateFmt:'yyyyMMdd'})" maxlength="50"/>
                    &nbsp;结束时间&nbsp;<html:text property="endtime" styleClass="Wdate" onclick="WdatePicker({dateFmt:'yyyyMMdd'})" maxlength="50"/>
                    &nbsp;冲正标志&nbsp;
                    <html:select property="revflag" >
                        <html:option value="">-------请选择-------</html:option>
                        <html:option value="0">未冲正</html:option>
                        <html:option value="1">已冲正</html:option>
                    </html:select>
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                </td>
                <td>
                    <select name="pageSize" onchange="changePageSize('transForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <div class="divTpad">
    <display:table name="listTransdtl" class="tablelist" export="false" id="row"
                   requestURI="epayTransManager.do?method=listEpayTransdtl" form="transForm">
        <display:column property="id.termseqno" title="终端流水号"  media="html"/> 
        <display:column property="custname"  title="姓名" />          
        <display:column property="custid"  title="客户号" />
        <display:column property="stuempno"  title="学/工号" />
        <display:column property="amount"  title="发生额" />
        <display:column property="cardbefbal"  title="交易前余额"/>
        <display:column property="cardaftbal"  title="交易后余额" />
        <display:column property="status"  title="流水状态" decorator="statusDecorator"/>
        <display:column property="revflag"  title="冲正标志" decorator="revflagDecorator" />
        <display:column property="transdate"  title="交易日期" />
        <display:column property="transtime"  title="交易时间" />
        <display:column title="操作" style="width:10%;" media="html">
            <a href="javascript:oper('epayTransManager.do?method=reverseEpay&refno=${row.refno.refno}&mac=${row.refno.mac}','${row.revflag}','transForm');"><span style="color:#FF6600;">冲正</span></a>
        </display:column>
        
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

    </script>
    </div>
</div>
</body>

</html>

