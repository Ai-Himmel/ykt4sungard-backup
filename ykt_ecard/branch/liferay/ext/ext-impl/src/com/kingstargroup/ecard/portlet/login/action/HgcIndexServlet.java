package com.kingstargroup.ecard.portlet.login.action;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.portlet.information.service.EcardInformationServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;

public class HgcIndexServlet extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		index(request, response);
	}

	@Override
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		index(request, response);
	}

	protected void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		List newsList = new ArrayList();
		List lostList = new ArrayList();
		try {
			ResultPage newsPage = EcardInformationServiceUtil.list(0, EcardConstants.INFORMATION_NEWS_TYPE, 6);
			newsList = newsPage.getList();
			ResultPage lostPage = EcardInformationServiceUtil.list(0, EcardConstants.INFORMATION_LOSTFOUND_TYPE, 6);
			lostList = lostPage.getList();
		} catch (PortalException e) {
			e.printStackTrace();
		}
		request.setAttribute("newsList", newsList);
		request.setAttribute("lostList", lostList);
		request.getRequestDispatcher("/html/index_hgc.jsp").forward(request, response);
	}
}
