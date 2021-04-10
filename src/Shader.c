#include <gpch.h>
#include <Glfix\Shader.h>

#include <Util\FileHandler.h>
#include <glad\glad.h>

//gets the location of a uniform || make it store it later but for now just get the location
static inline int32_t Glfix_Shader_GetUniformLocation(Glfix_Shader* shader, const char* name)
{
	if (!shader)
	{
		LogData("Glfix Warning: NULL Shader || Shader is NULL can not get uniform location of %s!\n", name);
		return -1;
	}

	int32_t loc = glGetUniformLocation(shader->id, name);
	if (loc == GL_INVALID_OPERATION)
		LogData("Glfix Error: NULL Shader Uniform Location || Shader Uniform: %s could not be found in current bound Shader!\n", name);

	return loc;
}

//compiles a shader
static inline int32_t Glfix_Shader_CompileShader(const char* source, uint32_t type)
{
	if (!source)
	{
		LogError("Shader NULL Source", "Failed to compile Shader source, source was NULL! Check filepath.");
		return -1;
	}

	uint32_t shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	//check if compiled
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		switch (type)
		{

			//Vertex
		case GL_VERTEX_SHADER:
			LogError("Compile Error: Vertex Shader", infoLog);
			glDeleteShader(shader);
			return -1;

			//Fragment
		case GL_FRAGMENT_SHADER:
			LogError("Compile Error: Fragment Shader", infoLog);
			glDeleteShader(shader);
			return -1;

			//Geometry
		case GL_GEOMETRY_SHADER:
			LogError("Compile Error: Geometry Shader", infoLog);
			glDeleteShader(shader);
			return -1;

			//compute

			//invalid
		default:
			LogError("Compile Error: Null Shader", "Invalid Shader of none existent type");
			glDeleteShader(shader);
			return -1;
		}
	}

	return shader;
}

Glfix_Shader* Glfix_Shader_CreateVertex(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	//read vertex and fragment path
	int32_t v = Glfix_Shader_CompileShader(Glfix_FileHandler_ReadFile(vertexPath), GL_VERTEX_SHADER);
	if (v == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Vertex Shader!");
		return NULL;
	}

	int32_t f = Glfix_Shader_CompileShader(Glfix_FileHandler_ReadFile(fragmentPath), GL_FRAGMENT_SHADER);
	if (f == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Fragment Shader!");
		return NULL;
	}

	int32_t g;
	if (geometryPath)
	{
		g = Glfix_Shader_CompileShader(Glfix_FileHandler_ReadFile(geometryPath), GL_GEOMETRY_SHADER);
		if (g == -1)
			return NULL;
	}

	//make shader
	Glfix_Shader* shader = malloc(sizeof(Glfix_Shader));
	shader->id = glCreateProgram();
	glAttachShader(shader->id, v);
	glAttachShader(shader->id, f);
	if (geometryPath)
		glAttachShader(shader->id, g);
	glLinkProgram(shader->id);

	//clean
	glDeleteShader(v);
	glDeleteShader(f);
	if (geometryPath)
		glDeleteShader(g);

	//check if linked correctly
	int  success;
	char infoLog[512];
	glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->id, 512, NULL, infoLog);
		LogError("Link Error: Shader Program", infoLog);
		glDeleteProgram(shader);
		free(shader);
		return NULL;
	}

	shader->type = Glfix_ShaderType_Vertex;
	return shader;
}

Glfix_Shader* Glfix_Shader_CreateVertexSource(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	if (!vertexSource)
	{
		LogError("Vertex Shader Fail", "Vertex source was NULL!");
		return NULL;
	}

	if (!fragmentSource)
	{
		LogError("Vertex Shader Fail", "Fragment source was NULL!");
		return NULL;
	}

	//read vertex and fragment path
	int32_t v = Glfix_Shader_CompileShader(vertexSource, GL_VERTEX_SHADER);
	if (v == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Vertex Shader!");
		return NULL;
	}

	int32_t f = Glfix_Shader_CompileShader(fragmentSource, GL_FRAGMENT_SHADER);
	if (f == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Fragment Shader!");
		return NULL;
	}

	int32_t g;
	if (geometrySource)
	{
		g = Glfix_Shader_CompileShader(geometrySource, GL_GEOMETRY_SHADER);
		if (g == -1)
			return NULL;
	}

	//make shader
	Glfix_Shader* shader = malloc(sizeof(Glfix_Shader));
	shader->id = glCreateProgram();
	glAttachShader(shader->id, v);
	glAttachShader(shader->id, f);
	if (geometrySource)
		glAttachShader(shader->id, g);
	glLinkProgram(shader->id);

	//clean
	glDeleteShader(v);
	glDeleteShader(f);
	if (geometrySource)
		glDeleteShader(g);

	//check if linked correctly
	int  success;
	char infoLog[512];
	glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->id, 512, NULL, infoLog);
		LogError("Link Error: Shader Program", infoLog);
		glDeleteProgram(shader);
		free(shader);
		return NULL;
	}

	shader->type = Glfix_ShaderType_Vertex;
	return shader;
}

void Glfix_Shader_Destroy(Glfix_Shader* shader)
{
	if (!shader)
	{
		LogError("Shader NULL", "Shader is NULL can not destroy!");
		return;
	}

	glDeleteProgram(shader->id);
	//clean seartched unforms
	free(shader);
	shader = NULL;
}

void Glfix_Shader_Bind(Glfix_Shader* shader)
{
	if (!shader)
	{
		LogError("Shader NULL", "Shader is NULL can not bind!");
		return;
	}

	glUseProgram(shader->id);
}

void Glfix_Shader_Unbind()
{
	glUseProgram(0);
}

void Glfix_Shader_SetBool(Glfix_Shader* shader, const char* name, bool value)
{
	glUniform1i(Glfix_Shader_GetUniformLocation(shader, name), value);
}

void Glfix_Shader_SetInt(Glfix_Shader* shader, const char* name, int32_t value)
{
	glUniform1i(Glfix_Shader_GetUniformLocation(shader, name), value);
}

void Glfix_Shader_SetInt2(Glfix_Shader* shader, const char* name, int32_t value1, int32_t value2)
{
	glUniform2i(Glfix_Shader_GetUniformLocation(shader, name), value1, value2);
}

void Glfix_Shader_SetInt3(Glfix_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3)
{
	glUniform3i(Glfix_Shader_GetUniformLocation(shader, name), value1, value2, value3);
}

void Glfix_Shader_SetInt4(Glfix_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3, int32_t value4)
{
	glUniform4i(Glfix_Shader_GetUniformLocation(shader, name), value1, value2, value3, value4);
}

void Glfix_Shader_SetIntArray(Glfix_Shader* shader, const char* name, uint32_t count, int32_t* values)
{
	glUniform1iv(Glfix_Shader_GetUniformLocation(shader, name), count, values);
}

void Glfix_Shader_SetIntVec2(Glfix_Shader* shader, const char* name, int32_t* value)
{
	glUniform2iv(Glfix_Shader_GetUniformLocation(shader, name), 2, value);
}

void Glfix_Shader_SetIntVec3(Glfix_Shader* shader, const char* name, int32_t* value)
{
	glUniform3iv(Glfix_Shader_GetUniformLocation(shader, name), 3, value);
}

void Glfix_Shader_SetIntVec4(Glfix_Shader* shader, const char* name, int32_t* value)
{
	glUniform4iv(Glfix_Shader_GetUniformLocation(shader, name), 4, value);
}

void Glfix_Shader_SetUint(Glfix_Shader* shader, const char* name, uint32_t value)
{
	glUniform1ui(Glfix_Shader_GetUniformLocation(shader, name), value);
}

void Glfix_Shader_SetUint2(Glfix_Shader* shader, const char* name, uint32_t value1, uint32_t value2)
{
	glUniform2ui(Glfix_Shader_GetUniformLocation(shader, name), value1, value2);
}

void Glfix_Shader_SetUint3(Glfix_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3)
{
	glUniform3ui(Glfix_Shader_GetUniformLocation(shader, name), value1, value2, value3);
}

void Glfix_Shader_SetUint4(Glfix_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3, uint32_t value4)
{
	glUniform4ui(Glfix_Shader_GetUniformLocation(shader, name), value1, value2, value3, value4);
}

void Glfix_Shader_SetUintVec2(Glfix_Shader* shader, const char* name, uint32_t* value)
{
	glUniform2uiv(Glfix_Shader_GetUniformLocation(shader, name), 2, value);
}

void Glfix_Shader_SetUintVec3(Glfix_Shader* shader, const char* name, uint32_t* value)
{
	glUniform3uiv(Glfix_Shader_GetUniformLocation(shader, name), 3, value);
}

void Glfix_Shader_SetUintVec4(Glfix_Shader* shader, const char* name, uint32_t* value)
{
	glUniform4uiv(Glfix_Shader_GetUniformLocation(shader, name), 4, value);
}

void Glfix_Shader_SetFloat(Glfix_Shader* shader, const char* name, float value)
{
	glUniform1f(Glfix_Shader_GetUniformLocation(shader, name), value);
}

void Glfix_Shader_SetFloat2(Glfix_Shader* shader, const char* name, float value1, float value2)
{
	glUniform2f(Glfix_Shader_GetUniformLocation(shader, name), value1, value2);
}

void Glfix_Shader_SetFloat3(Glfix_Shader* shader, const char* name, float value1, float value2, float value3)
{
	glUniform3f(Glfix_Shader_GetUniformLocation(shader, name), value1, value2, value3);
}

void Glfix_Shader_SetFloat4(Glfix_Shader* shader, const char* name, float value1, float value2, float value3, float value4)
{
	glUniform4f(Glfix_Shader_GetUniformLocation(shader, name), value1, value2, value3, value4);
}

void Glfix_Shader_SetVec2(Glfix_Shader* shader, const char* name, const float* value)
{
	glUniform2fv(Glfix_Shader_GetUniformLocation(shader, name), 2, value);
}

void Glfix_Shader_SetVec3(Glfix_Shader* shader, const char* name, const float* value)
{
	glUniform3fv(Glfix_Shader_GetUniformLocation(shader, name), 3, value);
}

void Glfix_Shader_SetVec4(Glfix_Shader* shader, const char* name, const float* value)
{
	glUniform4fv(Glfix_Shader_GetUniformLocation(shader, name), 4, value);
}

void Glfix_Shader_SetMat2(Glfix_Shader* shader, const char* name, bool transpose, const float* value)
{
	glUniformMatrix2fv(Glfix_Shader_GetUniformLocation(shader, name), 1, transpose, value);
}

void Glfix_Shader_SetMat3(Glfix_Shader* shader, const char* name, bool transpose, const float* value)
{
	glUniformMatrix3fv(Glfix_Shader_GetUniformLocation(shader, name), 1, transpose, value);
}

void Glfix_Shader_SetMat4(Glfix_Shader* shader, const char* name, bool transpose, const float* value)
{
	glUniformMatrix4fv(Glfix_Shader_GetUniformLocation(shader, name), 1, transpose, value);
}
