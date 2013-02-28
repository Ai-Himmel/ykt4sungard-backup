<%@ page import="org.king.domain.Order" %>
<%@ page import="java.util.List" %>
<%@page pageEncoding="UTF-8" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>我的订单</title>
    <link href="./themes/order.css" rel="stylesheet" type="text/css">
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
<div class="clear"></div>
<div class="wrapper">
    <div id="orderList" class="centersidebar">
        <div class="myddorder_tab">
            <a class="current">我的所有订单</a>

            <div class="clear">
            </div>
        </div>
        <ul class="myddorder_list">
            <li class="myddorder_title">
                <span class="list_order">订单号</span>
                <span class="list_name">收货人</span>
                <span class="list_way">付款方式</span>
                <span class="list_total">订单总金额</span>
                <span class="list_status">订单状态</span>
                <span class="list_time">下单日期</span>
                <span class="list_time">下单时间</span>
            </li>
            <%
                List<Order> orders = (List<Order>) request.getSession().getAttribute("orders");
                for (Order order : orders) {
            %>
            <li>
                <span class="list_order" title="<%=order.getOid()%>"><%=order.getOid()%></span>
                <span class="list_name" title="Shirely">Shirely</span>
                <span class="list_way" title="一卡通电子支付">一卡通电子支付</span>
                <span class="list_total">￥<%=order.getAmount()%></span>
                <span class="list_status"><%=order.getStatus()%></span>
                <span class="list_time"><%=order.getDate()%></span>
                <span class="list_time"><%=order.getTime()%></span>
            </li>
            <%
                }
            %>
        </ul>
        <div class="fanye">
            <div>（共<%=orders.size()%>条）</div>
        </div>
    </div>
</div>
</body>
</html>