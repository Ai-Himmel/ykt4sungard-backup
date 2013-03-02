package com.kingstargroup.ecard.portlet.shop.service;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.exceptions.BccException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.hibernate.device.VTerm;
import com.kingstargroup.ecard.hibernate.shop.AccountDetailResult;
import com.kingstargroup.ecard.hibernate.shop.ShopDinnerReportResult;
import com.kingstargroup.ecard.hibernate.shop.ShopDinnerTotalReportResult;
import com.kingstargroup.ecard.hibernate.shop.StoreLimit;
import com.kingstargroup.ecard.hibernate.shop.StoreLimitId;
import com.kingstargroup.ecard.util.BccUtil;
import com.kingstargroup.ecard.util.StringRegUtil;
import com.liferay.portal.kernel.util.StringUtil;

public class ShopServiceImpl extends ShopServiceBase {

	public List createShopJSList(String rootId) throws PortalException {
		return shopPersistence.createShopJSList(rootId);
	}

	public String getStoreLimitString(long userid) throws PortalException {
		return StringUtil.merge(shopPersistence.getStoreList(String
				.valueOf(userid)), ",");
	}

	public void updateStoreLimit(String userid, String storeLimitString)
			throws PortalException {
		shopPersistence.deleteStoreList(userid);

		String storeLimits[] = StringUtil.split(storeLimitString, ",");
		String storedStr = ",";
		for (int i = 0; i < storeLimits.length; i++) {
			if (storedStr.indexOf("," + storeLimits[i] + ",") == -1) {
				StoreLimitId key = new StoreLimitId();
				key.setStoreCode(storeLimits[i]);
				key.setOperCode(userid);
				StoreLimit storelimit = new StoreLimit(key);
				shopPersistence.save(storelimit);
				storedStr += storeLimits[i] + ",";
			}
		}
	}

	public List getShopDinnerReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"shop_dinner_report", 846708);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List shopReportList = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						shopid);// 商户号
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						shoplevel);// 商户级别

				bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),
						begindate.getBytes());// 开始日期
				bcc.SetStringFieldByName(xpackhandle, 0, "sdate2".getBytes(),
						enddate.getBytes());// 结束日期

				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 3000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String shopname = "";
							String devicename = "";
							String mealname = "";
							int transcnt = 0;
							double cramt = 0;
							double dramt = 0;
							double damt3 = 0;

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];

							bcc.GetStringFieldByName(xpackhandle, i,
									"vsvarstr1".getBytes(), byteStrRec, 256);
							shopname = BccUtil.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i,
									"sbankname".getBytes(), byteStrRec, 81);
							devicename = BccUtil.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i,
									"sall_name".getBytes(), byteStrRec, 81);
							mealname = BccUtil.getStringFromByte(byteStrRec);

							bcc.GetIntFieldByName(xpackhandle, i, "lvol0"
									.getBytes(), intRec);
							transcnt = intRec[0];

							bcc.GetDoubleFieldByName(xpackhandle, i, "damt2"
									.getBytes(), doubleRec);
							cramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt1"
									.getBytes(), doubleRec);
							dramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt3"
									.getBytes(), doubleRec);
							damt3 = doubleRec[0];
							ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
							shopname = StringRegUtil.replaceStartsWithSpace(
									shopname, "&nbsp;&nbsp;");
							shopdinnerreportRt.setShopname(shopname);
							shopdinnerreportRt.setDevicename(devicename);
							shopdinnerreportRt.setMealname(mealname);
							shopdinnerreportRt.setTranscnt(transcnt);
							shopdinnerreportRt.setCramt(cramt);
							shopdinnerreportRt.setDramt(dramt);
							shopdinnerreportRt.setDamt3(damt3);
							shopReportList.add(shopdinnerreportRt);
						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;
							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);

							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String shopname = "";
										String devicename = "";
										String mealname = "";
										int transcnt = 0;
										double cramt = 0;
										double dramt = 0;
										double damt3 = 0;

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];

										bcc.GetStringFieldByName(xpackhandle,
												i, "vsvarstr1".getBytes(),
												byteStrRec, 256);
										shopname = BccUtil
												.getStringFromByte(byteStrRec);
										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sbankname".getBytes(),
												byteStrRec, 81);
										devicename = BccUtil
												.getStringFromByte(byteStrRec);
										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sall_name".getBytes(),
												byteStrRec, 81);
										mealname = BccUtil
												.getStringFromByte(byteStrRec);

										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol0".getBytes(), intRec);
										transcnt = intRec[0];

										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt2".getBytes(),
												doubleRec);
										cramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt1".getBytes(),
												doubleRec);
										dramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt3".getBytes(),
												doubleRec);
										damt3 = doubleRec[0];
										ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
										shopname = StringRegUtil
												.replaceStartsWithSpace(
														shopname,
														"&nbsp;&nbsp;");
										shopdinnerreportRt
												.setShopname(shopname);
										shopdinnerreportRt
												.setDevicename(devicename);
										shopdinnerreportRt
												.setMealname(mealname);
										shopdinnerreportRt
												.setTranscnt(transcnt);
										shopdinnerreportRt.setCramt(cramt);
										shopdinnerreportRt.setDramt(dramt);
										shopdinnerreportRt.setDamt3(damt3);
										shopReportList.add(shopdinnerreportRt);
									}

								}

							}
						}
						return shopReportList;

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("未知错误");
						}

					}

				} else {
					// 请求失败
					throw new BccException("请求失败");
				}
			} else {
				throw new BccException("cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("动态库加载失败，请稍后重试！");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}

	public List getShopTodayDinnerReportList(int shopid, int shoplevel)
			throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"shop_today_dinner_report", 846110);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List shopReportList = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						shopid);// 商户号
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						shoplevel);// 商户级别

				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String shopname = "";
							String summary = "";
							int transcnt = 0;
							double cramt = 0;
							double dramt = 0;
							double damt3 = 0;

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];
							// 商户名
							bcc.GetStringFieldByName(xpackhandle, i,
									"vsvarstr1".getBytes(), byteStrRec, 256);
							shopname = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							// 摘要
							bcc.GetStringFieldByName(xpackhandle, i, "snote"
									.getBytes(), byteStrRec, 81);
							summary = BccUtil.getStringFromByte(byteStrRec);
							// 交易次数
							bcc.GetIntFieldByName(xpackhandle, i, "lvol0"
									.getBytes(), intRec);
							transcnt = intRec[0];
							// 收入
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt2"
									.getBytes(), doubleRec);
							cramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 支出
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt1"
									.getBytes(), doubleRec);
							dramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 结算
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt3"
									.getBytes(), doubleRec);
							damt3 = doubleRec[0];
							ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
							shopdinnerreportRt.setShopname(shopname);
							shopdinnerreportRt.setSummary(summary);
							shopdinnerreportRt.setTranscnt(transcnt);
							shopdinnerreportRt.setCramt(cramt);
							shopdinnerreportRt.setDramt(dramt);
							shopdinnerreportRt.setDamt3(damt3);
							shopReportList.add(shopdinnerreportRt);
						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;

							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);
							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String shopname = "";
										String summary = "";
										int transcnt = 0;
										double cramt = 0;
										double dramt = 0;
										double damt3 = 0;

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];

										bcc.GetStringFieldByName(xpackhandle,
												i, "vsvarstr1".getBytes(),
												byteStrRec, 256);
										shopname = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "snote".getBytes(),
												byteStrRec, 81);
										summary = BccUtil
												.getStringFromByte(byteStrRec);

										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol0".getBytes(), intRec);
										transcnt = intRec[0];

										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt2".getBytes(),
												doubleRec);
										cramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt1".getBytes(),
												doubleRec);
										dramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt3".getBytes(),
												doubleRec);
										damt3 = doubleRec[0];
										ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
										shopdinnerreportRt
												.setShopname(shopname);
										shopdinnerreportRt.setSummary(summary);
										shopdinnerreportRt
												.setTranscnt(transcnt);
										shopdinnerreportRt.setCramt(cramt);
										shopdinnerreportRt.setDramt(dramt);
										shopdinnerreportRt.setDamt3(damt3);
										shopReportList.add(shopdinnerreportRt);
									}

								}

							}
						}
						return shopReportList;

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("未知错误");
						}

					}

				} else {
					// 请求失败
					throw new BccException("请求失败");
				}
			} else {
				throw new BccException("cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("动态库加载失败，请稍后重试！");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}

	public List getShopDinnerTotalReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"shop_dinner_total_report", 846710);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List shopDinnerTotalReportList = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						shopid);// 商户号
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						shoplevel);// 商户级别

				bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),
						begindate.getBytes());// 开始日期
				bcc.SetStringFieldByName(xpackhandle, 0, "sdate2".getBytes(),
						enddate.getBytes());// 结束日期

				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String shopname = "";
							int transcnt1 = 0;
							int transcnt2 = 0;
							int transcnt3 = 0;
							int transcnt4 = 0;
							int totalcnt = 0;

							double transamt1 = 0;
							double transamt2 = 0;
							double transamt3 = 0;
							double transamt4 = 0;
							double totalamt = 0;

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];

							bcc.GetStringFieldByName(xpackhandle, i,
									"vsvarstr1".getBytes(), byteStrRec, 256);
							shopname = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, i, "lvol6"
									.getBytes(), intRec);
							transcnt1 = intRec[0];

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, i, "lvol7"
									.getBytes(), intRec);
							transcnt2 = intRec[0];

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, i, "lvol8"
									.getBytes(), intRec);
							transcnt3 = intRec[0];

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, i, "lvol9"
									.getBytes(), intRec);
							transcnt4 = intRec[0];

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, i, "lvol10"
									.getBytes(), intRec);
							totalcnt = intRec[0];

							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt6"
									.getBytes(), doubleRec);
							transamt1 = doubleRec[0];

							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt7"
									.getBytes(), doubleRec);
							transamt2 = doubleRec[0];

							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt8"
									.getBytes(), doubleRec);
							transamt3 = doubleRec[0];

							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt9"
									.getBytes(), doubleRec);
							transamt4 = doubleRec[0];

							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt10"
									.getBytes(), doubleRec);
							totalamt = doubleRec[0];

							ShopDinnerTotalReportResult shopdinnertotalreportRt = new ShopDinnerTotalReportResult();
							shopname = StringRegUtil.replaceStartsWithSpace(
									shopname, "&nbsp;&nbsp;");
							shopdinnertotalreportRt.setShopname(shopname);
							shopdinnertotalreportRt.setTranscnt1(transcnt1);
							shopdinnertotalreportRt.setTranscnt2(transcnt2);
							shopdinnertotalreportRt.setTranscnt3(transcnt3);
							shopdinnertotalreportRt.setTranscnt4(transcnt4);
							shopdinnertotalreportRt.setTotalcnt(totalcnt);
							shopdinnertotalreportRt.setTransamt1(transamt1);
							shopdinnertotalreportRt.setTransamt2(transamt2);
							shopdinnertotalreportRt.setTransamt3(transamt3);
							shopdinnertotalreportRt.setTransamt4(transamt4);
							shopdinnertotalreportRt.setTotalamt(totalamt);

							shopDinnerTotalReportList
									.add(shopdinnertotalreportRt);
						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;

							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);

							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String shopname = "";
										int transcnt1 = 0;
										int transcnt2 = 0;
										int transcnt3 = 0;
										int transcnt4 = 0;
										int totalcnt = 0;

										double transamt1 = 0;
										double transamt2 = 0;
										double transamt3 = 0;
										double transamt4 = 0;
										double totalamt = 0;

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];

										bcc.GetStringFieldByName(xpackhandle,
												i, "vsvarstr1".getBytes(),
												byteStrRec, 256);
										shopname = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(intRec, 0);
										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol6".getBytes(), intRec);
										transcnt1 = intRec[0];

										Arrays.fill(intRec, 0);
										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol7".getBytes(), intRec);
										transcnt2 = intRec[0];

										Arrays.fill(intRec, 0);
										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol8".getBytes(), intRec);
										transcnt3 = intRec[0];

										Arrays.fill(intRec, 0);
										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol9".getBytes(), intRec);
										transcnt4 = intRec[0];

										Arrays.fill(intRec, 0);
										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol10".getBytes(), intRec);
										totalcnt = intRec[0];

										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt6".getBytes(),
												doubleRec);
										transamt1 = doubleRec[0];

										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt7".getBytes(),
												doubleRec);
										transamt2 = doubleRec[0];

										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt8".getBytes(),
												doubleRec);
										transamt3 = doubleRec[0];

										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt9".getBytes(),
												doubleRec);
										transamt4 = doubleRec[0];

										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt10".getBytes(),
												doubleRec);
										totalamt = doubleRec[0];

										ShopDinnerTotalReportResult shopdinnertotalreportRt = new ShopDinnerTotalReportResult();
										shopname = StringRegUtil
												.replaceStartsWithSpace(
														shopname,
														"&nbsp;&nbsp;");
										shopdinnertotalreportRt
												.setShopname(shopname);
										shopdinnertotalreportRt
												.setTranscnt1(transcnt1);
										shopdinnertotalreportRt
												.setTranscnt2(transcnt2);
										shopdinnertotalreportRt
												.setTranscnt3(transcnt3);
										shopdinnertotalreportRt
												.setTranscnt4(transcnt4);
										shopdinnertotalreportRt
												.setTotalcnt(totalcnt);
										shopdinnertotalreportRt
												.setTransamt1(transamt1);
										shopdinnertotalreportRt
												.setTransamt2(transamt2);
										shopdinnertotalreportRt
												.setTransamt3(transamt3);
										shopdinnertotalreportRt
												.setTransamt4(transamt4);
										shopdinnertotalreportRt
												.setTotalamt(totalamt);

										shopDinnerTotalReportList
												.add(shopdinnertotalreportRt);
									}

								}

							}
						}
						return shopDinnerTotalReportList;

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("未知错误");
						}

					}

				} else {
					// 请求失败
					throw new BccException("请求失败");
				}
			} else {
				throw new BccException("cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("动态库加载失败，请稍后重试！");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}

	public List getShopPosCatalogReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"shop_pos_catalog_report", 846706);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List shopReportList = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						shopid);// 商户号
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						shoplevel);// 商户级别

				bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),
						begindate.getBytes());// 开始日期
				bcc.SetStringFieldByName(xpackhandle, 0, "sdate2".getBytes(),
						enddate.getBytes());// 结束日期

				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String shopname = "";
							int deviceid = 0;
							String devicename = "";
							String transdate = "";
							String summary = "";
							int transcnt = 0;
							double cramt = 0;
							double dramt = 0;
							double damt3 = 0;

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];
							// 商户名
							bcc.GetStringFieldByName(xpackhandle, i,
									"vsvarstr1".getBytes(), byteStrRec, 256);
							shopname = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(intRec, 0);
							// 终端id
							bcc.GetIntFieldByName(xpackhandle, i,
									"lwithdraw_flag".getBytes(), intRec);
							deviceid = intRec[0];

							Arrays.fill(byteStrRec, (byte) 0);
							// 终端名称
							bcc.GetStringFieldByName(xpackhandle, i,
									"sbankname".getBytes(), byteStrRec, 81);
							devicename = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							// 终端名称
							bcc.GetStringFieldByName(xpackhandle, i, "sdate0"
									.getBytes(), byteStrRec, 9);
							transdate = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							// 摘要
							bcc.GetStringFieldByName(xpackhandle, i, "snote"
									.getBytes(), byteStrRec, 81);
							summary = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(intRec, 0);
							// 交易次数
							bcc.GetIntFieldByName(xpackhandle, i, "lvol0"
									.getBytes(), intRec);
							transcnt = intRec[0];
							// 收入
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt2"
									.getBytes(), doubleRec);
							cramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 支出
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt1"
									.getBytes(), doubleRec);
							dramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 结算
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt3"
									.getBytes(), doubleRec);
							damt3 = doubleRec[0];
							ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
							shopdinnerreportRt.setShopname(shopname);
							shopdinnerreportRt.setTransdate(transdate);
							shopdinnerreportRt.setDeviceid(deviceid);
							shopdinnerreportRt.setDevicename(devicename);
							shopdinnerreportRt.setSummary(summary);
							shopdinnerreportRt.setTranscnt(transcnt);
							shopdinnerreportRt.setCramt(cramt);
							shopdinnerreportRt.setDramt(dramt);
							shopdinnerreportRt.setDamt3(damt3);
							shopReportList.add(shopdinnerreportRt);
						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;

							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);

							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String shopname = "";
										int deviceid = 0;
										String devicename = "";
										String transdate = "";
										String summary = "";
										int transcnt = 0;
										double cramt = 0;
										double dramt = 0;
										double damt3 = 0;

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];
										// 商户名
										bcc.GetStringFieldByName(xpackhandle,
												i, "vsvarstr1".getBytes(),
												byteStrRec, 256);
										shopname = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(intRec, 0);
										// 终端id
										bcc.GetIntFieldByName(xpackhandle, i,
												"lwithdraw_flag".getBytes(),
												intRec);
										deviceid = intRec[0];

										Arrays.fill(byteStrRec, (byte) 0);
										// 终端名称
										bcc.GetStringFieldByName(xpackhandle,
												i, "sbankname".getBytes(),
												byteStrRec, 81);
										devicename = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										// 终端名称
										bcc.GetStringFieldByName(xpackhandle,
												i, "sdate0".getBytes(),
												byteStrRec, 9);
										transdate = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										// 摘要
										bcc.GetStringFieldByName(xpackhandle,
												i, "snote".getBytes(),
												byteStrRec, 81);
										summary = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(intRec, 0);
										// 交易次数
										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol0".getBytes(), intRec);
										transcnt = intRec[0];
										// 收入
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt2".getBytes(),
												doubleRec);
										cramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										// 支出
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt1".getBytes(),
												doubleRec);
										dramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										// 结算
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt3".getBytes(),
												doubleRec);
										damt3 = doubleRec[0];
										ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
										shopdinnerreportRt
												.setShopname(shopname);
										shopdinnerreportRt
												.setTransdate(transdate);
										shopdinnerreportRt
												.setDeviceid(deviceid);
										shopdinnerreportRt
												.setDevicename(devicename);
										shopdinnerreportRt.setSummary(summary);
										shopdinnerreportRt
												.setTranscnt(transcnt);
										shopdinnerreportRt.setCramt(cramt);
										shopdinnerreportRt.setDramt(dramt);
										shopdinnerreportRt.setDamt3(damt3);
										shopReportList.add(shopdinnerreportRt);
									}

								}

							}
						}
						return shopReportList;

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("未知错误");
						}

					}

				} else {
					// 请求失败
					throw new BccException("请求失败");
				}
			} else {
				throw new BccException("cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("动态库加载失败，请稍后重试！");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}

	public List getShopCatalogReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"shop_catalog_report", 846706);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List shopReportList = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						shopid);// 商户号
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						shoplevel);// 商户级别

				bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),
						begindate.getBytes());// 开始日期
				bcc.SetStringFieldByName(xpackhandle, 0, "sdate2".getBytes(),
						enddate.getBytes());// 结束日期

				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String shopname = "";
							String accdate = "";
							String summary = "";
							int transcnt = 0;
							double cramt = 0;
							double dramt = 0;
							double damt3 = 0;
							int num = 0;

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];
							// 商户名
							bcc.GetStringFieldByName(xpackhandle, i,
									"vsvarstr1".getBytes(), byteStrRec, 256);
							shopname = BccUtil.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							// 日期
							bcc.GetStringFieldByName(xpackhandle, i, "sdate3"
									.getBytes(), byteStrRec, 81);
							accdate = BccUtil.getStringFromByte(byteStrRec);
							Arrays.fill(byteStrRec, (byte) 0);
							// 摘要
							bcc.GetStringFieldByName(xpackhandle, i, "snote"
									.getBytes(), byteStrRec, 81);
							summary = BccUtil.getStringFromByte(byteStrRec);
							// 交易次数
							bcc.GetIntFieldByName(xpackhandle, i, "lvol0"
									.getBytes(), intRec);
							transcnt = intRec[0];
							// 收入
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt2"
									.getBytes(), doubleRec);
							cramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 支出
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt1"
									.getBytes(), doubleRec);
							dramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 结算
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt3"
									.getBytes(), doubleRec);
							damt3 = doubleRec[0];
							//交易人次
							bcc.GetIntFieldByName(xpackhandle, i, "lvol1"
									.getBytes(), intRec);
							num = intRec[0];
							ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
							shopdinnerreportRt.setShopname(shopname);
							shopdinnerreportRt.setTransdate(accdate);
							shopdinnerreportRt.setSummary(summary);
							shopdinnerreportRt.setTranscnt(transcnt);
							shopdinnerreportRt.setCramt(cramt);
							shopdinnerreportRt.setDramt(dramt);
							shopdinnerreportRt.setDamt3(damt3);
							shopdinnerreportRt.setNum(num);
							shopReportList.add(shopdinnerreportRt);
						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;

							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);

							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String shopname = "";
										String accdate = "";
										String summary = "";
										int transcnt = 0;
										double cramt = 0;
										double dramt = 0;
										double damt3 = 0;
										int num = 0;

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];

										bcc.GetStringFieldByName(xpackhandle,
												i, "vsvarstr1".getBytes(),
												byteStrRec, 256);
										shopname = BccUtil
												.getStringFromByte(byteStrRec);
										
										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle, i, "sdate3"
												.getBytes(), byteStrRec, 81);
										accdate = BccUtil.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "snote".getBytes(),
												byteStrRec, 81);
										summary = BccUtil
												.getStringFromByte(byteStrRec);

										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol0".getBytes(), intRec);
										transcnt = intRec[0];

										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt2".getBytes(),
												doubleRec);
										cramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt1".getBytes(),
												doubleRec);
										dramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt3".getBytes(),
												doubleRec);
										damt3 = doubleRec[0];
										//交易人次
										bcc.GetIntFieldByName(xpackhandle, i, "lvol1"
												.getBytes(), intRec);
										num = intRec[0];
										ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
										shopdinnerreportRt.setShopname(shopname);
										shopdinnerreportRt.setTransdate(accdate);
										shopdinnerreportRt.setSummary(summary);
										shopdinnerreportRt.setTranscnt(transcnt);
										shopdinnerreportRt.setCramt(cramt);
										shopdinnerreportRt.setDramt(dramt);
										shopdinnerreportRt.setDamt3(damt3);
										shopdinnerreportRt.setNum(num);
										shopReportList.add(shopdinnerreportRt);
									}

								}

							}
						}
						return shopReportList;

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("未知错误");
						}

					}

				} else {
					// 请求失败
					throw new BccException("请求失败");
				}
			} else {
				throw new BccException("cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("动态库加载失败，请稍后重试！");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}

	public List getShopTotalReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"shop_total_report", 846706);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List shopReportList = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						shopid);// 商户号
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						shoplevel);// 商户级别

				bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),
						begindate.getBytes());// 开始日期
				bcc.SetStringFieldByName(xpackhandle, 0, "sdate2".getBytes(),
						enddate.getBytes());// 结束日期

				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String shopname = "";
							String summary = "";
							int transcnt = 0;
							double cramt = 0;
							double dramt = 0;
							double damt3 = 0;
							int num = 0;

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];
							// 商户名
							bcc.GetStringFieldByName(xpackhandle, i,
									"vsvarstr1".getBytes(), byteStrRec, 256);
							shopname = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							// 摘要
							bcc.GetStringFieldByName(xpackhandle, i, "snote"
									.getBytes(), byteStrRec, 81);
							summary = BccUtil.getStringFromByte(byteStrRec);
							// 交易次数
							bcc.GetIntFieldByName(xpackhandle, i, "lvol0"
									.getBytes(), intRec);
							transcnt = intRec[0];
							// 佣金
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt2"
									.getBytes(), doubleRec);
							cramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 营业额
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt1"
									.getBytes(), doubleRec);
							dramt = doubleRec[0];
							Arrays.fill(doubleRec, 0);
							// 结算金额
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt3"
									.getBytes(), doubleRec);
							damt3 = doubleRec[0];
							//交易人次
							bcc.GetIntFieldByName(xpackhandle, i, "lvol1"
									.getBytes(), intRec);
							num = intRec[0];
							ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
							shopdinnerreportRt.setShopname(shopname);
							shopdinnerreportRt.setSummary(summary);
							shopdinnerreportRt.setTranscnt(transcnt);
							shopdinnerreportRt.setCramt(cramt);
							shopdinnerreportRt.setDramt(dramt);
							shopdinnerreportRt.setDamt3(damt3);
							shopdinnerreportRt.setNum(num);
							
							shopReportList.add(shopdinnerreportRt);
						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;

							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);

							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String shopname = "";
										String summary = "";
										int transcnt = 0;
										double cramt = 0;
										double dramt = 0;
										double damt3 = 0;
										int num = 0;

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];

										bcc.GetStringFieldByName(xpackhandle,
												i, "vsvarstr1".getBytes(),
												byteStrRec, 256);
										shopname = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "snote".getBytes(),
												byteStrRec, 81);
										summary = BccUtil
												.getStringFromByte(byteStrRec);

										bcc.GetIntFieldByName(xpackhandle, i,
												"lvol0".getBytes(), intRec);
										transcnt = intRec[0];

										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt2".getBytes(),
												doubleRec);
										cramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt1".getBytes(),
												doubleRec);
										dramt = doubleRec[0];
										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt3".getBytes(),
												doubleRec);
										damt3 = doubleRec[0];
										//交易人次
										bcc.GetIntFieldByName(xpackhandle, i, "lvol1"
												.getBytes(), intRec);
										num = intRec[0];
										ShopDinnerReportResult shopdinnerreportRt = new ShopDinnerReportResult();
										shopdinnerreportRt
												.setShopname(shopname);
										shopdinnerreportRt.setSummary(summary);
										shopdinnerreportRt
												.setTranscnt(transcnt);
										shopdinnerreportRt.setCramt(cramt);
										shopdinnerreportRt.setDramt(dramt);
										shopdinnerreportRt.setDamt3(damt3);
										shopdinnerreportRt.setNum(num);
										shopReportList.add(shopdinnerreportRt);
									}

								}

							}
						}
						return shopReportList;

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("未知错误");
						}

					}

				} else {
					// 请求失败
					throw new BccException("请求失败");
				}
			} else {
				throw new BccException("cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("动态库加载失败，请稍后重试！");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}

	public List getShopAccountDetailList(int shopid, String begindate,
			String enddate, int termid) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"shop_account_detail", 846606);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List shopReportList = new ArrayList();
		HashMap devnamehash = new HashMap();
		HashMap custHash = new HashMap();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),
						shopid);// 商户号
				// bcc.SetStringFieldByName(xpackhandle, 0,
				// "scust_auth".getBytes(), "2004".getBytes());//科目号
				bcc.SetIntFieldByName(xpackhandle, 0, "lwithdraw_flag"
						.getBytes(), termid);// 终端id

				bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),
						begindate.getBytes());// 开始日期
				bcc.SetStringFieldByName(xpackhandle, 0, "sdate2".getBytes(),
						enddate.getBytes());// 结束日期

				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String accdate = "";
							String acctime = "";
							int devid = 0;
							String devname = "";
							int termserial = 0;
							String transdate = "";
							String transtime = "";
							String summary = "";
							String accno = "";
							String accno2 = "";
							String stuempno = "";
							String accname = "";
							String accname2 = "";
							String dcflag = "";
							double amount = 0;
							double balance = 0;

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i, "sdate3"
									.getBytes(), byteStrRec, 9);
							accdate = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i, "stime3"
									.getBytes(), byteStrRec, 9);
							acctime = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, i,
									"lwithdraw_flag".getBytes(), intRec);
							devid = intRec[0];
							String termname = (String) devnamehash.get(String
									.valueOf(devid));
							if (null == termname || "".equals(termname)) {
								VTerm vterm = devicePersistence
										.getVTermById(String.valueOf(devid));

								if (vterm != null) {
									devname = vterm.getTermname();
								} else {
									devname = "";
								}
								devnamehash.put(String.valueOf(devid), devname);
							} else {
								devname = termname;
							}

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, i, "lserial1"
									.getBytes(), intRec);
							termserial = intRec[0];

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i, "sdate0"
									.getBytes(), byteStrRec, 9);
							transdate = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i, "stime0"
									.getBytes(), byteStrRec, 9);
							transtime = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i, "snote"
									.getBytes(), byteStrRec, 81);
							summary = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i,
									"sbank_acc".getBytes(), byteStrRec, 41);
							accno = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i,
									"sbank_acc2".getBytes(), byteStrRec, 41);
							accno2 = BccUtil.getStringFromByte(byteStrRec);

							String stuempno_tmp = (String) devnamehash
									.get(String.valueOf(accno2));
							if (null == stuempno_tmp) {
								TCustomer tcustomer = customerPersistence
										.getCustomerByAccno(accno2);
								if (tcustomer != null) {
									stuempno = tcustomer.getStuempno();
								} else {
									stuempno = "";
								}
								devnamehash.put(accno2, stuempno);
							} else {
								stuempno = stuempno_tmp;
							}

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i,
									"sbankname".getBytes(), byteStrRec, 41);
							accname = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i,
									"sbankname2".getBytes(), byteStrRec, 41);
							accname2 = BccUtil.getStringFromByte(byteStrRec);

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i,
									"smain_flag".getBytes(), byteStrRec, 2);
							dcflag = BccUtil.getStringFromByte(byteStrRec);

							if ("2".equals(dcflag)) {
								Arrays.fill(doubleRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle, i,
										"damt3".getBytes(), doubleRec);
								amount = doubleRec[0];
							} else {
								Arrays.fill(doubleRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle, i,
										"damt4".getBytes(), doubleRec);
								amount = -doubleRec[0];
							}

							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, i, "damt1"
									.getBytes(), doubleRec);
							balance = doubleRec[0];

							if("".equals(accdate)){
								Arrays.fill(doubleRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle, i, "damt0".getBytes(),doubleRec);
								amount = doubleRec[0];
								//统计信息
								AccountDetailResult adresult = new AccountDetailResult();										
								adresult.setAmount(amount);
								adresult.setDevname(summary);
								shopReportList.add(adresult);
							}else{
								AccountDetailResult adresult = new AccountDetailResult();										
								adresult.setAccdate(accdate);
								adresult.setAccno(accno);
								adresult.setAccno2(accno2);
								adresult.setStuempno(stuempno);
								adresult.setAcctime(acctime);
								adresult.setAmount(amount);
								adresult.setBalance(balance);
								adresult.setDcflag(dcflag);
								adresult.setAccname(accname);
								adresult.setAccname2(accname2);
								adresult.setDevid(devid);
								adresult.setDevname(devname);
								adresult.setSummary(summary);
								adresult.setTermserial(termserial);
								adresult.setTransdate(transdate);
								adresult.setTranstime(transtime);
								shopReportList.add(adresult);
							}
						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;

							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);

							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String accdate = "";
										String acctime = "";
										int devid = 0;
										String devname = "";
										int termserial = 0;
										String transdate = "";
										String transtime = "";
										String summary = "";
										String accno = "";
										String accno2 = "";
										String stuempno = "";
										String accname = "";
										String accname2 = "";
										String dcflag = "";
										double amount = 0;
										double balance = 0;

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sdate3".getBytes(),
												byteStrRec, 9);
										accdate = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "stime3".getBytes(),
												byteStrRec, 9);
										acctime = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(intRec, 0);
										bcc.GetIntFieldByName(xpackhandle, i,
												"lwithdraw_flag".getBytes(),
												intRec);
										devid = intRec[0];
										String termname = (String) devnamehash
												.get(String.valueOf(devid));
										if (null == termname
												|| "".equals(termname)) {
											VTerm vterm = devicePersistence
													.getVTermById(String
															.valueOf(devid));

											if (vterm != null) {
												devname = vterm.getTermname();
											} else {
												devname = "";
											}
											devnamehash.put(String
													.valueOf(devid), devname);
										} else {
											devname = termname;
										}

										Arrays.fill(intRec, 0);
										bcc.GetIntFieldByName(xpackhandle, i,
												"lserial1".getBytes(), intRec);
										termserial = intRec[0];

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sdate0".getBytes(),
												byteStrRec, 9);
										transdate = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "stime0".getBytes(),
												byteStrRec, 9);
										transtime = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "snote".getBytes(),
												byteStrRec, 81);
										summary = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sbank_acc".getBytes(),
												byteStrRec, 41);
										accno = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sbank_acc2".getBytes(),
												byteStrRec, 41);
										accno2 = BccUtil
												.getStringFromByte(byteStrRec);

										String stuempno_tmp = (String) devnamehash
												.get(String.valueOf(accno2));
										if (null == stuempno_tmp) {
											TCustomer tcustomer = customerPersistence
													.getCustomerByAccno(accno2);
											if (tcustomer != null) {
												stuempno = tcustomer
														.getStuempno();
											} else {
												stuempno = "";
											}
											devnamehash.put(accno2, stuempno);
										} else {
											stuempno = stuempno_tmp;
										}

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sbankname".getBytes(),
												byteStrRec, 41);
										accname = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "sbankname2".getBytes(),
												byteStrRec, 41);
										accname2 = BccUtil
												.getStringFromByte(byteStrRec);

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "smain_flag".getBytes(),
												byteStrRec, 2);
										dcflag = BccUtil
												.getStringFromByte(byteStrRec);

										if ("2".equals(dcflag)) {
											Arrays.fill(doubleRec, 0);
											bcc.GetDoubleFieldByName(
													xpackhandle, i, "damt3"
															.getBytes(),
													doubleRec);
											amount = doubleRec[0];
										} else {
											Arrays.fill(doubleRec, 0);
											bcc.GetDoubleFieldByName(
													xpackhandle, i, "damt4"
															.getBytes(),
													doubleRec);
											amount = -doubleRec[0];
										}

										Arrays.fill(doubleRec, 0);
										bcc.GetDoubleFieldByName(xpackhandle,
												i, "damt1".getBytes(),
												doubleRec);
										balance = doubleRec[0];
										
										
										if("".equals(accdate)){
											Arrays.fill(doubleRec, 0);
											bcc.GetDoubleFieldByName(xpackhandle, i, "damt0".getBytes(),doubleRec);
											amount = doubleRec[0];
											//统计信息
											AccountDetailResult adresult = new AccountDetailResult();										
											adresult.setAmount(amount);
											adresult.setDevname(summary);
											shopReportList.add(adresult);
										}else{
											AccountDetailResult adresult = new AccountDetailResult();										
											adresult.setAccdate(accdate);
											adresult.setAccno(accno);
											adresult.setAccno2(accno2);
											adresult.setStuempno(stuempno);
											adresult.setAcctime(acctime);
											adresult.setAmount(amount);
											adresult.setBalance(balance);
											adresult.setDcflag(dcflag);
											adresult.setAccname(accname);
											adresult.setAccname2(accname2);
											adresult.setDevid(devid);
											adresult.setDevname(devname);
											adresult.setSummary(summary);
											adresult.setTermserial(termserial);
											adresult.setTransdate(transdate);
											adresult.setTranstime(transtime);
											shopReportList.add(adresult);
										}
										
									}

								}

							}
						}
						return shopReportList;

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);

							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("未知错误");
						}

					}

				} else {
					// 请求失败
					throw new BccException("请求失败，网络问题或者后台无响应");
				}
			} else {
				throw new BccException("cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("动态库加载失败，请稍后重试！");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
	
	public List getShopBrasDetailList(String begindate, String enddate,String refno,String stuempno,String custname,
			String oppaccno, String oppaccname,String status, String brastype)
			throws PortalException{
		return shopPersistence.getBrasTransLogList(begindate,enddate,refno,stuempno,custname,oppaccno,oppaccname,status,brastype);
	}

	public List getShopList(long userid) throws PortalException {
		return shopPersistence.getShopList(String.valueOf(userid));
	}

	public List getShopPosDetailList(int shopid, String begindate,
			String enddate, String devphyId) throws PortalException{
		return shopPersistence.getShopPosList( shopid, begindate, enddate, devphyId);
	}

}
