package com.kingstar.task;

import java.util.ArrayList;
import java.util.Arrays;

import org.apache.log4j.Logger;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2BrastransDAO;
import com.kingstargroup.fdykt.dto.BrastransdtlDTO;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;

public class TimeTaskForSerialCheckThread extends Thread {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(TimeTaskForSerialCheckThread.class);

	private static boolean requestStop = false;
	private int restartcheck = 0;
	private String checktime = "032000";

	public void run() {
		while (!requestStop) {
			
			restartcheck = KSConfiguration.getInstance().getPropertyAsInt(
					"restartcheck", 0);
			checktime = KSConfiguration.getInstance().getProperty("checktime",
					"032000");
			
			if (restartcheck == 1) {// 定时启动，重启不直接运行
				try {

					long sleepTime = DateUtil.getIntervalTime(DateUtil
							.getNewDateTime(DateUtil.getNow("yyyyMMdd"), 1,
									"yyyyMMdd")
							+ checktime, DateUtil.getNow());
					if (logger.isInfoEnabled()) {
						logger
								.info("bras对账线程进入休眠状态!"
										+ " 休眠开始时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss") + ", 休眠时间:" + sleepTime + " 毫秒"); //$NON-NLS-1$
					}
					if (sleepTime <= 0) {
						sleep(24 * 3600 * 1000);
					} else {
						sleep(sleepTime);
					}
				} catch (InterruptedException e) {
					logger.error("bras对账线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
				} catch (Exception e) {
					logger.error("bras对账线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
				}
			}

			
			DB2BrastransDAO brastransdao = new DB2BrastransDAO();
			String uncheckdate = DateUtil.getNow("yyyyMMdd");
			try {
				uncheckdate = brastransdao.getMinUncheckBrasTransLogDate();
			} catch (Exception e2) {
				// TODO Auto-generated catch block
				e2.printStackTrace();
			}

			String nowdate = DateUtil.getNow("yyyyMMdd");

			checkLogic(brastransdao,uncheckdate, nowdate);
			try {

				long sleepTime = DateUtil.getIntervalTime(DateUtil
						.getNewDateTime(DateUtil.getNow("yyyyMMdd"), 1,
								"yyyyMMdd")
						+ checktime, DateUtil.getNow());
				if (logger.isInfoEnabled()) {
					logger
							.info("bras对账线程进入休眠状态!"
									+ " 休眠开始时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss") + ", 休眠时间:" + sleepTime + " 毫秒"); //$NON-NLS-1$
				}
				if (sleepTime <= 0) {
					sleep(24 * 3600 * 1000);
				} else {
					sleep(sleepTime);
				}
			} catch (InterruptedException e) {
				logger.error("bras对账线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
			} catch (Exception e) {
				logger.error("bras对账线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
			}
		}

	}

	private void checkLogic(DB2BrastransDAO brastransdao,String uncheckdate,
			String nowdate) {
		/**
		 * 1、本地中查询出所有问题流水，即出来处理成功的所有流水， 2、向第三方请求对账数据 3、逐条对账 包括流水号、金额
		 * 4、补入不对的流水、更新标记 5、更新不需补入的流水标记
		 * 
		 */

		while (DateUtil.checkSpecialTimeSequence(uncheckdate, nowdate,
				"yyyyMMdd") <0) {

			String serialnoStr = "";
			ArrayList list = null;
			try {
				list = brastransdao
						.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.v_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1 and a.REFNO like '"
								+ uncheckdate + "%' ");
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			if (list != null && list.size() > 0) {
				try {
					serialnoStr = getLikeStrFromServer(uncheckdate);
				} catch (Exception e2) {
					// TODO Auto-generated catch block
					e2.printStackTrace();
					logger.info("第三方服务器暂不可用，对账失败");
					break;
				}
				
				for (int i = 0; i < list.size(); i++) {
					BrastransdtlDTO brasdto = (BrastransdtlDTO) list.get(i);
					if ("1".equals(brasdto.getRevflag())) {
						// 已冲正
						brasdto.setStatus(0);
						brasdto.setRemark("流水已经冲正");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						} catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}

					} else {
						String sendrefno = "YK"
								+ brasdto.getRefno().substring(2);
						if (serialnoStr.indexOf(sendrefno) == -1) {
							// send
							sendreq(brastransdao,brasdto);
						} else {
							// update
							brasdto.setStatus(0);
							brasdto.setRemark("网费充值成功");
							try {
								brastransdao.updateBrasTransLog(brasdto);
							} catch (Exception e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					}

				}

			}

			try {
				brastransdao.updateBrasTransLogCHKFLAG(uncheckdate);
			} catch (Exception e) {
				// TODO Auto-generated catch block

				e.printStackTrace();
			}

			
			
			//log brastransdtl表里没有的问题
			
			ArrayList lostlist = null;
			try {
				lostlist = brastransdao
						.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.v_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1 and a.REFNO like '"
								+ uncheckdate + "%' ");
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			
			
			
			uncheckdate = DateUtil.getNewDateTime(uncheckdate, 1, "yyyyMMdd");

		}


		ArrayList unchecklist = null;
		try {
			unchecklist = brastransdao
					.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.v_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1 and a.refno<'"
							+ nowdate + "'");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if (unchecklist != null && unchecklist.size() > 0) {
			for (int j = 0; j < unchecklist.size(); j++) {
				BrastransdtlDTO brasdto = (BrastransdtlDTO) unchecklist.get(j);

				if ("1".equals(brasdto.getRevflag())) {
					// 已冲正
					brasdto.setStatus(0);
					brasdto.setRemark("流水已经冲正");
					try {
						brastransdao.updateBrasTransLog(brasdto);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}

				} else {
					String retStr = "";
					try {
						retStr = getLikeStrFromServer(brasdto.getRefno());
					} catch (Exception e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
						logger.info("第三方服务器请求出错,本条对账失败");
						continue;
					}
					String sendrefno = "YK" + brasdto.getRefno().substring(2);
					if (retStr.indexOf(sendrefno) == -1) {
						// send
						sendreq(brastransdao,brasdto);
					} else {
						// update
						brasdto.setStatus(0);
						brasdto.setRemark("网费充值成功");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						} catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}

			}

		}

	}

	private String getLikeStrFromServer(String serialno) throws Exception {

		String serialnoStr = "";
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_check", 3003);// 后台业务功能号
		// int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
		// 3);// 默认重试次数
		String loginName = KSConfiguration.getInstance().getProperty(
				"loginName", "");
		String loginPwd = KSConfiguration.getInstance().getProperty("loginPwd",
				"");
		String endpoint = KSConfiguration.getInstance().getProperty("endpoint",
				"http://localhost/csi/services/CamsWebService");

		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0,
						"vsvarstr0".getBytes(), endpoint.getBytes());// 第三方服务地址
				bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),
						loginName.getBytes());// 第三方登录名
				bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(),
						loginPwd.getBytes());// 第三方登录密码
				String reqrefno = "YK" + serialno.substring(2) + "%";
				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation0".getBytes(), reqrefno.getBytes());// 查询flowid

				logger.info("查询第三方流水，查询条件：" + reqrefno);
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 60000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String refno = "";
							// String oppaccno = "";
							// String transamt = "";

							byte[] byteStrRec = new byte[256];
							// int[] intRec = new int[1];
							// double[] doubleRec = new double[1];

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i, "scard0"
									.getBytes(), byteStrRec, 256);
							refno = BccUtil.getStringFromByte(byteStrRec);

							serialnoStr += refno + ",";

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
										String refno = "";
										// String oppaccno = "";
										// String transamt = "";

										byte[] byteStrRec = new byte[256];
										// int[] intRec = new int[1];
										// double[] doubleRec = new double[1];

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "scard0".getBytes(),
												byteStrRec, 256);
										refno = BccUtil
												.getStringFromByte(byteStrRec);

										serialnoStr += refno + ",";
									}

								}

							}
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							logger.info("对账发生错误 错误原因" + vs_mess);
							throw new Exception("对账发生错误 错误原因" + vs_mess);

						} else {
							// throw exception //unknow err
							logger.info("对账发生未知错误 错误码：" + RetCode[0]);
							throw new Exception("对账发生未知错误 错误码：" + RetCode[0]);
						}

					}

				} else {
					// 请求失败
					logger.info("对账发生错误：请求失败，网络问题或者后台无响应");

					throw new Exception("对账发生错误：请求失败，网络问题或者后台无响应");
				}
			} else {
				logger.info("对账发生错误：cpack初始化失败");
				throw new Exception("对账发生错误：cpack初始化失败");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			logger.info("对账发生错误：动态库加载失败，请稍后重试！");
			throw new Exception(e);
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		logger.info("返回结果：" + serialnoStr);
		return serialnoStr;
	}

	private void sendreq(DB2BrastransDAO brastransdao,BrastransdtlDTO brasdto) {
		if (logger.isDebugEnabled()) {
			logger.debug("sendreq(BrastransdtlDTO) - start"); //$NON-NLS-1$
		}

		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_pay", 3002);// 后台业务功能号
		// int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
		// 3);// 默认重试次数
		String loginName = KSConfiguration.getInstance().getProperty(
				"loginName", "");
		String loginPwd = KSConfiguration.getInstance().getProperty("loginPwd",
				"");
		String endpoint = KSConfiguration.getInstance().getProperty("endpoint",
				"http://localhost/csi/services/CamsWebService");

		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0,
						"vsvarstr0".getBytes(), endpoint.getBytes());// 第三方服务地址
				bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),
						loginName.getBytes());// 第三方登录名
				bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(),
						loginPwd.getBytes());// 第三方登录密码
				String reqrefno = "YK" + brasdto.getRefno().substring(2);
				bcc.SetStringFieldByName(xpackhandle, 0, "scard0".getBytes(),
						reqrefno.getBytes());// 流水凭证号
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						brasdto.getOppaccno().getBytes());// 第三方账号
				String tsamt = String.valueOf(brasdto.getTransamt());
				tsamt = tsamt.substring(0, tsamt.indexOf("."));
				bcc
						.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
								Integer.parseInt(tsamt));// 转账金额
				logger.info("第三方补入请求，流水" + brasdto.getRefno() + "金额："
						+ brasdto.getTransamt());
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 30000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						brasdto.setStatus(0);
						brasdto.setRemark("网费充值补入成功");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						} catch (Exception e) {
							// TODO: handle exception
							logger.error("更新网费充值表失败,流水号：" + brasdto.getRefno()
									+ "状态：[" + brasdto.getStatus() + "],备注："
									+ brasdto.getRemark());
							e.printStackTrace();
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);

							String vs_mess = BccUtil.getStringFromByte(vsmess);

							brasdto.setRemark("网费充值补入失败：" + vs_mess);
							try {
								brastransdao.updateBrasTransLog(brasdto);
							} catch (Exception e) {
								// TODO: handle exception
								logger.error("更新网费充值表失败,流水号："
										+ brasdto.getRefno() + "状态：["
										+ brasdto.getStatus() + "],备注："
										+ brasdto.getRemark());
								e.printStackTrace();
							}
						} else {

							brasdto.setRemark("网费充值补入失败：返回码=" + RetCode[0]);
							try {
								brastransdao.updateBrasTransLog(brasdto);
							} catch (Exception e) {
								// TODO: handle exception
								logger.error("更新网费充值表失败,流水号："
										+ brasdto.getRefno() + "状态：["
										+ brasdto.getStatus() + "],备注："
										+ brasdto.getRemark());
								e.printStackTrace();
							}
						}

					}

				} else {
					// 请求失败

					brasdto.setRemark("网费充值补入失败：后台通讯暂时不可用");
					try {
						brastransdao.updateBrasTransLog(brasdto);
					} catch (Exception e) {
						// TODO: handle exception
						logger.error("更新网费充值表失败,流水号：" + brasdto.getRefno()
								+ "状态：[" + brasdto.getStatus() + "],备注："
								+ brasdto.getRemark());
						e.printStackTrace();
					}
				}
			}else{
				brasdto.setRemark("网费充值补入失败：cpack初始化失败");
				try {
					brastransdao.updateBrasTransLog(brasdto);
				} catch (Exception e) {
					// TODO: handle exception
					logger.error("更新网费充值表失败,流水号：" + brasdto.getRefno() + "状态：["
							+ brasdto.getStatus() + "],备注：" + brasdto.getRemark());
					e.printStackTrace();
				}
			}

			

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());

		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());

		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

		if (logger.isDebugEnabled()) {
			logger.debug("sendreq(BrastransdtlDTO) - end"); //$NON-NLS-1$
		}
	}
}
