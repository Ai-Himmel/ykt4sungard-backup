package org.king.dictionary;

import java.util.Map;

/**
 * 系统字典
 * @author cash
 *
 */
public interface YKTDictionEntry  {
	
	/**
	 * @return 返回唯一字典标识
	 */
	abstract public String getKey();

	/**
	 * 加载字典数据
	 * @return 加载成功返回 true , 失败返回 false
	 */
	abstract public boolean loadDiction(Map dict);

	/**
	 * 释放字典缓存中的数据
	 * @return 成功返回 true , 失败返回 false
	 */
	abstract public boolean releaseDiction();

	/**
	 * 读取字典中的值
	 * @param key 字典的 key
	 * @return 返回字典的数据, 没有找到返回 null
	 */
	abstract public Object getValue(Object key);

}