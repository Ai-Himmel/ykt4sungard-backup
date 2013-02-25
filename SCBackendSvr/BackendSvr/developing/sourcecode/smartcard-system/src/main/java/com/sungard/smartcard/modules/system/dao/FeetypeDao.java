package com.sungard.smartcard.modules.system.dao;

import java.util.List;
import com.sungard.smartcard.domain.Feetype;
/**
 * [TODO 收费类型基本的数据库实现.]
 * 
 * @author <a href="mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-20
 * 
 */
public interface FeetypeDao {
	public List<Feetype> findFeetype();
	public List<Feetype> findFeetype(String sql,Object[] args);
	public List<Feetype> findFeetype(Feetype feetype);
	public Feetype getFeetype(String feetype);
	public int updateFeetype(Feetype feetype);
	public int removeFeetype(String feetype);
	public int addFeetype(Feetype feetype);
}
