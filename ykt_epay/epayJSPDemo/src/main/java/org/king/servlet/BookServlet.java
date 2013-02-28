package org.king.servlet;

import org.apache.log4j.Logger;
import org.king.common.Configuration;
import org.king.common.Constant;
import org.king.domain.Item;
import org.king.domain.Order;
import org.king.utils.DateUtil;
import org.king.utils.MD5;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-11-8
 */
public class BookServlet extends HttpServlet {
    private static final Logger logger = Logger.getLogger(BookServlet.class);

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        book(request, response);
    }

    private void book(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        //generate order
        String bookId = request.getParameter("bookId");
        String bookName = request.getParameter("bookName");
        String price = request.getParameter("price");
        Item item = new Item(Long.valueOf(bookId), bookName, Double.valueOf(price));

        Date now = new Date();
        String oid = String.valueOf(now.getTime());
        Order order = new Order(oid);
        order.setAmount(Double.valueOf(price));
        order.setDate(DateUtil.getDate(now));
        order.setTime(DateUtil.getTime(now));
        order.setStatus("等待付款");
        order.setRemark("通过电子账户付款");
        order.addItem(item);
        String shopid = Configuration.getProperty(Constant.SHOPID, "");
        String key = Configuration.getProperty(Constant.KEY, "");
        String epayUrl = Configuration.getProperty(Constant.EPAYURL, "");
        String server = request.getScheme() + "://" + request.getLocalAddr() + ":" + request.getLocalPort();
        String context = request.getContextPath();
        if (!context.startsWith("/")) {
            context = "/" + context;
        }
        if (!context.endsWith("/")) {
            context = context + "/";
        }
        String v_url = server + context + "result";
        logger.info("v_url = " + v_url);
        logger.info("encode string:" + shopid + oid + order.getAmount().toString() + order.getCurrency() + v_url + key);
        String code = MD5.MD5Encode(shopid + oid + order.getAmount().toString() + order.getCurrency() + v_url + key);

        request.setAttribute("order", order);
        request.setAttribute("epayUrl", epayUrl);
        request.setAttribute("v_url", v_url);
        request.setAttribute("v_code", code);
        request.setAttribute("v_shopid", shopid);

        List<Order> orders = (List<Order>) request.getSession().getAttribute("orders");
        if (orders == null) {
            orders = new ArrayList<Order>();
            request.getSession().setAttribute("orders", orders);
        }
        orders.add(order);

        getServletConfig().getServletContext().getRequestDispatcher("/WEB-INF/pages/book.jsp").forward(request, response);
    }
}
