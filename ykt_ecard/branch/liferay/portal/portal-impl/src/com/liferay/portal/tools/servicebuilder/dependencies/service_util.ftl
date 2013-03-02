package ${packagePath}.service;

/**
 * <a href="${entity.name}${sessionTypeName}ServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>${packagePath}.service.${entity.name}${sessionTypeName}Service</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>${packagePath}.service.${entity.name}${sessionTypeName}ServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see ${packagePath}.service.${entity.name}${sessionTypeName}Service
 * @see ${packagePath}.service.${entity.name}${sessionTypeName}ServiceFactory
 *
 */
public class ${entity.name}${sessionTypeName}ServiceUtil {

	<#list methods as method>
		<#if !method.isConstructor() && method.isPublic() && serviceBuilder.isCustomMethod(method)>
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
				${entity.name}${sessionTypeName}Service ${entity.varName}${sessionTypeName}Service = ${entity.name}${sessionTypeName}ServiceFactory.getService();

				<#if method.returns.value != "void">
					return
				</#if>

				${entity.varName}${sessionTypeName}Service.${method.name}(

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

}