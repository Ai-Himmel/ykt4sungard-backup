<#list entities as entity>
	<#assign modelName = packagePath + ".model." + entity.name>

	<#if entity.hasColumns()>
		<model name="${modelName}">
			<#if modelHintsUtil.getDefaultHints(modelName)??>
				<#assign defaultHints = modelHintsUtil.getDefaultHints(modelName).entrySet()>

				<#if defaultHints?size gt 0>
					<default-hints>
						<#list defaultHints as defaultHint>
							<hint name="${defaultHint.key}">${defaultHint.value}</hint>
						</#list>
					</default-hints>
				</#if>
			</#if>

			<#list entity.columnList as column>
				<#if !column.isCollection()>
					<field name="${column.name}" type="${column.type}"

					<#if modelHintsUtil.getFieldsEl(modelName, column.name)??>
						<#assign field = modelHintsUtil.getFieldsEl(modelName, column.name)>
						<#assign hints = field.elements()>

						<#if hints?size gt 0>
							>

							<#list hints as hint>
								<#if hint.name == "hint">
									<hint name="${hint.attributeValue("name")}">${hint.text}</hint>
								<#else>
									<hint-collection name="${hint.attributeValue("name")}" />
								</#if>
							</#list>

							</field>
						<#else>
							/>
						</#if>
					<#else>
						/>
					</#if>
				</#if>
			</#list>
		</model>
	</#if>
</#list>