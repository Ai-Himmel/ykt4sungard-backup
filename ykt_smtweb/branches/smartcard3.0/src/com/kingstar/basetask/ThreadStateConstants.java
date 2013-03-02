package com.kingstar.basetask;

public class ThreadStateConstants {

	// thread status
	public static final int START = 0;

	public static final int RUN = 1;

	public static final int CLOSED = 2;

	public static final int ERROR = 3;

	public static final String stateDescr[] = { "START", "RUN", "CLOSED",
			"ERROR" };

	public String getThreadStatus(int i) {
		String s = "";

		if (START == i) {
			s = "��ʼ";
		}
		if (RUN == i) {
			s = "����";

		}
		if (CLOSED == i) {
			s = "�ر�";

		}
		if (ERROR == i) {
			s = "����";

		} else {
			s = "δ֪״̬";
		}
		return s;

	}
}