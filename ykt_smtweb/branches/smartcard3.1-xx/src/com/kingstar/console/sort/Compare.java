package com.kingstar.console.sort;

public interface Compare {
	boolean lessThan(Object lhs, Object rhs);

	//С�ڵ���
	boolean lessThanOrEqual(Object lhs, Object rhs);
}
