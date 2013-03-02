package com.kingstargroup;

import java.util.HashMap;

import javax.servlet.http.HttpSession;

public abstract class BusinessProcessor {

	static public final String THIRD_PART_MESSAGE = "third_part_message";

	/**
	 * Method name:checkThirdpart Description: 第三方链路检查,信息校验
	 * 
	 * @param session
	 *            用户保存一些异步信息，譬如返回的message信息
	 * @param personId
	 *            用户id如 学工号，可用于第三方账号校验合法性
	 * @param personName
	 *            用户名称
	 * @param args
	 *            业务处理过程中，需要的其他的相关参数。
	 * @return boolean true：第三方系统运行正常，false:第三方系统出现异常
	 */
	public abstract boolean checkThirdpart(HttpSession session,
			String personId, String personName, String amount, HashMap args);

	/**
	 * Method name:getThirdpartInfo Description: 第三方信息返回 给用户确认 Return:
	 * 
	 * @param session
	 *            用户保存一些异步信息，譬如返回的message信息
	 * @param personId
	 *            用户id如 学工号，可用于第三方账号校验合法性
	 * @param personName
	 *            用户名称
	 * @param amount
	 *            本次充值的金额。
	 * @param args
	 *            业务处理过程中，需要的其他的相关参数。
	 * @return HashMap 返回信息hash表 entity为信息项抬头，value为信息内容，譬如{用户名=abc};
	 */
	public abstract HashMap getThirdpartInfo(HttpSession session,
			String personId, String personName, String amount, HashMap args);

	/**
	 * Method name:businessProcess Description: 进行专项充值的具体的业务处理。
	 * 
	 * @param session
	 *            用户保存一些异步信息，譬如返回的message信息
	 * @param refno
	 *            交易参考号，双方对应的流水参考号，用户对账
	 * @param personId
	 *            需要进行充值的人员ID号，可为学号或职工号。
	 * @param personName
	 *            需要进行充值的人员的姓名。
	 * @param amount
	 *            本次充值的金额。
	 * @param args
	 *            业务处理过程中，需要的其他的相关参数。
	 * @return boolean 业务处理是否成功。 true:业务处理成功，false：业务处理失败。
	 */
	public abstract boolean businessProcess(HttpSession session, String refno,
			String personId, String personName, String amount, HashMap args);

	/**
	 * Method name:getProcessMessage Description: 第三方系统返回信息
	 * 
	 * @param session
	 *            用于保存信息所用的session key为THIRD_PART_MESSAGE
	 * @return String 返回第三方信息
	 */
	public abstract String getProcessMessage(HttpSession session);

	/**
	 * Method name:businessRollback Description:
	 * 对进行充值业务的处理成功后，但在一卡通的帐号进行转帐时出错。可通此方法进行充值业务的回退。
	 * 
	 * @param session
	 *            用户保存一些异步信息，譬如返回的message信息
	 * @param refno
	 *            交易参考号，双方对应的流水参考号，用户对账
	 * @param personId
	 *            需要进行充值的人员ID号，可为学号或职工号。
	 * @param personName
	 *            需要进行充值的人员的姓名。
	 * @param amount
	 *            本次充值的金额。
	 * @param args
	 *            业务处理过程中，需要的其他的相关参数。
	 * @return 业务处理是否成功。 true:业务处理成功，false：业务处理失败。
	 */
	public abstract boolean businessRollback(HttpSession session, String refno,
			String personId, String personName, String amount, HashMap args);

}
