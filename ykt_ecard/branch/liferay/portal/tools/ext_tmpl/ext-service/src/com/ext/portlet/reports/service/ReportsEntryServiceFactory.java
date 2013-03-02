package com.ext.portlet.reports.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;


/**
 * <a href="ReportsEntryServiceFactory.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is responsible for the lookup of the implementation for
 * <code>com.ext.portlet.reports.service.ReportsEntryService</code>.
 * Spring manages the lookup and lifecycle of the beans. This means you can
 * modify the Spring configuration files to return a different implementation or
 * to inject additional behavior.
 * </p>
 *
 * <p>
 * See the <code>spring.configs</code> property in portal.properties for
 * additional information on how to customize the Spring XML files.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.ext.portlet.reports.service.ReportsEntryService
 * @see com.ext.portlet.reports.service.ReportsEntryServiceUtil
 *
 */
public class ReportsEntryServiceFactory {
    private static final String _FACTORY = ReportsEntryServiceFactory.class.getName();
    private static final String _IMPL = ReportsEntryService.class.getName() +
        ".impl";
    private static final String _TX_IMPL = ReportsEntryService.class.getName() +
        ".transaction";
    private static ReportsEntryServiceFactory _factory;
    private static ReportsEntryService _impl;
    private static ReportsEntryService _txImpl;
    private ReportsEntryService _service;

    public static ReportsEntryService getService() {
        return _getFactory()._service;
    }

    public static ReportsEntryService getImpl() {
        if (_impl == null) {
            _impl = (ReportsEntryService) BeanLocatorUtil.locate(_IMPL);
        }

        return _impl;
    }

    public static ReportsEntryService getTxImpl() {
        if (_txImpl == null) {
            _txImpl = (ReportsEntryService) BeanLocatorUtil.locate(_TX_IMPL);
        }

        return _txImpl;
    }

    public void setService(ReportsEntryService service) {
        _service = service;
    }

    private static ReportsEntryServiceFactory _getFactory() {
        if (_factory == null) {
            _factory = (ReportsEntryServiceFactory) BeanLocatorUtil.locate(_FACTORY);
        }

        return _factory;
    }
}
