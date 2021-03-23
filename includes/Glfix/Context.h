//defines the Context for the C API

#ifndef Context_h
#define Context_h

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

	//the create info
	typedef struct
	{
		//the settings
		bool enableBlending, enableFaceCulling, enableDepthBuffer;

		//the viewport size
		uint32_t viewPortWidth, viewPortHeight;

		//if GLFW needs to be inited by the Context
		bool GLFWIsInit;
		uint32_t openglMinorVer, openglMajorVer;

	} Glfix_Context_CreateInfo;

	//the Context
	typedef struct
	{
		bool depthBufferIsEnabled; //is needed when clearing the screen
		void* window; //stored only if it has to init GLFW

	} Glfix_Context;

	//inits the create info to default values
	void Glfix_Context_InitCreateInfo(Glfix_Context_CreateInfo* info);

	//creates a Context
	Glfix_Context* Glfix_Context_Create(Glfix_Context_CreateInfo* info);
	//destroys a Context
	void Glfix_Context_Destroy(Glfix_Context* context);

	//sets the clear color
	void Glfix_Context_SetClearColor(float r, float g, float b, float a);
	//sets the clear color || expects a 4 element array
	void Glfix_Context_SetClearColorVec4(float* color);

	//clears the screen
	void Glfix_Context_Clear(Glfix_Context* context);

	//sets if face culling should be used
	void Glfix_Context_EnableFaceCulling(bool state);
	//sets if blending should be used
	void Glfix_Context_EnableBlending(bool state);
	//sets if the depth buffer should be used
	void Glfix_Context_EnableDepthBuffer(Glfix_Context* context, bool state);
	//sets the view port
	void Glfix_Context_SetViewPort(int32_t xPos, int32_t yPos, int32_t width, int32_t height);

#ifdef __cplusplus
}
#endif

#endif