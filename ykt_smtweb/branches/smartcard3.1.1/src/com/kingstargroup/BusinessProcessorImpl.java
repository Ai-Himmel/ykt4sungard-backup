package com.kingstargroup;

import java.util.HashMap;

import javax.servlet.http.HttpSession;

public class BusinessProcessorImpl extends BusinessProcessor {

	public boolean businessProcess(HttpSession session, String refno,
			String personId, String personName, String amount, HashMap args) {
		// TODO Auto-generated method stub
		return true;
	}

	public boolean businessRollback(HttpSession session, String refno,
			String personId, String personName, String amount, HashMap args) {
		// TODO Auto-generated method stub
		return true;
	}

	public boolean checkThirdpart(HttpSession session, String personId,
			String personName, String amount, HashMap args) {
		// TODO Auto-generated method stub
		return true;
	}
	public HashMap getThirdpartInfo(HttpSession session, String personId,
			String personName, String amount, HashMap args) {
		// TODO Auto-generated method stub
		return null;
	}
	public String getProcessMessage(HttpSession session) {
		// TODO Auto-generated method stub
		return session.getAttribute(THIRD_PART_MESSAGE) == null ? ""
				: (String) session.getAttribute(THIRD_PART_MESSAGE);
	}



}
