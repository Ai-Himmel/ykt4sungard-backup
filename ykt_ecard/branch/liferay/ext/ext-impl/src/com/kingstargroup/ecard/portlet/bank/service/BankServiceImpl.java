package com.kingstargroup.ecard.portlet.bank.service;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;

import org.apache.commons.lang.StringUtils;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.exceptions.BccException;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.util.BccUtil;

public class BankServiceImpl extends BankServiceBase {
	
	/*
	 * 联机查询银行卡号
	 */
	public String getLinkBankBindingAcc( String stuempno)throws PortalException {
		String bankcardno = "";
		//String errinfo = "";
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 6000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("bank_account_query", 841603);// 后台业务功能号
		//int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(), "Q".getBytes());// 交易类型
				bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(), stuempno.getBytes());// 学号
				bcc.SetIntFieldByName(xpackhandle, 0, "lwithdraw_flag".getBytes(), 1);//终端编号
				boolean bccret = false;
				try{
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 10000, errcode, errmsg);
				}catch(Exception e){
					System.out.println(e.toString());
				}
				System.out.println(bcc);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						byte[] byteStrRec = new byte[256];
						Arrays.fill(byteStrRec, (byte) 0);
						bcc.GetStringFieldByName(xpackhandle, 0,"scard0".getBytes(), byteStrRec, 51);
						bankcardno = BccUtil.getStringFromByte(byteStrRec);
						return bankcardno;
					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
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
	
	/*
	 * 绑定银行卡操作 A’表示添加，‘D’表示解除绑定，‘S‘表示同步,’R‘表示重置验证码

	 */
	public void linkBindingOper( String stuempno,String bankAcc,String authcode,String operType)throws PortalException {
		//String bankcardno = "";
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 6000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("bank_account_query", 841603);// 后台业务功能号
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(), "B".getBytes());// 交易类型
				bcc.SetIntFieldByName(xpackhandle, 0, "lwithdraw_flag".getBytes(), 1);//终端编号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(), stuempno.getBytes());// 学号
				bcc.SetStringFieldByName(xpackhandle, 0, "scard0".getBytes(), bankAcc.getBytes());// 银行卡号
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1".getBytes(), operType.getBytes());// 操作类型
				if(StringUtils.isNotBlank(authcode)){
					bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd".getBytes(), authcode.getBytes());//银行卡校验码
				}
				
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						//byte[] byteStrRec = new byte[256];
						//Arrays.fill(byteStrRec, (byte) 0);
						//bcc.GetStringFieldByName(xpackhandle, 0,"scard0".getBytes(), byteStrRec, 51);
						//bankcardno = BccUtil.getStringFromByte(byteStrRec);
						//return bankcardno;
					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
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
	/*
	 * y
	 */
	public String getBankBindingAccount(TCustomer tcustomer, String stuempno)
			throws PortalException {
		String bankcardno = "";
		String errinfo = "";
		try {
			bankcardno = bankPersistence.getBankAccountFromDB(tcustomer
					.getCustid(), "00");
		} catch (DBSystemException e) {
			// TODO: handle exception
			e.printStackTrace();
		}

		return bankcardno;


	}

	public String updateBankBindingAccount(TCustomer tcustomer,
			String stuempno, String bankcardno) throws PortalException {
		
		if("".equals(bankcardno)){
			throw new BccBgInfoException("不能更新为空银行卡号，可以使用删除功能删除绑定");
		}

		String bankcardno_db = "";
		try {
			bankcardno_db = bankPersistence.getBankAccountFromDB(tcustomer
					.getCustid(), "00");
		} catch (DBSystemException e) {
			// TODO: handle exception
			e.printStackTrace();
			throw e;

		}
		System.out.println("local card no:"+bankcardno_db+"****");
		if (!bankcardno_db.equals(bankcardno)) {

			if(!"".equals(bankcardno_db)){
				try {
					System.out.println("delete local bank acc:"+bankcardno_db+"****");
					deleteBankBindingAccount(tcustomer, stuempno, false);
				} catch (PortalException e) {
					// TODO: handle exception
					throw e;
				}
			}		

			long xpackhandle = 0;
			int drtpno = 1;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction1", 5000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"bank_account_query", 270001);// 后台业务功能号
			int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
					3);// 默认重试次数
			int[] RetCode = new int[1];
			int[] RecordCount = new int[1];
			bccclt bcc = null;
			try {
				bcc = BccctlInit.getBccctlInstance();
				xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
						.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
				if (0 != xpackhandle) {
					bcc.SetRequestType(xpackhandle, func);
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
							.getBytes(), "A".getBytes());// 交易类型
					try {
						bcc.SetStringFieldByName(xpackhandle, 0, "sall_name"
								.getBytes(), tcustomer.getCustname().getBytes("GBK"));
					} catch (UnsupportedEncodingException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}// 姓名
					bcc.SetStringFieldByName(xpackhandle, 0, "semail2"
							.getBytes(), tcustomer.getIdno().getBytes());// 身份证号
					bcc.SetStringFieldByName(xpackhandle, 0, "spager"
							.getBytes(), tcustomer.getStuempno().getBytes());// 学号
					bcc.SetStringFieldByName(xpackhandle, 0, "scard0"
							.getBytes(), bankcardno.getBytes());
					boolean bccret = false;

					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 20000, errcode, errmsg);

					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {

							int[] intRec = new int[1];
							byte[] byteStrRec = new byte[256];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lsafe_level"
									.getBytes(), intRec);
							if (0 == intRec[0]) {
								try {
									System.out.println("update local card no:"+bankcardno+"****");
									bankPersistence.updateBankAccountToDB(
											tcustomer.getCustid(), "00",
											bankcardno);
								} catch (DBSystemException e) {
									// TODO: handle exception
									e.printStackTrace();
									throw new DBSystemException(
											"银行端更新绑定成功，本地数据库更新绑定失败");
								}
								return bankcardno;

							} else {
							try{
								System.out.println("remove local card no:"+bankcardno+"****");
								bankPersistence.removeBankAccountFromDB(tcustomer.getCustid(), "00", bankcardno);
							} catch (DBSystemException e) {
								// TODO: handle exception
								e.printStackTrace();
								throw new DBSystemException(
										"银行端更新绑定成功，本地数据库更新绑定失败");
							}
							Arrays.fill(byteStrRec, (byte) 0);
								bcc
										.GetStringFieldByName(xpackhandle, 0,
												"vsvarstr0".getBytes(),
												byteStrRec, 256);
								throw new BccBgInfoException("银行返回信息:"+BccUtil
										.getStringFromByte(byteStrRec));
							}

						} else {
							// 失败
							if (0 < RecordCount[0]) {

								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
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

		}else{
			throw new BccBgInfoException("此银行卡号已经绑定，无需更新");
		}
	}

	public boolean deleteBankBindingAccount(TCustomer tcustomer,
			String stuempno, boolean flag) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 5000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"bank_account_query", 270001);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(),
						"D".getBytes());// 交易类型
				try {
					bcc.SetStringFieldByName(xpackhandle, 0,
							"sall_name".getBytes(), tcustomer.getCustname()
									.getBytes("GBK"));
				} catch (UnsupportedEncodingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}// 姓名
				bcc.SetStringFieldByName(xpackhandle, 0, "semail2".getBytes(),
						tcustomer.getIdno().getBytes());// 身份证号
				bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(),
						tcustomer.getStuempno().getBytes());// 学号
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);				
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						int[] intRec = new int[1];
						byte[] byteStrRec = new byte[256];
						Arrays.fill(intRec, 0);
						bcc.GetIntFieldByName(xpackhandle, 0, "lsafe_level"
								.getBytes(), intRec);
						if (0 == intRec[0]) {
							if (flag) {
								try {
									bankPersistence.removeBankAccountFromDB(
											tcustomer.getCustid(), "00", "");
								} catch (Exception e) {
									// TODO: handle exception
									e.printStackTrace();
									throw new DBSystemException(
											"银行端删除成功，本地数据库更新删除失败");
								}
							}
							return true;

						} else {
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,
									"vsvarstr0".getBytes(), byteStrRec, 256);
							throw new BccBgInfoException("银行返回信息:"+BccUtil
									.getStringFromByte(byteStrRec));
						}
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

}
