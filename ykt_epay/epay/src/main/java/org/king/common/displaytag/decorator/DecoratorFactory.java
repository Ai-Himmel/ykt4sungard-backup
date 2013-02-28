package org.king.common.displaytag.decorator;

import org.king.utils.Contants;


/**
 * .
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class DecoratorFactory {

	public static StateDecorator getAccStatusDecorator() {
		 return new StateDecorator(Contants.NETACC_STATUS);
	}
	
	public static StateDecorator getStopPayFlagDecorator() {
		 return new StateDecorator(Contants.STOPPAY_FLAG);
	}

	public static StateDecorator getStatusDecorator() {
		return new StateDecorator(Contants.TRANSDTL_STATUS);
	}

	public static StateDecorator getRevflagDecorator() {
		return new StateDecorator(Contants.REV_TRANSDTL_FLAG);
	}

}
