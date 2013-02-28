package org.king.servlet;

import org.apache.log4j.Logger;
import org.king.domain.Order;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-11-13
 */
public class OrderServlet extends HttpServlet {
    private static final Logger logger = Logger.getLogger(OrderServlet.class);

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        listOrder(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        listOrder(request, response);
    }

    private void listOrder(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Order> orders = (List<Order>) request.getSession().getAttribute("orders");
        if (orders == null) {
            orders = new ArrayList<Order>();
            request.getSession().setAttribute("orders", orders);
        }
        getServletConfig().getServletContext().getRequestDispatcher("/WEB-INF/pages/order.jsp").forward(request, response);
    }
}
