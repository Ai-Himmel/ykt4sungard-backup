package org.king.common.displaytag.decorator;

import org.king.utils.Contants;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class DecoratorFactory {
    public static StateDecorator getHostStatusDecorator() {
        return new StateDecorator(Contants.HOST_STATUS);
    }

    public static StateDecorator getServiceStatusDecorator() {
        return new StateDecorator(Contants.SERVICE_STATUS);
    }

    public static StateDecorator getTermdeviceStatusDecorator() {
        return new StateDecorator(Contants.TERMDEVICE_STATUS);
    }

    public static StateDecorator getTermdevserviceStatusDecorator() {
        return new StateDecorator(Contants.TERMDEVSERVICE_STATUS);
    }

    public static StateDecorator getYesNoStatusDecorator() {
        return new StateDecorator(Contants.YES_NO_STATUS);
    }

    public static DateDecorator getDateDecorator() {
        return new DateDecorator(Contants.DATE_FORMAT);
    }

    public static DateIntervalDecorator getDateIntervalDecorator() {
        return new DateIntervalDecorator();
    }

    public static EntityDecorator getEntityDecorator(PropertyCallback propertyCallback) {
        return new EntityDecorator(propertyCallback);
    }

    public static StateDecorator getHostTypeDecorator(){
        return new StateDecorator(Contants.HOST_TYPE);
    }
}
