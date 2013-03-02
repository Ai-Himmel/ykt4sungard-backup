package ${packagePath}.service.persistence;

public class ${entity.name}FinderUtil {

	<#list methods as method>
		<#if !method.isConstructor() && method.isPublic()>
			public static ${method.returns.value}${serviceBuilder.getDimensions(method.returns.dimensions)} ${method.name}(

			<#list method.parameters as parameter>
				${parameter.type.value}${serviceBuilder.getDimensions(parameter.type.dimensions)} ${parameter.name}

				<#if parameter_has_next>
					,
				</#if>
			</#list>

			)

			<#list method.exceptions as exception>
				<#if exception_index == 0>
					throws
				</#if>

				${exception.value}

				<#if exception_has_next>
					,
				</#if>
			</#list>

			{
				<#if method.returns.value != "void">
					return
				</#if>

				getFinder().${method.name}(

				<#list method.parameters as parameter>
					${parameter.name}

					<#if parameter_has_next>
						,
					</#if>
				</#list>

				);
			}
		</#if>
	</#list>

	public static ${entity.name}Finder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(${entity.name}Finder finder) {
		_finder = finder;
	}

	private static ${entity.name}FinderUtil _getUtil() {
		if (_util == null) {
			_util = (${entity.name}FinderUtil)${beanLocatorUtilPackage}.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ${entity.name}FinderUtil.class.getName();

	private static ${entity.name}FinderUtil _util;

	private ${entity.name}Finder _finder;

}