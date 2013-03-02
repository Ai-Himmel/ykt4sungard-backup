package ${packagePath}.service.persistence;

public interface ${entity.name}Finder {

	<#list methods as method>
		<#if !method.isConstructor() && method.isPublic()>
			public ${method.returns.value}${serviceBuilder.getDimensions(method.returns.dimensions)} ${method.name}(

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
			</#list>;
		</#if>
	</#list>

}