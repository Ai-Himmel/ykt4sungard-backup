<%@page pageEncoding="UTF-8" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>订单结算</title>
    <link href="./themes/confirm.css" rel="stylesheet" type="text/css">
    <script type="text/javascript">
        function book() {
            document.confirmForm.submit();
        }
    </script>
</head>
<body>
<form action="book" name="confirmForm" method="post">
    <input type="hidden" name="bookId" value="<%=request.getAttribute("bookId")%>"/>
    <input type="hidden" name="bookName" value="<%=request.getAttribute("bookName")%>"/>
    <input type="hidden" name="price" value="<%=request.getAttribute("price")%>"/>
</form>
<div class="newhead_operate">
    <ul class="newhead_operate_nav">
        <li><a href="goods">商品列表</a></li>
        <li class="newhead_separate"></li>
        <li><a href="order">我的订单</a></li>
        <li class="newhead_separate"></li>
    </ul>
</div>
<div class="shoppingcart_wrapper">
    <div class="shoppingcart_footer_experience">请确认以下信息，然后提交订单</div>

    <div class="clearing_border">
        <div id="div_consignee">
            <div class="refer_m"><h4>收货人信息</h4>
                <ul>
                    <li>Shirely，中国，上海，浦东新区</li>
                </ul>
            </div>
        </div>
        <div id="div_shipment">
            <div class="refer_m"><h4>送货方式</h4>
                <ul>
                    <li>普通快递送货上门，周六日及公众假期</li>
                </ul>
            </div>
        </div>
        <div id="div_payment">
            <div class="refer_m"><h4>付款方式</h4>
                <ul>
                    <li id="li_pay_id_name" class="li_pay_id_name_1">一卡通电子支付</li>
                </ul>
            </div>
        </div>
        <div class="refer_m refer_m2"><h4>商品清单</h4>

            <div class="business_box">
                <div class="business_box_border">
                    <div id="rpt_cart_items">
                        <ul class="shoppingcart_subject">
                            <li class="row1">商品名称</li>
                            <li class="row2">所在仓库</li>
                            <li class="row3">价格</li>
                            <li class="row5">数量</li>
                            <li class="row6">小计</li>
                        </ul>
                        <div class="shoppingcart_general">
                            <ul class="shoppingcart_list">
                                <li class="row0">20866026</li>
                                <li class="row1"><%=request.getAttribute("bookName")%>
                                </li>
                                <li class="row2">上海</li>
                                <li class="row3">￥<%=request.getAttribute("price")%>
                                </li>
                                <li class="row5">1</li>
                                <li class="row6">￥<%=request.getAttribute("price")%>
                                </li>
                            </ul>
                            <br class="clear"><span class="price_charge_border"></span></div>
                    </div>
                    <div class="price_charge"><p class="p_charge1">商品金额总计：￥<%=request.getAttribute("price")%>
                    </p>

                        <p class="p_charge1">运费：￥0.00</p>

                        <p class="change_total">您需支付：￥<span
                                id="sp_payable"><%=request.getAttribute("price")%></span></span>
                        </p></div>
                </div>
            </div>
            <br class="clear">

            <div class="item">
                <button type="button" class="submitBtn" onclick="book()">提交订单</button>
            </div>
            <div class="clear"></div>
        </div>
    </div>
</div>
</body>
</html>