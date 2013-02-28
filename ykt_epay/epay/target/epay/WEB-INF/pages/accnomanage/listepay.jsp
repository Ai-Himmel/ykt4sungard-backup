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
</head>
<body>
<div class="content">
    <html:form action="epayManager.do?method=listepay" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="searchTable">
            <tr class="T1">
                <td>
                    &nbsp;开始时间&nbsp;<html:text property="starttime" styleClass="Wdate"  onclick="WdatePicker({dateFmt:'yyyyMMdd'})" maxlength="50"/>
                    &nbsp;结束时间&nbsp;<html:text property="endtime" styleClass="Wdate" onclick="WdatePicker({dateFmt:'yyyyMMdd'})" maxlength="50"/>
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                </td>
                <td>
                    <select name="pageSize" onchange="changePageSize('payrecordForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <div class="divTpad">
    <display:table name="payRecord" class="tablelist" export="false" id="row"
                   requestURI="epayManager.do?method=listepay" form="payrecordForm">
        <display:column property="refno"  title="流水号" style="width:5%;"/>
        <display:column property="epaydate"  title="流水日期" style="width:5%;"/>
        <display:column property="transcode.transname"  title="交易类别" style="width:5%;"/>
        <display:column property="amount"  title="发生额" style="width:5%;"/>
        <display:column property="tshop.shopname"  title="商户名称" style="width:5%;"/>
        <display:column property="remark"  title="备注" style="width:5%;"/>
        
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

    </script>
    </div>
</div>
</body>

</html>
