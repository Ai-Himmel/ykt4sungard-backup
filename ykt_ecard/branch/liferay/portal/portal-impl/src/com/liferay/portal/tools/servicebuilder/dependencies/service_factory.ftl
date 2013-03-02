package ${packagePath}.service;

import ${beanLocatorUtilPackage}.BeanLocatorUtil;

/**
 * <a href="${entity.name}${sessionTypeName}ServiceFactory.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is responsible for the lookup of the implementation for
 * <code>${packagePath}.service.${entity.name}${sessionTypeName}Service</code>.
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
 * @see ${packagePath}.service.${entity.name}${sessionTypeName}Service
 * @see ${packagePath}.service.${entity.name}${sessionTypeName}ServiceUtil
 *
 */
public class ${entity.name}${sessionTypeName}ServiceFactory {

	public static ${entity.name}${sessionTypeName}Service getService() {
		return _getFactory()._service;
	}

	public static ${entity.name}${sessionTypeName}Service getImpl() {
		if (_impl == null) {
			_impl = (${entity.name}${sessionTypeName}Service) BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static ${entity.name}${sessionTypeName}Service getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (${entity.name}${sessionTypeName}Service)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(${entity.name}${sessionTypeName}Service service) {
		_service = service;
	}

	private static ${entity.name}${sessionTypeName}ServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (${entity.name}${sessionTypeName}ServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = ${entity.name}${sessionTypeName}ServiceFactory.class.getName();

	private static final String _IMPL = ${entity.name}${sessionTypeName}Service.class.getName() + ".impl";

	private static final String _TX_IMPL = ${entity.name}${sessionTypeName}Service.class.getName() + ".transaction";

	private static ${entity.name}${sessionTypeName}ServiceFactory _factory;

	private static ${entity.name}${sessionTypeName}Service _impl;

	private static ${entity.name}${sessionTypeName}Service _txImpl;

	private ${entity.name}${sessionTypeName}Service _service;

}