<%@page pageEncoding="UTF-8" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

    <title>商品列表</title>
    <meta name="keywords" content=";">
    <link href="./themes/goods.css" rel="stylesheet" type="text/css">
    <script type="text/javascript">
        function buy(bookId, bookName, price) {
            document.goodsForm.bookId.value = bookId;
            document.goodsForm.bookName.value = bookName;
            document.goodsForm.price.value = price;
            document.goodsForm.submit();
        }
    </script>
</head>
<body>
<form action="cart" name="goodsForm" method="post">
    <input type="hidden" name="bookId"/>
    <input type="hidden" name="bookName"/>
    <input type="hidden" name="price"/>
</form>
<div class="newhead_operate">
    <ul class="newhead_operate_nav">
        <li><a href="goods">商品列表</a></li>
        <li class="newhead_separate"></li>
        <li><a href="order">我的订单</a></li>
        <li class="newhead_separate"></li>
    </ul>
</div>
<div class="search_wrap">
    <div class="search_book_list">
        <ul>
            <li>
                <div class="listitem pic">
                    <img src="./themes/21096920_l.jpg" alt="Linux内核设计的艺术：图解Linux操作系统架构设计与实现原理">
                </div>
                <div class="listitem detail">
                    <ul class="tiplist">
                        <li class="maintitle">
                            Linux内核设计的艺术：图解Linux操作系统架构设计与实现原理
                        </li>
                        <li class="subtitle"><p></p></li>
                        <li class="publicer_info">
                            新设计团队<span>/</span>2011年06月<span>/</span>机械工业出版社
                        </li>
                        <li class="describ">
                            <p>
                                关于Linux内核的书已经不计其数，但这本书却是独树一帜的，它的内容代表着Linux内核研究成果的世界顶尖级水平，它在世界范围内首次提出并阐述了操作系统设计的核心指导思想——主奴机制，这是所有操作<font
                                    class="dot">...</font></p></li>
                        <li>
                            <div class="panel operate">
                                <a href="javascript:buy(21096920,'Linux内核设计的艺术','59.20')"><img
                                        src="./themes/btn_buy.gif" alt="购 买" title="购 买"></a></div>
                            <div class="panel price">
                                <span class="price_d">￥<span class="num">59.20</span></span>
                            </div>
                        </li>
                    </ul>
                </div>
            </li>

            <li>
                <div class="listitem pic">
                    <img src="./themes/20978050_l.jpg" alt="构建嵌入式Linux系统（第二版）">
                </div>
                <div class="listitem detail">
                    <ul class="tiplist">
                        <li class="maintitle">
                            构建嵌入式Linux系统（第二版）
                        </li>
                        <li class="subtitle"><p></p></li>
                        <li class="publicer_info">
                            (加)亚荷毛尔　等著，秦云川　改编<span>/</span>2011年01月<span>/</span>中国电力出版社
                        </li>
                        <li class="describ">
                            <p>
                                虽然Linux嵌入式系统几乎无所不在，从手机到汽车的ABS系统以及净水厂都可以发现它的踪迹，但是令人惊讶的是，建立、安装和测试Linux内核以及相关工具的信息来源却少得可怜。《构建嵌入式LINUX系统(第二<font
                                    class="dot">...</font></p></li>
                        <li>
                            <div class="panel operate">
                                <a href="javascript:buy(20978050,'构建嵌入式Linux系统（第二版）','43.50')"><img
                                        src="./themes/btn_buy.gif" alt="购 买" title="购 买"></a></div>
                            <div class="panel price">
                                <span class="price_d">￥<span class="num">43.50</span></span>
                            </div>
                        </li>
                    </ul>
                </div>
            </li>
            <li>
                <div class="listitem pic">
                    <img src="./themes/20811405_l.jpg" alt="实战Linux Shell编程与服务器管理">
                </div>
                <div class="listitem detail">
                    <ul class="tiplist">
                        <li class="maintitle">
                            实战Linux Shell编程与服务器管理
                        </li>
                        <li class="subtitle"><p></p></li>
                        <li class="publicer_info">
                            卧龙小三　著，梁昌泰，张琦，黄琨　改编<span>/</span>2010年03月<span>/</span>电子工业出版社
                        </li>
                        <li class="describ">
                            <p>
                                操作系统Shell编程一直是系统管理员必备高级技能之一。主机管理的上乘之道，就在于尽量让计算机去完成所有的琐事。要达到这个境界，管理者必须具备相当程度的Shell操控能力与Shell程序设计能力，笔<font
                                    class="dot">...</font></p>
                        </li>
                        <li>
                            <div class="panel operate">
                                <a name="link_sale" href="javascript:buy(20811405,'实战Linux Shell编程与服务器管理','43.00')"><img
                                        src="./themes/btn_buy.gif" alt="购 买" title="购 买"></a></div>
                            <div class="panel price">
                                <span class="price_d">￥<span class="num">43.00</span></span>
                            </div>
                        </li>
                    </ul>
                </div>
            </li>
        </ul>
    </div>
</div>
</body>
</html>