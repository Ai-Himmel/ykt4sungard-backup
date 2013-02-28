<%@page pageEncoding="UTF-8" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta http-equiv="Page-Exit" content="blendTrans(Duration=1)">
    <title>支付结果</title>
    <link href="./themes/book.css" rel="stylesheet" type="text/css">
    <script type="text/javascript">
        function order() {
            window.location = "order";
        }
    </script>
</head>
<body>
<div class="newhead_operate">
    <ul class="newhead_operate_nav">
        <li><a href="goods">商品列表</a></li>
        <li class="newhead_separate"></li>
        <li><a href="order">我的订单</a></li>
        <li class="newhead_separate"></li>
    </ul>
</div>
<div class="order_content">
    <div class="border">
        <div class="money_notice e-book">
            <h4 class="money_notice_name">
                订单【<%=request.getAttribute("v_oid") == null ? "" : request.getAttribute("v_oid")%>
                】<%=request.getAttribute("status")%>
                。<%=request.getAttribute("msg")%>
            </h4>

            <div id="div_select" class="layout_bankpay firstpay_bp">
                <div class="paylist">
                    <h3>
                        <span><b>订单信息：</b></span>
                    </h3>
                    <table width="0" border="0" cellspacing="0" cellpadding="0" class="ul_bank">
                        <tbody>
                        <tr>
                            <td style="height:40px">
                                订单号：
                            </td>
                            <td style="height:40px">
                                <%=request.getAttribute("v_oid") == null ? "" : request.getAttribute("v_oid")%>
                            </td>
                        </tr>
                        <tr>
                            <td style="height:40px">
                                订单总金额：
                            </td>
                            <td style="height:40px">
                                <%=request.getAttribute("v_amount") == null ? "" : request.getAttribute("v_amount")%>
                            </td>
                        </tr>
                        <tr>
                            <td style="height:40px">
                                订单状态：
                            </td>
                            <td style="height:40px">
                                <%=request.getAttribute("v_status") == null ? "" : request.getAttribute("v_status")%>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <button type="button" class="submitBtn" onclick="order()">返回我的订单</button>
                            </td>
                            <td></td>
                        </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</div>
<input type="hidden" name="v_refno"
       value="<%=request.getAttribute("v_refno") == null ? "" : request.getAttribute("v_refno")%>"/>
<input type="hidden" name="v_oid"
       value="<%=request.getAttribute("v_oid") == null ? "" : request.getAttribute("v_oid")%>"/>
<input type="hidden" name="v_status"
       value="<%=request.getAttribute("v_status") == null ? "" : request.getAttribute("v_status")%>"/>
<input type="hidden" name="v_code"
       value="<%=request.getAttribute("v_code") == null ? "" : request.getAttribute("v_code")%>"/>
<input type="hidden" name="v_amount"
       value="<%=request.getAttribute("v_amount") == null ? "" : request.getAttribute("v_amount")%>"/>
<input type="hidden" name="v_currency"
       value="<%=request.getAttribute("v_currency") == null ? "" : request.getAttribute("v_currency")%>"/>
<input type="hidden" name="v_errcode"
       value="<%=request.getAttribute("v_errcode") == null ? "" : request.getAttribute("v_errcode")%>"/>
<input type="hidden" name="v_errmsg"
       value="<%=request.getAttribute("v_errmsg") == null ? "" : request.getAttribute("v_errmsg")%>"/>
<input type="hidden" name="v_name"
       value="<%=request.getAttribute("v_name") == null ? "" : request.getAttribute("v_name")%>"/>
<input type="hidden" name="v_remark"
       value="<%=request.getAttribute("v_remark") == null ? "" : request.getAttribute("v_remark")%>"/>
</body>
</html>