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
			s = "开始";
		}
		if (RUN == i) {
			s = "运行";

		}
		if (CLOSED == i) {
			s = "关闭";

		}
		if (ERROR == i) {
			s = "错误";

		} else {
			s = "未知状态";
		}
		return s;

	}
}