<%@page pageEncoding="UTF-8" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>购物车</title>
    <link href="./themes/cart.css" rel="stylesheet" type="text/css">
    <script type="text/javascript">
        function confirmCart() {
            document.cartForm.submit();
        }
    </script>
</head>
<body>
<form action="confirm" name="cartForm" method="post">
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
<div class="shoppingcart_wrapper" id="shoppingcart">
    <a name="ddtop"></a>
    <ul class="shoppingcart_subject" id="ui_shoppingcart_title">
        <li class="row1">商品名称</li>
        <li class="row3">价格</li>
        <li class="row5">数量</li>
    </ul>
    <div name="promo_s" class="shoppingcart_general" id="collection_0" style="display: block; ">
        <ul class="shoppingcart_list">
            <li class="row00"><a><img src="./themes/<%=request.getAttribute("bookId")%>_s.jpg"></a></li>
            <li class="row11"><p><span class="name"><%=request.getAttribute("bookName")%></span>
            </p></li>
            <li class="row33">￥<%=request.getAttribute("price")%>
            </li>
            <li class="row55">
                <span>1</span></li>
        </ul>
        <div class="clear"></div>
    </div>
    <div class="shoppingcart_total" id="div_total" style="display: block; ">
        <p class="price">商品金额总计：
            <span>￥</span>
            <span id="total_account"><%=request.getAttribute("price")%></span>
        </p>

        <p id="balance">
            <button type="button" class="submitBtn" onclick="confirmCart()">结&nbsp;&nbsp;算</button>
        </p>
    </div>
</div>
</body>
</html>