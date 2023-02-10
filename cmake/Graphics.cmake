
function(add_shader TARGET SHADER)
	# Find glslc shader compiler.
	find_program(GLSLC glslc)

	# All shaders for a sample are found here.

	set(current-shader-path ${CMAKE_SOURCE_DIR}/sources/shaders/${SHADER})

	# For Android, write SPIR-V files to app/assets which is then packaged into the APK.
	# Otherwise, output in the binary directory.
	set(current-output-path ${CMAKE_BINARY_DIR}/shaders/${SHADER}.spv)

	# Add a custom command to compile GLSL to SPIR-V.
	get_filename_component(current-output-dir ${current-output-path} DIRECTORY)
	file(MAKE_DIRECTORY ${current-output-dir})
	add_custom_command(
		OUTPUT ${current-output-path}
		COMMAND ${GLSLC} ${current-shader-path} -o  ${current-output-path}
		DEPENDS ${current-shader-path}
		IMPLICIT_DEPENDS CXX ${current-shader-path}
		VERBATIM)

	# Make sure our native build depends on this output.
	set_source_files_properties(${current-output-path} PROPERTIES GENERATED TRUE)
	target_sources(${TARGET} PRIVATE ${current-output-path})
endfunction(add_shader)