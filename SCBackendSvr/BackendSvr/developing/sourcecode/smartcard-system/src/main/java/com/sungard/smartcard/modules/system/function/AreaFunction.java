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
import com.sungard.smartcard.domain.Area;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.AreaService;
/**
 * 区域信息增删改查
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-2-22
 */

@SmartCardFunction(infotype = 3, funcnum = 10007100, name = "区域信息设置及查询")
@Component
public class AreaFunction extends AbstractFunction{
	private static final Logger logger = LoggerFactory.getLogger(SpecialtyFunction.class);
	
	@Autowired
	@Qualifier("areaServiceImpl")
	private AreaService areaService;
	
	/**
	 * 新增保存
	 * */
	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		String areacode = session.GetStringFieldByName(0, TransfersNodeType.sroom_no.getName()); //区域编号
		String areaname = session.GetStringFieldByName(0, TransfersNodeType.sbankname.getName()); //区域名称
		String fareacode = session.GetStringFieldByName(0, TransfersNodeType.sroom_no2.getName()); //上级区域代码		
		String addr = session.GetStringFieldByName(0, TransfersNodeType.vsvarstr0.getName()); //地址	
		String remark = session.GetStringFieldByName(0, TransfersNodeType.vsvarstr1.getName()); //备注
		

		if(areacode==null||"".equals(areacode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"区域代码");
		}
		if(areaname==null||"".equals(areaname)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"区域名称");
		}
		if(fareacode==null||"".equals(fareacode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"上级区域");
		}

			
		/**
		 * 判断区域代码是否重复
		 * false 不存在
		 * true  存在
		 * */
		if(this.areaService.isExistArea(areacode)==true){
			throw new FunctionException(RetCode.IS_EXISTS,"区域代码"+areacode);
		}	
		
		/**
		 * 判断上级区域代码是否存在
		 * false 不存在
		 * true  存在
		 * */
		if(this.areaService.isExistArea(fareacode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS,"上级区域代码"+fareacode);
		}
		/**
		 * 判断区域名称不能重复
		 * false 不存在
		 * true  存在
		 * */
		if(this.areaService.isExistAreaName(null,areaname)==true){
			throw new FunctionException(RetCode.IS_EXISTS,"区域名称"+areaname);
		}	
		
		Area area=new Area();
		area.setAreacode(areacode);
		area.setAreaname(areaname);
		area.setFareacode(fareacode);
		area.setAddr(addr);
		area.setRemark(remark);
		
		int adds=this.areaService.addArea(area);		
		logger.info("[{} records was add]", areacode);
	}

	/**
	 * 删除
	 * */
	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		String areacode = session.GetStringFieldByName(0, TransfersNodeType.sroom_no.getName()); //区域编号
		if(areacode==null||"".equals(areacode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"区域编号");
		}
		/**
		 * 判断该条记录是否存在  不存在则不能删除 抛出
		 * false 不存在
		 * true  存在
		 * */
		if(this.areaService.isExistArea(areacode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS,"区域代码"+areacode);
		}	
		/**
		 * 判断是不是根区域      是根区域不能删除
		 * false 不存在
		 * true  存在
		 * */	
		if(this.areaService.isFareArea(areacode)==true){
			throw new FunctionException(RetCode.NO_DELORUPD_FARTHERNODE,"删除");
		}
		/**
		 * 判断是不是存在子区域      有子根区域不能删除，需要先删除子区域
		 * false 不存在
		 * true  存在
		 * */	
		if(this.areaService.isExistSonArea(areacode)==true){
			throw new FunctionException(RetCode.FIRST_DELETE_SONNODE,"区域");//先删除下级区域
		}	
		int deletes=this.areaService.deleArea(areacode);	
		logger.info("[{} records was delete]",areacode);
	}

	/**
	 * 查询
	 * */
	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		List<Area> listarea= this.areaService.allAreas();		

		super.outPack(listarea, Area.class, session);
	}

	/**
	 * 修改保存
	 * */
	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		String areacode = session.GetStringFieldByName(0, TransfersNodeType.sroom_no.getName()); //区域编号
		String areaname = session.GetStringFieldByName(0, TransfersNodeType.sbankname.getName()); //区域名称
		String fareacode = session.GetStringFieldByName(0, TransfersNodeType.sroom_no2.getName()); //上级区域代码
//		int arealevel = session.GetIntFieldByName(0,TransfersNodeType.lcert_code.getName()); //区域级别
		String addr = session.GetStringFieldByName(0, TransfersNodeType.vsvarstr0.getName()); //地址	
		String remark = session.GetStringFieldByName(0, TransfersNodeType.vsvarstr1.getName()); //备注

		//为空判断
		if(areacode==null||"".equals(areacode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"区域编号");
		}
		if(areaname==null||"".equals(areaname)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"区域名称");
		}
		if(fareacode==null||"".equals(fareacode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"上级区域");
		}
//		if(arealevel==0){
//			throw new FunctionException(RetCode.IS_NOT_NULL,"区域级别");
//		}
		/**
		 * 判断是不是根区域     
		 * 是根区域不能修改  抛出
		 * false 不存在
		 * true  存在
		 * */	
		//根节点的上去区域代码为空，在前面已被过滤掉，不需要再做判断
//		if(this.areaService.isFareArea(areacode)==true){
//			throw new FunctionException(RetCode.NO_DELORUPD_FARTHERNODE,"修改");
//		}
		/**
		 * 判断该条记录是否存在  不存在不能修改  则抛出
		 * false 不存在
		 * true  存在
		 * */
		if(this.areaService.isExistArea(areacode)==false){
			throw new FunctionException(RetCode.IS_EXISTS,"区域代码"+areacode);
		}
		/**
		 * 判断上级区域代码是否存在 不存在父区域  则抛出
		 * false 不存在
		 * true  存在
		 * */
		if(this.areaService.isExistArea(fareacode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS,"上级区域代码"+fareacode);
		}
		
		/**
		 * 判断区域名称是否已存在，存在抛出
		 * false 不存在
		 * true  存在
		 * */
		if(this.areaService.isExistAreaName(areacode,areaname)==true){
			throw new FunctionException(RetCode.IS_EXISTS,"区域名称"+areaname);
		}	
		
		Area area=new Area();
		area.setAreacode(areacode);
		area.setAreaname(areaname);
//		area.setFareacode(fareacode);//上级区域代码只做验证使用
//		area.setArealevel(arealevel);
		area.setAddr(addr);
		area.setRemark(remark);
		
		int updates=this.areaService.updateArea(area);				
		logger.info("[{} records was update]", areacode);
	}


}
