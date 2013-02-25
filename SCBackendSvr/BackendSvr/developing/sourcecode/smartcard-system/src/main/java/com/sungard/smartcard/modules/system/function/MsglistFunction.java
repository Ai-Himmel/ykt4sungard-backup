package com.sungard.smartcard.modules.system.function;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Msglist;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.MsglistService;


/**
 * 消息队列信息管理
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-2-23
 */

@SmartCardFunction(infotype = 3, funcnum =10004105, name = "消息队列管理")
@Component
public class MsglistFunction extends AbstractFunction{

	private static final Logger logger = LoggerFactory.getLogger(SpecialtyFunction.class);
	
	@Autowired
	@Qualifier("msglistServiceImpl")
	private MsglistService msglistService;

	/**
	 * 删除
	 * */
	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		//int msgid=0;
		Integer msgid=session.GetIntFieldByName2(0,TransfersNodeType.lvol0.getName()); //消息队列编号
//		if(msgid=null){
//			throw new FunctionException(RetCode.IS_NOT_NULL,"消息队列编号");
//		}
		/**
		 * 根据msgid查询是否存在消息队列记录
		 * */
		if(this.msglistService.isExistMsglist(msgid)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "消息队列记录");
		}
		int deletes=this.msglistService.deleteMsglist(msgid);
		logger.info("[{} records was delete]", msgid);
	}

	/**
	 * 查询
	 * */
	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Msglist params= super.getParameter(Msglist.class,session);
		List<Msglist> msglist = this.msglistService.listMsglist(params);
		super.outPack(msglist,Msglist.class,session);
	}

	/**
	 * 修改
	 * */
	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
//		int msgid=0;
//		int maxsendcnt=0;
//		int status=0;
		Integer msgid=session.GetIntFieldByName2(0,TransfersNodeType.lvol0.getName()); //消息队列编号
//		if(msgid==0){
//			throw new FunctionException(RetCode.IS_NOT_NULL,"条消息队列编号");
//		}
		/**
		 * 根据msgid查询是否存在消息队列记录
		 * */
		if(this.msglistService.isExistMsglist(msgid)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "消息队列记录");
		}
		Integer maxsendcnt=session.GetIntFieldByName2(0,TransfersNodeType.lvol8.getName()); //最大发送次数
		Integer status=session.GetIntFieldByName2(0,TransfersNodeType.lvol11.getName()); //消息状态
//		if(maxsendcnt==0){
//			throw new FunctionException(RetCode.IS_NOT_NULL,"最大发送次数");
//		}
//		if(status==0){
//			throw new FunctionException(RetCode.IS_NOT_NULL,"消息状态");
//		}
		
		Msglist msglist = new Msglist();
		msglist.setMsgid(msgid);
		msglist.setMaxsendcnt(maxsendcnt);
		msglist.setStatus(status);
		
		int updates=this.msglistService.updateMsglist(msglist);
		
		logger.info("[{} records was update]", msgid);	
	}

}
