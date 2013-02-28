package org.king.servlet;

import org.apache.log4j.Logger;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * .
 * User: Yiming.You
 * Date: 2011-11-7
 */
public class CartServlet extends HttpServlet {
    private static final Logger logger = Logger.getLogger(CartServlet.class);

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        cart(request, response);
    }

    private void cart(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String bookId = request.getParameter("bookId");
        String bookName = request.getParameter("bookName");
        String price = request.getParameter("price");
        request.setAttribute("bookId", bookId);
        request.setAttribute("bookName", bookName);
        request.setAttribute("price", price);

        getServletConfig().getServletContext().getRequestDispatcher("/WEB-INF/pages/cart.jsp").forward(request, response);
    }
}
