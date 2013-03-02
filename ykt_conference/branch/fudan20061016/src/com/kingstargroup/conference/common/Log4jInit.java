package com.kingstargroup.conference.common;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.PropertyConfigurator;

public class Log4jInit extends HttpServlet {

	public void init() {
		System.out.println("................log4j beginstart");
		String prefix = getServletContext().getRealPath("/");
		String file = getInitParameter("log4j");
		// if the log4j-init-file is not set, then no point in trying
		System.out.println("................log4j endstart");
		if (file != null) {
			PropertyConfigurator.configure(prefix + file);
		}
	}

	public void doGet(HttpServletRequest req, HttpServletResponse res) {
		
	}
}