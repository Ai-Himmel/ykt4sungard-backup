package com.kingstar.basetask;

public class ApplicationStateConstants {

	public static final int NORMAL = 1;

	public static final int ERROR = 2;

	public String getAppStatus(int i) {
		String s = "";

		if (NORMAL == i) {
			s = "����";
		}
		if (ERROR == i) {
			s = "����";

		} else {
			s = "δ֪״̬";
		}
		return s;

	}
}
