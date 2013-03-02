package ${packagePath}.service.persistence;

import java.util.Date;

public interface ${entity.name}Persistence {

	<#list methods as method>
		<#if !method.isConstructor() && method.isPublic()>
			public ${method.returns.value}${serviceBuilder.getDimensions("${method.returns.dimensions}")} ${method.name} (

			<#assign parameters = method.parameters>

			<#list parameters as parameter>
				${parameter.type.value}${serviceBuilder.getDimensions("${parameter.type.dimensions}")} ${parameter.name}

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

			;
		</#if>
	</#list>

}