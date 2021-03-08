//defines Shaders

#ifndef Shader_h
#define Shader_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

	//defines the shader types
	typedef enum
	{
		Glfix_ShaderType_Vertex = 0x01,
		Glfix_ShaderType_Compute = 0x02
		//Glfix_ShaderType_Geometry = 0x02,
		//Glfix_ShaderType_Compute = 0x04

	} Glfix_Shader_ShaderType;

	//defines a shader
	typedef struct
	{
		uint32_t id;
		uint8_t type : 2; //0b00000000

		//seartched uniforms

	} Glfix_Shader_Shader;

	//creates a vertex Shader
	Glfix_Shader_Shader* Glfix_Shader_CreateVertex(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	//creates a vertex Shader from source
	Glfix_Shader_Shader* Glfix_Shader_CreateVertexSource(const char* vertexSource, const char* fragmentSource, const char* geometrySource);
	//creates a compute Shader
	//Glfix_Shader_Shader* Glfix_Shader_CreateCompute(const char* computePath);
	//destroys a Shader
	void Glfix_Shader_Destroy(Glfix_Shader_Shader* shader);

	//binds a Shader
	void Glfix_Shader_Bind(Glfix_Shader_Shader* shader);
	//unbinds a Shader
	void Glfix_Shader_Unbind();

	//pass a bool unform
	void Glfix_Shader_SetBool(Glfix_Shader_Shader* shader, const char* name, bool value);

	//pass a int1 uniform
	void Glfix_Shader_SetInt(Glfix_Shader_Shader* shader, const char* name, int32_t value);
	//pass a int2 uniform || expects a 2 element array
	void Glfix_Shader_SetInt2(Glfix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2);
	//pass a int3 uniform || expects a 3 element array
	void Glfix_Shader_SetInt3(Glfix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3);
	//pass a int4 uniform || expects a 4 element array
	void Glfix_Shader_SetInt4(Glfix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3, int32_t value4);

	//pass a int vec2 uniform || expects a 2 element array
	void Glfix_Shader_SetIntVec2(Glfix_Shader_Shader* shader, const char* name, int32_t* value);
	//pass a int vec3 uniform || expects a 3 element array
	void Glfix_Shader_SetIntVec3(Glfix_Shader_Shader* shader, const char* name, int32_t* value);
	//pass a int vec4 uniform || expects a 4 element array
	void Glfix_Shader_SetIntVec4(Glfix_Shader_Shader* shader, const char* name, int32_t* value);

	//pass a uint1 uniform
	void Glfix_Shader_SetUint(Glfix_Shader_Shader* shader, const char* name, uint32_t value);
	//pass a uint2 uniform 
	void Glfix_Shader_SetUint2(Glfix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2);
	//pass a uint3 uniform 
	void Glfix_Shader_SetUint3(Glfix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3);
	//pass a uint4 uniform 
	void Glfix_Shader_SetUint4(Glfix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3, uint32_t value4);

	//pass a uint vec2 uniform || expects a 2 element array
	void Glfix_Shader_SetUintVec2(Glfix_Shader_Shader* shader, const char* name, uint32_t* value);
	//pass a uint vec3 uniform || expects a 3 element array
	void Glfix_Shader_SetUintVec3(Glfix_Shader_Shader* shader, const char* name, uint32_t* value);
	//pass a uint vec4 uniform || expects a 4 element array
	void Glfix_Shader_SetUintVec4(Glfix_Shader_Shader* shader, const char* name, uint32_t* value);

	//pass a float1 uniform
	void Glfix_Shader_SetFloat(Glfix_Shader_Shader* shader, const char* name, float value);
	//pass a float2 uniform
	void Glfix_Shader_SetFloat2(Glfix_Shader_Shader* shader, const char* name, float value1, float value2);
	//pass a float3 uniform 
	void Glfix_Shader_SetFloat3(Glfix_Shader_Shader* shader, const char* name, float value1, float value2, float value3);
	//pass a float4 uniform 
	void Glfix_Shader_SetFloat4(Glfix_Shader_Shader* shader, const char* name, float value1, float value2, float value3, float value4);

	//pass a float vec2 uniform || expects a 2 element array
	void Glfix_Shader_SetVec2(Glfix_Shader_Shader* shader, const char* name, const float* value);
	//pass a float vec3 uniform || expects a 3 element array				 
	void Glfix_Shader_SetVec3(Glfix_Shader_Shader* shader, const char* name, const float* value);
	//pass a float vec4 uniform || expects a 4 element array				 
	void Glfix_Shader_SetVec4(Glfix_Shader_Shader* shader, const char* name, const float* value);

	//pass a mat2 uniform || expects a 2 element array
	void Glfix_Shader_SetMat2(Glfix_Shader_Shader* shader, const char* name, bool transpose, const float* value);
	//pass a mat3 uniform || expects a 3 element array										 
	void Glfix_Shader_SetMat3(Glfix_Shader_Shader* shader, const char* name, bool transpose, const float* value);
	//pass a mat4 uniform || expects a 4 element array										
	void Glfix_Shader_SetMat4(Glfix_Shader_Shader* shader, const char* name, bool transpose, const float* value);

#ifdef __cplusplus
}
#endif

#endif