package com.sungard.smartcard.modules.system.dao.impl;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.domain.Msglist;
import com.sungard.smartcard.modules.system.dao.MsglistDao;

/**
 * 消息队列管理数据库操作类实现
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-20
 */
@Repository
public class MsglistDaoImpl implements MsglistDao{

	@Autowired
    private JdbcTemplate jdbcTemplate;

	/**
	 * 根据msgid修改保存
	 * */
	@Override
	public int updateMsglist(Msglist msglist) {
		String updatesql="update t_msglist set maxsendcnt=?, status=?,errcode=?,errmsg=? where msgid=?  ";
		return this.jdbcTemplate.update(updatesql, msglist.getMaxsendcnt(),
				msglist.getStatus(),9999,null,msglist.getMsgid());
	}
	
	/**
	 * 根据条件查询
	 * */
	@Override
	public List<Msglist> listMsglist(Msglist msglist) {
		StringBuffer selectsql = new StringBuffer("select * from t_msglist where 1=1 ");
		List<Msglist> listmsglist=null;
		List args = new ArrayList();
		if(msglist!=null){
			if(msglist.getMsgid()!=0){
				selectsql.append(" and msgid=? ");
				args.add(msglist.getMsgid());
			}
			if(msglist.getMsgtype()!=0){
				selectsql.append(" and msgtype=? ");
				args.add(msglist.getMsgtype());
			}
			if(msglist.getMsglevel()!=0){
				selectsql.append(" and msglevel=? ");
				args.add(msglist.getMsglevel());
			}
			if(msglist.getSysid()!=0){
				selectsql.append(" and sysid=? ");
				args.add(msglist.getSysid());
			}
			if(msglist.getDeviceid()!=0){
				selectsql.append(" and deviceid=? ");
				args.add(msglist.getDeviceid());
			}
			if(msglist.getCardno()!=0){
				selectsql.append(" and cardno=? ");
				args.add(msglist.getCardno());
			}
			if(msglist.getTransdate()!=null&&!"".equals(msglist.getTransdate())){
				selectsql.append(" and transdate=? ");
				args.add(msglist.getTransdate().trim());
			}
			if(msglist.getStarttime()!=null&&!"".equals(msglist.getStarttime())){
				selectsql.append(" and starttime=? ");
				args.add(msglist.getStarttime().trim());
			}
			if(msglist.getEndtime()!=null&&!"".equals(msglist.getEndtime())){
				selectsql.append(" and endtime=? ");
				args.add(msglist.getEndtime().trim());
			}
			if(msglist.getFuncno()!=0){
				selectsql.append(" and funcno=? ");
				args.add(msglist.getFuncno());
			}
			if(msglist.getPfuncno()!=0){
				selectsql.append(" and pfuncno=? ");
				args.add(msglist.getPfuncno());
			}
			if(msglist.getStatus()!=0){
				selectsql.append(" and status=? ");
				args.add(msglist.getStatus());
			}
			if(msglist.getOpercode()!=null&&!"".equals(msglist.getOpercode())){
				selectsql.append(" and opercode=? ");
				args.add(msglist.getOpercode().trim());
			}
			if(msglist.getErrcode()!=0){
				selectsql.append(" and errcode=? ");
				args.add(msglist.getErrcode());
			}
			if(msglist.getDelflag()!=null&&!"".equals(msglist.getDelflag())){
				selectsql.append(" and delflag=? ");
				args.add(msglist.getDelflag().trim());
			}
			
		}
		selectsql.append(" order by msgid ");
		listmsglist=jdbcTemplate.query(selectsql.toString(),(args!=null&&args.size()>0)?args.toArray():null,
				new BeanPropertyRowMapper(Msglist.class));
		return listmsglist;
	}
	/**
	 * 根据msgid删除消息队列记录
	 * */
	@Override
	public int deleteMsglist(int msgid) {	
		return this.jdbcTemplate.update("delete from t_msglist where msgid=? ", msgid);
	}
	/**
	 * 根据msgid判断是否存在消息队列记录
	 * */
	@Override
	public boolean isExistMsglist(int msgid) {
		String sql =" select count(*) from t_msglist where msgid=?  ";
		int i=0;
		i=this.jdbcTemplate.queryForInt(sql, msgid);
		if(i>0){
			return true;
		}
		return false;
	}

}
