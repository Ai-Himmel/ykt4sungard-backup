<%@page pageEncoding="UTF-8" %>
<%@ page import="org.king.domain.Order" %>
<%
    Order order = (Order) request.getAttribute("order");
%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta http-equiv="Page-Exit" content="blendTrans(Duration=1)">
    <title>网上支付</title>
    <link href="./themes/book.css" rel="stylesheet" type="text/css">
    <script type="text/javascript" src="./themes/lightbox.js"></script>
    <script type="text/javascript">
        function pay() {
            openXbox();
            var epayUrl = '<%=request.getAttribute("epayUrl")%>';
            epayUrl = epayUrl.replace(/^\s*(.*?)[\s\n]*$/g, '$1');
            if (epayUrl == '') {
                alert('请配置一卡通支付地址！');
                return;
            }
            document.bookForm.submit();
        }
        var xbox;
        function openXbox() {
            if (!xbox) {
                xbox = new LightBox("xbox-mock");
            }
            xbox.OverLay.Color = "#000";
            xbox.Center = true;
            xbox.Over = true;
            xbox.OverLay.Opacity = 50;
            xbox.Fixed = true;
            xbox.Show();
            document.getElementById("xbox-iframe").style.display = "block";
        }
    </script>
</head>
<body>
<form action="<%=request.getAttribute("epayUrl")%>" name="bookForm" method="post" target="_blank">
    <input type="hidden" name="v_shopid" value="<%=request.getAttribute("v_shopid")%>"/>
    <input type="hidden" name="v_oid" value="<%=order.getOid()%>"/>
    <input type="hidden" name="v_amount" value="<%=order.getAmount()%>"/>
    <input type="hidden" name="v_currency" value="<%=order.getCurrency()%>"/>
    <input type="hidden" name="v_url" value="<%=request.getAttribute("v_url")%>"/>
    <input type="hidden" name="v_code" value="<%=request.getAttribute("v_code")%>"/>
    <input type="hidden" name="v_date" value="<%=order.getDate()%>"/>
    <input type="hidden" name="v_time" value="<%=order.getTime()%>"/>
    <input type="hidden" name="v_name" value="Shirely"/>
    <input type="hidden" name="v_remark" value="<%=order.getRemark()%>"/>

</form>
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
            <h4 class="money_notice_name">订单<%=order.getOid()%>已提交，您需要支付<span
                    class="red_bold">￥<%=order.getAmount()%></span></h4>

            <div id="div_select" class="layout_bankpay firstpay_bp">
                <div class="paylist">
                    <h3>
                        <span><b>请使用以下平台支付：</b></span>
                    </h3>
                    <table width="0" border="0" cellspacing="0" cellpadding="0" class="ul_bank">
                        <tbody>
                        <tr>
                            <td class="bank_item">
            	            <span class="pay_pic">
                                <input type="image" src="./themes/pay_zxzf.gif"
                                       style="border-color:#CCCCCC;border-width:1px;border-style:solid;height:40px;width:117px;"></span>
                            </td>


                            <td class="bank_item">
            	                <span class="pay_pic">
                                    <input type="image" src="./themes/pay_zhifubao.gif"
                                           style="border-color:#CCCCCC;border-width:1px;border-style:solid;height:40px;width:117px;"></span>
                            </td>
                        </tr>
                        <tr>
                            <td class="bank_item">
                                <button type="button" class="submitBtn" onclick="pay()">去一卡通支付</button>
                            </td>
                            <td class="bank_item"></td>
                        </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</div>
<div id="xbox-mock" style="top: 255px; display: none; width: 500px; height: 226px; left: 381.5px; "
     class="ui-xbox">
    <div class="ui-xbox-content">
        <iframe id="xbox-iframe" name="xbox-iframe" frameborder="no" scrolling="no"
                src="./themes/xbox.htm?id=1"
                style="display: none; width: 500px; height: 226px; "></iframe>
    </div>
</div>
</body>
</html>