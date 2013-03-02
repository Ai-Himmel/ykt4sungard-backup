package com.kingstar.console.sort;

public interface Compare {
	boolean lessThan(Object lhs, Object rhs);

	//小于等于
	boolean lessThanOrEqual(Object lhs, Object rhs);
}
