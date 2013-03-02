package org.king.check.util;

import java.util.Iterator;
import java.util.Map;
import java.util.TimerTask;
import java.util.Calendar;
import java.text.SimpleDateFormat;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.service.WorkInfoService;
import org.king.framework.service.ServiceLocator;

public class Taskers extends TimerTask {

	private static final Log log = LogFactory.getLog(Taskers.class);

	private WorkInfoService aWorkInfoService;

	private static SimpleDateFormat formatter_yyyymm = new SimpleDateFormat(
			"yyyy-MM");

	/**
	 * 默认开始时间00:00:05； 执行周期24 hours
	 */
	public static int HOUR = 0;

	public static int MIN = 5;

	public static int MILL = 5;

	public static long PEIROD = 24 * 60 * 60 * 1000;

	/**
     * 
     */
	public static final int TYPE_YEAR = 1;

	public static final int TYPE_MONTH = 2;

	public static final int TYPE_DATE = 3;

	public static final int TYPE_HOUR = 4;

	public static final int TYPE_MINIUTE = 5;

	public static final int TYPE_SECOND = 6;

	/**
	 * 当前日期比comparedD与相差>= no（年/月/日/小时/分/秒）
	 * 
	 * @param comparedD
	 * @param type
	 * @param no
	 * @return true OR false
	 */
	public static boolean compareTime(Calendar comparedD, int type, int no) {
		boolean flag = false;
		Calendar currentD = Calendar.getInstance();
		int yearNO = 0;
		int monNO = 0;
		int dateNO = 0;
		int hourNO = 0;
		int minNO = 0;
		int secNO = 0;
		if (no > 0) {
			switch (type) {
			case Taskers.TYPE_YEAR:
				yearNO = no;
				break;
			case Taskers.TYPE_MONTH:
				monNO = no;
				break;
			case Taskers.TYPE_DATE:
				dateNO = no;
				break;
			case Taskers.TYPE_HOUR:
				hourNO = no;
				break;
			case Taskers.TYPE_MINIUTE:
				minNO = no;
				break;
			case Taskers.TYPE_SECOND:
				secNO = no;
				break;
			}
		}
		if (type >= Taskers.TYPE_YEAR) {
			if ((currentD.get(Calendar.YEAR) - comparedD.get(Calendar.YEAR)) >= yearNO) {
				flag = true;
			} else {
				flag = false;
				return flag;
			}
		}
		if (type >= Taskers.TYPE_MONTH) {
			if ((currentD.get(Calendar.MONTH) - comparedD.get(Calendar.MONTH)) >= monNO) {
				flag = true;
			} else {
				flag = false;
				return flag;
			}
		}
		if (type >= Taskers.TYPE_DATE) {
			if ((currentD.get(Calendar.DAY_OF_MONTH) - comparedD
					.get(Calendar.DAY_OF_MONTH)) >= dateNO) {
				flag = true;
			} else {
				flag = false;
				return flag;
			}
		}
		if (type >= Taskers.TYPE_HOUR) {
			if ((currentD.get(Calendar.HOUR_OF_DAY) - comparedD
					.get(Calendar.HOUR_OF_DAY)) >= hourNO) {
				flag = true;
			} else {
				flag = false;
				return flag;
			}
		}
		if (type >= Taskers.TYPE_MINIUTE) {
			if ((currentD.get(Calendar.MINUTE) - comparedD.get(Calendar.MINUTE)) >= minNO) {
				flag = true;
			} else {
				flag = false;
				return flag;
			}
		}
		if (type >= Taskers.TYPE_SECOND) {
			if ((currentD.get(Calendar.SECOND) - comparedD.get(Calendar.SECOND)) >= secNO) {
				flag = true;
			} else {
				flag = false;
				return flag;
			}
		}
		return flag;
	}

	public void runSumKQ() {
		log.debug("begin kq sum process...");
		aWorkInfoService = (WorkInfoService) ServiceLocator.getInstance().getService("workInfoService");

		Calendar cal = Calendar.getInstance();
		String sumMonth = formatter_yyyymm.format(cal.getTime());
		cal.add(Calendar.MONTH, -1);
		String sumMonth_Prior1 = formatter_yyyymm.format(cal.getTime());
		 cal = Calendar.getInstance();
		cal.add(Calendar.MONTH, -2);
		String sumMonth_Prior2 = formatter_yyyymm.format(cal.getTime());
		 cal = Calendar.getInstance();
		cal.add(Calendar.MONTH, -3);
		String sumMonth_Prior3 = formatter_yyyymm.format(cal.getTime());

		try {
			aWorkInfoService.deleteRecords(sumMonth);
			aWorkInfoService.deleteRecords(sumMonth_Prior1);
			aWorkInfoService.deleteRecords(sumMonth_Prior2);
			aWorkInfoService.deleteRecords(sumMonth_Prior3);

			List deptList = aWorkInfoService.getDeptListForKQService();

			StringBuffer deptStr = new StringBuffer();
			for (int i = 0; i < deptList.size(); i++) {
				Map deptMap = (Map) deptList.get(i);
				String dep = deptMap.get("deptId").toString();
				if (deptList.size() == 1) {
					deptStr.append(dep);
				} else {
					if (i == 0) {
						deptStr.append(dep).append("',");
					} else if (i == deptList.size() - 1) {
						deptStr.append("'").append(dep);
					} else {
						deptStr.append("'").append(dep).append("',");
					}
				}

			}
			
			//当前月的统计运算
			List kqList = aWorkInfoService.makeCheckReport(sumMonth, deptStr.toString());

			int deleterow = 0;
			Iterator reportIter = kqList.iterator();
			while (reportIter.hasNext()) {
				Map reportMap = (Map) reportIter.next();

				// 如果没有考勤记录，则把这行跳过去，不再显示
				if ("0".equals(reportMap.get("totPatch").toString())) {
					deleterow++;
					continue;
				}
				String deptName = reportMap.get("deptName").toString();
				String stuempNo = reportMap.get("stuempNo").toString();
				String custName = reportMap.get("custName").toString();
				String custType = reportMap.get("custType").toString();
				log.debug(deptName + "," + stuempNo + "," + custName + "," + custType);

				aWorkInfoService.insertRecords(sumMonth, reportMap);
			}

			//前一个月的统计运算
			List kqList_Prior1 = aWorkInfoService.makeCheckReport(sumMonth_Prior1,deptStr.toString());

			int deleterow_Prior1 = 0;
			Iterator reportIter_Prior1 = kqList_Prior1.iterator();
			while (reportIter_Prior1.hasNext()) {
				Map reportMap = (Map) reportIter_Prior1.next();

				// 如果没有考勤记录，则把这行跳过去，不再显示
				if ("0".equals(reportMap.get("totPatch").toString())) {
					deleterow_Prior1++;
					continue;
				}
				String deptName = reportMap.get("deptName").toString();
				String stuempNo = reportMap.get("stuempNo").toString();
				String custName = reportMap.get("custName").toString();
				String custType = reportMap.get("custType").toString();
				log.debug(deptName + "," + stuempNo + "," + custName + "," + custType);

				aWorkInfoService.insertRecords(sumMonth_Prior1, reportMap);
			}
			//前二个月的统计运算
			List kqList_Prior2 = aWorkInfoService.makeCheckReport(sumMonth_Prior2,
					deptStr.toString());

			int deleterow_Prior2 = 0;
			Iterator reportIter_Prior2 = kqList_Prior2.iterator();
			while (reportIter_Prior2.hasNext()) {
				Map reportMap = (Map) reportIter_Prior2.next();

				// 如果没有考勤记录，则把这行跳过去，不再显示
				if ("0".equals(reportMap.get("totPatch").toString())) {
					deleterow_Prior2++;
					continue;
				}
				String deptName = reportMap.get("deptName").toString();
				String stuempNo = reportMap.get("stuempNo").toString();
				String custName = reportMap.get("custName").toString();
				String custType = reportMap.get("custType").toString();
				log.debug(deptName + "," + stuempNo + "," + custName + "," + custType);

				aWorkInfoService.insertRecords(sumMonth_Prior2, reportMap);
			}
			//前三个月的统计运算
			List kqList_Prior3 = aWorkInfoService.makeCheckReport(sumMonth_Prior3,
					deptStr.toString());

			int deleterow_Prior3 = 0;
			Iterator reportIter_Prior3 = kqList_Prior3.iterator();
			while (reportIter_Prior3.hasNext()) {
				Map reportMap = (Map) reportIter_Prior3.next();

				// 如果没有考勤记录，则把这行跳过去，不再显示
				if ("0".equals(reportMap.get("totPatch").toString())) {
					deleterow_Prior3++;
					continue;
				}
				String deptName = reportMap.get("deptName").toString();
				String stuempNo = reportMap.get("stuempNo").toString();
				String custName = reportMap.get("custName").toString();
				String custType = reportMap.get("custType").toString();
				log.debug(deptName + "," + stuempNo + "," + custName + "," + custType);

				aWorkInfoService.insertRecords(sumMonth_Prior3, reportMap);
			}
			
			aWorkInfoService.deleteHistoryRecords();

		} catch (Exception e1) {
			e1.printStackTrace();
		}
		log.debug("end kq sum process...");

	}

	public void run() {
        Calendar cal = Calendar.getInstance();
        int week = cal.get(Calendar.DAY_OF_WEEK);
        if ((week !=1)&&(week!=7)){
            runSumKQ();
        }
	}

}
