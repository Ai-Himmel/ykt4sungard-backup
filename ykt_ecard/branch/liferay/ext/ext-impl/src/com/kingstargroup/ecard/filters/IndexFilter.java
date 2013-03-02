package com.kingstargroup.ecard.filters;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;

import org.apache.log4j.Logger;
import org.stringtree.util.StringUtils;

import com.kingstargroup.ecard.KSConfiguration;

public class IndexFilter implements Filter {
	private static Logger log = Logger.getLogger(IndexFilter.class);
	private String customIndex;
	private String indexUrl;

	public void destroy() {
	}

	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		HttpServletRequest req = (HttpServletRequest) request;
		String queryString = req.getQueryString();
		log.debug(queryString);
		if ("true".equals(customIndex)) {
			if (req.getSession().getAttribute("LOGIN_ERROR") != null) {
				// ��½ʧ��֮��LOGIN_ERROR��Ϊ��
				request.getRequestDispatcher(indexUrl).forward(request, response);
			} else {
				if (StringUtils.isBlank(queryString)) {
					// ������ҳ���ߵ�½ҳ��ʱqueryStringΪ��
					request.getRequestDispatcher(indexUrl).forward(request, response);
				} else if (request.getParameter("id") == null && request.getParameter("filter") == null && queryString.indexOf("extWiscomLogin") == -1) {
					// ���û�����ص���ҳʱ����ת���Զ�����ҳ
					request.getRequestDispatcher(indexUrl).forward(request, response);
				} else {
					chain.doFilter(request, response);
				}
			}
		} else {
			chain.doFilter(request, response);
		}
	}

	public void init(FilterConfig conf) throws ServletException {
		customIndex = KSConfiguration.getInstance().getProperty("customIndex");
		indexUrl = KSConfiguration.getInstance().getProperty("indexUrl");
	}

}
